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

double Thermostat::calculateTemp(ParticleContainer &particles) const {
    double e_kin = 0.0;
    for (const auto &particle: particles) {
        e_kin += particle.getM() *
        (particle.getV()[0] * particle.getV()[0]
         + particle.getV()[1] * particle.getV()[1]
         + particle.getV()[2] * particle.getV()[2]);
    }
    return e_kin / (particles.size() * dim);
}

void Thermostat::scaleV(ParticleContainer *particles) const {
    double temp_c = calculateTemp(*particles);
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
            particle->setV(beta * particle->getV());
        }
    }
}
