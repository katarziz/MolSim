
#include "FileReader.h"
#include "outputWriter/XYZWriter.h"
#include "outputWriter/VTKWriter.h"
#include "utils/ArrayUtils.h"

#include <iostream>
#include <list>

#include  <getopt.h>

/**** forward declaration of the calculation functions ****/

//! function to calculate and update the velocity of the particles
void calculateF();

//! function to calculate and update the position of the particles
void calculateX();

//! function to calculate and update the velocity of the particles
void calculateV();


//! function to plot the particles using the output writer
/*!
\param iteration int representing the number of the current iteration
*/
void plotParticles(int iteration);
//! constant double representing the start time of the simulation.
constexpr double start_time = 0;
//! double representing the end time of the simulation. Default:1000
double end_time = 1000;
//! double representing the timestep of the simulation. Default:0.014
double delta_t = 0.014;
//! ParticleContainer containing all particles in the simulation
ParticleContainer particles;

//! int representation of the output writer being used
/*!
*writer_flag=0 -> vtk writer
*writer_flag=1 -> xyz  writer
*/
int writer_flag=0;
//! main function of the Molecular Simulation
int main(int argc, char *argsv[]) {

  // handle options and arguments passed to the executable using getopt
  int help_flag = 0;
  char *input_file = nullptr;

  option long_options[] = {
    {"help", no_argument, &help_flag, 1},
    {"input_file", required_argument, nullptr, 'i'},
    {"delta_t", optional_argument, nullptr, 'd'},
    {"t_end",optional_argument, nullptr, 't'},
    {"writer",optional_argument,nullptr,'w'},
    {nullptr}
  };

  while (true) {
    int options = getopt_long(argc, argsv, "hi:d:t:w:", long_options, nullptr);

    if (options == -1) {
      break;
    }

    switch (options) {
      case 'h': {
        help_flag = 1;
        break;
      }
      case 'i': {
        input_file = optarg;
        break;
      }
      case 'd': {
        char *endptr;
        errno = 0;
        delta_t = strtod(optarg, &endptr);
        if (endptr == optarg || *endptr != '\0' || errno != 0) {
          std::cout << "failed to parse delta_t into a valid double" << std::endl;
          exit(-1);
        }
        break;
      }
      case 't': {
        char *endptr;
        errno = 0;
        end_time = strtod(optarg, &endptr);
        if (endptr == optarg || *endptr != '\0' || errno != 0) {
          std::cout << "failed to parse t_end into a valid double" << std::endl;
          exit(-1);
        }
        break;
      }
    case 'w': {
          if (strcmp(optarg, "xyz")==0)
          { writer_flag=1;
          }else if (strcmp(optarg, "vtk")==0){
            writer_flag=0;
          }else {
            std::cout << "passed string is not a valid writer." << std::endl;
            exit(-1);
          }
          break;
        }
      case '?': {
        std::cout << "unknown option" << std::endl;
        exit(-1);
      }
      default: {
        break;
      }
    }
  }

  // prints available options and arguments in case the user invoked --help
  if (help_flag) {
    std::cout << "options:" << std::endl;
    std::cout << "-h or --help : print this usage explanation" << std::endl;
    std::cout << "required arguments:" << std::endl;
    std::cout << "-i or --input_file INPUT_FILE : pass the set of molecules for the simulation" << std::endl;
    std::cout << "optional arguments:" << std::endl;
    std::cout << "-d or --delta_t DELTA_T : pass the time step of the simulation" << std::endl;
    std::cout << "-t or --t_end T_END : pass the last time to be simulated" << std::endl;
    std::cout << "-w or --writer WRITER : pass a string representation of the desired output writer. Currently 'xyz' and 'vtk' are supported." << std::endl;
    exit(0);
  }

  std::cout << "Hello from MolSim for PSE!" << std::endl;

  FileReader fileReader;
  fileReader.readFile(particles, input_file);

  double current_time = start_time;

  int iteration = 0;

  // for this loop, we assume: current x, current f and current v are known
  while (current_time < end_time) {
    // calculate new x
    calculateX();
    // calculate new f
    calculateF();
    // calculate new v
    calculateV();

    iteration++;
    if (iteration % 10 == 0) {
      plotParticles(iteration);
    }
    std::cout << "Iteration " << iteration << " finished." << std::endl;

    current_time += delta_t;
  }

  std::cout << "output written. Terminating..." << std::endl;
  return 0;
}

void calculateF() {
  for (auto &p1 : particles) {
    std::array<double, 3> force = {0,0,0};
    for (auto &p2 : particles) {
      if (p1 == p2) {
        continue;
      }

      // F_{ij} = m_i m_j (||x_i - x_j||_2)^{-3} (x_j - x_i)
      // only (x_j - x_i) changes for each vector entry
      // factor calculates m_i m_j (||x_i - x_j||_2)^{-3}
      double factor = 0.0;
      for (int i = 0; i < 3; ++i) {
        const double diff = (p1.getX()[i] - p2.getX()[i]);
        factor += diff * diff;
      }
      // faster version of factor = p1.getM() * p2.getM() * std::pow(factor,-1.5)
      factor = std::sqrt(factor);
      factor = factor * factor * factor;
      factor = p1.getM() * p2.getM() / (factor);

      for (int i = 0; i < 3; ++i) {
        force[i] += factor * (p2.getX()[i] - p1.getX()[i]);
      }
    }
    p1.setOldF(p1.getF());
    p1.setF(force);
  }
}

void calculateX() {
  for (auto &p : particles) {
    std::array<double, 3> x = p.getX();
    //calculations according to Stoermer-Verlet
    for (int i = 0; i < 3; ++i) {
      x[i] += delta_t * p.getV()[i] + delta_t * delta_t * p.getF()[i] / (2 * p.getM());
    }
    p.setX(x);
  }
}

void calculateV() {
  for (auto &p : particles) {
    std::array<double, 3> v = p.getV();
    // calculations according to Stoermer-Verlet
    for (int i = 0; i < 3; ++i) {
      v[i] += delta_t * (p.getOldF()[i] + p.getF()[i]) / (2 * p.getM());
    }
    p.setV(v);
  }
}

void plotParticles(int iteration) {
  std::string out_name("MD_vtk");

  if (writer_flag==1)  {
    outputWriter::XYZWriter writer;
    writer.plotParticles(particles, out_name, iteration);
  } else {
    outputWriter::VTKWriter writer;
    writer.initializeOutput(static_cast<int>(particles.size()));
    for (auto &p : particles) {
      writer.plotParticle(p);
    }
    writer.writeFile(out_name, iteration);
  }
}
