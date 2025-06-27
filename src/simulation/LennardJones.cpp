//
// Created by cpsch on 18.05.2025.
//

#include "LennardJones.h"
#include "utils/ArrayUtils.h"



void calculateF_LJ(Particle &i, Particle &j, double cutoff) {
    const std::array<double, 3> dist = i.getX() - j.getX();
    const double norm = ArrayUtils::L2Norm(dist);
    if (norm > cutoff) {
        return;
    }
    double eps;
    double sig;
    //TODO: Decide if this is if is necessary or if we calculate ever time?
    if (i.getEps()==j.getEps()&&i.getSig()==j.getSig())
    {
        eps=i.getEps();
        sig=i.getSig();
    }else
    {
        eps=sqrt(i.getEps()*j.getEps());
        sig= (i.getSig()+j.getSig())/2;
    }
    const double factor = std::pow(sig / norm, 6);
    const std::array<double, 3> force =
            24 * eps * (2 * factor * factor - factor) / (norm * norm) * dist;
    i.setF(i.getF() + force);
    j.setF(j.getF() - force);
}
