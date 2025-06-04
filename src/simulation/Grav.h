//
// Created by cpsch on 18.05.2025.
//

#ifndef GRAV_H
#define GRAV_H
#include "../objects/ParticleContainer.h"
//! A function to calculate the forces acting on a set of particles
/*!
 \param particles a reference to the container of particles the forces will be applied to
 */
void calculateF_G(ParticleContainer &particles);

#endif //GRAV_H
