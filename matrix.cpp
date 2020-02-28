#include "matrix.h"
#include "matrixFactory.hpp"

//keep this is all in one file. Too lazy to write new files for each subclass....


Matrix::~Matrix(){
  //do jack. stupid virtual descructors...
}

DenseMatrix :: DenseMatrix(size_t dim){
  N = dim;
  data.resize(dim*dim, 0.0);
  this->type = "matrix_dense";
}

DenseMatrix :: ~DenseMatrix(){
  data.clear(); //we do not need this. why?
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


//TrashMatrix - ie how not to write code

TrashMatrix :: TrashMatrix(size_t dim){
  N = dim;
  data = new double*[N];
  for(size_t i=0;i<N;i++){ //yes, even post-increment in Trash!
    data[i] = new double[N];
  }
  this->type = "matrix_trash";
}

TrashMatrix :: ~TrashMatrix(){
  //while including mem leaks by design might fit the theme of TrashMatrix,
  //I really shouldn't. So we'll clean up. Begrudgingly...
  for(size_t i=0;i<N;i++){
    delete[] data[i];
  }
  delete[] data;
}

TrashMatrix :: TrashMatrix(TrashMatrix& A){
  N = A.N;
  //if we can't break the compiler to do shallow copying..
  for(size_t i=0;i<N;i++){
    for(size_t j=0;j<N;j++){
      data[j][i] = A.data[j][i]; 
    }
  }
}

TrashMatrix :: TrashMatrix(TrashMatrix &&A){
  //ok, we can't break moving, but we can ignore it..
  copy(A);

}

TrashMatrix& TrashMatrix::operator+(const TrashMatrix& A){
  if(N != A.N){
    printf("Dimension mismatch...\n");
    return *this;
  }
  for(size_t i=0;i<N;i++){
    for(size_t j=0;j<N;j++){
      double temp1 = data[j][i];
      double temp2 = A.data[j][i];
      double temp3 = temp1 + temp2;
      data[j][i] = temp3; //this hurt to write..
    }
  }
  return *this;
}

TrashMatrix* TrashMatrix::operator+(const TrashMatrix* A){
  if(N != A->N){
    printf("Dimension mismatch...\n");
    return this;
  }
  for(size_t i=0;i<N;i++){
    for(size_t j=0;j<N;j++){
      double temp1 = data[j][i];
      double temp2 = A->data[j][i];
      double temp3 = temp1 + temp2;
      data[j][i] = temp3; //this hurt to write..
    }
  }
  return this;
}


TrashMatrix& TrashMatrix::operator*(const TrashMatrix& A){
  
  if(N != A.N){
    printf("Dimension mismatch!\n");
    exit(1);
  }

  return *this;
}

TrashMatrix& TrashMatrix::operator=(const TrashMatrix& A){
  copy(A);
  return *this;
}

TrashMatrix& TrashMatrix::operator=(const TrashMatrix&& A){
  copy(A);
  return *this;
}

void TrashMatrix::printMatrix(){
  //so this one actually works fine enough. 
  printf("\n");
  for(size_t i=0;i<N;++i){
    printf("\n");
    for(size_t j=0;j<N;++j){
      printf(" %.5f ", data[i][j]);
    }
  }
  printf("\n");
}

void TrashMatrix::fillData(size_t i, size_t j, double val){
  if(i > N || i < 0 || j > N || j < 0){
    printf("Attempting to access memory outside of the allocated data..");
    return;
  }
  data[i][j] = val;
}

void TrashMatrix::copy(const TrashMatrix& A){
  N = A.N;
  for(size_t i=0;i<N;i++){
    for(size_t j=0;j<N;j++){
      double temp1 = A.data[j][i];
      data[j][i] = temp1; //this hurt to write..
    }
  }
}


