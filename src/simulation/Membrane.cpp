//
// Created by cpsch on 30.06.2025.
//

#include "Membrane.h"

#include "MolSim.h"

Membrane::Membrane(int offset_arg, int size_arg, int width_arg, double k_arg, double r_0_arg,std::array<double,3> f,std::vector<int> f_part)
{
    offset = offset_arg;
    size = size_arg;
    width = width_arg;
    k = k_arg;
    r_0 = r_0_arg;
    r_0_root=sqrt(2)*r_0;
    F_up = f;
    force_particles = f_part;
}


void Membrane::calculateF_Harm(Particle& i, Particle& j) const
{
    const std::array<double, 3> dist = i.x - j.x;
    const double norm =ArrayUtils::L2Norm(dist);
    const double factor=k*(norm-r_0)/norm;
    const std::array<double, 3> force = factor * dist;

    i.f = i.f - force;
    j.f = j.f + force;
}

void Membrane::calculateF_Harm_Diag(Particle& i, Particle& j) const
{
    const std::array<double, 3> dist = i.x - j.x;
    const double norm = ArrayUtils::L2Norm(dist);
    const double factor=k*(1-r_0_root/norm);
    const std::array<double, 3> force = factor * dist;
    i.f = i.f - force;
    j.f = j.f + force;
}

void Membrane::calculateF_LJ_Trunc(Particle& i, Particle& j) const
{
    const std::array<double, 3> dist = i.x - j.x;
    const double squared_norm = dist[0] * dist[0] + dist[1] * dist[1] + dist[2] * dist[2];
    const double eps = sqrt(i.eps * j.eps);
    const double sig = (i.sig + j.sig) / 2;
    const double sn2 = (sig * sig / squared_norm);
    //Truncation of the LJ Force for distances greater than 2**(1/6) *sigma
    if (1/sn2 > r_c) {
        return;
    }
    const double sn6 = sn2 * sn2 * sn2;
    const double factor = 24 * eps * (2 * sn6 * sn6 - sn6) / squared_norm;
    const std::array<double, 3> force = factor * dist;
    i.f = i.f + force;
    j.f = j.f - force;
}


