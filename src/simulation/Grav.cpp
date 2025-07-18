//
// Created by cpsch on 18.05.2025.
//

#include "Grav.h"
#include "utils/ArrayUtils.h"

void calculateF_G(Particle &i, Particle &j, double cutoff) {
    const std::array<double, 3> dist = i.getX() - j.getX();
    const double norm = ArrayUtils::L2Norm(dist);
    if (norm > cutoff) {
        return;
    }
    const double factor = i.getM() * j.getM() / (norm * norm * norm);
    const std::array<double, 3> force = -1 * factor * dist;
    i.setF(i.getF() + force);
    j.setF(j.getF() - force);
}

void calculateF_GE(Particle &i, std::array<double,3> grav) {
      i.f = i.f+i.m*grav;
}
