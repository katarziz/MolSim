//
// Created by cpsch on 30.06.2025.
//

#ifndef MEMBRANE_H
#define MEMBRANE_H
#include "LennardJones.h"
#include "utils/ArrayUtils.h"
class Membrane{
private:

    //! int giving the index within a ParticleContainer of the first membrane particle
    int offset;
    //! number of  particles in the membrane
    int size;
    //! width of the membrane
    int width;
    //!spring constant k of the harmonic potential
    double k;
    //! bond length of the harmonic potential
    double r_0;
    //!bond length of the harmonic potential times sqrt(2)
    double r_0_root;
    //!vector of the perpendicular force
    std::array<double,3> F_up;
    //!vector of particles to which perp. force is applied
    std::vector<int> force_particles;

public:

    //! Constructor for a Membrane object
    /*!
    * \param offset int giving the index within a ParticleContainer of the first membrane particle
    * \param size number of membrane particles
    * \param width of the membrane
    * \param k spring constant k of the harmonic potential between particles
    * \param r_0 bond length of the harmonic potential
    * \param f vector of the perpendicular force
    * \param f_part vector of particles to which perp. force is applied
    */
    Membrane(int offset, int size, int width, double k, double r_0,std::array<double,3> f,std::vector<int> f_part);

    [[nodiscard]] int get_offset() const
    {
        return offset;
    }
    //! Function to calculate the harmonic potential between direct neighbors
    /*!
    * \param i first particle of a direct neighbor pair
    * \param j second particle of a direct neighbor pair
    */
    void calculateF_Harm(Particle &i, Particle &j) const;

    //! Function to calculate the harmonic potential between diagonal neighbors
    /*!
    * \param i first particle of a diagonal neighbor pair
    * \param j second particle of a diagonal neighbor pair
    */
    void calculateF_Harm_Diag(Particle &i, Particle &j) const ;

    //! Function which returns the indices of the particles to which
    //!perpendicular force should be applied


    [[nodiscard]] std::vector<int> get_force_particles() const
    {
        return force_particles;
    }

    void set_offset(int offset)
    {
        this->offset = offset;
    }

    [[nodiscard]] int get_size() const
    {
        return size;
    }

    void set_size(int size)
    {
        this->size = size;
    }

    [[nodiscard]] int get_width() const
    {
        return width;
    }

    void set_width(int width)
    {
        this->width = width;
    }

    [[nodiscard]] std::array<double,3> get_f_up() const
    {
        return F_up;
    }

    void set_f_up(std::array<double,3>  f_up)
    {
        F_up = f_up;
    }

};
#endif //MEMBRANE_H