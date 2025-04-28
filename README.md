MolSim - GroupB
===

---

to build the project run `$cmake .` and `$make`

to execute run `$./MolSim INPUT_FILE`

The input file has to have the following format:
```text
#
# file format: 
# Lines of comment start with '#' and are only allowed at the
# beginning of the file
# Empty lines are not allowed.
# The first line not being a comment has to be one integer,
# indicating the number of molecule data sets.
#
# Molecule data consists of 
# * xyz-coordinates (3 double values)
# * velocities (3 double values)
# * mass (1 double value)
#
# xyz-coord      velocity        mass
```
Consider this example:
```text
# comment
2
0.1 1.2 3.5  8.1 3.2 1.3  4.5
1.2 4.8 1.6  3.2 6.4 1.2  8.2
```

---

The Molecular Dynamics teaching code.
