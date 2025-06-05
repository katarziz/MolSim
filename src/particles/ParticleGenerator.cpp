//
// Created by mawinkle on 19.05.25.
//

#include "ParticleGenerator.h"
#include "../utils/MaxwellBoltzmannDistribution.h"

ParticleContainer ParticleGenerator::generateCube(const std::array<double, 3> &base_coordinates,
                                                               const std::array<int64_t, 3> &number_of_particles, const double spacing, const double mass,
                                                               const std::array<double, 3> &velocity, const double brownian_motion_avg_velocity) {
    std::vector<Particle> particles;
    particles.reserve(number_of_particles[0]*number_of_particles[1]*number_of_particles[2]);

    // 3D-iteration over the cuboid
    for (int i = 0; i < number_of_particles[0]; ++i) {
        for (int j = 0; j < number_of_particles[1]; ++j) {
            for (int k = 0; k < number_of_particles[2]; ++k) {
                // all particles are set up in a cuboid with a base velocity and an initial velocity-offset
                // based on brownian motion and the Maxwell-Boltzmann Distribution
                const std::array<double, 3> position = {
                    // x-coordinate starting from "left"
                    base_coordinates[0] + spacing * i,
                    // y-coordinate starting from "lower"
                    base_coordinates[1] + spacing * j,
                    // z-coordinate starting from "front-side"
                    base_coordinates[2] - spacing * k
                };
                std::array<double, 3> particle_velocity =
                    maxwellBoltzmannDistributedVelocity(brownian_motion_avg_velocity, 3);
                particle_velocity[0] += velocity[0];
                particle_velocity[1] += velocity[1];
                particle_velocity[2] += velocity[2];
                particles.emplace_back(position, particle_velocity, mass);
            }
        }
    }
    return {particles};
}
ParticleContainer ParticleGenerator::generateDisc(const std::array<double, 3> &base_coordinates,
                                                               const int64_t &radius, const double spacing, const double mass,
                                                               const std::array<double, 3> &velocity, const double brownian_motion_avg_velocity)
{    std::vector<Particle> particles;
    particles.reserve(4*radius*radius);
    // 3D-iteration over the cuboid
    for (int i = 0; i <= radius; ++i)
    {
        for (int j = 0; j < radius; ++j) {
            //Checking if Particle is within the disc radius
             if ((i * i)+(j * j)<=(radius*radius))
             {    // all particles are set up in a disc with a base velocity and an initial velocity-offset
                 // based on brownian motion and the Maxwell-Boltzmann Distribution
                std::array<double, 3> particle_velocity =
                    maxwellBoltzmannDistributedVelocity(brownian_motion_avg_velocity, 3);
                particle_velocity[0] += velocity[0];
                particle_velocity[1] += velocity[1];
                particle_velocity[2] += velocity[2];
                //Adding Particles in all 4 Quadrants of the disc
                particles.emplace_back((std::array<double,3>){
                    base_coordinates[0] + spacing * i,
                    base_coordinates[1] + spacing * j,
                    base_coordinates[2]
                }, particle_velocity, mass);
                particles.emplace_back((std::array<double,3>){
                   base_coordinates[0] + spacing * i,
                   base_coordinates[1] - spacing * j,
                   base_coordinates[2]
               }, particle_velocity, mass);
                particles.emplace_back((std::array<double,3>){
                   base_coordinates[0] - spacing * i,
                   base_coordinates[1] + spacing * j,
                   base_coordinates[2]
               }, particle_velocity, mass);
                particles.emplace_back((std::array<double,3>){
                   base_coordinates[0] - spacing * i,
                   base_coordinates[1] - spacing * j,
                   base_coordinates[2]
               }, particle_velocity, mass);

            }
        }
    }
    return {particles};

}
