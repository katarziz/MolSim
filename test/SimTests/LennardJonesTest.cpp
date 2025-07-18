//
// Created by cpsch on 19.05.2025.
//

#include "LennardJonesTest.h"
#include <gtest/gtest.h>

#include "objects/BasicParticleContainer.h"


TEST(TwoParticleLJTest, LJForceCalcTests)
{ BasicParticleContainer particles=BasicParticleContainer(coll);
    for (auto p1=particles.begin();p1!=particles.end();++p1)
    {
        for (auto p2=particles.begin();p2!=p1;++p2)
        {
          calculateF_LJ(*p1,*p2);
        }

    }


    for (int i=0;i<particles.getParticles()[0].getF().size();i++)
    {
        EXPECT_FLOAT_EQ(particles.getParticles()[0].getF()[i],check[i]);
        EXPECT_FLOAT_EQ(particles.getParticles()[1].getF()[i],-1*check[i]);
    }
}

TEST(ThreeParticleLJTest,LJForceCalcTests)
{ BasicParticleContainer particles=BasicParticleContainer(coll3);
    for (auto p1=particles.begin();p1!=particles.end();++p1)
    {
        for (auto p2=particles.begin();p2!=p1;++p2)
        {
            calculateF_LJ(*p1,*p2);
        }

    }
    for (int i=0;i<particles.getParticles()[0].getF().size();i++)
    {
        EXPECT_FLOAT_EQ(particles.getParticles()[0].getF()[i],check1[i]);
        EXPECT_FLOAT_EQ(particles.getParticles()[1].getF()[i],check2[i]);
        EXPECT_FLOAT_EQ(particles.getParticles()[2].getF()[i],check3[i]);
    }
}