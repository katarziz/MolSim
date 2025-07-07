//
// Created by cpsch on 21.06.2025.
//

#include "ThermostatTest.h"

#include <cmath>
#include <simulation/Thermostat.h>
#include <gtest/gtest.h>

#include "io/input.h"
#include "objects/ParticleGenerator.h"

TEST(TempInit, ThermostatTest)
{ BasicParticleContainer particles=BasicParticleContainer();
  Thermostat thermostat=Thermostat();
  thermostat.setParams( 0,0,3);
  double temp_init=40;
  double f_i=std::sqrt(temp_init/1);
  ParticleGenerator::generateCube(particles,{0,0,0},{30,30,30},1,1,5,1,{0,0,0},0,3,f_i);
  double temp=thermostat.calculateTemp(particles);
  EXPECT_LE(abs(temp-temp_init),0.5);
}
TEST(ImmediateScalingTest,ThermostatTests)
{
  BasicParticleContainer particles=BasicParticleContainer();
  Thermostat thermostat=Thermostat();
  thermostat.setParams( 60,INFINITY,3);
  double temp_init=40;
  double f_i=std::sqrt(temp_init/1);
  ParticleGenerator::generateCube(particles,{0,0,0},{3,3,3},1,1,5,1,{0,0,0},0,3,f_i);
  double temp=thermostat.calculateTemp(particles);
  thermostat.scaleV(&particles);
  temp=thermostat.calculateTemp(particles);
  EXPECT_FLOAT_EQ(temp,60);
}

TEST(HeatingTest,ThermostatTests)
{
  BasicParticleContainer particles=BasicParticleContainer();
  Thermostat thermostat=Thermostat();
  double t_targ=60;
  double delta_temp=5;
  double temp_init=40;
  int dim=3;
  thermostat.setParams( t_targ,delta_temp,3);
  double f_i=std::sqrt(temp_init/1);
  ParticleGenerator::generateCube(particles,{0,0,0},{30,30,30},1,1,5,1,{0,0,0},0,3,f_i);
  double temp=thermostat.calculateTemp(particles);
  temp_init=temp;
  for (int i=0;i<=(t_targ-temp_init);i+=delta_temp)
    {
      temp=thermostat.calculateTemp(particles);
      EXPECT_FLOAT_EQ(temp,temp_init+i);
      thermostat.scaleV(&particles);
     }
    temp=thermostat.calculateTemp(particles);
    EXPECT_FLOAT_EQ(temp,t_targ);
}

TEST(CoolingTest,ThermostatTests)
{
  BasicParticleContainer particles=BasicParticleContainer();
  Thermostat thermostat=Thermostat();
  double t_targ=40;
  double delta_temp=5;
  double temp_init=60;
  int dim=3;
  thermostat.setParams( t_targ,delta_temp,3);
  double f_i=std::sqrt(temp_init/1);
  ParticleGenerator::generateCube(particles,{0,0,0},{30,30,30},1,1,5,1,{0,0,0},0,dim,f_i);
  double temp=thermostat.calculateTemp(particles);
  temp_init=temp;
  for (int i=0;i<=abs(t_targ-temp_init);i+=delta_temp)
  {
    temp=thermostat.calculateTemp(particles);
    EXPECT_FLOAT_EQ(temp,temp_init-i);
    thermostat.scaleV(&particles);
  }
  temp=thermostat.calculateTemp(particles);
  EXPECT_FLOAT_EQ(temp,t_targ);
}
TEST(MaintainingTest,ThermostatTests)
{
  BasicParticleContainer particles=BasicParticleContainer();
  Thermostat thermostat=Thermostat();
  double temp_init=40;
  double temp_target=temp_init;
  double f_i=std::sqrt(temp_init/1);
  thermostat.setParams( temp_target,INFINITY,3);
  ParticleGenerator::generateCube(particles,{0,0,0},{30,30,30},1,1,5,1,{0,0,0},0,3,f_i);
  double temp=thermostat.calculateTemp(particles);
  temp_init=temp;
  for (auto & particle : particles)
  {
    particle.setV({particle.getV()[0]+1,particle.getV()[1]+1,particle.getV()[2]+1});
  }
  double temp_test=thermostat.calculateTemp(particles);
  thermostat.scaleV(&particles);
  temp=thermostat.calculateTemp(particles);
  EXPECT_LT(temp,temp_test);
  EXPECT_GE(temp,temp_target);

}

