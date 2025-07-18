//
// Created by mawinkle on 19.05.25.
//

#include "ParticleGenerator.h"
#include "BasicParticleContainer.h"
#include "LinkedCellParticleContainer.h"
#include "../utils/MaxwellBoltzmannDistribution.h"

void ParticleGenerator::generateCube(ParticleContainer &particles,
                                     const std::array<double, 3> &base_coordinates,
                                     const std::array<int64_t, 3> &number_of_particles,
                                     const double spacing, const double mass,
                                     const double eps, const double sig,
                                     const std::array<double, 3> &velocity,
                                     const int type, const int dim,
                                     const double brownian_motion_avg_velocity, ParticleState state) {
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
                    base_coordinates[2] + spacing * k
                };
                std::array<double, 3> particle_velocity = {0, 0, 0};
                if (state != ParticleState::Fixed) {
                    particle_velocity = generateInitVel(velocity, dim, brownian_motion_avg_velocity);
                }
                particles.addParticle({position, particle_velocity, mass, eps, sig, type, state});
            }
        }
    }
}


void ParticleGenerator::generateDisc(ParticleContainer &particles, const std::array<double, 3> &base_coordinates,
                                     const int &radius, const bool sphere, const double &spacing, const double &mass,
                                     const double eps, const double sig,
                                     const std::array<double, 3> &velocity,
                                     const int type, const int dim,
                                     const double &brownian_motion_avg_velocity, ParticleState state) {
    // iteration over the Disc
    for (int i = 0; i <= radius; ++i) {
        for (int j = 0; j <= radius; ++j) {
            for (int k = 0; k <= (sphere ? radius : 0); ++k) {
                //Checking if Particle is within the disc radius
                if ((i * i) + (j * j) + (k * k) <= radius * radius) {
                    // all particles are set up in a disc with a base velocity and an initial velocity-offset
                    // based on brownian motion and the Maxwell-Boltzmann Distribution
                    std::array<double, 3> particle_velocity = {0, 0, 0};
                    if (state != ParticleState::Fixed) {
                        particle_velocity = generateInitVel(velocity, dim, brownian_motion_avg_velocity);
                    }
                    //Adding Particles in all 4 Quadrants of the disc
                    particles.addParticle(Particle((std::array<double, 3>){
                                                       base_coordinates[0] + spacing * i,
                                                       base_coordinates[1] + spacing * j,
                                                       base_coordinates[2] + spacing * k,
                                                   }, particle_velocity, mass, eps, sig, type, state));

                    if (j != 0) {
                        particle_velocity = {0, 0, 0};
                        if (state != ParticleState::Fixed) {
                            particle_velocity = generateInitVel(velocity, dim, brownian_motion_avg_velocity);
                        }
                        particles.addParticle(Particle((std::array<double, 3>){
                                                           base_coordinates[0] + spacing * i,
                                                           base_coordinates[1] - spacing * j,
                                                           base_coordinates[2] + spacing * k
                                                       }, particle_velocity, mass, eps, sig, type, state));
                    }
                    if (i != 0) {
                        particle_velocity = {0, 0, 0};
                        if (state != ParticleState::Fixed) {
                            particle_velocity = generateInitVel(velocity, dim, brownian_motion_avg_velocity);
                        }
                        particles.addParticle(Particle((std::array<double, 3>){
                                                           base_coordinates[0] - spacing * i,
                                                           base_coordinates[1] + spacing * j,
                                                           base_coordinates[2] + spacing * k
                                                       }, particle_velocity, mass, eps, sig, type, state));
                    }
                    if (i != 0 && j != 0) {
                        particle_velocity = {0, 0, 0};
                        if (state != ParticleState::Fixed) {
                            particle_velocity = generateInitVel(velocity, dim, brownian_motion_avg_velocity);
                        }
                        particles.addParticle(Particle((std::array<double, 3>){
                                                           base_coordinates[0] - spacing * i,
                                                           base_coordinates[1] - spacing * j,
                                                           base_coordinates[2] + spacing * k
                                                       }, particle_velocity, mass, eps, sig, type, state));
                    }
                    if (k != 0) {
                        particle_velocity = {0, 0, 0};
                        if (state != ParticleState::Fixed) {
                            particle_velocity = generateInitVel(velocity, dim, brownian_motion_avg_velocity);
                        }
                        particles.addParticle(Particle((std::array<double, 3>){
                                                           base_coordinates[0] + spacing * i,
                                                           base_coordinates[1] + spacing * j,
                                                           base_coordinates[2] - spacing * k
                                                       }, particle_velocity, mass, eps, sig, type, state));

                        if (j != 0) {
                            particle_velocity = {0, 0, 0};
                            if (state != ParticleState::Fixed) {
                                particle_velocity = generateInitVel(velocity, dim, brownian_motion_avg_velocity);
                            }
                            particles.addParticle(Particle((std::array<double, 3>){
                                                               base_coordinates[0] + spacing * i,
                                                               base_coordinates[1] - spacing * j,
                                                               base_coordinates[2] - spacing * k
                                                           }, particle_velocity, mass, eps, sig, type, state));
                        }
                        if (i != 0) {
                            particle_velocity = {0, 0, 0};
                            if (state != ParticleState::Fixed) {
                                particle_velocity = generateInitVel(velocity, dim, brownian_motion_avg_velocity);
                            }
                            particles.addParticle(Particle((std::array<double, 3>){
                                                               base_coordinates[0] - spacing * i,
                                                               base_coordinates[1] + spacing * j,
                                                               base_coordinates[2] - spacing * k
                                                           }, particle_velocity, mass, eps, sig, type, state));
                        }
                        if (i != 0 && j != 0) {
                            particle_velocity = {0, 0, 0};
                            if (state != ParticleState::Fixed) {
                                particle_velocity = generateInitVel(velocity, dim, brownian_motion_avg_velocity);
                            }
                            particles.addParticle(Particle((std::array<double, 3>){
                                                               base_coordinates[0] - spacing * i,
                                                               base_coordinates[1] - spacing * j,
                                                               base_coordinates[2] - spacing * k
                                                           }, particle_velocity, mass, eps, sig, type, state));
                        }
                    }
                }
            }
        }
    }
}


void ParticleGenerator::generateMembrane(ParticleContainer &particles, std::array<double, 3> base_coordinates,
                                         const std::array<int64_t, 3> &number_of_particles, double spacing, double mass,
                                         double eps, double sig,
                                         const std::array<double, 3> &velocity, int type, int dim,
                                         double brownian_motion_avg_velocity,
                                         const double k_arg, const double r_0, std::array<double, 3> f,
                                         std::vector<int> f_part) {
    int offset = particles.size();
    int size = number_of_particles[0] * number_of_particles[1] * number_of_particles[2] + offset;
    int width = std::max(number_of_particles[0], number_of_particles[1]);
    Membrane mem = Membrane(offset, size, width, k_arg, r_0, f, f_part);
    particles.addMembrane(mem);
    int k = 0;
    if (number_of_particles[0] == 1) { k = 1; } else if (number_of_particles[1] == 1) { k = 2; }
    for (int i = 0; i < number_of_particles[k]; ++i) {
        for (int j = 0; j < number_of_particles[(k + 1) % 3]; ++j) {
            std::array<double, 3> position = {
                // x-coordinate starting from "left"
                base_coordinates[0],
                // y-coordinate starting from "lower"
                base_coordinates[1],
                // z-coordinate starting from "front-side"
                base_coordinates[2]
            };
            position[k] = base_coordinates[k] + spacing * i;
            position[(k + 1) % 3] = base_coordinates[(k + 1) % 3] + spacing * j;
            position[(k + 2) % 3] = base_coordinates[(k + 2) % 3];

            std::array<double, 3> particle_velocity = generateInitVel(velocity, dim, brownian_motion_avg_velocity);
            particles.addParticle(Particle(position, particle_velocity, mass, eps, sig, type, ParticleState::Membrane));
        }
    }
}


std::array<double, 3> ParticleGenerator::generateInitVel(const std::array<double, 3> &velocity, int dim,
                                                         const double &brownian_motion_avg_velocity) {
    std::array<double, 3> particle_velocity = maxwellBoltzmannDistributedVelocity(brownian_motion_avg_velocity, dim);
    particle_velocity[0] += velocity[0];
    particle_velocity[1] += velocity[1];
    particle_velocity[2] += velocity[2];
    return particle_velocity;
}
