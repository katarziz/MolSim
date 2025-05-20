// Created by cpsch on 12.05.2025.

#include "ParticleContainerTest.h"
#include <gtest/gtest.h>
#include "../src/ParticleContainer.h"


/*!Test initialization of an empty Particle container*/
TEST(EmpytInitTest, ParticleContainerTests) {
    ParticleContainer emp=ParticleContainer();
    // Expect equality.
    EXPECT_EQ(0, emp.size());
    EXPECT_EQ(emp.begin(),emp.end());
}

/*!Test initialization of a Particle container*/
TEST(InitTest, ParticleContainerTests) {
    ParticleContainer con=ParticleContainer(coll);
    EXPECT_EQ(coll.size(), con.size());
    for(int i=0;i<coll.size();i++)
    {
        EXPECT_TRUE(particle_sem_eq(coll[i],con.getParticles()[i]));
    }
}

