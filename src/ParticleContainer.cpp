/*
 * ParticleContainer.h
 *
 * Created on: 02.05.2025
 *      Author: mawinkle
 */

#include "ParticleContainer.h"

ParticleContainer::ParticleContainer() {
    std::vector<Particle> particles;
}

ParticleContainer::ParticleContainer(const std::vector<Particle> &particles_arg) {
    particles = particles_arg;
}

void ParticleContainer::addParticle(const Particle &p) {
    particles.emplace_back(p);
}

void ParticleContainer::addParticles(const std::vector<Particle> &particles_arg) {
    particles.insert(particles.end(), particles_arg.begin(), particles_arg.end());
}

int ParticleContainer::size() const {
    return particles.size();
}

const std::vector<Particle> &ParticleContainer::getParticles() const {
    return particles;
}

std::vector<Particle>::iterator ParticleContainer::begin() {
    return particles.begin();
}

std::vector<Particle>::iterator ParticleContainer::end() {
    return particles.end();
}


std::vector<Particle>::const_iterator ParticleContainer::begin() const {
    return particles.cbegin();
}

std::vector<Particle>::const_iterator ParticleContainer::end() const {
    return particles.cend();
}
