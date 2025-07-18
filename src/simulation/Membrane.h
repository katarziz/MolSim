//
// Created by cpsch on 30.06.2025.
//

#ifndef MEMBRANE_H
#define MEMBRANE_H
#include "LennardJones.h"
#include "utils/ArrayUtils.h"
class Membrane{
private:

    int offset;
    int size;
    int width;
    double k;
    double r_0;
    double r_0_root;
    std::array<double,3> F_up;
    std::vector<int> force_particles;

public:

    /**
     *
     * @param offset
     * @param size
     * @param width
     * @param k
     * @param r_0
     * @param F_up
     */
    Membrane(int offset, int size, int width, double k, double r_0,std::array<double,3> f,std::vector<int> f_part);

    [[nodiscard]] int get_offset() const
    {
        return offset;
    }
    void calculateF_Harm(Particle &i, Particle &j) const;
    void calculateF_Harm_Diag(Particle &i, Particle &j) const ;

    [[nodiscard]] std::vector<int> get_force_particles() const
    {
        return force_particles;
    }

    void set_offset(int offset)
    {
        this->offset = offset;
    }

    [[nodiscard]] int get_size() const
    {
        return size;
    }

    void set_size(int size)
    {
        this->size = size;
    }

    [[nodiscard]] int get_width() const
    {
        return width;
    }

    void set_width(int width)
    {
        this->width = width;
    }

    [[nodiscard]] std::array<double,3> get_f_up() const
    {
        return F_up;
    }

    void set_f_up(std::array<double,3>  f_up)
    {
        F_up = f_up;
    }

};
#endif //MEMBRANE_H