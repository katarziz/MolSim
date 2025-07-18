//
// Created by cpsch on 04.06.2025.
//

#ifndef XMLREADERTEST_H
#define XMLREADERTEST_H
#include "../src/objects/ParticleGenerator.h"

//! double representing the average brownian velocity. Set to 0 for Tests
inline double brown=0.0;
//! vector of boltzmann velocity set to zero
inline std::array<double, 3> v_b ={0,0,0};
//! The x3 axis is considered to increase 'towards the viewer'

/**
 * Particle c1 to be used in Tests, belonging to Cube 1
 */
inline Particle c1=Particle({0.0,0.0,0.0},v_b,1.0,5,1,0);
/**
 * Particle c2 to be used in Tests, belonging to Cube 1
 */
inline Particle c2=Particle({0.0,0.0,-1.0},v_b,1.0,5,1,0);
/**
 * Particle c3 to be used in Tests, belonging to Cube 1
 */
inline Particle c3=Particle({0.0,1.0,0.0},v_b,1.0,5,1,0);
/**
 * Particle c4 to be used in Tests, belonging to Cube 1
 */
inline Particle c4=Particle({0.0,1.0,-1.0},v_b,1.0,5,1,0);
/**
 * Particle c5 to be used in Tests, belonging to Cube 1
 */
inline Particle c5=Particle({1.0,0.0,0.0},v_b,1.0,5,1,0);
/**
 * Particle c6 to be used in Tests, belonging to Cube 1
 */
inline Particle c6=Particle({1.0,0.0,-1.0},v_b,1.0,5,1,0);
/**
 * Particle c7 to be used in Tests, belonging to Cube 1
 */
inline Particle c7=Particle({1.0,1.0,0.0},v_b,1.0,5,1,0);
/**
 * Particle c8 to be used in Tests, belonging to Cube 1
 */
inline Particle c8=Particle({1.0,1.0,-1.0},v_b,1.0,5,1,0);
/**
 * ParticleContainer representing Cube 2 to be used in Tests:
 * Origin: (0.0,0.0,0.0)    NumberParticles: (2,2,2)    Spacing: 1.0
 * Mass : 1.0               Velocity:   (0.0,0.0,0.0)   Brown_Vel: 0.0
 */
inline BasicParticleContainer cube1=BasicParticleContainer({c1,c2,c3,c4,c5,c6,c7,c8});
/**
 * Particle d1 to be used in Tests, belonging to Cube 2
 */
inline Particle d1=Particle({0.5,0.5,0.5},v_b,2.0,5,1,0);
/**
 * Particle d2 to be used in Tests, belonging to Cube 2
 */
inline Particle d2=Particle({1.5,0.5,0.5},v_b,2.0,5,1,0);
/**
 * Particle d3 to be used in Tests, belonging to Cube 2
 */
inline Particle d3=Particle({0.5,1.5,0.5},v_b,2.0,5,1,0);
/**
 * Particle d4 to be used in Testsv, belonging to Cube 2
 */
inline Particle d4=Particle({1.5,1.5,0.5},v_b,2.0,5,1,0);
/**
 * ParticleContainer representing Cube 2 to be used in Tests:
 * Origin: (0.5,0.5,0.5)    NumberParticles: (2,2,1)    Spacing: 1.0
 * Mass : 2.0               Velocity:   (0.0,0.0,0.0)   Brown_Vel: 0.0
 */
inline BasicParticleContainer cube2=BasicParticleContainer({d1,d2,d3,d4,});

/**
 * Particle p1 to be used in Tests
 */
inline Particle pt1= Particle({0.0,5.0,0.0},{0.0,-1.0,0.0},1.0,5,1,0);

/**
 * Particle p2 to be used in Tests
 */
inline Particle pt2= Particle({2.0,1.0,0.0},{0.0,0.0,0.0},1.0,5,1,0);

/**
 * ParticleContainer containing Cube1 Cube2, p1 and p2
 */
inline  BasicParticleContainer all=BasicParticleContainer({c1,c2,c3,c4,c5,c6,c7,c8,d1,d3,d2,d4,pt1,pt2});

/**
 * ParticleContainer containing particles for the Disc
 * origin(0,0,0),R=2, spacing=1.0
 */
inline BasicParticleContainer disc_c=BasicParticleContainer({
    Particle({0.0,0.0,0.0},{0.0,0.0,0.0},1.0,5,1,0),
    Particle({0.0,1.0,0.0},{0.0,0.0,0.0},1.0,5,1,0),
    Particle({0.0,-1.0,0.0},{0.0,0.0,0.0},1.0,5,1,0),
    Particle({0.0,2.0,0.0},{0.0,0.0,0.0},1.0,5,1,0),
    Particle({0.0,-2.0,0.0},{0.0,0.0,0.0},1.0,5,1,0),
    Particle({1.0,0.0,0.0},{0.0,0.0,0.0},1.0,5,1,0),
    Particle({-1.0,0.0,0.0},{0.0,0.0,0.0},1.0,5,1,0),
    Particle({1.0,1.0,0.0},{0.0,0.0,0.0},1.0,5,1,0),
    Particle({1.0,-1.0,0.0},{0.0,0.0,0.0},1.0,5,1,0),
    Particle({-1.0,1.0,0.0},{0.0,0.0,0.0},1.0,5,1,0),
    Particle({-1.0,-1.0,0.0},{0.0,0.0,0.0},1.0,5,1,0),
    Particle({2.0,0.0,0.0},{0.0,0.0,0.0},1.0,5,1,0),
    Particle({-2.0,0.0,0.0},{0.0,0.0,0.0},1.0,5,1,0),
});

/**
 * ParticleContainer containing particles for the Sphere
 * origin(0,0,0),R=2, spacing=1.0
 */
inline BasicParticleContainer sphere_c=BasicParticleContainer({
    Particle({0.0,0.0,0.0},{0.0,0.0,0.0},1.0,5,1,0),
    Particle({0.0,0.0,1.0},{0.0,0.0,0.0},1.0,5,1,0),
    Particle({0.0,0.0,-1.0},{0.0,0.0,0.0},1.0,5,1,0),
    Particle({0.0,0.0,2.0},{0.0,0.0,0.0},1.0,5,1,0),
    Particle({0.0,0.0,-2.0},{0.0,0.0,0.0},1.0,5,1,0),

    Particle({0.0,1.0,0.0},{0.0,0.0,0.0},1.0,5,1,0),
    Particle({0.0,-1.0,0.0},{0.0,0.0,0.0},1.0,5,1,0),
    Particle({0.0,1.0,1.0},{0.0,0.0,0.0},1.0,5,1,0),
    Particle({0.0,-1.0,1.0},{0.0,0.0,0.0},1.0,5,1,0),
    Particle({0.0,1.0,-1.0},{0.0,0.0,0.0},1.0,5,1,0),
    Particle({0.0,-1.0,-1.0},{0.0,0.0,0.0},1.0,5,1,0),

    Particle({0.0,2.0,0.0},{0.0,0.0,0.0},1.0,5,1,0),
    Particle({0.0,-2.0,0.0},{0.0,0.0,0.0},1.0,5,1,0),

    Particle({1.0,0.0,0.0},{0.0,0.0,0.0},1.0,5,1,0),
    Particle({-1.0,0.0,0.0},{0.0,0.0,0.0},1.0,5,1,0),

    Particle({1.0,0.0,1.0},{0.0,0.0,0.0},1.0,5,1,0),
    Particle({-1.0,0.0,1.0},{0.0,0.0,0.0},1.0,5,1,0),
    Particle({1.0,0.0,-1.0},{0.0,0.0,0.0},1.0,5,1,0),
    Particle({-1.0,0.0,-1.0},{0.0,0.0,0.0},1.0,5,1,0),

    Particle({1.0,1.0,0.0},{0.0,0.0,0.0},1.0,5,1,0),
    Particle({1.0,-1.0,0.0},{0.0,0.0,0.0},1.0,5,1,0),
    Particle({-1.0,1.0,0.0},{0.0,0.0,0.0},1.0,5,1,0),
    Particle({-1.0,-1.0,0.0},{0.0,0.0,0.0},1.0,5,1,0),

    Particle({1.0,1.0,1.0},{0.0,0.0,0.0},1.0,5,1,0),
    Particle({1.0,-1.0,1.0},{0.0,0.0,0.0},1.0,5,1,0),
    Particle({-1.0,1.0,1.0},{0.0,0.0,0.0},1.0,5,1,0),
    Particle({-1.0,-1.0,1.0},{0.0,0.0,0.0},1.0,5,1,0),
    Particle({1.0,1.0,-1.0},{0.0,0.0,0.0},1.0,5,1,0),
    Particle({1.0,-1.0,-1.0},{0.0,0.0,0.0},1.0,5,1,0),
    Particle({-1.0,1.0,-1.0},{0.0,0.0,0.0},1.0,5,1,0),
    Particle({-1.0,-1.0,-1.0},{0.0,0.0,0.0},1.0,5,1,0),

    Particle({2.0,0.0,0.0},{0.0,0.0,0.0},1.0,5,1,0),
    Particle({-2.0,0.0,0.0},{0.0,0.0,0.0},1.0,5,1,0),

});

#endif //XMLREADERTEST_H
