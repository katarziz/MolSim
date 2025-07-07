//
// Created by cpsch on 12.05.2025.
//

#include "ParticleTest.h"
#include <gtest/gtest.h>
//#include "../src/Particle.h"


TEST(InitTest, ParticleTests)
{
    std::array<double, 3> x_t = {1.0, 0.0, 0.0};
    std::array<double, 3> v_t = {0.0, 0.0, 0.0};
    Particle t=Particle(x_t,v_t,1.0,5,1,0);
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

TEST(GetterSetterTest, ParticleTests)
{
    std::array<double, 3> x_t = {1.0, 7.0, 13.0};
    std::array<double, 3> v_t = {8.0, 2.0, 9.0};
    std::array<double, 3> f_t = {5.0,1.0,3.0};
    Particle t=Particle({0.0,0.0,0.0},{0.0,0.0,0.0},1.0,5,1,0);

    EXPECT_EQ(t.getM(),1.0);
    EXPECT_EQ(t.getType(),0);
    for (int i=0;i<x_t.size();++i){
        EXPECT_EQ(t.getX()[i],0.0);
        EXPECT_EQ(t.getV()[i],0.0);
        EXPECT_EQ(t.getF()[i],0.0);
        EXPECT_EQ(t.getOldF()[i],0);
    }
    t.setOldF(t.getF());
    t.setF(f_t);
    t.setV(v_t);
    t.setX(x_t);
    for (int i=0;i<x_t.size();++i){
        EXPECT_EQ(t.getX()[i],x_t[i]);
        EXPECT_EQ(t.getV()[i],v_t[i]);
        EXPECT_EQ(t.getF()[i],f_t[i]);
        EXPECT_EQ(t.getOldF()[i],0.0);
    }
}

TEST(SemEqTest, ParticleTests)
{ Particle t=Particle(p1.getX(),p1.getV(),p1.getM(),p1.getEps(),p1.getSig(),p1.getType());
    t.setF(p1.getF());
    t.setOldF(p1.getOldF());
    EXPECT_TRUE(particle_sem_eq(p1,t));
    EXPECT_FALSE(particle_sem_eq(p1,p2));
}


