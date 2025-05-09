/*!\mainpage


MolSim - GroupB
===

---

### Documentation

To create the documentation for the project using Doxygen run `$make doc_doxygen`, the documentation can be found at ./docs/html/index.html

In case your system does not have Doxygen, please run `$cmake -D BUILD_DOC=off .` instead of `$cmake .`

### Building and Executing

To build the project run `$cmake .` and `$make`

To execute run `$./MolSim -i INPUT_FILE`

The input file has to have the following format:

- Lines of comment start with '#' and are only allowed at the beginning of the file
- Empty lines are not allowed.
- The first line not being a comment has to be one integer, indicating the number of molecule data sets.
- Every line following after contains one set of molecule data consisting of:
    - xyz-coordinates (3 double values)
    - velocities (3 double values)
    - mass (1 double value)

Consider this example:
```text
# comment
2
0.1 1.2 3.5  8.1 3.2 1.3  4.5
1.2 4.8 1.6  3.2 6.4 1.2  8.2
```

For further options and arguments supported by the executable, please refer to the output of `$./MolSim -h`

---

The Molecular Dynamics teaching code.