/*!\mainpage


MolSim - GroupB
===

---

### Building

To build the project run:

```shell
mkdir build && cd build
cmake ..
cmake --build .
```

In case you prefer clang to your system's default compiler, in place of `cmake ..` run:

```shell
cmake -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ ..
```

### Documentation

In case your system does not have doxygen, please run `cmake -D BUILD_DOC=off ..` instead of `cmake ..`

To create the documentation for the project using Doxygen run `cmake --build . --target doc_doxygen`

the documentation can be found at project_root/docs/html/index.html

### Executing

To execute from within the build directory, run:

```shell
./MolSim -i INPUT_FILE
```

The input file has to have the following format:

- Lines of comment start with '#' and are only allowed at the beginning of the file
- Empty lines are not allowed.
- The first line of a block has to denote the type: PARTICLES or CUBOID
- PARTICLES data consists of
  * num_particles (1 integer) - specifying how many particles to read
  * the following {num_particles} line have to contain:
  * xyz-coordinates (3 double values)
  * velocities (3 double values)
  * mass (1 double value)
- CUBOID data consists of
  * xyz-coordinates of the lower left front-side corner (3 double values)
  * velocities (3 double values)
  * mass of one particle (1 double value)
  * number of particles per dimension (3 double values)
  * distance of the particles (mesh width of the grid) (1 double value)

Consider this example for PARTICLES:
```text
# comment
2
0.1 1.2 3.5  8.1 3.2 1.3  4.5
1.2 4.8 1.6  3.2 6.4 1.2  8.2
```

For further options and arguments supported by the executable, please refer to the output of `$./MolSim -h`

### Logging

logs are placed at project_root/build/logs

the default level of logging is INFO and can be changed by running `cmake .. -DLOG_LEVEL={LEVEL}` instead of `cmake ..`

available levels of logging are: `TRACE DEBUG INFO WARN ERROR CRITICAL OFF`

---

The Molecular Dynamics teaching code.