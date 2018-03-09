
#ifndef SYMMAT_H
#define  SYMMAT_H

#include <iostream>
#include <cstdlib>
#include <vector>
#include <eigen3/Eigen/Dense> // eigen3 is installed in usr/local/include
#include <string>

/*
 * The following code works for 2D square matrix. 
 * */



/* class for a symmetric matrix */

template <typename Derived, typename T> // Derived is the type of Eigen::Matrix and 
                                        // 'T' is the datatype of the values in the input matrix.
class SymMat {
  private:
    std::vector<std::vector<T> > symmetric; // for storing the  upper triangular part of a Symmetric Eigen::Matrix
    int dim; // for storing the dimension of the input matrix
  public:

    // Constructor for populating 'symmetric' with all zeros
    SymMat(int order) {  // order is the dimension of the square Eigen::Matrix it represents
      dim = order;
      for(int i=0; i<dim; ++i) {
        std::vector<T> vecRow;
        for(int j=i; j<dim; ++j) {
          vecRow.push_back((T)0);
        }
        symmetric.push_back(vecRow);
      }
    }

    // Constructor for storing the upper triangular part of the Eigen::Matrix in 'symmetric'
    SymMat(Derived& M) {
      assert(M.rows() == M.cols()); // make sure that the Eigen::Matrix, M, is a square matrix -- a sanity check.
      dim = M.rows();
      for(int i=0; i<dim; ++i) {
        std::vector<T> vecRow;
        for(int j=i; j<dim; ++j) {
          vecRow.push_back(M(i,j));
        }
        symmetric.push_back(vecRow);
      }
    }

    // getter -- return the element of the symmetric matrix at the index (r,c)  
    T& operator()(int r, int c) throw (const char *) { // overloading the operator () 

      if (r < 0 || r >= dim || c < 0 || c >= dim) throw "Invalid access"; // throw an exception upon encountering an out of bounds access
      else {
        if(r > c) { // (r > c) is an element in the lower triangular part of the matrix, 
                    // hence swap 'r' & 'c' to get the corresponding element from the upper triangular part of the matrix. 
          r = r ^ c;
          c = r ^ c;
          r = r ^ c;
        }
        return symmetric[r][c-r]; // the row id is subtracted from the column id to get the correct index since that is the offset

      }
    }

    // overloading the + operator for (SymMat + SymMat)
    SymMat operator + (SymMat& S2) throw (const char *) { 
      if(this->dim != S2.dim) throw "Matrix dimensions do not match"; // throw an exception if matrix dimensions do not match
      else {
        SymMat S1(dim); // creating an object of SymMat for storing the result. 
        for(int i=0; i<dim; i++) {
          for(int j=0; j<symmetric[i].size();j++)
            S1.symmetric[i][j] = symmetric[i][j] + S2.symmetric[i][j]; 
        }
        return S1; // returns an object of SymMat
      }
    }

    // overloading the - operator for (SymMat - SymMat)
    SymMat operator - (SymMat& S2) throw (const char *) {  
      if(dim != S2.dim) throw "Matrix dimensions do not match"; // throw an exception if matrix dimensions do not match
      else {
        SymMat S1(dim); // creating an object for storing the result
        for(int i=0; i<dim; i++) {
          for(int j=0; j<symmetric[i].size();j++)
            S1.symmetric[i][j] = symmetric[i][j] - S2.symmetric[i][j];
        }
        return S1; // returns an object of SymMat
      }
    }


    // overloading the + operator for (SymMat + Eigen::Matrix)
    Derived operator + (Derived& M) throw (const char*) { 
      assert(M.rows() == M.cols());  // checking if Eigen::Matrix, M, is a square matrix -- a sanity check
      if(M.rows() != dim) throw "Matrix dimensions do not match"; // throw an exception if matrix dimensions do not match
      else {
        Derived res(dim,dim); // creating an object of Eigen::Matrix for storing the result
        for(int i=0; i<dim; ++i)
          for(int j=0; j<dim; ++j)
            res(i,j) = operator()(i,j) + M(i,j); // populating the result matrix
        return res; // returns an object of Eigen::Matrix
      }
    }

    // overloading the - operator for (SymMat - Eigen::Matrix)
    Derived operator - (Derived& M) throw (const char*) {  
      assert(M.rows() == M.cols()); // checking if Eigen::Matrix, M, is a square matrix -- a sanity check
      if(M.rows() != dim) throw "Matrix dimensions do not match"; // throw an exception if matrix dimensions do not match
      else {
        Derived res(dim,dim);// creating an object of Eigen::Matrix for storing the result
        for(int i=0; i<dim; ++i)
          for(int j=0; j<dim; ++j)
            res(i,j) = operator()(i,j) - M(i,j); // populating the result matrix
        return res; // returns an object of Eigen::Matrix
      }
    }

    // overloading the * operator for (SymMat * SymMat)
    Derived operator * (SymMat& S2) {  // the result may not be a symmetric matrix
      if(this->dim != S2.dim) throw "Matrix dimensions do not match"; // throw an exception if matrix dimensions do not match
      else {
        Derived res(dim,dim);// creating an object of Eigen::Matrix for storing the result
        for(int i=0; i<dim; i++) {
          for(int j=0; j<dim; j++) {
            res(i,j) = (T)0;
            for(int k=0; k<dim; k++) 
              res(i,j) += operator()(i,k) * S2.operator()(k,j);  // populating the result matrix
          }
        }
        return res;  // returns an object of Eigen::Matrix
      }
    }

    // overloading the * operator for (SymMat * Eigen::Matrix)
    Derived operator * (Derived& M) { // the result may not be a symmetric matrix
      assert(M.rows() == M.cols()); // checking if Eigen::Matrix, M, is a square matrix -- a sanity check
      if(M.rows() != dim) throw "Matrix dimensions do not match"; // throw an exception if matrix dimensions do not match
      else {
        Derived res(dim,dim);// creating an object of Eigen::Matrix for storing the result
        for(int i=0; i<dim; i++) {
          for(int j=0; j<dim; j++) {
            res(i,j) = (T)0;
            for(int k=0; k<dim; k++) 
              res(i,j) += operator()(i,k) * M(k,j); // populating the result matrix
          }
        }
        return res; // returns an object of Eigen::Matrix
      }
    }

    void print_space(std::string s) {
      int len = s.length();
      for(int i=0; i<=len; ++i)
        std::cout << " " ;
    } 

    //function for displaying the contents of SymMat as an upper triangular matrix
    void print_symMat() {
      for(int i=0; i<dim; ++i) {
        for(int k=0; k<i;++k) // adding appropriate spaces for printing
          print_space(std::to_string(symmetric[k][k])); 
        if(i == dim-1) 
          std::cout << " ";
        for(int j=0; j< symmetric[i].size(); j++) 
          std::cout << symmetric[i][j] << " "; // printing one row done.
        std::cout << std::endl;
      }
    }
};

#endif 

