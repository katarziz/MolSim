//
// Created by mawinkle on 6/5/25.
//

#pragma once

#include <memory>
#include <vector>

#include "Particle.h"
#include "ParticleContainer.h"

class LinkedCellParticleContainer : public ParticleContainer {
private:
    std::array<double, 3> box_size;
    std::array<int64_t, 3> cell_number;
    std::vector<std::vector<std::unique_ptr<Particle>>> cells;
    std::vector<Particle> particles;
    std::vector<Particle> halo;
    double cutoff;
    const int boundary_width = 1;
    std::array<int, 4> boundary_conditions;

public:
    //! a constructor for an empty Particle Container
    /*!
     \param box_size_arg a reference to a vector of doubles to set the size of cells
     \param cell_number_arg a reference to a vector of int64_t's to set the number of cells
     \param cutoff_arg a reference to a double to set the cutoff radius
     */
    LinkedCellParticleContainer(const std::array<double, 3> &box_size_arg,
                                const std::array<int64_t, 3> &cell_number_arg,
                                const double &cutoff_arg, const std::array<int, 4> &bounds_arg);

    //! a constructor for a Particle Container
    /*!
     \param particles_arg a reference to a vector of Particles to fill the ParticleContainer
     \param box_size_arg a reference to a vector of doubles to set the size of cells
     \param cell_number_arg a reference to a vector of int64_t's to set the number of cells
     \param cutoff_arg a reference to a double to set the cutoff radius
     */
    LinkedCellParticleContainer(const std::vector<Particle> &particles_arg, const std::array<double, 3> &box_size_arg,
                                const std::array<int64_t, 3> &cell_number_arg, const double &cutoff_arg,
                                const std::array<int, 4> &bounds_arg);

    void setParameters(const std::array<double, 3> &box_size_arg,
                       const std::array<int64_t, 3> &cell_number_arg,
                       const double &cutoff_arg, const std::array<int, 4> &bounds_arg);
    //! A function to add a Particle to the ParticleContainer
    /*!
     \param p reference to the Particle to be added to the container
     */
    void addParticle(const Particle &p) override;
    //! A function to add a vector of Particles to the ParticleContainer
    /*!
     \param p reference to the vector of Particles to be added to the container
     */
    void addParticles(const std::vector<Particle> &p) override;
    //! A function to return the Particles int the ParticleContainer
    /*!
     \returns a vector of the Particles in the Container
     */
    const std::vector<Particle> &getParticles() const override;
    //! A function to return the size of the ParticleContainer
    /*!
     \returns an int representing the number of Particles in the Container
     */
    int size() const override;
    //! A function to return an iterator pointing to the beginning of the ParticleContainer
    /*!
     \returns an iterator pointing to the beginning of the ParticleContainer
     */
    std::vector<Particle>::iterator begin() override;
    //! A function to return an iterator pointing to the end of the ParticleContainer
    /*!
     \returns an iterator pointing to the bend of the ParticleContainer
     */
    std::vector<Particle>::iterator end() override;
    //! A function to return a constant iterator pointing to the beginning of the ParticleContainer
    /*!
     \returns a constant iterator pointing to the beginning of the ParticleContainer
     */
    std::vector<Particle>::const_iterator begin() const override;
    //! A function to return a constant iterator pointing to the end of the ParticleContainer
    /*!
    \returns a constant iterator pointing to the end of the ParticleContainer
    */
    std::vector<Particle>::const_iterator end() const override;
    //! A function to apply a unary function to the Particles in the ParticleContainer
    /*!
    \param a unary function to be applied to the Particles in the ParticleContainer
   */
    void applyUnary(std::function<void(Particle &i)> fun) override;
    //! A function to apply a binary function to pairs of Particles in neighboring cells of the ParticleContainer
    /*!
        \param a binary function to be applied pairwise to the Particles in neighboring cells of the ParticleContainer
    */
    void applyBinary(std::function<void(Particle &i, Particle &j)> fun) override;
    //! A function to update the cells of the ParticleContainer
    /*!
        A function to update the cells of the ParticleContainer
    */
    void updateCells();

    void applyUnaryToBoundary(const std::function<void(Particle &i)> &fun);

    void applyUnaryToHalo(const std::function<void(Particle &i)> &fun);

    void deleteHalo();

    void outflow(const Particle *p);

    void reflect(Particle *p, int boundary);
};
