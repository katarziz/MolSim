//! A Generator class for Particle Objects
/*! A class implementing an Object to generate a collection of Particles based on parameters.
 * This class can create Particle Containers.
 * Created on 19.05.2025
 *      Author: mawinkle
 */

#pragma once

#include <array>

#include "ParticleContainer.h"

class ParticleGenerator {
public:
    //! A constructor for a Particle Generator from given Parameters
    /*!
     \param base_coordinates The coordinate of of the lower left front-side corner of the cuboid
     \param number_of_particles Number of particles per dimension N1 x N2 x N3
     \param spacing Distance h of the particle (mesh width of the grid)
     \param mass Mass m of one particle
     \param velocity Initial velocity v of the particles
     \param brownian_motion_avg_velocity The mean-value of the velocity of the Brownian Motion
     \returns a set-up cuboid of particles in a ParticleContainer
     */
    static ParticleContainer generateParticleContainer(const std::array<double, 3> &base_coordinates,
        const std::array<int64_t, 3> &number_of_particles, double spacing, double mass,
        const std::array<double, 3> &velocity, double brownian_motion_avg_velocity);

};
