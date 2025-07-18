//
// Created by cpsch on 30.06.2025.
//

#include "Membrane.h"

#include "MolSim.h"

Membrane::Membrane(int offset_arg, int size_arg, int width_arg, double k_arg, double r_0_arg, std::array<double, 3> f,
                   std::vector<int> f_part) {
    offset = offset_arg;
    size = size_arg;
    width = width_arg;
    k = k_arg;
    r_0 = r_0_arg;
    r_0_root = sqrt(2) * r_0;
    F_up = f;
    force_particles = f_part;
}


void Membrane::calculateF_Harm(Particle &i, Particle &j) const {
    if ((i.getState() & ParticleState::InActive) == ParticleState::InActive || (j.getState() & ParticleState::InActive)
        == ParticleState::InActive) { return; }
    const std::array<double, 3> dist = i.getX() - j.getX();
    const double norm = ArrayUtils::L2Norm(dist);
    const double factor = k * (norm - r_0) / norm;
    const std::array<double, 3> force = factor * dist;

    i.setF(i.getF() - force);
    j.setF(j.getF() + force);
}

void Membrane::calculateF_Harm_Diag(Particle &i, Particle &j) const {
    if ((i.getState() & ParticleState::InActive) == ParticleState::InActive || (j.getState() & ParticleState::InActive)
        == ParticleState::InActive) { return; }
    const std::array<double, 3> dist = i.getX() - j.getX();
    const double norm = ArrayUtils::L2Norm(dist);
    const double factor = k * (1 - r_0_root / norm);
    const std::array<double, 3> force = factor * dist;
    i.setF(i.getF() - force);
    j.setF(j.getF() + force);
}
