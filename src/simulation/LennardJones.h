//
// Created by cpsch on 18.05.2025.
//

#pragma once

#include <cmath>

#include "../objects/Particle.h"

//! A function to calculate and apply the forces acting on a pair of particles
/*!
 \param i the first particle of the pair
 \param j the second particle of the pair
 */
void calculateF_LJ(Particle &i, Particle &j, double cutoff = INFINITY);
