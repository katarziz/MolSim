//
// Created by cpsch on 22.05.2025.
//

#include "ParticleGeneratorTest.h"
#include <gtest/gtest.h>



TEST(SimpleCube, ParticleGeneratorTests)
{
 ParticleContainer con= ParticleGenerator::generateCube({0.0,0.0,0.0},
  {2,2,2},1.0,1.0,{0.0,0.0,0.0},brown);
 EXPECT_TRUE(ParticleContainer::cont_sem_eq(con,cube1));
 for (auto cube_it=cube1.begin(); cube_it != cube1.end(); ++cube_it)
 {
  std::cout << cube_it->toString() << std::endl;
 }
 for (auto cont_it=con.begin(); cont_it != con.end(); ++cont_it)
 {
  std::cout << cont_it->toString()<< std::endl;
  EXPECT_TRUE(ParticleContainer::contains(cube1,*cont_it));
 }
}

TEST(TwoCubes, ParticleGeneratorTests)
{ ParticleContainer con= ParticleGenerator::generateCube({0.0,0.0,0.0},
 {2,2,2},1.0,1.0,{0.0,0.0,0.0},brown);
 con.addParticles(ParticleGenerator::generateCube({0.5,0.5,0.5},
  {2,2,1},1.0,2.0,{0.0,0.0,0.0},brown).getParticles());
 EXPECT_TRUE(ParticleContainer::cont_sem_eq(con,cube2));

}