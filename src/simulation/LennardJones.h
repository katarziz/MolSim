//
// Created by cpsch on 18.05.2025.
//

#ifndef LENNARDJONES_H
#define LENNARDJONES_H
#include "../objects/ParticleContainer.h"
//! A function to calculate and apply the forces acting on a set of particles
/*!
 \param particles a reference to the container of particles the force will be applied to
 */
void calculateF_LJ(ParticleContainer &particles);
#endif //LENNARDJONES_H

