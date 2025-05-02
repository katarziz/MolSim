/*
 * ParticleContainer.h
 *
 * Created on: 02.05.2025
 *      Author: mawinkle
 */

#pragma once

#include <vector>

#include "Particle.h"

class ParticleContainer {
private:
    std::vector<Particle> particles;

public:
    ParticleContainer(const std::vector<Particle> &particles_arg);

    ParticleContainer();

    void addParticle(const Particle &particle);

    void addParticles(const std::vector<Particle> &particles_arg);

    int size() const;

    const std::vector<Particle> &getParticles() const;

    std::vector<Particle>::iterator begin();

    std::vector<Particle>::iterator end();

    std::vector<Particle>::const_iterator begin() const;

    std::vector<Particle>::const_iterator end() const;

    // TODO iterator over vec<pair<Particle,Particle>>
};
