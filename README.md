# Evaluation Test for *Faster Matrix Algebra for ATLAS*

### Getting the code

- Clone the code into a directory called SymMat
    ```
    git clone --branch=master https://github.com/ssomesh/symMat
    ```


## Compiling and Testing the code

- *driver.cpp* contains a sample program that uses SymMat.
    - Compile *driver.cpp* and execute
        ```    
        make
        ./symMat
        ```
- There are 3 test cases in *driver.cpp*. The result of each of them will be printed to stdout upon executing *symMat*
- The code has been tested on a machine running Ubuntu 14.04. It was compiled with GCC version 4.8.4
