//
// Created by mawinkle on 6/4/25.
//

#pragma once

#include <vector>
#include <functional>

#include "Particle.h"

class ParticleContainer {
public:
    virtual ~ParticleContainer() = default;

    virtual void addParticle(const Particle &p) = 0;

    virtual void addParticles(const std::vector<Particle> &p) = 0;

    virtual const std::vector<Particle> &getParticles() const = 0;

    virtual int size() const = 0;

    virtual std::vector<Particle>::iterator begin() = 0;

    virtual std::vector<Particle>::iterator end() = 0;

    virtual std::vector<Particle>::const_iterator begin() const = 0;

    virtual std::vector<Particle>::const_iterator end() const = 0;

    virtual void applyUnary(std::function<void(Particle &i)> fun) = 0;

    virtual void applyBinary(std::function<void(Particle &i, Particle &j)> fun) = 0;
};
