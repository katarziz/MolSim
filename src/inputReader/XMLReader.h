//
// Created by cpsch on 02.06.2025.
//

#ifndef XMLREADER_H
#define XMLREADER_H
#include "../particles/ParticleContainer.h"

class XMLReader {

public:
    XMLReader();
    virtual ~XMLReader();

    static void readFile(ParticleContainer &particles, const char *filename);
};
#endif //XMLREADER_H
