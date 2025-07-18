//
// Created by cpsch on 18.05.2025.
//

#pragma once

#include "../objects/Particle.h"

//! A function to calculate and apply the forces action on a pair of particles
/*!
 \param i the first particle of the pair
 \param j the second particle of the pair
 */
void calculateF_G(Particle &i, Particle &j, double cutoff);

//! A function to apply gravitational force of the environment to a particle
/*!
 \param i a particle
 */
void calculateF_GE(Particle &i, std::array<double,3> grav);
