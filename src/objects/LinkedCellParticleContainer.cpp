//
// Created by mawinkle on 6/5/25.
//

#include "LinkedCellParticleContainer.h"

#include <cmath>
#include <fstream>
#include <spdlog/spdlog.h>
#include <omp.h>

#include "simulation/LennardJones.h"
#include "utils/ArrayUtils.h"


LinkedCellParticleContainer::LinkedCellParticleContainer(const std::array<double, 3> &box_size_arg,
                                                         const std::array<int, 3> &cell_number_arg,
                                                         const double &cutoff_arg,
                                                         const std::array<int, 6> &bounds_arg) {
    box_size = box_size_arg;
    //What is box size?
    cell_number = cell_number_arg;
    const int size =
            cell_number[0] *
            cell_number[1] *
            cell_number[2];
    cells = std::vector<std::vector<int> >(size);
    for (int i = 0; i < size; i++) {
        cells[i] = std::vector<int>();
    }
    particles = std::vector<Particle>();
    boundary = std::vector<int>();
    halo = std::vector<int>();
    cutoff = cutoff_arg;
    boundary_conditions = bounds_arg;
    membranes={};
}

LinkedCellParticleContainer::LinkedCellParticleContainer(const std::vector<Particle> &particles_arg,
                                                         const std::array<double, 3> &box_size_arg,
                                                         const std::array<int, 3> &cell_number_arg,
                                                         const double &cutoff_arg,
                                                         const std::array<int, 6> &bounds_arg) {
    box_size = box_size_arg;
    cell_number = cell_number_arg;
    const int size =
            cell_number[0] *
            cell_number[1] *
            cell_number[2];
    cells = std::vector<std::vector<int> >(size);
    for (int i = 0; i < size; i++) {
        cells[i] = std::vector<int>();
    }
    particles = particles_arg;
    // particles are not assigned to the correct cells until updateCells() is called
    boundary = std::vector<int>();
    halo = std::vector<int>();
    cutoff = cutoff_arg;
    boundary_conditions = bounds_arg;
    membranes={};
}



void LinkedCellParticleContainer::setParameters(const std::array<double, 3> &box_size_arg,
                                                const std::array<int, 3> &cell_number_arg,
                                                const double &cutoff_arg,
                                                const std::array<int, 6> &bounds_arg) {
    box_size = box_size_arg;
    cell_number = cell_number_arg;
    const int size =
            cell_number[0] *
            cell_number[1] *
            cell_number[2];
    cells = std::vector<std::vector<int> >(size);
    for (int i = 0; i < size; i++) {
        cells[i] = std::vector<int>();
    }
    cutoff = cutoff_arg;
    boundary_conditions = bounds_arg;
}

void LinkedCellParticleContainer::setOMPStrategy(const int &omp_strategy_arg) {
    omp_strategy = omp_strategy_arg;
}


void LinkedCellParticleContainer::addParticle(const Particle &p) {
    particles.push_back(p);
}

void LinkedCellParticleContainer::addParticles(const std::vector<Particle> &p) {
    for (const auto &particle: p) {
        addParticle(particle);
    }
}

int LinkedCellParticleContainer::size() const {
    int size = 0;
    for (auto &p: particles) {
        if ((p.state & 1) != 1) {
            size++;
        }
    }
    return size;
}

const std::vector<Particle> &LinkedCellParticleContainer::getParticles() const {
    return particles;
}

void LinkedCellParticleContainer::addMembrane(Membrane &mem)
{
    membranes.push_back(mem);
}

const std::vector<Membrane> &LinkedCellParticleContainer::getMembranes() const
{
    return membranes;
}

std::vector<Particle>::iterator LinkedCellParticleContainer::begin() {
    return particles.begin();
}

std::vector<Particle>::iterator LinkedCellParticleContainer::end() {
    return particles.end();
}

std::vector<Particle>::const_iterator LinkedCellParticleContainer::begin() const {
    return particles.cbegin();
}

std::vector<Particle>::const_iterator LinkedCellParticleContainer::end() const {
    return particles.cend();
}

void LinkedCellParticleContainer::applyUnary(const std::function<void(Particle &i)> &fun) {
    for (auto &particle: particles) {
        // skip if deactivated
        if ((particle.state & 1) == 1) {
            continue;
        }
        fun(particle);
    }
}

inline int LinkedCellParticleContainer::calcIndex(const int &i_x, const int &i_y, const int &i_z) const {
    return i_x + i_y * cell_number[0] + i_z * cell_number[0] * cell_number[1];
}


void LinkedCellParticleContainer::applyBinaryToCells(const std::function<void(Particle &i, Particle &j)> &fun,
                                                     const std::vector<int> &i_cell, const std::vector<int> &j_cell) {
    for (unsigned int i = 0; i < i_cell.size(); ++i) {
        for (unsigned int j = 0; j < j_cell.size(); ++j) {
            fun(particles.at(i_cell[i]), particles.at(j_cell[j]));
        }
    }
}

void LinkedCellParticleContainer::applyBinaryToNeighbors(const std::function<void(Particle &i, Particle &j)> &fun,
                                                         const int &i_x, const int &i_y, const int &i_z, const std::vector<int> &i_cell) {
    // the immediate and diagonal neighbors of i_cell are 26.
    // to avoid calculating twice, only one side of each pair of neighbors is used for the calculation.
    // a pair is such, that fun(a,a+offset) is the same as fun(b-offset,b) or fun(b,b-offset)
    // we only need to calculate either +offset or -offset.
    // were one to replace j = i - 1 with j = i + 1, this would calculate the other half.
    int j_x = i_x - 1, j_y, j_z;
    for (j_y = i_y - 1; j_y < i_y + 2; ++j_y) {
        for (j_z = i_z - 1; j_z < i_z + 2; ++j_z) {
            if (j_x >= 0 && j_x < cell_number[0] &&
                j_y >= 0 && j_y < cell_number[1] &&
                j_z >= 0 && j_z < cell_number[2]) {
                auto &j_cell = cells[calcIndex(j_x, j_y, j_z)];
                applyBinaryToCells(fun, i_cell, j_cell);
            }
        }
    }
    j_x = i_x;
    j_y = i_y - 1;
    for (j_z = i_z - 1; j_z < i_z + 2; ++j_z) {
        if (j_x >= 0 && j_x < cell_number[0] &&
            j_y >= 0 && j_y < cell_number[1] &&
            j_z >= 0 && j_z < cell_number[2]) {
            auto &j_cell = cells[calcIndex(j_x, j_y, j_z)];
            applyBinaryToCells(fun, i_cell, j_cell);
        }
    }
    j_y = i_y;
    j_z = i_z - 1;
    if (j_x >= 0 && j_x < cell_number[0] &&
        j_y >= 0 && j_y < cell_number[1] &&
        j_z >= 0 && j_z < cell_number[2]) {
        auto &j_cell = cells[calcIndex(j_x, j_y, j_z)];
        applyBinaryToCells(fun, i_cell, j_cell);
    }
}

void LinkedCellParticleContainer::applyBinary(const std::function<void(Particle &i, Particle &j)> &fun) {
    if (omp_strategy < 2) {
        for (int even = 0; even < 2; ++even) {
#ifdef _OPENMP
#pragma omp parallel for schedule(dynamic) if(omp_strategy == 1)
#endif
            for (int i_x = even; i_x < cell_number[0]; i_x += 2) {
                for (int i_y = 0; i_y < cell_number[1]; ++i_y) {
                    for (int i_z = 0; i_z < cell_number[2]; ++i_z) {
                        auto &i_cell = cells[calcIndex(i_x, i_y, i_z)];
                        // calculations within i_cell to avoid duplicate calculations.
                        for (unsigned int i = 0; i < i_cell.size(); ++i) {
                            for (unsigned int j = 0; j < i; ++j) {
                                fun(particles.at(i_cell[i]), particles.at(i_cell[j]));
                            }
                        }
                        applyBinaryToNeighbors(fun, i_x, i_y, i_z, i_cell);
                    }
                }
            }
        }
    } else {
        for (int color = 0; color < 18; ++color) {
#ifdef _OPENMP
#pragma omp parallel for collapse(3) schedule(dynamic)
#endif
            for (int i_x = color & 1; i_x < cell_number[0]; i_x += 2) {
                for (int i_y = (color >> 1) % 3; i_y < cell_number[1]; i_y += 3) {
                    for (int i_z = (color / 6) % 3; i_z < cell_number[2]; i_z += 3) {
                        auto &i_cell = cells[calcIndex(i_x, i_y, i_z)];
                        // calculations within i_cell to avoid duplicate calculations.
                        for (unsigned int i = 0; i < i_cell.size(); ++i) {
                            for (unsigned int j = 0; j < i; ++j) {
                                fun(particles.at(i_cell[i]), particles.at(i_cell[j]));
                            }
                        }
                        applyBinaryToNeighbors(fun, i_x, i_y, i_z, i_cell);
                    }
                }
            }
        }
    }
}

//TODO: Make Main Force not Apply to Membrane amongst itself (??? )and All Forces not apply on fixed Particles!!
/**
 *
 * @param mem
 * @param fun
 */
void LinkedCellParticleContainer::applyUnarytoMembrane(const Membrane &mem, const std::function<void(Particle &i)> & fun)
{
    for (auto i=mem.get_offset();i<mem.get_offset()+mem.get_size();++i)
    {
        fun(particles[i]);
    }
}

void LinkedCellParticleContainer::applyPerpForce(const Membrane &mem)
{
    for (int i=0;i<mem.get_force_particles().size();++i)
    {
        particles[mem.get_force_particles()[i]].f=particles[mem.get_force_particles()[i]].f+mem.get_f_up();
    }
}
//TODO: What if pieces of Membrane are marked disabled???
//TODO: Parallelize Rows??
void LinkedCellParticleContainer::applyMembraneForces(const Membrane& mem)
{
    int begin = mem.get_offset();
    int end = mem.get_offset() + mem.get_size();
    int width = mem.get_width();
    //TODO: Check conditions & Decide wether to keep diag functions...
    for (auto i = begin; i < end; ++i)
    {
        if (i + 1 < end && (i - begin) / width == (i + 1 - begin) / width)
        {
            mem.calculateF_Harm(particles[i], particles[i + 1]);
        }
        if (i + width < end)
        {
            mem.calculateF_Harm(particles[i], particles[i + width]);
        }
        if (i + width + 1 < end && (i - begin) / width + 1 == (i + width + 1 - begin) / width)
        {
            mem.calculateF_Harm_Diag(particles[i], particles[i + width + 1]);
        }
        if (i + width - 1 < end && (i - begin) / width + 1 == (i + width - 1 - begin) / width)
        {
            mem.calculateF_Harm_Diag(particles[i], particles[i + width - 1]);
        }
    }
}



void LinkedCellParticleContainer::updateCells() {
    // cells is cleared by being reinitialized and particles are assigned the correct cell.
    // this is resource intensive, but more efficient than removing and adding a Particle each time they change cells.
    const int64_t size =
            cell_number[0] *
            cell_number[1] *
            cell_number[2];
    if (cells.size() != size) {
        cells = std::vector<std::vector<int> >(size);
        for (int i = 0; i < size; ++i) {
            cells[i] = std::vector<int>();
        }
    } else {
        for (int i = 0; i < size; ++i) {
            cells[i].clear();
        }
    }
    boundary.clear();
    for (int i = 0; i < particles.size(); ++i) {
        Particle &p = particles[i];
        if ((p.state & 1)  == 1) {
            continue;
        }
        bool in_boundary = false;
        std::array<int, 3> indices = {0, 0, 0};
        for (int j = 0; j < 3; ++j) {
            indices[j] = std::floor(p.x[j] / (box_size[j] / cell_number[j]));
            // particles outside the domain are deactivated
            if (indices[j] < 0 || indices[j] >= cell_number[j]) {
                if (indices[j] < 0 && boundary_conditions[j] == 2) {
                    SPDLOG_LOGGER_DEBUG(spdlog::get("default"), "Particle at {},{},{} moved by periodic.",
                                        p.getX()[0], p.getX()[1], p.getX()[2]);
                    indices[j] += cell_number[j];
                    p.x[j] += box_size[j];
                } else if (indices[j] >= cell_number[j] && boundary_conditions[j + 3] == 2) {
                    SPDLOG_LOGGER_DEBUG(spdlog::get("default"), "Particle at {},{},{} moved by periodic.",
                                        p.getX()[0], p.getX()[1], p.getX()[2]);
                    indices[j] -= cell_number[j];
                    p.x[j] -= box_size[j];
                } else {
                    SPDLOG_LOGGER_INFO(spdlog::get("default"), "Particle at {},{},{} moved to halo.",
                                       p.getX()[0], p.getX()[1], p.getX()[2]);
                    halo.push_back(i);
                    p.state |= 1;
                    break;
                }
            }
            // boundary conditions are applied to particles in the boundary
            if ((indices[j] == 0 || indices[j] == cell_number[j] - 1) && cell_number[j] > 1 && !in_boundary) {
                boundary.push_back(i);
                in_boundary = true;
            }
        }
        // if a particle is active, it is added back to the pool of particles.
        if ((p.state & 1) == 0) {
            cells[calcIndex(indices[0], indices[1], indices[2])].push_back(i);
        }
    }
}

void LinkedCellParticleContainer::applyBoundaryConditions() {
    // this handling of reflective boundaries is particle based.
    // this means, that everything is calculated, regardless of location being corner/edge/face
    // on the other hand this is far more parallelizable and less complex
    for (auto p_index = boundary.begin(); p_index != boundary.end(); ++p_index) {
        Particle &p = particles.at(*p_index);
        std::array<int, 3> indices = {0, 0, 0};
        // precomputing the mirrored x values avoids recomputation and the need to differentiate x==0 and x==max
        std::array<double, 3> position = {0, 0, 0};
        int reflect = 0; // this will be a combined indicator for the boundary conditions.
        for (int dim = 0; dim < 3; ++dim) {
            indices[dim] = std::floor(p.x[dim] / (box_size[dim] / cell_number[dim]));
            if ((indices[dim] == 0 && boundary_conditions[dim] == 1) || (indices[dim] == cell_number[dim] - 1 && boundary_conditions[dim + 3] == 1)) {
                position[dim] = -p.x[dim] + 2 * box_size[dim] * (indices[dim] / (cell_number[dim] - 1));
                reflect |= 1 << dim;
            }
        }

        // combinations of reflective boundaries are ordered/executed based on Grey Code.
        // therefore all combinations are accounted for and only one value needs to be changed between computations.
        auto virtual_particle = Particle(p);
        if (reflect & 1) {
            virtual_particle.x[0] = position[0]; // 000 -> 100
            calculateF_LJ(p, virtual_particle, cutoff); // 100
            if (reflect & 2) {
                virtual_particle.x[1] = position[1]; // 100 -> 110
                calculateF_LJ(p, virtual_particle, cutoff); // 110
                virtual_particle.x[0] = p.x[0]; // 110 -> 010
                calculateF_LJ(p, virtual_particle, cutoff); // 010
                if (reflect & 4) {
                    virtual_particle.x[2] = position[2]; // 010 -> 011
                    calculateF_LJ(p, virtual_particle, cutoff); // 011
                    virtual_particle.x[0] = position[0]; // 011 -> 111
                    calculateF_LJ(p, virtual_particle, cutoff); // 111
                    virtual_particle.x[1] = p.x[1]; // 111 -> 101
                    calculateF_LJ(p, virtual_particle, cutoff); // 101
                    virtual_particle.x[0] = p.x[0]; // 101 -> 001
                    calculateF_LJ(p, virtual_particle, cutoff); // 001
                }
            } else {
                if (reflect & 4) {
                    virtual_particle.x[2] = position[2]; // 100 -> 101
                    calculateF_LJ(p, virtual_particle, cutoff); // 101
                    virtual_particle.x[0] = p.x[0]; // 101 -> 001
                    calculateF_LJ(p, virtual_particle, cutoff); // 001
                }
            }
        } else {
            if (reflect & 2) {
                virtual_particle.x[1] = position[1]; // 000 -> 010
                calculateF_LJ(p, virtual_particle, cutoff); // 010
                if (reflect & 4) {
                    virtual_particle.x[2] = position[2]; // 010 -> 011
                    calculateF_LJ(p, virtual_particle, cutoff); // 011
                    virtual_particle.x[1] = p.x[1]; // 011 -> 001
                    calculateF_LJ(p, virtual_particle, cutoff); // 001
                }
            } else {
                if (reflect & 4) {
                    virtual_particle.x[2] = position[2]; // 000 -> 010
                    calculateF_LJ(p, virtual_particle, cutoff); // 010
                }
            }
        }
    }

    if (boundary_conditions[0] != 2 && boundary_conditions[1] != 2 && boundary_conditions[2] != 2) {
        return;
    }
    std::array<int, 3> i = {0, 0, 0};
    for (i[0] = 0; i[0] < cell_number[0]; ++i[0]) {
        for (i[1] = 0; i[1] < cell_number[1]; ++i[1]) {
            for (i[2] = 0; i[2] < cell_number[2]; ++i[2]) {
                if (!(
                    ((i[0] == 0 || i[0] == cell_number[0] - 1) && boundary_conditions[0] == 2) ||
                    ((i[1] == 0 || i[1] == cell_number[1] - 1) && boundary_conditions[1] == 2) ||
                    ((i[2] == 0 || i[2] == cell_number[2] - 1) && boundary_conditions[2] == 2)
                    )) {
                    continue;
                }
                auto &i_cell = cells[calcIndex(i[0], i[1], i[2])];
                std::array<double, 3> displacement = {0, 0, 0};
                std::array<int, 3> displacement_index = {i[0], i[1], i[2]};
                for (int j = 0; j < 3; ++j) {
                    if (boundary_conditions[j] == 2) {
                        if (i[j] == 0) {
                            displacement[j] = box_size[j];
                            displacement_index[j] = cell_number[j];
                        }
                        if (i[j] == cell_number[j] - 1) {
                            displacement[j] = -box_size[j];
                            displacement_index[j] = 0;
                        }
                    }
                }
                for (auto i_index = i_cell.begin(); i_index != i_cell.end(); ++i_index) {
                    particles[*i_index].x = particles[*i_index].x + displacement;
                }
                applyBinaryToNeighbors([this](Particle &i_p, Particle&j_p){calculateF_LJ(i_p,j_p,cutoff);},
                    displacement_index[0], displacement_index[1], displacement_index[2], i_cell);
                for (auto i_index = i_cell.begin(); i_index != i_cell.end(); ++i_index) {
                    particles[*i_index].x = particles[*i_index].x - displacement;
                }
            }
        }
    }
}

void LinkedCellParticleContainer::applyUnaryToBoundary(const std::function<void(Particle &i)> &fun) {
    for (auto i = boundary.begin(); i != boundary.end(); ++i) {
        Particle &p = particles.at(*i);
        SPDLOG_LOGGER_DEBUG(spdlog::get("default"), "Particle at {},{},{}. applied unary to boundary.",
                            p.getX()[0], p.getX()[1], p.getX()[2]);
        fun(p);
    }
}


void LinkedCellParticleContainer::applyUnaryToHalo(const std::function<void(Particle &i)> &fun) {
    for (auto i = halo.begin(); i != halo.end(); ++i) {
        Particle &p = particles.at(*i);
        SPDLOG_LOGGER_DEBUG(spdlog::get("default"), "Particle at {},{},{}. applied unary to halo.",
                            p.getX()[0], p.getX()[1], p.getX()[2]);
        fun(p);
    }
}

void LinkedCellParticleContainer::deleteHalo() {
    applyUnaryToHalo([](Particle &i) {
        SPDLOG_LOGGER_DEBUG(spdlog::get("default"), "Particle at {},{},{}. applied unary to halo.",
                            i.getX()[0], i.getX()[1], i.getX()[2]);
        i.state = 1;
    });
}

void LinkedCellParticleContainer::writeState(std::ofstream &vel_prof, std::ofstream &N_prof)
{   std::array<int,50> N;
    std::array<std::array<double,3>,50> vel;
    for (auto i=0;i<N.size();++i)
    {
        N[i]=0;
        vel[i]={0,0,0};
    }
    for (auto p=particles.begin();p!=particles.end();++p)
    {   if ((p->state & 1)==1){continue;}
        int index=floor(p->x[0] / (box_size[0] / 50));
        N[index]++;
        vel[index]=vel[index]+p->v;
    }
    for (auto i=0;i<N.size();++i)
    {
        if (N[i]!=0){ vel[i]=(1.0/N[i])*vel[i];}
        if (i!=0)
        {
            vel_prof<<",";
            N_prof<<",";
        }
        vel_prof <<vel[i][0]<<","<<vel[i][1]<<","<<vel[i][2];
        N_prof << N[i] ;
    }
    vel_prof << std::endl;
    N_prof << std::endl;
}


