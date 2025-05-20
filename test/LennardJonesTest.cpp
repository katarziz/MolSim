//
// Created by cpsch on 19.05.2025.
//

#include "LennardJonesTest.h"
#include "ParticleContainerTest.h"
#include <gtest/gtest.h>


TEST(TwoParticleLJTest,LJForceCalcTests)
{ ParticleContainer particles=ParticleContainer(coll);
    calculateF_LJ(particles);
    std::vector<double> check={-120.0,0.0,0.0};
    for (int i=0;i<particles.getParticles()[0].getF().size();i++)
    {
        EXPECT_FLOAT_EQ(particles.getParticles()[0].getF()[i],check[i]);
        EXPECT_FLOAT_EQ(particles.getParticles()[1].getF()[i],-1*check[i]);
    }
}

TEST(ThreeParticleLJTest,LJForceCalcTests)
{ ParticleContainer particles=ParticleContainer(coll3);
  calculateF_LJ(particles);
    std::vector<double> check1={-120.0,-120.0,0.0};
    std::vector<double> check2={(915.0/8),(45.0/8),0.0};
    std::vector<double> check3={(45.0/8),(915.0/8),0.0};
    for (int i=0;i<particles.getParticles()[0].getF().size();i++)
    {
        EXPECT_FLOAT_EQ(particles.getParticles()[0].getF()[i],check1[i]);
        EXPECT_FLOAT_EQ(particles.getParticles()[1].getF()[i],check2[i]);
        EXPECT_FLOAT_EQ(particles.getParticles()[2].getF()[i],check3[i]);
    }
}