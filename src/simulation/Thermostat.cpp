//
// Created by cpsch on 16.06.2025.
//

#include "Thermostat.h"

#include <iostream>

#include "utils/ArrayUtils.h"

Thermostat::Thermostat() {
    temp_target = 0;
    delta_temp = 0;
    dim = 2;
}

void Thermostat::setParams(double temp_target_arg, double delta_temp_arg, int dim_arg) {
    temp_target = temp_target_arg;
    delta_temp = delta_temp_arg;
    dim = dim_arg;
}

double Thermostat::calculateTemp_old(ParticleContainer &particles) const {
    double e_kin = 0.0;
    for (const auto &particle: particles) {
        if ((particle.getState() & ParticleState::Fixed) != ParticleState::Fixed) {
            e_kin += particle.getM() *
            (particle.getV()[0] * particle.getV()[0]
             + particle.getV()[1] * particle.getV()[1]
             + particle.getV()[2] * particle.getV()[2]);
        }
    }
    return e_kin / (particles.size() * dim);
}

void Thermostat::scaleV_old(ParticleContainer *particles) const {
    double temp_c = calculateTemp_old(*particles);
    double temp_n;

    if (delta_temp != 0) //delta_temp=0 -> Thermostat Off, delta_temp=inf-> immediate scaling
    {
        if (temp_c < temp_target - delta_temp) {
            temp_n = temp_c + delta_temp;
        } else if (temp_c > temp_target + delta_temp) {
            temp_n = temp_c - delta_temp;
        } else {
            temp_n = temp_target;
        }
        double beta = sqrt(temp_n / temp_c);


        for (auto particle = particles->begin(); particle != particles->end(); ++particle) {
            if ((particle->getState() & ParticleState::Fixed) != ParticleState::Fixed) {
                particle->setV(beta * particle->getV());
            }
        }
    }
}

std::array<double, 3> Thermostat::calculateAverageVel(ParticleContainer &particles) {
    if (particles.size() == 0) { return {0, 0, 0}; }
    std::array<double, 3> sum_vel = {0, 0, 0};
    for (auto p = particles.begin(); p != particles.end(); ++p) {
        sum_vel = sum_vel + p->getV();
    }
    return (1.0 / particles.size()) * sum_vel;
}

double Thermostat::calculateTemp(ParticleContainer &particles, const std::array<double, 3> &avg_vel) const {
    double e_kin = 0.0;
    for (const auto &particle: particles) {
        if ((particle.getState() & ParticleState::Fixed) != ParticleState::Fixed) {
            std::array<double, 3> therm_vel = particle.getV() - avg_vel;
            e_kin += particle.getM() *
            (therm_vel[0] * therm_vel[0]
             + therm_vel[1] * therm_vel[1]
             + therm_vel[2] * therm_vel[2]);
        }
    }
    return e_kin / (particles.size() * dim);
}

void Thermostat::scaleV(ParticleContainer *particles) const {
    std::array<double, 3> avg_vel = calculateAverageVel(*particles);
    double temp_c = calculateTemp(*particles, avg_vel);
    double temp_n;

    if (delta_temp != 0) //delta_temp=0 -> Thermostat Off, delta_temp=inf-> immediate scaling
    {
        if (temp_c < temp_target - delta_temp) {
            temp_n = temp_c + delta_temp;
        } else if (temp_c > temp_target + delta_temp) {
            temp_n = temp_c - delta_temp;
        } else {
            temp_n = temp_target;
        }
        double beta = sqrt(temp_n / temp_c);


        particles->applyUnary([beta, avg_vel](Particle &p) {
            if ((p.getState() & ParticleState::Fixed) != ParticleState::Fixed) {
                p.setV((1 - beta) * avg_vel + beta * p.getV());
            }
        });
    }
}
