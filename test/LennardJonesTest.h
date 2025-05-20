//
// Created by cpsch on 19.05.2025.
//

#ifndef LENNARDJONESTEST_H
#define LENNARDJONESTEST_H
#include "../src/ParticleContainer.h"
#include "../src/LennardJones.h"
//! Function to calculate the Lennard Jones Force between the Particles in
//!the global ParticleContainer particles
/*!
Function to calculate the Lennard Jones Force between the Particles in
the global ParticleContainer particles.
Puts values of F into F_old, and calculates the new forces F
*/
void calculateF_LJ();
//! Function to calculate the Lennard Jones Force between the Particles in
//!the passed ParticleContainer particles
/*!
 \param particles ParticleContainer
Function to calculate the Lennard Jones Force between the Particles in
the global ParticleContainer particles.
Puts values of F into F_old, and calculates the new forces F
*/
void calculateF_LJ(ParticleContainer& particles);


#endif //LENNARDJONESTEST_H
