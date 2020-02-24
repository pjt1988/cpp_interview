#include "matrix.h"
#include "matrixFactory.hpp"


DenseMatrix :: DenseMatrix(size_t dim){
  N = dim;
  data.resize(dim*dim, 0.0);
  this->type = "matrix_dense";
}

DenseMatrix :: ~DenseMatrix(){
  data.clear(); //do we need to do this?
}

DenseMatrix :: DenseMatrix(DenseMatrix& A){
  N = A.N;
  data = A.data; //automatic deep copy!
}

DenseMatrix :: DenseMatrix(DenseMatrix &&A){
  N = A.N;
  data = std::move(A.data);
}

DenseMatrix& DenseMatrix::operator+(const DenseMatrix& A){
  
  size_t dim = N*N;
  if(A.N * A.N < dim) dim = A.N * A.N;

  for(size_t i=0;i<dim;++i){
    data[i] += A.data[i];
  }
  return *this;
}

DenseMatrix& DenseMatrix::operator*(const DenseMatrix& A){
  
  if(N != A.N){
    printf("Dimension mismatch!\n");
    exit(1);
  }
  return *this;
}

DenseMatrix& DenseMatrix::operator=(const DenseMatrix& A){
  copy(A);
  return *this;
}

DenseMatrix& DenseMatrix::operator=(const DenseMatrix&& A){
  printf("Also later..\n");
  return *this;
}

void DenseMatrix::printMatrix(){
  printf("\n");
  for(size_t i=0;i<N;++i){
    printf("\n");
    for(size_t j=0;j<N;++j){
      printf(" %.5f ", data[j+i*N]);
    }
  }
  printf("\n");
}

void DenseMatrix::fillData(size_t i, size_t j, double val){
  if(i > N || i < 0 || j > N || j < 0){
    printf("Attempting to access memory outside of the allocated data..");
    return;
  }
  if(j+i*N > data.size()){
    printf("Vector is too tiny...\n");
    return;
  }
  data[j+i*N] = val;
}

void DenseMatrix::copy(const DenseMatrix& A){
  N = A.N;
  data  = A.data;
}

int main(){
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



  return 0;
}
