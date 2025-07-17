//! A Container class for Particle Objects
/*! A class implementing an Object to manage a collection of Particles.
 * This class can create Particle Containers, add Particles to them, and Iterate over the Particles.
 * Created on 02.05.2025
 *      Author: mawinkle
 */

#pragma once

#include <vector>

#include "Particle.h"
#include "ParticleContainer.h"

class BasicParticleContainer : public ParticleContainer {
private:
    std::vector<Particle> particles;
    std::vector<Membrane> membranes;

public:
    //! a constructor for an empty Particle Container
    BasicParticleContainer();

    //! A constructor for a Particle Container from an existing vector of Particles
    /*!
     \param particles_arg a reference to a vector of particles to initialize the ParticleContainer
     */
    explicit BasicParticleContainer(const std::vector<Particle> &particles_arg);

    //! A function to add a single Particle to a ParticleContainer
    /*!
     \param p a reference to a Particles to be added to the ParticleContainer
     */
    void addParticle(const Particle &p) override;

    //! A function to add a vector of Particles to a ParticleContainer
    /*!
     \param p a reference to a vector of Particles to be added to the ParticleContainer
     */
    void addParticles(const std::vector<Particle> &p) override;

    //! A function to get the Particles in a ParticleContainer
    /*!
     \returns the internal vector of the ParticleContainer
     */
    const std::vector<Particle> &getParticles() const override;

    //! A function to add a membrane of Particles to a ParticleContainer
    /*!
     \param mem a reference to an array of 3 int representing
     the indices of the first particle,the last particle and
     the width of the membrane
     */
    void addMembrane(Membrane &mem) override ;

    //! A function to get the Membranes of a ParticleContainer
    /*!
     \returns the internal vector of the membrane management object
     */
    const std::vector<Membrane> &getMembranes() const override;

    void applyUnarytoMembrane(const Membrane& mem, const std::function<void(Particle& i)>& fun) override;
    void applyPerpForce(const Membrane& mem);

    void applyMembraneForces(const Membrane& mem) override;
    //! A function to get the number of Particles in a Container
    /*!
     \returns the number of Particles in the Particle Container
     */
    int size() const override;

    //! Iterator to the beginning of the Particle Container
    /*!
     \returns Iterator at the first Particle in the ParticleContainer
     */
    std::vector<Particle>::iterator begin() override;

    //! Iterator to the element past the end of the ParticleContainer
    /*!
     \returns Iterator to the element past the end of the ParticleContainer
     */
    std::vector<Particle>::iterator end() override;

    //! Constant Iterator to the beginning of the Particle Container
    /*!
     \returns constant Iterator at the first Particle in the ParticleContainer
     */
    std::vector<Particle>::const_iterator begin() const override;

    //! Constant iterator to the element past the end of the ParticleContainer
    /*!
     \returns constant iterator to the element past the end of the ParticleContainer
     */
    std::vector<Particle>::const_iterator end() const override;

    //! method to iterate over all particles and apply a unary function
    /*!
     \param fun a lambda function to be applied to all particles
     */
    void applyUnary(const std::function<void(Particle &i)> & fun) override;

    //! method to iterate over all particles pairwise and apply a binary function
    /*!
     \param fun a lambda function to be applied to all particles pairwise
     */
    void applyBinary(const std::function<void(Particle &i, Particle &j)> & fun) override;

    //! Function which checks whether a Particle is present in a PArticleContainer
    /*!
     \param particles ParticleContainer
     \param p Particle
     \returns bool that signifies if a particle is present in the ParticleContainer
    */
    static bool contains(BasicParticleContainer &particles, const Particle &p);

    ///! Function which checks whether two Particle containers contain the same Particles
    /*!
     \param c1 First Particle Container
     \param c2 Second Particle Container
     \returns bool which indicates whether the two ParticleContainers contain exactly the same Particles.
     */
    static bool cont_sem_eq(BasicParticleContainer &c1, BasicParticleContainer &c2);
};
