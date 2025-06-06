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
    const int size =
            cell_number[0] *
            cell_number[1] *
            cell_number[2];
    cells = std::vector<std::vector<Particle*>>(size);
    for (int i = 0; i < size; i++) {
        cells[i] = std::vector<Particle*>();
    }
    particles = std::vector<Particle>();
    halo = std::vector<Particle>();
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
    const int size =
            cell_number[0] *
            cell_number[1] *
            cell_number[2];
    cells = std::vector<std::vector<Particle*>>(size);
    for (int i = 0; i < size; i++) {
        cells[i] = std::vector<Particle*>();
    }
    particles = particles_arg;
    for (auto p : particles) {
        std::array<int, 3> indices;
        for (int i = 0; i < 3; ++i) {
            indices[i] = std::floor(p.getX()[i]+0.5*box_size[i])/(box_size[i]/cell_number[i]);
        }
        cells[indices[0] + indices[1]*cell_number[0] + indices[2]*cell_number[0]*cell_number[1]].push_back(&p);
    }
    halo = std::vector<Particle>();
    cutoff = cutoff_arg;
    boundary_conditions = bounds_arg;
}

void LinkedCellParticleContainer::setParameters(const std::array<double, 3> &box_size_arg,
                                                const std::array<int64_t, 3> &cell_number_arg,
                                                const double &cutoff_arg,
                                                const std::array<int, 4> &bounds_arg) {
    box_size = box_size_arg;
    cell_number = cell_number_arg;
    const int size =
            cell_number[0] *
            cell_number[1] *
            cell_number[2];
    auto temp = std::vector<std::vector<Particle*>>(size);
    for (int i = 0; i < size; ++i) {
        temp[i] = std::vector<Particle*>();
    }
    for (int i = 0; i < cells.size(); ++i) {
        for (int j = 0; i < cells[i].size(); ++j) {
            std::array<int, 3> indices;
            for (int k = 0; k < 3; ++k) {
                indices[k] = std::floor(cells[i][j]->getX()[k]+0.5*box_size[k])/(box_size[k]/cell_number[k]);
            }
            temp[indices[0] + indices[1]*cell_number[0] + indices[2]*cell_number[0]*cell_number[1]].push_back(cells[i][j]);
        }
    }
    cells = temp;
    cutoff = cutoff_arg;
    boundary_conditions = bounds_arg;
}

void LinkedCellParticleContainer::addParticle(const Particle &p) {
    particles.push_back(p);
    std::array<int, 3> indices;
    for (int k = 0; k < 3; ++k) {
        indices[k] = std::floor(p.getX()[k]+0.5*box_size[k])/(box_size[k]/cell_number[k]);
    }
    cells[indices[0] + indices[1]*cell_number[0] + indices[2]*cell_number[0]*cell_number[1]].push_back(&*particles.end());
}

void LinkedCellParticleContainer::addParticles(const std::vector<Particle> &p) {
    for (auto particle : p) {
        addParticle(particle);
    }
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
                const int index = i_x + i_y * cell_number[0] + i_z * cell_number[0] * cell_number[1];
                auto i_cell = cells[index];
                // calculations within i_cell to avoid duplicate calculations.
                for (auto i = 0; i < i_cell.size(); ++i) {
                    for (auto j = 0; j < i; ++j) {
                        fun(*i_cell[i], *i_cell[j]);
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
                            for (auto i = 0; i < i_cell.size(); ++i) {
                                for (auto j = 0; j < j_cell.size(); ++j) {
                                    fun(*i_cell[i], *j_cell[j]);
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
    const int size =
        cell_number[0] *
        cell_number[1] *
        cell_number[2];
    cells = std::vector<std::vector<Particle*>>(size);
    for (int i = 0; i < size; ++i) {
        cells[i] = std::vector<Particle*>();
    }
    for (int i = 0; i < particles.size(); ++i) {
        Particle &p = particles[i];
        if (p.getX()[i]+box_size[i]/2 < 0 || p.getX()[i]+box_size[i] >= box_size[i]) {
            SPDLOG_LOGGER_INFO(spdlog::get("default"), "Particle at {},{},{} moved to halo.",
                               p.getX()[0], p.getX()[1], p.getX()[2]);
            halo.push_back(p);
            goto SKIP;
        }
        std::array<int, 3> indices;
        for (int k = 0; k < 3; ++k) {
            indices[k] = std::floor(p.getX()[k]+0.5*box_size[k])/(box_size[k]/cell_number[k]);
        }
        cells[indices[0] + indices[1]*cell_number[0] + indices[2]*cell_number[0]*cell_number[1]].push_back(&p);
        SKIP:;
    }
    for (auto p = halo.begin(); p != halo.end(); ++p) {
        particles.erase(std::find(particles.begin(), particles.end(), *p));
    }
    for (int i = 0; i < cells.size(); ++i) {
        if (i < cell_number[0]) {
            for (auto j = cells[i].begin(); j != cells[i].end(); ++j) {
                if (boundary_conditions[2] == 1) {
                    reflect(*j,2);
                } else if (boundary_conditions[2] == 0) {
                    outflow(*j);
                }
            }
        }
        if (i >= cell_number[0]*(cell_number[1]-1)) {
            for (auto j = cells[i].begin(); j != cells[i].end(); ++j) {
                if (boundary_conditions[0] == 1) {
                    reflect(*j,0);
                } else if (boundary_conditions[0] == 0) {
                    outflow(*j);
                }
            }
        }
        if (i % cell_number[0] == 0) {
            for (auto j = cells[i].begin(); j != cells[i].end(); ++j) {
                if (boundary_conditions[3] == 1) {
                    reflect(*j,3);
                } else if (boundary_conditions[3] == 0) {
                    outflow(*j);
                }
            }
        }
        if (i % cell_number[0] == cell_number[0] - 1) {
            for (auto j = cells[i].begin(); j != cells[i].end(); ++j) {
                if (boundary_conditions[1] == 1) {
                    reflect(*j,1);
                } else if (boundary_conditions[1] == 0) {
                    outflow(*j);
                }
            }
        }
    }
}

void LinkedCellParticleContainer::applyUnaryToBoundary(const std::function<void(Particle &i)> &fun) {
    for (int i = 0; i < cells.size(); ++i) {
        if (i < cell_number[0] || i >= cell_number[0]*(cell_number[1]-1) || i % cell_number[0] == 0 || i % cell_number[0] == cell_number[0] - 1) {
            for (auto j = cells[i].begin(); j != cells[i].end(); ++j) {
                fun(**j);
            }
        }
    }
}


void LinkedCellParticleContainer::applyUnaryToHalo(const std::function<void(Particle &i)> &fun) {
    for (auto i = halo.begin(); i != halo.end(); ++i) {
        fun(*i);
    }
}

void LinkedCellParticleContainer::deleteHalo() {
    halo = std::vector<Particle>();
}

void LinkedCellParticleContainer::outflow(const Particle *p) {
    particles.erase(std::find(particles.begin(), particles.end(), *p));
    std::array<int, 3> indices;
    for (int k = 0; k < 3; ++k) {
        indices[k] = std::floor(p->getX()[k]+0.5*box_size[k])/(box_size[k]/cell_number[k]);
    }
    auto cell = cells[indices[0] + indices[1]*cell_number[0] + indices[2]*cell_number[0]*cell_number[1]];
    cell.erase(std::find(cell.begin(), cell.end(), p));

}

void LinkedCellParticleContainer::reflect(Particle *p, const int boundary) {
    std::array<double, 3> counter_particle_X = p->getX();
    if (boundary == 0) {
        counter_particle_X[1] = box_size[1] + (box_size[1] - counter_particle_X[0]);
    } else if (boundary == 1) {
        counter_particle_X[0] = box_size[0] + (box_size[0] - counter_particle_X[0]);
    } else if (boundary == 2) {
        counter_particle_X[1] = 0 - counter_particle_X[1];
    } else if (boundary == 3) {
        counter_particle_X[0] = 0 - counter_particle_X[0];
    }
    auto counter_particle = Particle(counter_particle_X, p->getV(), p->getM(), p->getType());
    calculateF_LJ(*p, counter_particle);
}
