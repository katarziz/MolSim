//
// Created by cpsch on 02.06.2025.
//

#include "../io/XMLReader.h"

#include <spdlog/spdlog.h>
#include "../objects/ParticleGenerator.h"
#include "../MolSim.h"
#include <iostream>

#include "FileReader.h"
#include "input.h"
using namespace std;

XMLReader::XMLReader() = default;

XMLReader::~XMLReader() = default;

void XMLReader::readFile(ParticleContainer *particles, const char *filename)
{   SPDLOG_LOGGER_DEBUG(spdlog::get("default"), "Started reading file {}", filename);
    try
    {
        //read out XML Input from input file  filename
        unique_ptr<Molsim_Input> input =Molsim_Input_ (filename);
        Parameters param=input->Parameters();
        Particles particle_in=input->Particles();
        ThermostatParams therm=input->ThermostatParams();
        readoutParams(param);

        //Log basic simulation parameters
        SPDLOG_LOGGER_INFO(spdlog::get("default"),
            "Simulation Parameters:\n\\"
            "Output Writer: {}\tOutput Name: {}\tOutput Frequency: {}\tCheckpoint Frequency: {}\n\\"
            "Delta t = {}\tEnd t = {}\tForce: {}\tGravitation: {}",
            param.writer().c_str(), out_name, out_freq, checkpoint_freq, delta_t, end_time,
            param.force().c_str(), param.grav());

        //Set up initialization of Particle Container depending on param container
        //! int giving the number of dimensions based on the domain /box size
        int dim;
        if (param.box_size().z_size()==0)
        {
            dim=2;
        }else
        {
            dim=3;
        }

        f_therm=therm.f_therm();

        thermostat.setParams(therm.T_targ(), therm.delta_T(), dim);

        //! double representing the cutoff radius. Default:3.0
            double r_c=param.cutoff();

            //! array of three doubles representing the domain size.
            if (dim==2)
            {
                box_dim = {param.box_size().x_size(), param.box_size().y_size(), 1};
            }else
            {
              box_dim = {param.box_size().x_size(), param.box_size().y_size(), param.box_size().z_size()};
            }


        //! array of three ints representing the number of cells. Default:1x1x1
            cell_num={static_cast<int64_t>(std::floor(box_dim[0] / r_c)),static_cast<int64_t>(ceil(box_dim[1]/r_c)),static_cast<int64_t>(ceil(box_dim[2]/r_c))};


            //! array of six ints representing the boundary conditions: left, bottom, back, right, top, front
            // outflow:0 ("out"), reflecting:1 ("ref"), periodic_2 ("per")
            //Default:outflow

            std::array<int,6>boundaries={
                parse_bound(param.boundary_conditions().left_bound().c_str()),
                parse_bound(param.boundary_conditions().bottom_bound().c_str()),
                parse_bound(param.boundary_conditions().back_bound().c_str()),
                parse_bound(param.boundary_conditions().right_bound().c_str()),
                parse_bound(param.boundary_conditions().top_bound().c_str()),
                parse_bound(param.boundary_conditions().front_bound().c_str()),
                };
            if (!check_bounds(boundaries))
            {
                cerr << "Periodic bounds must be set in pairs tp/bottom, left/right, front/back" << endl;
                exit(1);
            } else
            {
                bounds=boundaries;
            }


            //Log Linked Cell Container Parameters
            SPDLOG_LOGGER_INFO(spdlog::get("default"),
                "Cutoff Radius = {}\tDomain Dimensions = ({}, {}, {})\n\\"
                "Boundary Conditions: (Left: {}, Bottom: {}, Back: {}, Right: {}, Top: {}, Front: {})",
                param.cutoff(), box_dim[0], box_dim[1], box_dim[2],
                param.boundary_conditions().left_bound().c_str(), param.boundary_conditions().bottom_bound().c_str(),
                param.boundary_conditions().back_bound().c_str(), param.boundary_conditions().right_bound().c_str(),
                param.boundary_conditions().top_bound().c_str(), param.boundary_conditions().front_bound().c_str());

        if (particle_in.checkpoint().begin()!=particle_in.checkpoint().end())
        {
            FileReader::readCheckpoint(start_time, *particles, particle_in.checkpoint().begin()->checkpoint_file().data());
            SPDLOG_LOGGER_INFO(spdlog::get("default"),"Checkpoint file loaded. continuing at time {}",start_time);
        }

        //Reading in all Particle Cubes
        readInCubes(particle_in,*particles,dim,therm.T_init());

        //Reading in all single Particles
        readInDiscs(particle_in,*particles,dim,therm.T_init());

        //Reading in all Particle discs
        readInParticles(particle_in,*particles,dim,therm.T_init());


        SPDLOG_LOGGER_DEBUG(spdlog::get("default"), "Finished reading in Particles.", iteration);
    }
    catch (const xml_schema::exception& e)
    {
        cerr << e << endl;
    }
}

bool XMLReader::check_bounds(const std::array<int, 6>& bounds)
{
    if ((bounds[0]==2||bounds[3]==2)&&bounds[0]!=bounds[3])
    {
        return false;
    }
    else if ((bounds[1]==2||bounds[4]==2)&&bounds[1]!=bounds[4])
    {
        return false;
    } else if ((bounds[2]==2||bounds[5]==2)&&bounds[2]!=bounds[5])
    {
        return false;
    }
    return true;
}

void XMLReader::readoutParams(Parameters& param)
{
    //assign Parameters given in the XML
    delta_t=param.delta_t();
    grav=param.grav();
    end_time=param.t_end();
    out_name=param.output_name().c_str();
    out_freq=param.output_frequency();
    checkpoint_freq=param.checkpoint_freq();

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
}
void XMLReader::readInCubes(Particles &particle_in,ParticleContainer &particles, int dim, double T_init)
{
    for (auto & cube : particle_in.cuboid())
    {   double f_i = sqrt(T_init / cube.mass());
        std::array<double,3> x={cube.base_coordinates().x_coordinate(),cube.base_coordinates().y_coordinate(),cube.base_coordinates().z_coordinate()};
        std::array<int64_t,3> n={cube.number_particles().x_number(),cube.number_particles().y_number(),cube.number_particles().z_number()};
        std::array<double,3> v={cube.velocity().x_velocity(),cube.velocity().y_velocity(),cube.velocity().z_velocity()};
        ParticleGenerator::generateCube(particles,x,n,cube.spacing(),cube.mass(),cube.eps(),cube.sigma(),
            v,cube.type(), dim,f_i);
    }
}
void XMLReader::readInDiscs(Particles &particle_in,ParticleContainer &particles, int dim, double T_init)
{
    for (auto & disc : particle_in.disc())
    {   double f_i = sqrt(T_init / disc.mass());
        std::array<double,3> x={disc.position().x_coordinate(),disc.position().y_coordinate(),disc.position().z_coordinate()};
        std::array<double,3> v={disc.velocity().x_velocity(),disc.velocity().y_velocity(),disc.velocity().z_velocity()};
        ParticleGenerator::generateDisc(particles, x, disc.radius(), disc.spacing(), disc.mass(),
                                        disc.eps(),disc.sigma(), v,disc.type(), dim,f_i);
    }

}
void XMLReader::readInParticles(Particles &particle_in,ParticleContainer &particles, int dim, double T_init)
{
    for (auto & part : particle_in.particle())
    {   double f_i=sqrt(T_init/part.mass());
        std::array<double,3> x={part.position().x_coordinate(),part.position().y_coordinate(),part.position().z_coordinate()};
        std::array<double,3> v={part.velocity().x_velocity(),part.velocity().y_velocity(),part.velocity().z_velocity()};
        v=ParticleGenerator::generateInitVel(v,dim,f_i);
        particles.addParticle(Particle(x,v,part.mass(),part.eps(), part.sigma(),part.type(),0));
    }
}

int XMLReader::parse_bound(const std::string& bound)
{
    if (strcmp(bound.c_str(), "ref")==0)
    {
     return 1;
    } else if (strcmp(bound.c_str(), "per")==0)
    {
        return 2;
    } else
    {
        return 0;
    }
}

