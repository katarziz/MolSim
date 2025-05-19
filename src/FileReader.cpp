/*
 * FileReader.cpp
 *
 *  Created on: 23.02.2010
 *      Author: eckhardw
 */

#include "FileReader.h"

#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>

#include "ParticleGenerator.h"

FileReader::FileReader() = default;

FileReader::~FileReader() = default;

void FileReader::readFile(ParticleContainer &particles, char *filename) {
  std::array<double, 3> x;
  std::array<double, 3> v;
  double m;
  std::array<int64_t, 3> n;
  double h;
  int num_particles = 0;

  std::ifstream input_file(filename);
  std::string tmp_string;

  if (input_file.is_open()) {

    getline(input_file, tmp_string);
    std::cout << "Read line: " << tmp_string << std::endl;

    while (tmp_string.empty() or tmp_string[0] == '#') {
      getline(input_file, tmp_string);
      std::cout << "Read line: " << tmp_string << std::endl;
    }

    // TODO Multiple inputs
    // CUBOID could already do multiple inputs using a similar method to particles,
    // but for now, I want each "set" of particles separate

    if (tmp_string == "PARTICLES") {
      getline(input_file, tmp_string);
      std::cout << "Read line: " << tmp_string << std::endl;
      std::istringstream numstream(tmp_string);
      numstream >> num_particles;
      std::cout << "Reading " << num_particles << "." << std::endl;
      getline(input_file, tmp_string);
      std::cout << "Read line: " << tmp_string << std::endl;

      for (int i = 0; i < num_particles; i++) {
        std::istringstream datastream(tmp_string);

        for (auto &xj : x) {
          datastream >> xj;
        }
        for (auto &vj : v) {
          datastream >> vj;
        }
        if (datastream.eof()) {
          std::cout
              << "Error reading file: eof reached unexpectedly reading from line "
              << i << std::endl;
          exit(-1);
        }
        datastream >> m;

        particles.addParticle(Particle(x, v, m));

        getline(input_file, tmp_string);
        std::cout << "Read line: " << tmp_string << std::endl;
      }
    } else if (tmp_string == "CUBOID") {
      getline(input_file, tmp_string);
      std::cout << "Read line: " << tmp_string << std::endl;

      std::istringstream datastream(tmp_string);

      for (auto &xj : x) {
        datastream >> xj;
      }
      for (auto &vj : v) {
        datastream >> vj;
      }
      datastream >> m;
      for (auto &nj : n) {
        datastream >> nj;
      }
      datastream >> h;

      // TODO MAGIC NUMBER 0.1 is hard coded Brownian Motion
      auto cuboid = ParticleGenerator::generateParticleContainer(x, n, h, m, v, 0.1);

      particles.addParticles(cuboid.getParticles());
    }
  } else {
    std::cout << "Error: could not open file " << filename << std::endl;
    exit(-1);
  }
}
