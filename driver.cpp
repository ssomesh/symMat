
#include <iostream>
#include <cstdlib>
#include <vector>
#include <eigen3/Eigen/Dense>
#include <sys/time.h>
#include <string>

#include "symmat.h"

template <typename Derived, typename T>

void fill_matrix_symmetric(Derived& M){  // a helper function to populate the matrix such that it is symmetric
  const int LIMIT = 30;
  struct timeval Tv;
  gettimeofday(&Tv, NULL); 
  int order = M.rows();
  T x;
  srand48(Tv.tv_usec); // using time of day as seed for the random number generation
  for(int i=0; i<order; ++i) {
    for(int j=i; j<order; ++j) {
      x = (T) (drand48() * LIMIT) ; // x will be in the range [0,LIMIT)
      M(i,j) = x; 
      M(j,i) = x;
    }
  }
}

template <typename Derived, typename T>
void fill_matrix_random(Derived& M){  // a helper function to populate the matrix with random values 
  const int LIMIT = 30;
  struct timeval Tv;
  gettimeofday(&Tv, NULL); // using time of day as seed
  int order = M.rows();
  T x;
  srand48(Tv.tv_usec); // generating a seed for the random number generation
  for(int i=0; i<order; ++i) {
    for(int j=i; j<order; ++j) {
      x = (T) (drand48() * LIMIT) ; // x will be in the range [0,LIMIT)
      M(i,j) = x; 
      M(j,i) = x;
    }
  }
}

int main(int argc, char** argv) {

  /*Driver code to test the functionality of the SymMat class */
  const int order = 4; // order of each of the input square Eigen::Matrix
  Eigen::MatrixXi M(order,order);
  fill_matrix_symmetric<Eigen::MatrixXi, int>(M); // M is a symmetric matrix  of type Eigen::MatrixXi and having 'int' values

  Eigen::MatrixXi M1(order,order);
  fill_matrix_symmetric<Eigen::MatrixXi, int>(M1); // M1 is a symmetric matrix  of type Eigen::MatrixXi and having 'int' values

  Eigen::MatrixXi M2(order,order);
  fill_matrix_random<Eigen::MatrixXi, int>(M2); // M2 is not a symmetric matrix. It is of type Eigen::MatrixXi and having 'int' values

  /*Displaying the Eigen::Matrix */
  std::cout << "M: " << std::endl << std::endl << M << std::endl;
  std::cout << std::endl;
  std::cout << "M1: " << std::endl << std::endl << M1 << std::endl;
  std::cout << std::endl;
  std::cout << "M2: "  << std::endl << std::endl << M2 << std::endl;
  std::cout << std::endl;

  // creating SymMat, S, from Eigen::Matrix, M.
  SymMat<Eigen::MatrixXi,int> S(M);
  std::cout << "S: "  << std::endl << std::endl;
  S.print_symMat(); // displaying the SymMat created
  std::cout << std::endl;

  // creating SymMat, S1, from Eigen::Matrix, M1.
  SymMat<Eigen::MatrixXi,int> S1(M1); 
  std::cout << "S1: "  << std::endl << std::endl;
  S1.print_symMat(); // displaying the SymMat created
  std::cout << std::endl;

  SymMat<Eigen::MatrixXi,int> res(order); // creating the result SymMat, res.

  std::cout << "S + S1: "  << std::endl << std::endl;
  try{
    res = S+S1; // testing the operation SymMat + SymMat. The operation is commutative.

  }
  catch(const char* e) {
    std::cout << e << std::endl;
  }
  res.print_symMat();
  std::cout << std::endl;

//  try {
//    std::cout << S1(order,0) << std::endl << std::endl;
//
//  }
//  catch(const char* e) {   // testing the case of invalid access
//    std::cout << e << std::endl << std::endl;;
//  }

  std::cout << "S - S1: "  << std::endl << std::endl;
  try {
    res = S-S1;  // testing the operation SymMat - SymMat
  }
  catch(const char* e) {
    std::cout << e << std::endl;
  }
  res.print_symMat(); // displaying the result
  std::cout << std::endl;

  Eigen::MatrixXi resM(order,order);  // creating the result Eigen::Matrix, resM.
  std::cout << "S + M2: "  << std::endl << std::endl;
  try {
    resM = S + M2;  // testing the operation SymMat + Eigen::Matrix. The operation is not commutative, i.e., resM = M2 + S is not allowed
  }
  catch(const char* e) {
    std::cout << e << std::endl;
  }
  std::cout << resM << std::endl; // displaying the result
  std::cout << std::endl;

  std::cout << "S - M2: "  << std::endl << std::endl;
  try {
    resM = S - M2;  // testing the operation SymMat - Eigen::Matrix.
  }
  catch(const char* e) {
    std::cout << e << std::endl;
  }
  std::cout << resM << std::endl; // displaying the result
  std::cout << std::endl;

  std::cout << "S * S1: "  << std::endl << std::endl;
  try {
    resM = S * S1;  // testing the operation SymMat * SymMat. The result need not be a symmetric matrix.
  }
  catch(const char* e) {
    std::cout << e << std::endl;
  }
  std::cout << resM << std::endl;
  std::cout << std::endl;

  std::cout << "S * M2: "  << std::endl << std::endl;
  try {
    resM = S * M2;
  }
  catch(const char* e) {
    std::cout << e << std::endl;
  }
  std::cout << resM << std::endl;
  std::cout << std::endl;

  return 0;
}
