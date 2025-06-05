//
// Created by mawinkle on 6/5/25.
//

#pragma once

#include <vector>

#include "Particle.h"
#include "ParticleContainer.h"

class LinkedCellParticleContainer : public ParticleContainer {
private:
    std::array<double, 3> box_size;
    std::array<int64_t, 3> cell_number;
    std::vector<std::vector<int>> cells;
    double cutoff;
    const int boundary_width = 1;
    std::vector<Particle> particles;
public:
    LinkedCellParticleContainer(const std::array<double, 3> &box_size_arg, const std::array<int64_t, 3> &cell_number_arg,
        const double &cutoff_arg);

    LinkedCellParticleContainer(const std::vector<Particle> &particles_arg, const std::array<double, 3> &box_size_arg,
                                const std::array<int64_t, 3> &cell_number_arg, const double &cutoff_arg);

    void addParticle(const Particle &p) override;

    void addParticles(const std::vector<Particle> &p) override;

    const std::vector<Particle> &getParticles() const override;

    int size() const override;

    std::vector<Particle>::iterator begin() override;

    std::vector<Particle>::iterator end() override;

    std::vector<Particle>::const_iterator begin() const override;

    std::vector<Particle>::const_iterator end() const override;

    void applyUnary(std::function<void(Particle &i)> fun) override;

    void applyBinary(std::function<void(Particle &i, Particle &j)> fun) override;

    void updateCells();
};