//
// Created by cpsch on 18.05.2025.
//
#include "utils/ArrayUtils.h"
#include "LennardJones.h"
#include "MolSim.h"
#include <iostream>

int eps= 5;
int sig=1;

void calculateF_LJ() {
  for (auto &p:particles)
  {
    p.setOldF(p.getF());
    p.setF(p.getF()-p.getF());
  }
  for (auto i=particles.begin();i!=particles.end();++i)
  {
    for (auto j=particles.begin();j!=i;++j)
    { double n_ij= ArrayUtils::L2Norm(i->getX()-j->getX());
      double xi=(sig/n_ij)*(sig/n_ij)*(sig/n_ij)*(sig/n_ij)*(sig/n_ij)*(sig/n_ij);
      std::array<double, 3> f_ij=-1*((24*eps)/(n_ij*n_ij))*(xi-2*xi*xi)*(i->getX()-j->getX());
      i->setF(i->getF()+f_ij);
      std::cout << "F " << f_ij<< std::endl;
      j->setF(j->getF()-f_ij);
    }
  }
}

void calculateF_LJ(ParticleContainer& particles) {
  for (auto &p:particles)
  {
    p.setOldF(p.getF());
    p.setF(p.getF()-p.getF());
  }
  for (auto i=particles.begin();i!=particles.end();++i)
  {
    for (auto j=particles.begin();j!=i;++j)
    { double n_ij= ArrayUtils::L2Norm(i->getX()-j->getX());
      double xi=(sig/n_ij)*(sig/n_ij)*(sig/n_ij)*(sig/n_ij)*(sig/n_ij)*(sig/n_ij);
      std::array<double, 3> f_ij=-1*((24*eps)/(n_ij*n_ij))*(xi-2*xi*xi)*(i->getX()-j->getX());
      i->setF(i->getF()+f_ij);
      j->setF(j->getF()-f_ij);
    }
  }
}