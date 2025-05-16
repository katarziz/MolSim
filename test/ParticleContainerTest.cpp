//
// Created by cpsch on 12.05.2025.

#include "ParticleContainerTest.h"
#include <gtest/gtest.h>
#include "../src/Particle.cpp"
#include "../src/ParticleContainer.cpp"



Particle p1= Particle({0.0,0.0,0.0},{0.0,0.0,0.0},1.0,0);
Particle p2= Particle({1.0,0.0,0.0},{0.0,0.0,0.0},2.0,0);
Particle p3= Particle({0.0,1.0,0.0},{0.0,0.0,0.0},1.5,0);
std::vector<Particle> coll={p1,p2};
std::vector<Particle> coll3={p1,p2,p3};
std::vector<Particle> empty={};

// Demonstrate some basic assertions.
TEST(EmpytInitTest, ParticleContainerTests) {
    ParticleContainer emp=ParticleContainer();
    // Expect equality.
    EXPECT_EQ(0, emp.size());
    EXPECT_EQ(emp.begin(),emp.end());
   // EXPECT_EQ(empty,emp.getParticles());
}
// Demonstrate some basic assertions.
TEST(InitTest, ParticleContainerTests) {
    ParticleContainer con=ParticleContainer(coll);
    // Expect equality.
    EXPECT_EQ(coll.size(), con.size());
   // EXPECT_EQ(coll.end(), con.end());
}

