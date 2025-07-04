//
// Created by cpsch on 30.06.2025.
//

#ifndef MEMBRANE_H
#define MEMBRANE_H
#include "LennardJones.h"
#include "utils/ArrayUtils.h"
const double trunc_const=std::cbrt(2);
class Membrane{
private:

    int8_t offset;
    int8_t size;
    int8_t width;
    double k;
    double r_0;
    double r_0_root;
    double F_up;

    /**
 *
 * @param i
 * @param j
 */
void calculateF_Harm(Particle &i, Particle &j);
void calculateF_Harm_Diag(Particle &i, Particle &j);
void calculateF_LJ_Trunc(Particle &i, Particle &j);

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
    Membrane(int8_t offset, int8_t size,int8_t width, double k, double r_0, double F_up);
    /**
     *
     * @param i
     * @param j
     */
    void calculateMem_Force(Particle &i, Particle &j) const;
    /**
     *
     * @param i
     * @param j
     */
    void calculateMem_Force_Diag(Particle &i, Particle &j) const;

    [[nodiscard]] int8_t get_offset() const
    {
        return offset;
    }

    void set_offset(int8_t offset)
    {
        this->offset = offset;
    }

    [[nodiscard]] int8_t get_size() const
    {
        return size;
    }

    void set_size(int8_t size)
    {
        this->size = size;
    }

    [[nodiscard]] int8_t get_width() const
    {
        return width;
    }

    void set_width(int8_t width)
    {
        this->width = width;
    }

    [[nodiscard]] double get_f_up() const
    {
        return F_up;
    }

    void set_f_up(double f_up)
    {
        F_up = f_up;
    }

};
#endif //MEMBRANE_H
