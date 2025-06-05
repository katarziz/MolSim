//
// Created by cpsch on 18.05.2025.
//
#ifndef MOLSIM_H
#define MOLSIM_H
/**** forward declaration of the calculation functions ****/

#include "particles/ParticleContainer.h"
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
inline double end_time= 5;
//! double representing the timestep of the simulation. Default:0.0002
inline double delta_t= 0.0002;
//! double representing the cutoff radius. Default:3.0
inline double r_c= 3.0;
//! array of three doubles representing the cell size. Default:r_c x r_c x 1
inline std::array<double,3>box_dim={r_c,r_c,1.0};
//! array of three ints representing the number of cells. Default:1x1x1
inline std::array<int64_t,3>cell_num={1,1,1};
//! array of four ints representing the boundary conditions: top,right,bottom, left
// outflow:0 ("out"), reflecting:1 ("ref")
//Default:outflow x outflow x outflow x outflow
inline std::array<int,4>bounds={0,0,0,0};


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

inline std::string out_name="MD_vtk";

inline int64_t out_freq=50;

//! main function of the Molecular Simulation
int main(int argc, char *argsv[]);


#endif //MOLSIM_H
