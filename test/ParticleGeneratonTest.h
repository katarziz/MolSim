//
// Created by cpsch on 22.05.2025.
//
#pragma once
#include "../src/ParticleGenerator.h"
//#include "../src/utils/MaxwellBoltzmannDistribution.h"

inline double brown=0.0;
inline std::array<double, 3> v_b ={0,0,0};//maxwellBoltzmannDistributedVelocity(brown, 3);
//! The x3 axis is considered to increase 'towards the viewer'
inline Particle c1=Particle({0.0,0.0,0.0},v_b,1.0,0);
inline Particle c2=Particle({0.0,0.0,-1.0},v_b,1.0,0);
inline Particle c3=Particle({0.0,1.0,0.0},v_b,1.0,0);
inline Particle c4=Particle({0.0,1.0,-1.0},v_b,1.0,0);
inline Particle c5=Particle({1.0,0.0,0.0},v_b,1.0,0);
inline Particle c6=Particle({1.0,0.0,-1.0},v_b,1.0,0);
inline Particle c7=Particle({1.0,1.0,0.0},v_b,1.0,0);
inline Particle c8=Particle({1.0,1.0,-1.0},v_b,1.0,0);
inline ParticleContainer cube1=ParticleContainer({c1,c2,c3,c4,c5,c6,c7,c8});
inline Particle d1=Particle({0.5,0.5,0.5},v_b,2.0,0);
inline Particle d2=Particle({1.5,0.5,0.5},v_b,2.0,0);
inline Particle d3=Particle({0.5,1.5,0.5},v_b,2.0,0);
inline Particle d4=Particle({1.5,1.5,0.5},v_b,2.0,0);
inline ParticleContainer cube2=ParticleContainer({c1,c2,c3,c4,c5,c6,c7,c8,d1,d2,d3,d4,});





