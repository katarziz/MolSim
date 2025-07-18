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
    std::array<int, 3> cell_number;
    std::vector<std::vector<int> > cells;
    std::vector<Particle> particles;
    std::vector<Membrane> membranes;
    std::vector<int> boundary;
    std::vector<int> halo;
    double cutoff;
    const int boundary_width = 1;
    std::array<int, 6> boundary_conditions;
    int omp_strategy = 0;

public:
    //! a constructor for an empty Particle Container
    /*!
     \param box_size_arg a reference to a vector of doubles to set the size of cells
     \param cell_number_arg a reference to a vector of int64_t's to set the number of cells
     \param cutoff_arg a reference to a double to set the cutoff radius
     \param bounds_arg an array of ints setting the boundary conditions of the imulaiton space
            0: outflow, 1: reflective, 2: periodic
     */
    LinkedCellParticleContainer(const std::array<double, 3> &box_size_arg,
                                const std::array<int, 3> &cell_number_arg,
                                const double &cutoff_arg, const std::array<int, 6> &bounds_arg);

    //! a constructor for a Particle Container
    /*!
     \param particles_arg a reference to a vector of Particles to fill the ParticleContainer
     \param box_size_arg a reference to a vector of doubles to set the size of cells
     \param cell_number_arg a reference to a vector of int64_t's to set the number of cells
     \param cutoff_arg a reference to a double to set the cutoff radius
     \param bounds_arg an array of ints setting the boundary conditions of the imulaiton space
            0: outflow, 1: reflective, 2: periodic
     */
    LinkedCellParticleContainer(const std::vector<Particle> &particles_arg, const std::array<double, 3> &box_size_arg,
                                const std::array<int, 3> &cell_number_arg, const double &cutoff_arg,
                                const std::array<int, 6> &bounds_arg);

    //! a function to set the parameters of a LinkedCellParticleContainer
    /*!
     \param box_size_arg a reference to a vector of doubles to set the size of cells
     \param cell_number_arg a reference to a vector of int64_t's to set the number of cells
     \param cutoff_arg a reference to a double to set the cutoff radius
     \param bounds_arg an array of ints setting the boundary conditions of the imulaiton space
            0: outflow, 1: reflective, 2: periodic
     */
    void setParameters(const std::array<double, 3> &box_size_arg,
                       const std::array<int, 3> &cell_number_arg,
                       const double &cutoff_arg, const std::array<int, 6> &bounds_arg);

    //! a function to set the omp strategy of a LinkedCellParticleContainer
    /*!
     \param omp_strategy_arg the strategy to use for computation
            0: none/serial, 1: coarse/block-wise parallel, 2: granular/cell-wise parallel
     */
    void setOMPStrategy(const int &omp_strategy_arg);

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
    [[nodiscard]] const std::vector<Particle> &getParticles() const override;

    //! A function to add a membrane of Particles to a ParticleContainer
    /*!
     \param mem a reference to an array of 3 int representing
     the indices of the first particle,the last particle and
     the width of the membrane
     */
    void addMembrane(Membrane &mem) override;

    //! A function to get the Membranes of a ParticleContainer
    /*!
     \returns the internal vector of the membrane management object
     */
    const std::vector<Membrane> &getMembranes() const override;

    //! A getter for the cutoff radius
    /*!
     \return the cutoff radius used in the ParticleContainer
     */
    double getCutoff() const;

    //! A function to return the size of the ParticleContainer
    /*!
     \returns an int representing the number of Particles in the Container
     */
    [[nodiscard]] int size() const override;

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
    [[nodiscard]] std::vector<Particle>::const_iterator begin() const override;

    //! A function to return a constant iterator pointing to the end of the ParticleContainer
    /*!
    \returns a constant iterator pointing to the end of the ParticleContainer
    */
    [[nodiscard]] std::vector<Particle>::const_iterator end() const override;

    //! A function to apply a unary function to the Particles in the ParticleContainer
    /*!
    \param fun a unary function to be applied to the Particles in the ParticleContainer
   */
    void applyUnary(const std::function<void(Particle &i)> &fun) override;

    //! A helper function to calculate the index of a flattened array based on three base indices
    /*!
     \param i_x the index on the x axis
     \param i_y the index on the y axis
     \param i_z the index on the z axis
     */
    [[nodiscard]] inline int calcIndex(const int &i_x, const int &i_y, const int &i_z) const;

    //! A function to apply a binary function to pairs of Particles between two cells of the ParticleContainer
    /*!
        \param fun a binary function to be applied pairwise to the Particles between two cells of the ParticleContainer
        \param i_cell the first cell of the operation
        \param j_cell the second cell of the operation
    */
    void applyBinaryToCells(const std::function<void(Particle &i, Particle &j)> &fun, const std::vector<int> &i_cell,
                            const std::vector<int> &j_cell);

    //! Applies a binary function to a particle at the specified index and its neighboring particles.
    /*!
     \param fun The binary function to be applied, taking two particles as arguments.
     \param i_x The x index of the middle cell
     \param i_y The y index of the middle cell
     \param i_z The z index of the middle cell
     \param i_cell
    */
    void applyBinaryToNeighbors(const std::function<void(Particle &i, Particle &j)> &fun,
                                const int &i_x, const int &i_y, const int &i_z, const std::vector<int> &i_cell);

    //! A function to apply a binary function to pairs of Particles in neighboring cells of the ParticleContainer
    /*!
        \param fun a binary function to be applied pairwise to the Particles in neighboring cells of the ParticleContainer
    */
    void applyBinary(const std::function<void(Particle &i, Particle &j)> &fun) override;

    //! A function to apply a unary function to Particles of a Membrane
    /*!
     *\param mem reference to a Membrane
      \param fun a binary function to be applied pairwise to the Particles in neighboring cells of the ParticleContainer
   */
    void applyUnarytoMembrane(const Membrane &mem, const std::function<void(Particle &i)> &fun) override;

    //! A function to apply the Membranes perpendicular force to the selected Particles of a Membrane
    /*!
     *\param mem reference to a Membrane
   */
    void applyPerpForce(const Membrane &mem) override;

    //! A function to apply the Harmonic force to neighboring Particles of a Membrane
    /*!
     *\param mem reference to a Membrane
   */

    void applyMembraneForces(const Membrane &mem) override;

    //! A function to update the cells of the ParticleContainer
    /*!
        A function to update the cells of the ParticleContainer
    */
    void updateCells();

    //! A function that applies reflective and periodic forces to particles at the boundary
    void applyBoundaryConditions();

    //! A function to apply a unary function to the particles in the boundary cells of the ParticleContainer
    /*!
     \param fun a unary function to be applied to the Particles in the boundary cells
    */
    void applyUnaryToBoundary(const std::function<void(Particle &i)> &fun);

    //! A function to apply a unary function to the particles in the halo region of the ParticleContainer
    /*!
     \param fun a unary function to be applied to the Particles in the halo region
    */
    void applyUnaryToHalo(const std::function<void(Particle &i)> &fun);

    //! A function to delete all particles in the halo region
    /*!
     This function deactivates all particles in the halo region by setting their state to 1
    */
    void deleteHalo();

    //! A function to write out the Density and Velocity Profile of the Simulation to .csv files
    /*!
     *\param vel_prof of stream to write velocity to
     *\param N_prof of stream to write the Number of particles to
   */

    void writeState(std::ofstream &vel_prof, std::ofstream &N_prof);
};
