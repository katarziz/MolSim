//
// Created by cpsch on 18.05.2025.
//

#include "LennardJones.h"
#include "utils/ArrayUtils.h"


void calculateF_LJ(Particle &i, Particle &j, double cutoff) {
    const std::array<double, 3> dist = i.getX() - j.getX();
    const double squared_norm = dist[0] * dist[0] + dist[1] * dist[1] + dist[2] * dist[2];
    if (squared_norm > cutoff * cutoff) {
        return;
    }
    const double eps = sqrt(i.getEps() * j.getEps());
    const double sig = (i.getSig() + j.getSig())/2;
    const double sn2 = (sig * sig / squared_norm);
    const double sn6 = sn2 * sn2 * sn2;
    const double factor = 24 * eps * (2 * sn6 * sn6 - sn6) / squared_norm;
    const std::array<double, 3> force = factor * dist;
    i.setF(i.getF() + force);
    j.setF(j.getF() - force);
}
