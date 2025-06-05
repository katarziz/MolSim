//
// Created by cpsch on 02.06.2025.
//

#include "../io/XMLReader.h"

#include <spdlog/spdlog.h>
#include "../objects/ParticleGenerator.h"
#include "../MolSim.h"
#include <iostream>
#include "input.h"
using namespace std;

XMLReader::XMLReader() = default;

XMLReader::~XMLReader() = default;

void XMLReader::readFile(ParticleContainer &particles, const char *filename)
{   SPDLOG_LOGGER_DEBUG(spdlog::get("default"), "Started reading file {}", filename);
    try
    {
        unique_ptr<Molsim_Input> input =Molsim_Input_ (filename);
        Parameters param=input->Parameters();
        Particles particle_in=input->Particles();
        delta_t=param.delta_t();
        end_time=param.t_end();
        out_name=param.output_name().c_str();
        out_freq=param.output_frequency();
        r_c=param.cutoff();
        box_dim={param.box_size().x_size(),param.box_size().y_size(),param.box_size().z_size()};
        cell_num={param.number_cells().x_number(),param.number_cells().y_number(),param.number_cells().z_number()};
        bounds={strcmp(param.boundary_conditions().top_bound().c_str(), "ref")==0?1:0,
            strcmp(param.boundary_conditions().right_bound().c_str(), "ref")==0?1:0,
            strcmp(param.boundary_conditions().bottom_bound().c_str(), "ref")==0?1:0,
            strcmp(param.boundary_conditions().left_bound().c_str(), "ref")==0?1:0};

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

        SPDLOG_LOGGER_INFO(spdlog::get("default"),
            "Simulation Parameters:\nOutput Writer: {}     Output Name: {}    Output Frequency: {} \nDelta t = {}    End t = {}    Force: {} "
            ,param.writer().c_str(), out_name,out_freq, delta_t, end_time,param.force().c_str());
        SPDLOG_LOGGER_INFO(spdlog::get("default"),"Cutoff Radius = {}    Box Dimensions = ({}, {}, {})\nBoundary Conditions:\nTop: {}    Right: {}    Bottom: {}    Left:{}"
            ,param.cutoff(), box_dim[0],box_dim[1],box_dim[2],param.boundary_conditions().top_bound().c_str(),
            param.boundary_conditions().right_bound().c_str(),param.boundary_conditions().bottom_bound().c_str(),
            param.boundary_conditions().right_bound().c_str());


        for (auto cube=particle_in.cuboid().begin();cube!=particle_in.cuboid().end();++cube)
        {
            std::array<double,3> x={cube->base_coordinates().x_coordinate(),cube->base_coordinates().y_coordinate(),cube->base_coordinates().z_coordinate()};
            std::array<int64_t,3> n={cube->number_particles().x_number(),cube->number_particles().y_number(),cube->number_particles().z_number()};
            std::array<double,3> v={cube->velocity().x_velocity(),cube->velocity().y_velocity(),cube->velocity().z_velocity()};
            ParticleGenerator::generateCube(particles,x,n,cube->spacing(),cube->mass(),v,cube->brownian_vel());
        }

        for (auto part=particle_in.particle().begin();part!=particle_in.particle().end();++part)
        {   std::array<double,3> x={part->position().x_coordinate(),part->position().y_coordinate(),part->position().z_coordinate()};
            std::array<double,3> v={part->velocity().x_velocity(),part->velocity().y_velocity(),part->velocity().z_velocity()};
            particles.addParticle(Particle(x,v,part->mass(),0));
        }
        for (auto disc=particle_in.disc().begin();disc!=particle_in.disc().end();++disc)
        {   std::array<double,3> x={disc->position().x_coordinate(),disc->position().y_coordinate(),disc->position().z_coordinate()};
            std::array<double,3> v={disc->velocity().x_velocity(),disc->velocity().y_velocity(),disc->velocity().z_velocity()};
            ParticleGenerator::generateDisc(particles, x, disc->radius(), disc->spacing(), disc->mass(), v, disc->brownian_vel());
        }
        SPDLOG_LOGGER_DEBUG(spdlog::get("default"), "Finished reading in Particles.", iteration);
    }
    catch (const xml_schema::exception& e)
    {
        cerr << e << endl;
    }
}