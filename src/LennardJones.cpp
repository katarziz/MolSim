//
// Created by cpsch on 18.05.2025.
//
#include "utils/ArrayUtils.h"
#include "LennardJones.h"
#include "MolSim.h"
#include <iostream>

int eps = 5;
int sig = 1;

void calculateF_LJ() {
    for (auto &p: particles) {
        p.setOldF(p.getF());
        p.setF({0, 0, 0});
    }
    for (auto i = particles.begin(); i != particles.end(); ++i) {
        for (auto j = particles.begin(); j != i; ++j) {
            double n_ij = ArrayUtils::L2Norm(i->getX() - j->getX());
            // double xi = (sig / n_ij) * (sig / n_ij) * (sig / n_ij) * (sig / n_ij) * (sig / n_ij) * (sig / n_ij);
            // std::array<double, 3> f_ij = -1 * ((24 * eps) / (n_ij * n_ij)) * (xi - 2 * xi * xi) * (
            //                                  i->getX() - j->getX());
            double f_ij = 24*eps*(2*std::pow(sig/n_ij,12)-std::pow(sig/n_ij,6))/n_ij;
            i->setF(i->getF() + (f_ij/n_ij*(i->getX() - j->getX())));
            j->setF(j->getF() - (f_ij/n_ij*(i->getX() - j->getX())));
        }
    }
}

void calculateF_LJ(ParticleContainer &particles) {
    for (auto &p: particles) {
        p.setOldF(p.getF());
        p.setF({0, 0, 0});
    }
    for (auto i = particles.begin(); i != particles.end(); ++i) {
        for (auto j = particles.begin(); j != i; ++j) {
            double n_ij = ArrayUtils::L2Norm(i->getX() - j->getX());
            // double xi = (sig / n_ij) * (sig / n_ij) * (sig / n_ij) * (sig / n_ij) * (sig / n_ij) * (sig / n_ij);
            // std::array<double, 3> f_ij = -1 * ((24 * eps) / (n_ij * n_ij)) * (xi - 2 * xi * xi) * (
            //                                  i->getX() - j->getX());
            double f_ij = 24*eps*(2*std::pow(sig/n_ij,12)-std::pow(sig/n_ij,6))/n_ij;
            i->setF(i->getF() + (f_ij/n_ij*(i->getX() - j->getX())));
            j->setF(j->getF() - (f_ij/n_ij*(i->getX() - j->getX())));
        }
    }
}