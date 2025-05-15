//! A Container class for Particle Objects
/*! A class implementing an Object to manage a collection of Particles.
 * This class can create Particle Containers, add Particles to them, and Iterate over the Particles.
 * Created on 02.05.2025
 *      Author: mawinkle
 */

#pragma once

#include <vector>

#include "Particle.h"

class ParticleContainer {
private:
    std::vector<Particle> particles;

public:
    //! A constructor for a Particle Container from an existing vector of Particles
    /*!
     \param particles_arg a reference to a vector of particles to initialize the ParticleContainer
     */
    ParticleContainer(const std::vector<Particle> &particles_arg);

    //! a constructor for an empty Particle Container
    ParticleContainer();

    //! A function to add a single Particle to a ParticleContainer
    /*!
     \param p a reference to a Particles to be added to the ParticleContainer
     */
    void addParticle(const Particle &particle);

    //! A function to add a vector of Particles to a ParticleContainer
    /*!
     \param particles_arg a reference to a vector of Particles to be added to the ParticleContainer
     */
    void addParticles(const std::vector<Particle> &particles_arg);

    //! A function to get the number of Particles in a Container
    /*!
     \returns the number of Particles in the Particle Container
     */
    int size() const;

    //! A function to get the Particles in a ParticleContainer
    /*!
     \returns the internal vector of the ParticleContainer
     */
    const std::vector<Particle> &getParticles() const;

    //! Iterator to the beginning of the Particle Container
    /*!
     \returns Iterator at the first Particle in the ParticleContainer
     */
    std::vector<Particle>::iterator begin();

    //! Iterator to the element past the end of the ParticleContainer
    /*!
     \returns Iterator to the element past the end of the ParticleContainer
     */
    std::vector<Particle>::iterator end();

    //! Constant Iterator to the beginning of the Particle Container
    /*!
     \returns constant Iterator at the first Particle in the ParticleContainer
     */
    std::vector<Particle>::const_iterator begin() const;

    ///! Constant iterator to the element past the end of the ParticleContainer
    /*!
     \returns constant iterator to the element past the end of the ParticleContainer
     */
    std::vector<Particle>::const_iterator end() const;
};
