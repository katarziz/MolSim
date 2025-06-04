//
// Created by cpsch on 18.05.2025.
//

#include "Grav.h"
#include "../MolSim.h"
#include "../utils/ArrayUtils.h"

void calculateF_G(ParticleContainer &particles) {
    for (auto p1 = particles.begin(); p1 != particles.end(); ++p1) {
        std::array<double, 3> force = {0,0,0};
        for (auto p2 = particles.begin(); p1 != p2; ++p2) {

            // diff_x = x_i - x_j
            std::array<double, 3> diff_x = {0,0,0};
            for (int i = 0; i < 3; ++i) {
                diff_x[i] = p1->getX()[i] - p2->getX()[i];
            }

            // l2_norm_x = ||diff_x||_2
            const double l2_norm_x = ArrayUtils::L2Norm(diff_x);

            // factor = m_i * m_j / (l2_norm_x)^3
            const double factor = p1->getM() * p2->getM() / (l2_norm_x * l2_norm_x * l2_norm_x);

            // F_ij = factor * (x_j - x_i) = factor * -1 * (x_i - x_j) = factor * -1 * diff_x
            for (int i = 0; i < 3; ++i) {
                force[i] += factor * -diff_x[i];
            }
        }
        p1->setOldF(p1->getF());
        p1->setF(force);
    }
}