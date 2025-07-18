#pragma once
#include "../../src/objects/ParticleContainer.h"

/**
 * Particle p1 to be used in Tests
 */
inline Particle p1= Particle({0.0,0.0,0.0},{0.0,0.0,0.0},1.0,0);
/**
 * Particle p2 to be used in Tests
 */
inline Particle p2= Particle({1.0,0.0,0.0},{0.0,0.0,0.0},2.0,0);
/**
 * Particle p3 to be used in Tests
 */
inline Particle p3= Particle({0.0,1.0,0.0},{0.0,0.0,0.0},1.5,0);

/**
 * Particle p4 to be used in Tests
 */
inline Particle p4= Particle({2.0,1.0,0.0},{0.0,0.0,0.0},1.0,0);

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