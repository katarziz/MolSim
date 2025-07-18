//
// Created by cpsch on 02.06.2025.
//

#ifndef XMLREADER_H
#define XMLREADER_H
#include "objects/ParticleContainer.h"
#include "input.h"

class XMLReader {
public:
    XMLReader();

    virtual ~XMLReader();

    static void readFile(ParticleContainer *particles, const char *filename);

private:
    static bool check_bounds(const std::array<int, 6> &bounds);

    static void readoutParams(Parameters &param);

    static void readInCubes(Particles &particle_in, ParticleContainer &particles, int dim, double T_init);

    static void readInDiscs(Particles &particle_in, ParticleContainer &particles, int dim, double T_init);

    static void readInParticles(Particles &particle_in, ParticleContainer &particles, int dim, double T_init);

    static void readInMembranes(const Particles &particle_in, ParticleContainer &particles, int dim, double T_init);

    static int parse_bound(const std::string &bound);
};
#endif //XMLREADER_H
