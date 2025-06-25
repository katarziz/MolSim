/*
 * FileReader.h
 *
 *  Created on: 23.02.2010
 *      Author: eckhardw
 */

#pragma once

#include "../objects/ParticleContainer.h"

class FileReader {

public:
  FileReader();
  virtual ~FileReader();

  static void readFile(ParticleContainer &particles, char *filename);

  static void readCheckpoint(double &time, ParticleContainer &particles, char *filename);

  static void writeCheckpoint(double &time, ParticleContainer &particles, char *filename);
};
