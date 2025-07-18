/*
 * ParticleContainer.h
 *
 * Created on: 02.05.2025
 *      Author: mawinkle
 */

#include "BasicParticleContainer.h"

BasicParticleContainer::BasicParticleContainer() {
    particles = std::vector<Particle>();
}

BasicParticleContainer::BasicParticleContainer(const std::vector<Particle> &particles_arg) {
    particles = particles_arg;
}

void BasicParticleContainer::addParticle(const Particle &p) {
    particles.push_back(p);
}

void BasicParticleContainer::addParticles(const std::vector<Particle> &p){
    particles.insert(particles.end(), p.begin(), p.end());
}

const std::vector<Particle> &BasicParticleContainer::getParticles() const {
    return particles;
}

int BasicParticleContainer::size() const {
    return static_cast<int>(particles.size());
}

std::vector<Particle>::iterator BasicParticleContainer::begin() {
    return particles.begin();
}

std::vector<Particle>::iterator BasicParticleContainer::end() {
    return particles.end();
}


std::vector<Particle>::const_iterator BasicParticleContainer::begin() const {
    return particles.cbegin();
}

std::vector<Particle>::const_iterator BasicParticleContainer::end() const {
    return particles.cend();
}

void BasicParticleContainer::applyUnary(std::function<void(Particle &i)> fun) {
    for (auto i = particles.begin(); i != particles.end(); ++i) {
        fun(*i);
    }
}

void BasicParticleContainer::applyBinary(std::function<void(Particle &i, Particle &j)> fun) {
    for (auto i = particles.begin(); i != particles.end(); ++i) {
        for (auto j = particles.begin(); j != i; ++j) {
            fun(*i, *j);
        }
    }
}

bool BasicParticleContainer::contains(BasicParticleContainer& particles, const Particle& p)
{
    for (auto it = particles.begin(); it != particles.end();++it)
{
    if (particle_sem_eq(p,*it))
    {return true;}
}
    return false;
}


bool BasicParticleContainer::cont_sem_eq(BasicParticleContainer& c1, BasicParticleContainer& c2)
{if (c1.size() != c2.size()){return false;}
    for (auto it = c1.begin(); it != c1.end(); ++it){
        if (!BasicParticleContainer::contains(c2,*it)){return false;}
    }
    return true;
}

