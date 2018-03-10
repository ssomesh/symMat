
#include <iostream>
#include <cstdlib>
#include <vector>
#include <eigen3/Eigen/Dense> // eigen3 is installed in /usr/local/include
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

  /* Test Case -1: */
  std::cout << "TEST CASE 1: Eigen::Matrix with integer values" << std::endl << "---------------------------------------" << std::endl;
  Eigen::MatrixXi M(order,order);
  fill_matrix_symmetric<Eigen::MatrixXi, int>(M); // M is a symmetric matrix  of type Eigen::MatrixXi and having 'int' values

  Eigen::MatrixXi M1(order,order);
  fill_matrix_symmetric<Eigen::MatrixXi, int>(M1); // M1 is a symmetric matrix  of type Eigen::MatrixXi and having 'int' values

  Eigen::MatrixXi M2(order,order);
  fill_matrix_random<Eigen::MatrixXi, int>(M2); // M2 is not a symmetric matrix. 
                                                // It is of type Eigen::MatrixXi and having 'int' values

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
    resM = S + M2;  // testing the operation SymMat + Eigen::Matrix. 
                    // The operation is not commutative, i.e., resM = M2 + S is not allowed
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

  std::cout << "--------------------------------------------------------------------------------------"<< std::endl << std::endl;


  /* Test Case -2: */
  std::cout << "TEST CASE 2: Eigen::Matrix with floating-point values" << std::endl << "----------------------------------------------" << std::endl;
  Eigen::MatrixXd Mat(order,order);
  fill_matrix_symmetric<Eigen::MatrixXd, double>(Mat); // Mat is a symmetric matrix  of type Eigen::MatrixXd and having 'double' values

  Eigen::MatrixXd Mat1(order,order);
  fill_matrix_symmetric<Eigen::MatrixXd, double>(Mat1); // Mat1 is a symmetric matrix  of type Eigen::MatrixXd and having 'double' values

  Eigen::MatrixXd Mat2(order,order);
  fill_matrix_random<Eigen::MatrixXd, double>(Mat2); // Mat2 is not a symmetric matrix. 
                                                     // It is of type Eigen::MatrixXd and having 'double' values

  /*Displaying the Eigen::Matrix */
  std::cout << "Mat: " << std::endl << std::endl << Mat << std::endl;
  std::cout << std::endl;
  std::cout << "Mat1: " << std::endl << std::endl << Mat1 << std::endl;
  std::cout << std::endl;
  std::cout << "Mat2: "  << std::endl << std::endl << Mat2 << std::endl;
  std::cout << std::endl;

  // creating SymMat, S2, from Eigen::Matrix, Mat.
  SymMat<Eigen::MatrixXd,double> S2(Mat);
  std::cout << "S2: "  << std::endl << std::endl;
  S2.print_symMat(); // displaying the SymMat created
  std::cout << std::endl;

  // creating SymMat, S3, from Eigen::Matrix, Mat1.
  SymMat<Eigen::MatrixXd,double> S3(Mat1); 
  std::cout << "S3: "  << std::endl << std::endl;
  S3.print_symMat(); // displaying the SymMat created
  std::cout << std::endl;

  SymMat<Eigen::MatrixXd,double> res1(order); // creating the result SymMat, res1.

  std::cout << "S2 + S3: "  << std::endl << std::endl;
  try{
    res1 = S2+S3; // testing the operation SymMat + SymMat. The operation is commutative.

  }
  catch(const char* e) {
    std::cout << e << std::endl;
  }
  res1.print_symMat();
  std::cout << std::endl;

  std::cout << "S2 - S3: "  << std::endl << std::endl;
  try {
    res1 = S2-S3;  // testing the operation SymMat - SymMat
  }
  catch(const char* e) {
    std::cout << e << std::endl;
  }
  res1.print_symMat(); // displaying the result
  std::cout << std::endl;

  Eigen::MatrixXd resM1(order,order);  // creating the result Eigen::Matrix, resM1.
  std::cout << "S2 + Mat2: "  << std::endl << std::endl;
  try {
    resM1 = S2 + Mat2;  // testing the operation SymMat + Eigen::Matrix. 
                    // The operation is not commutative, i.e., resM1 = Mat2 + S2 is not allowed
  }
  catch(const char* e) {
    std::cout << e << std::endl;
  }
  std::cout << resM1 << std::endl; // displaying the result
  std::cout << std::endl;

  std::cout << "S2 - Mat2: "  << std::endl << std::endl;
  try {
    resM1 = S2 - Mat2;  // testing the operation SymMat - Eigen::Matrix.
  }
  catch(const char* e) {
    std::cout << e << std::endl;
  }
  std::cout << resM1 << std::endl; // displaying the result
  std::cout << std::endl;

  std::cout << "S2 * S3: "  << std::endl << std::endl;
  try {
    resM1 = S2 * S3;  // testing the operation SymMat * SymMat. The result need not be a symmetric matrix.
  }
  catch(const char* e) {
    std::cout << e << std::endl;
  }
  std::cout << resM1 << std::endl;
  std::cout << std::endl;

  std::cout << "S2 * Mat2: "  << std::endl << std::endl;
  try {
    resM1 = S2 * Mat2;
  }
  catch(const char* e) {
    std::cout << e << std::endl;
  }
  std::cout << resM1 << std::endl;
  std::cout << std::endl;

  std::cout << "--------------------------------------------------------------------------------------"<< std::endl << std::endl;



  /* Test Case - 3: */
  std::cout << "TEST CASE 3: Eigen::Matrix with floating-point values declared on the stack" << std::endl;
  std::cout << "---------------------------------------------------------------------" << std::endl;
  Eigen::Matrix2d Mat3;
  fill_matrix_symmetric<Eigen::Matrix2d, double>(Mat3); // Mat3 is a symmetric matrix  of type Eigen::Matrix2d and having 'double' values

  Eigen::Matrix2d Mat4;
  fill_matrix_symmetric<Eigen::Matrix2d, double>(Mat4); // Mat4 is a symmetric matrix  of type Eigen::Matrix2d and having 'double' values

  Eigen::Matrix2d Mat5;
  fill_matrix_random<Eigen::Matrix2d, double>(Mat5); // Mat5 is not a symmetric matrix. 
                                                     // It is of type Eigen::Matrix2d and having 'double' values

  /*Displaying the Eigen::Matrix */
  std::cout << "Mat3: " << std::endl << std::endl << Mat3 << std::endl;
  std::cout << std::endl;
  std::cout << "Mat4: " << std::endl << std::endl << Mat4 << std::endl;
  std::cout << std::endl;
  std::cout << "Mat5: "  << std::endl << std::endl << Mat5 << std::endl;
  std::cout << std::endl;

  // creating SymMat, S4, from Eigen::Matrix, Mat3.
  SymMat<Eigen::Matrix2d,double> S4(Mat3);
  std::cout << "S4: "  << std::endl << std::endl;
  S4.print_symMat(); // displaying the SymMat created
  std::cout << std::endl;

  // creating SymMat, S5, from Eigen::Matrix, Mat1.
  SymMat<Eigen::Matrix2d,double> S5(Mat4); 
  std::cout << "S5: "  << std::endl << std::endl;
  S5.print_symMat(); // displaying the SymMat created
  std::cout << std::endl;

  SymMat<Eigen::Matrix2d,double> res2(2); // creating the result SymMat, res2.

  std::cout << "S4 + S5: "  << std::endl << std::endl;
  try{
    res2 = S4+S5; // testing the operation SymMat + SymMat. The operation is commutative.

  }
  catch(const char* e) {
    std::cout << e << std::endl;
  }
  res2.print_symMat();
  std::cout << std::endl;

  std::cout << "S4 - S5: "  << std::endl << std::endl;
  try {
    res2 = S4-S5;  // testing the operation SymMat - SymMat
  }
  catch(const char* e) {
    std::cout << e << std::endl;
  }
  res2.print_symMat(); // displaying the result
  std::cout << std::endl;

  Eigen::Matrix2d resM2;  // creating the result Eigen::Matrix, resM2.
  std::cout << "S4 + Mat5: "  << std::endl << std::endl;
  try {
    resM2 = S4 + Mat5;  // testing the operation SymMat + Eigen::Matrix. 
                    // The operation is not commutative, i.e., resM2 = Mat5 + S4 is not allowed
  }
  catch(const char* e) {
    std::cout << e << std::endl;
  }
  std::cout << resM2 << std::endl; // displaying the result
  std::cout << std::endl;

  std::cout << "S4 - Mat5: "  << std::endl << std::endl;
  try {
    resM2 = S4 - Mat5;  // testing the operation SymMat - Eigen::Matrix.
  }
  catch(const char* e) {
    std::cout << e << std::endl;
  }
  std::cout << resM2 << std::endl; // displaying the result
  std::cout << std::endl;

  std::cout << "S4 * S5: "  << std::endl << std::endl;
  try {
    resM2 = S4 * S5;  // testing the operation SymMat * SymMat. The result need not be a symmetric matrix.
  }
  catch(const char* e) {
    std::cout << e << std::endl;
  }
  std::cout << resM2 << std::endl;
  std::cout << std::endl;

  std::cout << "S4 * Mat5: "  << std::endl << std::endl;
  try {
    resM2 = S4 * Mat5;
  }
  catch(const char* e) {
    std::cout << e << std::endl;
  }
  std::cout << resM2 << std::endl;
  std::cout << std::endl;

  std::cout << "--------------------------------------------------------------------------------------"<< std::endl << std::endl;

  return 0;
}
