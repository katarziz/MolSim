
#include "MolSim.h"
#include "io/FileReader.h"
#include "io/XYZWriter.h"
#include "io/VTKWriter.h"
#include "utils/ArrayUtils.h"

#include <iostream>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>

#include  <getopt.h>
#include "simulation/LennardJones.h"
#include "simulation/Grav.h"
#include "io/XMLReader.h"
#include "io/input.h"
#include "spdlog/sinks/stdout_sinks.h"

int main(int argc, char *argsv[]) {
  std::shared_ptr<spdlog::logger> logger = nullptr;
  std::shared_ptr<spdlog::logger> stdout_logger = spdlog::stdout_logger_mt("stdout");
  try {
    logger = spdlog::basic_logger_mt("default", "logs/log.txt", true);
#if SPDLOG_ACTIVE_LEVEL == SPDLOG_LEVEL_TRACE
    logger->set_level(spdlog::level::trace);
#elif SPDLOG_ACTIVE_LEVEL == SPDLOG_LEVEL_DEBUG
    logger->set_level(spdlog::level::debug);
#elif SPDLOG_ACTIVE_LEVEL == SPDLOG_LEVEL_INFO
    logger->set_level(spdlog::level::info);
#elif SPDLOG_ACTIVE_LEVEL == SPDLOG_LEVEL_WARN
    logger->set_level(spdlog::level::warn);
#elif SPDLOG_ACTIVE_LEVEL == SPDLOG_LEVEL_ERROR
    logger->set_level(spdlog::level::err);
#elif SPDLOG_ACTIVE_LEVEL == SPDLOG_LEVEL_CRITICAL
    logger->set_level(spdlog::level::critical);
#elif SPDLOG_ACTIVE_LEVEL == SPDLOG_LEVEL_OFF
    logger->set_level(spdlog::level::off);
#else
    // Default to info if no match
    logger->set_level(spdlog::level::info);
#endif

  } catch (const spdlog::spdlog_ex &ex) {
    spdlog::error("Could not create log file: {}", ex.what());
    exit(-1);
  }

  // handle options and arguments passed to the executable using getopt
  int help_flag = 0;
  char *input_file = nullptr;

  option long_options[] = {
    {"help", no_argument, &help_flag, 1},
    {"input_file", required_argument, nullptr, 'i'},
    {"delta_t", optional_argument, nullptr, 'd'},
    {"t_end",optional_argument, nullptr, 't'},
    {"writer",optional_argument,nullptr,'w'},
    {"force",optional_argument,nullptr,'f'},
    {nullptr}
  };

  while (true) {
    int options = getopt_long(argc, argsv, "hi:d:t:w:f:", long_options, nullptr);

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
          SPDLOG_LOGGER_CRITICAL(spdlog::get("default"),"failed to parse delta_t into a valid double");
          exit(-1);
        }
        break;
      }
      case 't': {
        char *endptr;
        errno = 0;
        end_time = strtod(optarg, &endptr);
        if (endptr == optarg || *endptr != '\0' || errno != 0) {
          SPDLOG_LOGGER_CRITICAL(spdlog::get("default"),"failed to parse t_end into a valid double");
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
            SPDLOG_LOGGER_CRITICAL(spdlog::get("default"),"passed string is not a valid writer.");
            exit(-1);
          }
          break;
        }
    case 'f':   {
          if (strcmp(optarg, "lennard-jones")==0)
          { force_flag=0;
          }else if (strcmp(optarg, "newton")==0){
            force_flag=1;
          }else {
            SPDLOG_LOGGER_CRITICAL(spdlog::get("default"),"passed string is not a valid force calculation.");
            exit(-1);
          }
          break;
        }
      case '?': {
        SPDLOG_LOGGER_CRITICAL(spdlog::get("default"),"unknown option.");
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
    std::cout << "-f or --force FORCE : pass a string representation of the desired force calculation. Currently 'newton' and 'lennard-jones' are supported." << std::endl;
    exit(0);
  }

  //FileReader fileReader;
  XMLReader fileReader;
  fileReader.readFile(particles, input_file);

  SPDLOG_LOGGER_INFO(spdlog::get("default"), "Particles generated:");
#if SPDLOG_ACTIVE_LEVEL <= SPDLOG_LEVEL_DEBUG
  for (auto &p : particles) {
    SPDLOG_LOGGER_DEBUG(spdlog::get("default"), p.toString());
  }
#endif

  double current_time = start_time;

  int iteration = 0;

  SPDLOG_LOGGER_INFO(spdlog::get("default"), "Simulation started");
  SPDLOG_LOGGER_INFO(spdlog::get("stdout"), "Simulation started");


  // for this loop, we assume: current x, current f and current v are known
  while (current_time < end_time) {
    // calculate new x
    calculateX();
    // calculate new f
    calculateF();
    // calculate new v
    calculateV();

    iteration++;
    if (iteration % out_freq == 0) {
      plotParticles(iteration);
      SPDLOG_LOGGER_DEBUG(spdlog::get("default"), "Iteration {} finished.", iteration);
      std::cout << "\rProgress: " << std::ceil(100*current_time/end_time) << "%" << std::flush;
    }

    current_time += delta_t;
  }
  std::cout << std::endl;

  SPDLOG_LOGGER_INFO(spdlog::get("default"), "Simulation finished. Terminating...");
  SPDLOG_LOGGER_INFO(spdlog::get("stdout"), "Simulation finished. Terminating...");
  return 0;
}

void calculateF() {
  particles.applyUnary(
    [](Particle &p) {
      p.setOldF(p.getF());
      p.setF({0,0,0});
    });
  if (force_flag==1)
  {
    particles.applyBinary(calculateF_G);
  }else
  {
    particles.applyBinary(calculateF_LJ);
  }
}

void calculateX() {
  particles.applyUnary(
    [](Particle &p) {
      p.setX(p.getX() + delta_t*p.getV() + delta_t*delta_t/(2*p.getM())*p.getF());
    });
  if constexpr (std::is_same_v<decltype(particles), LinkedCellParticleContainer>) {
    static_cast<LinkedCellParticleContainer&>(static_cast<ParticleContainer&>(particles)).updateCells();
  }
}

void calculateV() {
  particles.applyUnary(
    [](Particle &p) {
      p.setV(p.getV() + delta_t/(2*p.getM())*(p.getOldF() + p.getF()));
    });
}

void plotParticles(int iteration) {

  if (writer_flag==1)  {
    outputWriter::XYZWriter writer;
    writer.plotParticles(particles, out_name, iteration);
  } else {
    outputWriter::VTKWriter writer;
    writer.initializeOutput(particles.size());
    for (auto &p : particles) {
      writer.plotParticle(p);
    }
    writer.writeFile(out_name, iteration);
  }
}
