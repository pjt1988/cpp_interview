#include "headers.h"
#include "timing.h"
#include "matrix.h"
#include "matrixFactory.hpp"

int main(){
  Time t0;
  MatrixFactory MatFact();

  DenseMatrix A = DenseMatrix(10);
  DenseMatrix B = DenseMatrix(10);

  //Matrix* C = MatrixFactory::createMatrix(10,"matrix_dense");
  std::unique_ptr<Matrix> E = MatrixFactory::createUMatrix(10,"matrix_dense");


  A.printMatrix();
  for(size_t i=0;i<10;++i) B.fillData(i,i,(double) i);
  B.printMatrix();

  for(size_t i=0;i<10;++i) B.fillData(i,i,(double) i*i);
  DenseMatrix D = DenseMatrix(B);
  D.printMatrix();

  A = A + D;
  A.printMatrix();

  *E = A + B;

  std::unique_ptr<Matrix> F = MatrixFactory::createUMatrix(10,"matrix_trash");
  std::unique_ptr<Matrix> G = MatrixFactory::createUMatrix(10,"matrix_trash");

  for(size_t i=0;i<10;++i){
    for(size_t j=0;j<10;++j){
      if(i == j){
        F->fillData(i,j,(double) i+j);
        G->fillData(i,j,(double) i*j);
      }else{
        F->fillData(i,j,0.0);
        G->fillData(i,j,0.0);
      }
    }
  }
  F->printMatrix();
  G->printMatrix();
  F->add(*G);
  F->printMatrix();




  return 0;
}

