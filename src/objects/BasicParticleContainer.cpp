/*
 * ParticleContainer.h
 *
 * Created on: 02.05.2025
 *      Author: mawinkle
 */

#include "BasicParticleContainer.h"

BasicParticleContainer::BasicParticleContainer() {
    particles = std::vector<Particle>();
    membranes=std::vector<Membrane>();
}

BasicParticleContainer::BasicParticleContainer(const std::vector<Particle> &particles_arg) {
    particles = particles_arg;
    membranes=std::vector<Membrane>();
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

void BasicParticleContainer::addMembrane(Membrane &mem)
{
    membranes.push_back(mem);
}

const std::vector<Membrane>& BasicParticleContainer::getMembranes() const
{
    return membranes;
}

void BasicParticleContainer::applyUnarytoMembrane(const Membrane &mem, const std::function<void(Particle &i)> &fun)
{
    for (auto i=mem.get_offset();i<mem.get_offset()+mem.get_size();++i)
    {
        fun(particles[i]);
    }
}


void BasicParticleContainer::applyPerpForce(const Membrane &mem)
{
    for (auto p=mem.get_force_particles().begin(); p!=mem.get_force_particles().end();++p)
    {
        particles[*p].f=particles[*p].f+mem.get_f_up();
    }
}

void BasicParticleContainer::applyMembraneForces(const Membrane &mem)
{   int8_t begin=mem.get_offset();
    int8_t end=mem.get_offset()+mem.get_size();
    int8_t width=mem.get_width();
    for (auto i=begin;i<end;++i)
    {
        if (i+1<end && (i-begin)/width== (i+1-begin)/width)
        {
            mem.calculateF_Harm(particles[i],particles[i+1]);
        }
        if (i+width<end)
        {
            mem.calculateF_Harm(particles[i],particles[i+width]);
        }
        if (i+width+1<end && (i-begin)/width+1== (i+width+1-begin)/width)
        {
            mem.calculateF_Harm_Diag(particles[i],particles[i+width+1]);
        }
        if (i+width-1<end && (i-begin)/width != (i+width-1-begin)/width)
        {
            mem.calculateF_Harm_Diag(particles[i],particles[i+width-1]);
        }
    }
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

void BasicParticleContainer::applyUnary(const std::function<void(Particle &i)> & fun) {
    for (auto i = particles.begin(); i != particles.end(); ++i) {
        fun(*i);
    }
}

void BasicParticleContainer::applyBinary(const std::function<void(Particle &i, Particle &j)>  & fun) {
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