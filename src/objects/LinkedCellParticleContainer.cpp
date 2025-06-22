//
// Created by mawinkle on 6/5/25.
//

#include "LinkedCellParticleContainer.h"

#include <cmath>
#include <spdlog/spdlog.h>

#include "simulation/LennardJones.h"
#include "utils/ArrayUtils.h"

LinkedCellParticleContainer::LinkedCellParticleContainer(const std::array<double, 3> &box_size_arg,
                                                         const std::array<int64_t, 3> &cell_number_arg,
                                                         const double &cutoff_arg,
                                                         const std::array<int, 4> &bounds_arg) {
    box_size = box_size_arg;
    cell_number = cell_number_arg;
    const int64_t size =
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
}

LinkedCellParticleContainer::LinkedCellParticleContainer(const std::vector<Particle> &particles_arg,
                                                         const std::array<double, 3> &box_size_arg,
                                                         const std::array<int64_t, 3> &cell_number_arg,
                                                         const double &cutoff_arg,
                                                         const std::array<int, 4> &bounds_arg) {
    box_size = box_size_arg;
    cell_number = cell_number_arg;
    const int64_t size =
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
}

void LinkedCellParticleContainer::setParameters(const std::array<double, 3> &box_size_arg,
                                                const std::array<int64_t, 3> &cell_number_arg,
                                                const double &cutoff_arg,
                                                const std::array<int, 4> &bounds_arg) {
    box_size = box_size_arg;
    cell_number = cell_number_arg;
    const int64_t size =
            cell_number[0] *
            cell_number[1] *
            cell_number[2];
    cells = std::vector<std::vector<int> >(size);
    for (int i = 0; i < size; i++) {
        cells[i] = std::vector<int>(size);
    }
    cutoff = cutoff_arg;
    boundary_conditions = bounds_arg;
}

void LinkedCellParticleContainer::addParticle(const Particle &p) {
    particles.push_back(p);
    // std::array<int, 3> indices = {0,0,0};
    // for (int k = 0; k < 3; ++k) {
    //     indices[k] = std::floor(p.getX()[k]+0.5*box_size[k])/(box_size[k]/cell_number[k]);
    // }
    // cells[indices[0] + indices[1]*cell_number[0] + indices[2]*cell_number[0]*cell_number[1]].push_back(particles.size()-1);
}

void LinkedCellParticleContainer::addParticles(const std::vector<Particle> &p) {
    for (const auto &particle: p) {
        addParticle(particle);
    }
}

int LinkedCellParticleContainer::size() const {
    int size = 0;
    for (auto &p : particles) {
        if (p.getState() == 0) {
            size++;
        }
    }
    return size;
}

const std::vector<Particle> &LinkedCellParticleContainer::getParticles() const {
    return particles;
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

void LinkedCellParticleContainer::applyUnary(const std::function<void(Particle &i)> fun) {
    for (auto &particle: particles) {
        // skip if deactivated
        if (particle.getState() == 1) {
            continue;
        }
        fun(particle);
    }
}

void LinkedCellParticleContainer::applyBinaryToCells(const std::function<void(Particle &i, Particle &j)> fun,
                                                     std::vector<int> &i_cell, std::vector<int> &j_cell) {
    for (auto i = 0; i < i_cell.size(); ++i) {
        for (auto j = 0; j < j_cell.size(); ++j) {
            fun(particles.at(i_cell[i]), particles.at(j_cell[j]));
        }
    }
}

void LinkedCellParticleContainer::applyBinary(const std::function<void(Particle &i, Particle &j)> fun) {
    for (int i_x = 0; i_x < cell_number[0]; ++i_x) {
        for (int i_y = 0; i_y < cell_number[1]; ++i_y) {
            for (int i_z = 0; i_z < cell_number[2]; ++i_z) {
                const int index = i_x + i_y * cell_number[0] + i_z * cell_number[0] * cell_number[1];
                auto &i_cell = cells[index];
                // calculations within i_cell to avoid duplicate calculations.
                for (auto i = 0; i < i_cell.size(); ++i) {
                    for (auto j = 0; j < i; ++j) {
                        fun(particles.at(i_cell[i]), particles.at(i_cell[j]));
                    }
                }
                // TODO is this iteration good?
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
                            auto &j_cell = cells[j_x + j_y * cell_number[0] + j_z * cell_number[0] * cell_number[1]];
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
                        auto &j_cell = cells[j_x + j_y * cell_number[0] + j_z * cell_number[0] * cell_number[1]];
                        applyBinaryToCells(fun, i_cell, j_cell);
                    }
                }
                j_y = i_y;
                j_z = i_z - 1;
                if (j_x >= 0 && j_x < cell_number[0] &&
                    j_y >= 0 && j_y < cell_number[1] &&
                    j_z >= 0 && j_z < cell_number[2]) {
                    auto &j_cell = cells[j_x + j_y * cell_number[0] + j_z * cell_number[0] * cell_number[1]];
                    applyBinaryToCells(fun, i_cell, j_cell);
                }
            }
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
    cells = std::vector<std::vector<int>>(size);
    for (int i = 0; i < size; ++i) {
        cells[i] = std::vector<int>();
    }
    for (int i = 0; i < particles.size(); ++i) {
        Particle &p = particles[i];
        if (p.getState() == 1) {
            continue;
        }
        std::array<int, 3> indices = {0, 0, 0};
        for (int j = 0; j < 3; ++j) {
            indices[j] = std::floor(p.getX()[j] / (box_size[j] / cell_number[j]));
            // particles outside the domain are deactivated
            if (indices[j] < 0 || indices[j] >= cell_number[j]) {
                SPDLOG_LOGGER_INFO(spdlog::get("default"), "Particle at {},{},{} moved to halo.",
                                   p.getX()[0], p.getX()[1], p.getX()[2]);
                halo.push_back(i);
                p.setState(1);
                break;
            }
            // boundary conditions are applied to particles in the boundary
            if (indices[j] == 0 || indices[j] == cell_number[j] - 1) {
                // TODO this clearly only works for 2d simulations. 3d simulations need more boundaries.
                if (j == 2) {
                    continue;
                }
                SPDLOG_LOGGER_DEBUG(spdlog::get("default"), "Particle at {},{},{} detected in boundary.",
                                   p.getX()[0], p.getX()[1], p.getX()[2]);
                if (indices[j] == 0) {
                    if (boundary_conditions[j] == 1) {
                        // reflect Particle p at boundary j
                        reflect(p, j);
                    } else if (boundary_conditions[j] == 0) {
                        // outflow Particle p at boundary j
                        outflow(p);
                    }
                } else if (indices[j] == cell_number[j] - 1) {
                    if (boundary_conditions[j + 2] == 1) {
                        // reflect Particle p at boundary j + 2
                        reflect(p, j + 2);
                    } else if (boundary_conditions[j + 2] == 0) {
                        // outflow Particle p at boundary j + 2
                        outflow(p);
                    }
                }
            }
        }
        // if a particle is active, it is added back to the pool of particles.
        if (p.getState() == 0) {
            cells[indices[0] + indices[1] * cell_number[0] + indices[2] * cell_number[0] * cell_number[1]].push_back(i);
        }
    }
}

void LinkedCellParticleContainer::applyUnaryToBoundary(const std::function<void(Particle &i)> &fun) {
    for (int i = 0; i < cells.size(); ++i) {
        if (i < cell_number[0] || i >= cell_number[0] * (cell_number[1] - 1) || i % cell_number[0] == 0 || i %
            cell_number[0] == cell_number[0] - 1) {
            auto p = particles.at(i);
            SPDLOG_LOGGER_DEBUG(spdlog::get("default"), "Particle at {},{},{}. applied unary to boundary.",
                               p.getX()[0], p.getX()[1], p.getX()[2]);
            for (auto j = cells[i].begin(); j != cells[i].end(); ++j) {
                fun(particles.at(*j));
            }
        }
    }
}


void LinkedCellParticleContainer::applyUnaryToHalo(const std::function<void(Particle &i)> &fun) {
    for (auto i = halo.begin(); i != halo.end(); ++i) {
        SPDLOG_LOGGER_DEBUG(spdlog::get("default"), "Particle at {},{},{}. applied unary to halo.",
                           p.getX()[0], p.getX()[1], p.getX()[2]);
        fun(particles.at(*i));
    }
}

void LinkedCellParticleContainer::deleteHalo() {
    SPDLOG_LOGGER_DEBUG(spdlog::get("default"), "deleting halo.");
    applyUnaryToHalo([](Particle &i) {
        i.setState(1);
    });
}

void LinkedCellParticleContainer::outflow(Particle &p) {
    SPDLOG_LOGGER_INFO(spdlog::get("default"), "Particle at {},{},{} experienced outflow.",
                       p.getX()[0], p.getX()[1], p.getX()[2]);
    p.setState(1);
}

void LinkedCellParticleContainer::reflect(Particle &p, const int boundary) {
    SPDLOG_LOGGER_INFO(spdlog::get("default"), "Particle at {},{},{} experienced reflect.",
                       p.getX()[0], p.getX()[1], p.getX()[2]);
    std::array<double, 3> counter_particle_X = p.getX();
    if (boundary == 0) { // left
        counter_particle_X[0] = 0 - counter_particle_X[0];
    } else if (boundary == 1) { // bottom
        counter_particle_X[1] = 0 - counter_particle_X[1];
    } else if (boundary == 2) { // right
        counter_particle_X[0] = box_size[0] + (box_size[0] - counter_particle_X[0]);
    } else if (boundary == 3) { // top
        counter_particle_X[1] = box_size[1] + (box_size[1] - counter_particle_X[1]);
    }
    auto counter_particle = Particle(counter_particle_X, p.getV(), p.getM(), p.getType());
    calculateF_LJ(p, counter_particle, cutoff);
}
