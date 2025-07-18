//
// Created by cpsch on 16.06.2025.
//

#ifndef THERMOSTAT_H
#define THERMOSTAT_H
#include "objects/BasicParticleContainer.h"
#include "objects/LinkedCellParticleContainer.h"


class Thermostat {
private:
    double temp_target;
    double delta_temp;
    int dim;

public:
    //! Constructor to for a Thermostat
    Thermostat();

    //! Function to set the parameters of a Thermostat
    /*!
    \param temp_target_arg a double giving the Target Temperature
    \param delta_temp_arg giving the maximal change of temperature applied at each scaling
    \param dim int giving the dimensions of the simulation
    */
    void setParams(double temp_target_arg, double delta_temp_arg, int dim);

    //! Function to calculate the Temperature of a set of Particles
    /*!
    \param particles pointer to a ParticleContainer containing the Particles
    */
    double calculateTemp_old(ParticleContainer &particles) const;

    //! Function to scale the velocities of the Particles in a Particle container to represent a change in Temperature
    /*!
    \param particles pointer to a ParticleContainer containing the Particles
    */
    void scaleV_old(ParticleContainer *particles) const;

    static std::array<double,3> calculateAverageVel(ParticleContainer &particles);

    //! Function to calculate the Temperature of a set of Particles
    /*!
    \param particles pointer to a ParticleContainer containing the Particles
    */
    double calculateTemp(ParticleContainer &particles, const std::array<double,3>& avg_vel) const;

    //! Function to scale the velocities of the Particles in a Particle container to represent a change in Temperature
    /*!
    \param particles pointer to a ParticleContainer containing the Particles
    */
    void scaleV(ParticleContainer *particles) const;

};


#endif //THERMOSTAT_H
