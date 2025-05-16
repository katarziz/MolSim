//
// Created by cpsch on 12.05.2025.
//
#include <gtest/gtest.h>
#include "ParticleTest.h"
#include "../src/Particle.h"
#include "../src/ParticleContainer.h"

//Particle p1= Particle({0.0,0.0,0.0},{0.0,0.0,0.0},1.0,0);
//Particle p2= Particle({1.0,0.0,0.0},{0.0,0.0,0.0},2.0,0);
//Particle p3= Particle({0.0,1.0,0.0},{0.0,0.0,0.0},1.5,0);

TEST(InitTest, ParticleTests)
{
    std::array<double, 3> x_t = {1.0, 0.0, 0.0};
    std::array<double, 3> v_t = {0.0, 0.0, 0.0};
    Particle t=Particle(x_t,v_t,1.0,0);
   for (int i=0;i<3;i++)
   {
       EXPECT_EQ(x_t[i],t.getX()[i]);
       EXPECT_EQ(v_t[i],t.getV()[i]);
       EXPECT_EQ(0.0,t.getF()[i]);
       EXPECT_EQ(0.0,t.getOldF()[i]);

   }
    EXPECT_EQ(t.getM(),1.0);
    EXPECT_EQ(t.getType(),0);

}
