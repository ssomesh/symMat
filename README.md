# Evaluation Test for *Faster Matrix Algebra for ATLAS*

### Getting the code

- Clone the code into a directory called SymMat
    ```
    git clone --branch=master https://github.com/ssomesh/symMat
    ```
- The source code for the class SymMat is present in the file *symmat.h*

### Compiling and Testing the code

- Include "symmat.h" (with the proper path) in the code and use.
- *driver.cpp* contains a sample program that uses SymMat.
    - Compile *driver.cpp* and execute
        ```    
        > make
        > ./symMat
        ```
- There are 3 test cases in *driver.cpp*. The output of each of the test cases will be printed to stdout upon executing *symMat*.
- The code has been tested on a machine running Ubuntu 14.04. It was compiled with GCC version 4.8.4.
