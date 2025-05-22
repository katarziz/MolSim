//
// Created by cpsch on 22.05.2025.
//

#include "ParticleGeneratonTest.h"
#include <gtest/gtest.h>



TEST(Init2x2, ParticleGeneratorTests)
{
 ParticleContainer con= ParticleGenerator::generateParticleContainer({0.0,0.0,0.0},
  {2,2,2},1.0,1.0,{0.0,0.0,0.0},brown);
 //EXPECT_TRUE(ParticleContainer::cont_sem_eq(con,cube1));
 for (auto i=con.begin(); i != con.end(); ++i)
 {
  std::cout << (*i).toString() << std::endl;
  EXPECT_TRUE(ParticleContainer::contains(cube1,*i));
 }
}

TEST(Init2Cubes, ParticleGeneratorTests)
{ ParticleContainer con= ParticleGenerator::generateParticleContainer({0.0,0.0,0.0},
 {2,2,2},1.0,1.0,{0.0,0.0,0.0},brown);
 con.addParticles(ParticleGenerator::generateParticleContainer({0.5,0.5,0.5},
  {2,2,1},1.0,2.0,{0.0,0.0,0.0},brown).getParticles());
 EXPECT_TRUE(ParticleContainer::cont_sem_eq(con,cube2));

}