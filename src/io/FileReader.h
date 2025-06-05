/*
 * FileReader.h
 *
 *  Created on: 23.02.2010
 *      Author: eckhardw
 */

#pragma once
<<<<<<<< HEAD:src/io/FileReader.h

#include "../objects/ParticleContainer.h"
========
#include "../particles/ParticleGenerator.h"
>>>>>>>> origin/Assignment3-devel:src/inputReader/FileReader.h

class FileReader {

public:
  FileReader();
  virtual ~FileReader();

  void readFile(ParticleContainer &particles, char *filename);
};
