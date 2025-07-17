/*
 * Particle.h
 *
 *  Created on: 23.02.2010
 *      Author: eckhardw
 */

#pragma once

#include <array>
#include <string>

class Particle {
public:
    /**
     * Position of the particle
     */
    std::array<double, 3> x;

    /**
     * Velocity of the particle
     */
    std::array<double, 3> v;

    /**
     * Force effective on this particle
     */
    std::array<double, 3> f;

    /**
     * Force which was effective on this particle
     */
    std::array<double, 3> old_f;

    /**
     * Mass of this particle
     */
    double m;
    /**
     * Lennard-Jones Parameter epsilon of this Particle, sqrt(epsilon) stored for performance reasons
     */
    double eps;
    /**
     * Lennard-Jones Parameter sigma of this Particle, sigma / 2 stored for performance reasons
     */
    double sig;

    /**
     * Type of the particle. Use it for whatever you want (e.g. to separate
     * molecules belonging to different bodies, matters, and so on)
     */
    int type;

    /**
     * The state of the particle. Is it to be considered active, disabled, or other options.
     * lowest bit: disabled 1, enabled 0
     * second-lowest bit: fixed 1, free 0
     * third-lowest bit: membrane 1, free 0
     */
    int state;

    explicit Particle(int type = 0);

    //! Constructor for a Particle from another Particle
    /*!
     \param other reference to a constant Particle
    */
    Particle(const Particle &other);

    //! Constructor for a Particle from properties
    /*!
     \param x_arg array of three doubles containing the x-,y-&z- position of the Particle
     \param v_arg array of three doubles containing the x-,y-&z- velocity of the Particle
     \param m_arg double containing the mass of the particle
     \param eps_arg  double containing Lennard-Jones Parameter epsilon of this Particle
     \param sig_arg   double containing Lennard-Jones Parameter sigma of this Particle
     \param type_arg int denoting the particle's type
     \param state_arg int denoting the particle's state
    */
    Particle(std::array<double, 3> x_arg, std::array<double, 3> v_arg, double m_arg,
             double eps_arg, double sig_arg, int type_arg, int state_arg = 0);

    virtual ~Particle();

    //! Getter for the positional values of the Particle
    /*!
     \return array of three doubles containing the x-,y-&z- position of the Particle
    */
    const std::array<double, 3> &getX() const;

    //! Setter for the current position values of the Particle
    /*!
     \param x_arg reference to an array of three doubles containing the new x-,y-&z-position of the Particle
    */
    void setX(const std::array<double, 3> &x_arg);

    //! Getter for the velocity values of the Particle
    /*!
     \return array of three doubles containing the x-,y-&z- velocity of the Particle
    */
    const std::array<double, 3> &getV() const;

    //! Setter for the current velocity values of the Particle
    /*!
     \param v_arg reference to an array of three doubles containing the new x-,y-&z- velocity of the Particle
    */
    void setV(const std::array<double, 3> &v_arg);

    //! Getter for the current force values of the Particle
    /*!
     \return array of three doubles containing the current x-,y-&z- forces of the Particle
    */
    const std::array<double, 3> &getF() const;

    //! Setter for the current force values of the Particle
    /*!
     \param f_arg reference to an array of three doubles containing the new x-,y-&z- forces of the Particle
    */
    void setF(const std::array<double, 3> &f_arg);

    //! Getter for the previous force values of the Particle
    /*!
     \return array of three doubles containing the previous x-,y-&z- forces of the Particle
    */

    const std::array<double, 3> &getOldF() const;

    //! Setter for the previous force values of the Particle
    /*!
     \param old_f_arg reference to an array of three doubles containing the new x-,y-&z- forces of the Particle
    */
    void setOldF(const std::array<double, 3> &old_f_arg);

    //! Getter for the mass of the Particle
    /*!
     \return double representing the mass of the Particle
    */
    double getM() const;

    //! Getter for the Lennard-Jones parameter epsilon of the Particle
    /*!
     \return double representing the Lennard-Jones parameter epsilonof the Particle
    */
    double getEps() const;

    //! Getter for the Lennard-Jones parameter sigma of the Particle
    /*!
     \return double representing the Lennard-Jones parameter sigma of the Particle
    */
    double getSig() const;

    //! Getter for the type of the Particle
    /*!
     \return int representing the type of the Particle
    */
    int getType() const;

    //! Getter for the state of the Particle
    /*!
     \return int representing the state of the Particle
     */
    int getState() const;

    //! Setter for the state of the Particle
    /*!
     \param state_arg int representing the new state of the Particle
     */
    void setState(int state_arg);

    //! Equality operator between Particles
    /*!
     \param other reference to Particle to be compared to this for equality
    */

    bool operator==(Particle &other);

    //! Equality operator between Particles
    /*!
     \param other reference to Particle to be compared to this for equality
    */

    bool operator==(const Particle &other) const;

    //! Function retuning a String representation of the Particle
    /*!
     \return String representation of the Particle
    */

    std::string toString() const;
};

//! Function retuning a Stream of the String representation of the Particle
/*!
 \param stream reference to an output stream
 \param p reference to a Particle p to be given to the stream
 \return Output Stream of the String representation of the Particle
*/
std::ostream &operator<<(std::ostream &stream, Particle &p);

//! Helper Function to determine semantic equality of two particles
/*!
 \param p1
 \param p2
 \returns bool to indicate weather the particles are semantically equal
*/
bool particle_sem_eq(const Particle &p1, const Particle &p2);
