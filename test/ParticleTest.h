#pragma once
#include <gtest/gtest.h>
#include "../src/Particle.h"

/**
 * Particle p1 to be used in Tests
 */
inline Particle p1= Particle({0.0,0.0,0.0},{0.0,0.0,0.0},1.0,0);
/**
 * Particle p2 to be used in Tests
 */
inline Particle p2= Particle({1.0,0.0,0.0},{0.0,0.0,0.0},2.0,0);
/**
 * Particle p3 to be used in Tests
 */
inline Particle p3= Particle({0.0,1.0,0.0},{0.0,0.0,0.0},1.5,0);

//! Helper Function to determine semantic equality of two particles
/*!
 \param p1
 \param p2
 \returns bool to indicate weather the particles are semantically equal
*/
bool  particle_sem_eq(Particle p1, Particle p2);