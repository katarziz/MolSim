/*
 * FileReader.h
 *
 *  Created on: 23.02.2010
 *      Author: eckhardw
 */

#pragma once

#include "../objects/ParticleContainer.h"

class FileReader {
public:
    //! Default constructor for the FileReader class
    /*!
     Creates a new FileReader instance
    */
    FileReader();

    //! Virtual destructor for the FileReader class
    /*!
     Destroys a FileReader instance
    */
    virtual ~FileReader();

    //! A function to read particle data from a text file
    /*!
     \param particles reference to a ParticleContainer where the particles will be stored
     \param filename pointer to a character array containing the path to the input file
     
     This function parses input files containing PARTICLES or CUBOID sections and 
     adds the corresponding particles to the container
    */
    static void readFile(ParticleContainer &particles, char *filename);

    //! A function to read particle data from a binary checkpoint file
    /*!
     \param time reference to a double where the simulation time will be stored
     \param particles reference to a ParticleContainer where the particles will be stored
     \param filename pointer to a character array containing the path to the checkpoint file
     
     This function reads binary checkpoint files containing simulation state data
    */
    static void readCheckpoint(double &time, ParticleContainer &particles, char *filename);

    //! A function to write particle data to a binary checkpoint file
    /*!
     \param time reference to the current simulation time
     \param particles reference to the ParticleContainer containing the particles to save
     \param filename pointer to a character array containing the path for the output checkpoint file
     
     This function writes the current simulation state to a binary checkpoint file for later resumption
    */
    static void writeCheckpoint(double &time, ParticleContainer &particles, char *filename);
};
