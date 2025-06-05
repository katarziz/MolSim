//
// Created by mawinkle on 6/5/25.
//

#include "LinkedCellParticleContainer.h"

#include <cmath>
#include <spdlog/spdlog.h>

LinkedCellParticleContainer::LinkedCellParticleContainer(const std::array<double, 3> &box_size_arg,
                                                         const std::array<int, 3> &cell_number_arg,
                                                         const double &cutoff_arg) {
    particles = std::vector<Particle>();
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
}

LinkedCellParticleContainer::LinkedCellParticleContainer(const std::vector<Particle> &particles_arg,
                                                         const std::array<double, 3> &box_size_arg,
                                                         const std::array<int, 3> &cell_number_arg,
                                                         const double &cutoff_arg) {
    particles = particles_arg;
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
}


void LinkedCellParticleContainer::addParticle(const Particle &particle) {
    particles.push_back(particle);
}

void LinkedCellParticleContainer::addParticles(const std::vector<Particle> &particles_arg) {
    particles.insert(particles.end(), particles_arg.begin(), particles_arg.end());
}

int LinkedCellParticleContainer::size() const {
    return particles.size();
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
    for (auto i = particles.begin(); i != particles.end(); ++i) {
        fun(*i);
    }
}

void LinkedCellParticleContainer::applyBinary(const std::function<void(Particle &i, Particle &j)> fun) {
    for (int i_x = 0; i_x < cell_number[0]; ++i_x) {
        for (int i_y = 0; i_y < cell_number[1]; ++i_y) {
            for (int i_z = 0; i_z < cell_number[2]; ++i_z) {
                int index = i_x + i_y * cell_number[0] + i_z * cell_number[0] * cell_number[1];
                auto i_cell = cells[index];
                // calculations within i_cell to avoid duplicate calculations.
                for (auto i = i_cell.begin(); i != i_cell.end(); ++i) {
                    for (auto j = i_cell.begin(); j != i; ++j) {
                        fun(particles.at(*i), particles.at(*j));
                    }
                }
                // calculations for cells with higher x,y,z to avoid duplicate calculations.
                for (int j_x = i_x; j_x < cell_number[0] && j_x <= std::ceil(
                                        i_x + cutoff / (box_size[0] / cell_number[0])); ++j_x) {
                    for (int j_y = i_y; j_y < cell_number[1] && j_y <= std::ceil(
                                            i_y + cutoff / (box_size[1] / cell_number[1])); ++j_y) {
                        for (int j_z = i_z; j_z < cell_number[2] && j_z <= std::ceil(
                                                i_z + cutoff / (box_size[2] / cell_number[2])); ++j_z) {
                            auto j_cell = cells[j_x + j_y * cell_number[0] + j_z * cell_number[0] * cell_number[1]];
                            // skip the already computed i_cell
                            if (i_cell == j_cell) {
                                continue;
                            }
                            //calculations between i_cell and j_cell are guaranteed to be distinct
                            for (auto i = i_cell.begin(); i != i_cell.end(); ++i) {
                                for (auto j = j_cell.begin(); j != j_cell.end(); ++j) {
                                    fun(particles.at(*i), particles.at(*j));
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void LinkedCellParticleContainer::updateCells() {
    SPDLOG_LOGGER_DEBUG(spdlog::get("default"),"Number of Particles: {}",particles.size());
    // TODO can be handled more efficiently
    const int size =
            cell_number[0] *
            cell_number[1] *
            cell_number[2];
    cells = std::vector<std::vector<int>>(size);
    for (int i = 0; i < size; i++) {
        cells[i] = std::vector<int>();
    }
    for (int p_index = 0; p_index < particles.size(); ++p_index) {
        Particle p = particles.at(p_index);
        std::array<int, 3> p_cell = {
            static_cast<int>(std::floor((p.getX()[0]+box_size[0]/2)/(box_size[0]/cell_number[0]))),
            static_cast<int>(std::floor((p.getX()[1]+box_size[1]/2)/(box_size[1]/cell_number[1]))),
            static_cast<int>(std::floor((p.getX()[2]+box_size[2]/2)/(box_size[2]/cell_number[2]))),
        };
        // cells within the boundary region are erased from particles
        for (int i = 0; i < 3; ++i) {
            if (p_cell[i] < 0 /*+ boundary_width*/ || p_cell[i] >= cell_number[i] /*- boundary_width*/) {
                SPDLOG_LOGGER_INFO(spdlog::get("default"), "Particle at {},{},{} removed. coordinate[{}] was {}",p.getX()[0],p.getX()[1],p.getX()[2],i,p_cell[i]);
                particles.erase(particles.begin() + p_index);
                goto SKIP;
            }
        }
        cells[p_cell[0] + p_cell[1] * cell_number[0] + p_cell[2] * cell_number[1] * cell_number[2]].push_back(p_index);
    SKIP:;
    }
}
