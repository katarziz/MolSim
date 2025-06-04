//
// Created by cpsch on 02.06.2025.
//

#include "XMLReader.h"

#include <spdlog/spdlog.h>
#include "../particles/ParticleGenerator.h"
#include "../MolSim.h"
#include <iostream>
#include "input.h"
using namespace std;

XMLReader::XMLReader() = default;

XMLReader::~XMLReader() = default;

void XMLReader::readFile(ParticleContainer &particles, const char *filename)
{   try
    {
        unique_ptr<Molsim_Input> input =Molsim_Input_ (filename);
        Parameters param=input->Parameters();
        Particles particle_in=input->Particles();
        delta_t=param.delta_t();
        end_time=param.t_end();
        out_name=param.output_name().c_str();
        out_freq=param.output_frequency();
        if (strcmp(param.writer().c_str(), "xyz")==0)
        {   writer_flag=1;
        }else if (strcmp(param.writer().c_str(), "vtk")==0){
            writer_flag=0;
        }
        if (strcmp(param.force().c_str(), "lennard-jones")==0)
        {  force_flag=0;
        }else if (strcmp(param.force().c_str(), "newton")==0){
           force_flag=1;
        }
        int count=0;
        for (auto cube=particle_in.cuboid().begin();cube!=particle_in.cuboid().end();++cube)
        {   count++;

            std::array<double,3> x={cube->base_coordinates().x_coordinate(),cube->base_coordinates().y_coordinate(),cube->base_coordinates().z_coordinate()};
            std::array<int64_t,3> n={cube->number_particles().x_number(),cube->number_particles().y_number(),cube->number_particles().z_number()};
            std::array<double,3> v={cube->velocity().x_velocity(),cube->velocity().y_velocity(),cube->velocity().z_velocity()};
            particles.addParticles(ParticleGenerator::generateParticleContainer(x,n,cube->spacing(),cube->mass(),v,cube->brownian_vel()).getParticles());
        }
        for (auto part=particle_in.particle().begin();part!=particle_in.particle().end();++part)
        {   std::array<double,3> x={part->position().x_coordinate(),part->position().y_coordinate(),part->position().z_coordinate()};
            std::array<double,3> v={part->velocity().x_velocity(),part->velocity().y_velocity(),part->velocity().z_velocity()};
            particles.addParticle(Particle(x,v,part->mass(),0));
        }
    }
    catch (const xml_schema::exception& e)
    {
        cerr << e << endl;
    }
}