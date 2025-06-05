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
#include <spdlog/spdlog.h>


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
    SPDLOG_LOGGER_INFO(spdlog::get("default"),"Read line: {}", tmp_string);

    while (tmp_string.empty() or tmp_string[0] == '#') {
      getline(input_file, tmp_string);
      SPDLOG_LOGGER_INFO(spdlog::get("default"),"Read line: {}", tmp_string);
    }

    while (!input_file.eof()) {
      if (tmp_string == "PARTICLES") {
        getline(input_file, tmp_string);
        SPDLOG_LOGGER_INFO(spdlog::get("default"),"Read line: {}", tmp_string);
        std::istringstream numstream(tmp_string);
        numstream >> num_particles;
        SPDLOG_LOGGER_INFO(spdlog::get("default"),"Read line: {}", tmp_string);
        getline(input_file, tmp_string);
        SPDLOG_LOGGER_INFO(spdlog::get("default"),"Read line: {}", tmp_string);

        for (int i = 0; i < num_particles; i++) {
          std::istringstream datastream(tmp_string);

          for (auto &xj : x) {
            datastream >> xj;
          }
          for (auto &vj : v) {
            datastream >> vj;
          }
          if (datastream.eof()) {
            SPDLOG_LOGGER_ERROR(spdlog::get("eof reached unexpectedly reading from line {}"),"Read line: {}", i);
            exit(-1);
          }
          datastream >> m;

          particles.addParticle(Particle(x, v, m));

          getline(input_file, tmp_string);
          SPDLOG_LOGGER_INFO(spdlog::get("default"),"Read line: {}", tmp_string);
        }
      } else if (tmp_string == "CUBOID") {
        getline(input_file, tmp_string);
        SPDLOG_LOGGER_INFO(spdlog::get("default"),"Read line: {}", tmp_string);

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
        auto cuboid = ParticleGenerator::generateCube(x, n, h, m, v, 0.1);

        particles.addParticles(cuboid.getParticles());
      }
      getline(input_file, tmp_string);
    }
  } else {
    SPDLOG_LOGGER_ERROR(spdlog::get("default"),"could not open file {}.", filename);
    exit(-1);
  }
}
