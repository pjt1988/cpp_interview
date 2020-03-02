#include "matrix.h"
#include "matrixFactory.hpp"

#define TILE 4


//keep this is all in one file. Too lazy to write new files for each subclass....


//yes, the casting is dirty, but if we want to use smart pointers, there's little choice
//well, there is, I'm just too lazy
Matrix& Matrix::operator+(const Matrix& B){
  if(verify_types(*this, B)){
    if(this->get_type() == "matrix_dense"){
      DenseMatrix& A = dynamic_cast<DenseMatrix&>(*this);
      const DenseMatrix& Bderiv = dynamic_cast<const DenseMatrix&>(B);
      A = A + Bderiv;
      Matrix& ret = static_cast<Matrix&>(A);
      return ret;
    }else if(this->get_type() == "matrix_trash"){
      TrashMatrix& A = dynamic_cast<TrashMatrix&>(*this);
      const TrashMatrix& Bderiv = dynamic_cast<const TrashMatrix&>(B);
      A = A + Bderiv;
      Matrix& ret = static_cast<Matrix&>(A);
      return ret;
    }
  }
  return *this; //shut it, -Wall...
}

Matrix& Matrix::operator*(const Matrix& B){
  if(verify_types(*this, B)){
    if(this->get_type() == "matrix_dense"){
      DenseMatrix& A = dynamic_cast<DenseMatrix&>(*this);
      const DenseMatrix& Bderiv = dynamic_cast<const DenseMatrix&>(B);
      A = A * Bderiv;
      Matrix& ret = static_cast<Matrix&>(A);
      return ret;
    }else if(this->get_type() == "matrix_trash"){
      TrashMatrix& A = dynamic_cast<TrashMatrix&>(*this);
      const TrashMatrix& Bderiv = dynamic_cast<const TrashMatrix&>(B);
      A = A * Bderiv;
      Matrix& ret = static_cast<Matrix&>(A);
      return ret;
    }
  }
  return *this; //shut it, -Wall...
}

Matrix& Matrix::operator=(const Matrix& B){
  if(verify_types(*this, B)){
    if(this->get_type() == "matrix_dense"){
      DenseMatrix& A = dynamic_cast<DenseMatrix&>(*this);
      const DenseMatrix& Bderiv = dynamic_cast<const DenseMatrix&>(B);
      A = Bderiv;
      Matrix& ret = static_cast<Matrix&>(A);
      return ret;
    }else if(this->get_type() == "matrix_trash"){
      TrashMatrix& A = dynamic_cast<TrashMatrix&>(*this);
      const TrashMatrix& Bderiv = dynamic_cast<const TrashMatrix&>(B);
      A = Bderiv;
      Matrix& ret = static_cast<Matrix&>(A);
      return ret;
    }
  }
  return *this;
}

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
  const std::vector<double>& adata = A.data;

  for(size_t ii=0;ii<N;ii+=TILE){
    size_t imax = ii + TILE > N ? N : ii + TILE;
    for(size_t jj=0;jj<N;jj+=TILE){
      size_t jmax = jj + TILE > N ? N : jj + TILE;
      for(size_t kk=0;kk<N;kk+=TILE){
        size_t kmax = kk + TILE > N ? N : kk + TILE;

        for(size_t i=ii;i<imax;++i){
          for(size_t j=jj;j<jmax;++j){
            size_t col = j*N;
            double temp = 0;
            for(size_t k=kk;k<kmax;++k){
              temp += data[i+k*N] * adata[k + col];
            }
            data[i+col] = temp;
          }
        }
      }
    }
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
    for(size_t j=0;j<N;j++) data[i][j] = 0.0;
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
    return *this;
  }
  double** adata = A.data;

  for(size_t i=0;i<N;i++){
    for(size_t j=0;j<N;j++){
      double temp = 0.0;
      for(size_t k=0;k<N;k++){
        temp += data[i][k] * adata[k][j];
      }
      data[i][j] = temp;
    }
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

bool verify_types(const Matrix& A, const Matrix& B){
  return (A.get_type() == B.get_type());
}


bool verify_types(const Matrix& A, const Matrix& B, const Matrix& C){
  return ((A.get_type() == B.get_type()) && (B.get_type() == C.get_type()));
}


