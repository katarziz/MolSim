//! A Generator class for Particle Objects
/*! A class implementing an Object to generate a collection of Particles based on parameters.
 * This class can create Particle Containers.
 * Created on 19.05.2025
 *      Author: mawinkle
 */

#pragma once

#include <array>

#include "BasicParticleContainer.h"


class ParticleGenerator {
public:
    //! A constructor for a Particle Generator from given Parameters
    /*!
     \param particles The ParticleContainer to be generated
     \param base_coordinates The coordinate of the lower left front-side corner of the cuboid
     \param number_of_particles Number of particles per dimension N1 x N2 x N3
     \param spacing Distance h of the particle (mesh width of the grid)
     \param mass Mass m of one particle
     \param eps  double containing Lennard-Jones Parameter epsilon of this Particle
     \param sig  double containing Lennard-Jones Parameter sigma of this Particle
     \param velocity Initial velocity v of the particles
     \param type int to denote the type of the particles
     \param dim int denoting the dimensions of the simulation to apply correct MB velocity
     \param brownian_motion_avg_velocity The mean-value of the velocity of the Brownian Motion
     \returns a set-up cuboid of particles in a ParticleContainer
     */
    static void generateCube(ParticleContainer &particles, const std::array<double, 3> &base_coordinates,
                             const std::array<int64_t, 3> &number_of_particles, double spacing,
                             double mass, double eps, double sig,
                             const std::array<double, 3> &velocity, int type, int dim,
                             double brownian_motion_avg_velocity);

    //! A constructor for a Particle Generator from given Parameters
    /*!
     \param particles The ParticleContainer to be generated
     \param base_coordinates The coordinate of the lower left front-side corner of the cuboid
     \param radius Number of particles forming the radius of the disc
     \param spacing Distance h of the particle (mesh width of the grid)
     \param mass Mass m of one particle
     \param eps  double containing Lennard-Jones Parameter epsilon of this Particle
     \param sig  double containing Lennard-Jones Parameter sigma of this Particle
     \param velocity Initial velocity v of the particles
     \param type int to denote the type of the particles
     \param dim int denoting the dimensions of the simulation to apply correct MB velocity
     \param brownian_motion_avg_velocity The mean-value of the velocity of the Brownian Motion
     \returns a set-up disc of particles in a ParticleContainer
     */
    static void generateDisc(ParticleContainer &particles, const std::array<double, 3> &base_coordinates,
                             const int &radius, const double &spacing, const double &mass,
                             double eps, double sig,
                             const std::array<double, 3> &velocity,
                             int type, int dim,
                             const double &brownian_motion_avg_velocity);

    //! A constructor for a Particle Generator from given Parameters
    /*!
     \param velocity Initial velocity v of the particles
     \param dim int denoting the dimensions of the simulation to apply correct MB velocity
     \param brownian_motion_avg_velocity The mean-value of the velocity of the Brownian Motion
     \returns an array of the initial velocity of the particles with brownian motion applied
     */
    static auto generateInitVel(const std::array<double, 3> &velocity, int dim,
                                const double &brownian_motion_avg_velocity) -> std::array<double, 3>;
};
