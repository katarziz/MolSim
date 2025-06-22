//
// Created by cpsch on 18.05.2025.
//

#include "LennardJones.h"
#include "utils/ArrayUtils.h"

int eps = 5;
int sig = 1;

void calculateF_LJ(Particle &i, Particle &j, double cutoff) {
    const std::array<double, 3> dist = i.getX() - j.getX();
    const double norm = ArrayUtils::L2Norm(dist);
    if (norm > cutoff) {
        return;
    }
    const double factor = std::pow(sig / norm, 6);
    const std::array<double, 3> force =
            24 * eps * (2 * factor * factor - factor) / (norm * norm) * dist;
    i.setF(i.getF() + force);
    j.setF(j.getF() - force);
}
