//
// Created by cpsch on 19.05.2025.
//

#ifndef LENNARDJONESTEST_H
#define LENNARDJONESTEST_H
#include "../../src/objects/ParticleContainer.h"
#include "../../src/simulation/LennardJones.h"

/**
 * Particle p1 to be used in Tests
 */
inline Particle p1= Particle({0.0,0.0,0.0},{0.0,0.0,0.0},1.0,5,1,0);
/**
 * Particle p2 to be used in Tests
 */
inline Particle p2= Particle({1.0,0.0,0.0},{0.0,0.0,0.0},2.0,5,1,0);
/**
 * Particle p3 to be used in Tests
 */
inline Particle p3= Particle({0.0,1.0,0.0},{0.0,0.0,0.0},1.5,5,1,0);

/**
 * Particle p4 to be used in Tests
 */
inline Particle p4= Particle({2.0,1.0,0.0},{0.0,0.0,0.0},1.0,5,1,0);

/**
 * vector of Particles containing p1 and p2 to be used in Tests
 */
inline std::vector<Particle> coll={p1,p2};
/**
 * vector of Particles containing p1 and p2 and p3 to be used in Tests
 */
inline std::vector<Particle> coll3={p1,p2,p3};
/**
 * empty vector of Particles to be used in Tests
 */
inline std::vector<Particle> empty={};

/**
 * Manually calculated Force Array of particle p1 for the Lennard-Jones potential between p1 and p2
 */
inline std::vector<double> check={-120.0,0.0,0.0};
/**
 * Manually calculated Force Array of particle p1 for the Lennard-Jones potential between p1, p2 and p3
 */
inline std::vector<double> check1={-120.0,-120.0,0.0};
/**
 * Manually calculated Force Array of particle p2 for the Lennard-Jones potential between p1, p2 and p3
 */
inline std::vector<double> check2={(915.0/8),(45.0/8),0.0};
/**
 * Manually calculated Force Array of particle p3 for the Lennard-Jones potential between p1, p2 and p3
 */
inline std::vector<double> check3={(45.0/8),(915.0/8),0.0};

#endif //LENNARDJONESTEST_H
