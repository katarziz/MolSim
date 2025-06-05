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

- The input file has to be an xml file following the schema denoted in input/input.xsd:

```shell
  * <?xml version="1.0" encoding="UTF-8"?>

<Molsim_Input xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
xsi:noNamespaceSchemaLocation="input.xsd">

[Parameters]
<Particles>
[Sequence of cuboids, particles and discs]
</Particles>

</Molsim_Input>
```
- The document must contain single Parameters object, passing the parameters of the simulation:
  * Parameters that are changed from the default value are set with `<param> new_value </param>`
  * Parameters that remain at the default value are denoted with `<param/>`
```shell
<Parameters>
        <delta_t/>
        <t_end/>
        <box_size>
            <x-size/>
            <y-size/>
            <z-size/>
        </box_size>
        <number_cells>
            <x-number/>
            <y-number/>
            <z-number/>
        </number_cells>
        <boundary_conditions>
            <top_bound/>
            <right_bound/>
            <bottom_bound/>
            <left_bound/>
        </boundary_conditions>
        <cutoff/>
        <writer/>
        <force/>
        <output_name/>
        <output_frequency/>
    </Parameters>
```
- The Parameters object is followed by a Particles object, representing a seqence of cuboid, disc and particle objects
- - CUBOID data consists of
  * xyz-coordinates of the lower left front-side corner (3 double values)
  * velocities (3 double values)
  * mass of one particle (1 double value)
  * number of particles per dimension (3 double values)
  * distance of the particles (mesh width of the grid) (1 double value)
  * borwnian-velocity (1 double value)
- Example cuboid:
```shell
 <cuboid>
            <base_coordinates>
                <x-coordinate>0.0</x-coordinate>
                <y-coordinate>0.0</y-coordinate>
                <z-coordinate>0.0</z-coordinate>
            </base_coordinates>
            <number_particles>
                <x-number>40</x-number>
                <y-number>8</y-number>
                <z-number>1</z-number>
            </number_particles>
            <velocity>
                <x-velocity>0.0</x-velocity>
                <y-velocity>0.0</y-velocity>
                <z-velocity>0.0</z-velocity>
            </velocity>
            <spacing>1.1225</spacing>
            <mass>1.0</mass>
            <brownian_vel>0.1</brownian_vel>
        </cuboid>
```
- PARTICLE data consists of
  * xyz-coordinates (3 double values)
  * velocities (3 double values)
  * mass (1 double value)
- Example particle:
```shell
<particle>
            <position>
                <x-coordinate>30.0</x-coordinate>
                <y-coordinate>15.0</y-coordinate>
                <z-coordinate>0.0</z-coordinate>
            </position>
            <velocity>
                <x-velocity>-5.0</x-velocity>
                <y-velocity>-5.0</y-velocity>
                <z-velocity>0.0</z-velocity>
            </velocity>
            <mass>2.0</mass>
        </particle>
```
- DISC data consists of
  * xyz-coordinates (3 double values)
  * velocities (3 double values)
  * radius in particles from center(1 integer value)
  * mass (1 double value)
  * spacing( 1 double value)
  * brownian_velocity (1 double value)
- Example disc:
```shell
<disc>
            <position>
                <x-coordinate>0.0</x-coordinate>
                <y-coordinate>0.0</y-coordinate>
                <z-coordinate>0.0</z-coordinate>
            </position>
            <velocity>
                <x-velocity>0.0</x-velocity>
                <y-velocity>0.0</y-velocity>
                <z-velocity>0.0</z-velocity>
            </velocity>
            <radius>2</radius>
            <mass>1.0</mass>
            <spacing>1.0</spacing>
            <brownian_vel>0.1</brownian_vel>
</disc>
```

### Logging

logs are placed at project_root/build/logs

the default level of logging is INFO and can be changed by running `cmake .. -DLOG_LEVEL={LEVEL}` instead of `cmake ..`

available levels of logging are: `TRACE DEBUG INFO WARN ERROR CRITICAL OFF`

---

The Molecular Dynamics teaching code.