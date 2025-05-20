//
// Created by cpsch on 18.05.2025.
//
#ifndef MOLSIM_H
#define MOLSIM_H
/**** forward declaration of the calculation functions ****/

#include "ParticleContainer.h"
//! function to calculate and update the velocity of the particles
void calculateF();

//! function to calculate and update the position of the particles
void calculateX();

//! function to calculate and update the velocity of the particles
void calculateV();

//! function to plot the particles using the output writer
/*!
\param iteration int representing the number of the current iteration
*/
void plotParticles(int iteration);
//! constant double representing the start time of the simulation.
constexpr double start_time =0;
//! double representing the end time of the simulation. Default:1000
inline double end_time= 1000;
//! double representing the timestep of the simulation. Default:0.014
inline double delta_t= 0.014;
//! ParticleContainer containing all particles in the simulation
inline ParticleContainer particles;

//! int representation of the output writer being used
/*!
*writer_flag=0 -> vtk writer
*writer_flag=1 -> xyz  writer
*/
inline int writer_flag=0;

//! int representation of the force calculation being used
/*!
*force_flag=0 -> lennard jones
*force_flag=1 -> newton
*/
inline int force_flag=0;

//! main function of the Molecular Simulation
int main(int argc, char *argsv[]);


#endif //MOLSIM_H
