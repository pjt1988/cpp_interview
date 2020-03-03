#include "headers.h"
#include "matrix.h"
#include "matrixFactory.hpp"
#include <chrono>

int main(int argc, char** argv){
  double lower_bound = 0;
  double upper_bound = 4;
  std::uniform_real_distribution<double> unif(lower_bound,upper_bound);
  std::default_random_engine re;

  size_t Nrow = 0;
  if(argc > 1){
    Nrow = std::atoi(argv[1]);
  }
  std::chrono::time_point<std::chrono::system_clock> start1,end1; //and this is why people generally write a wrapper function for this..
  printf("Setting up double**, doing C = A + B, and C = A * B \n");


  printf("Benchmarking Dense Matrix..\n");
  start1=std::chrono::system_clock::now();
  std::unique_ptr<Matrix> A = MatrixFactory::createUMatrix(Nrow,"matrix_dense");
  std::unique_ptr<Matrix> B = MatrixFactory::createUMatrix(Nrow,"matrix_dense");
  std::unique_ptr<Matrix> C = MatrixFactory::createUMatrix(Nrow,"matrix_dense");
  end1 = std::chrono::system_clock::now();
  std::chrono::duration<double> elapsed = end1 - start1;
  printf("Setup - %.4f s\n", elapsed.count());

  start1=std::chrono::system_clock::now();
  for(size_t i=0;i<Nrow;++i){
    for(size_t j=0;j<Nrow;++j){
      A->fillData(i,j,unif(re));
      B->fillData(i,j,unif(re));
    }
  }
  end1 = std::chrono::system_clock::now();
  elapsed = end1 - start1;
  printf("RandFill - %.4f s\n", elapsed.count());

  start1=std::chrono::system_clock::now();
  (*A) = (*A) + (*B);
  end1 = std::chrono::system_clock::now();
  elapsed = end1 - start1;
  printf("Add - %.4f s\n", elapsed.count());
  A->printMatrix();
  B->printMatrix();

  start1=std::chrono::system_clock::now();
  (*C) = (*A) * (*B);
  end1 = std::chrono::system_clock::now();
  elapsed = end1 - start1;
  printf("Mult - %.4f s\n", elapsed.count());
  C->printMatrix();


  printf("Benchmarking Trash Matrix..\n");
  start1=std::chrono::system_clock::now();
  std::unique_ptr<Matrix> D = MatrixFactory::createUMatrix(Nrow,"matrix_trash");
  std::unique_ptr<Matrix> E = MatrixFactory::createUMatrix(Nrow,"matrix_trash");
  std::unique_ptr<Matrix> F = MatrixFactory::createUMatrix(Nrow,"matrix_trash");
  end1 = std::chrono::system_clock::now();
  elapsed = end1 - start1;
  printf("Setup - %.4f s\n", elapsed.count());

  start1=std::chrono::system_clock::now();
  for(size_t i=0;i<Nrow;++i){
    for(size_t j=0;j<Nrow;++j){
      D->fillData(i,j,unif(re));
      E->fillData(i,j,unif(re));
    }
  }
  end1 = std::chrono::system_clock::now();
  elapsed = end1 - start1;
  printf("RandFill - %.4f s\n", elapsed.count());

  start1=std::chrono::system_clock::now();
  *D = (*D) + (*E);
  end1 = std::chrono::system_clock::now();
  elapsed = end1 - start1;
  printf("Add - %.4f s\n", elapsed.count());
  D->printMatrix();
  E->printMatrix();

  start1=std::chrono::system_clock::now();
  (*F) = (*D) * (*E);
  end1 = std::chrono::system_clock::now();
  elapsed = end1 - start1;
  printf("Mult - %.4f s\n", elapsed.count());
  F->printMatrix();




  //A.printMatrix();
  //for(size_t i=0;i<10;++i) B.fillData(i,i,(double) i);
  //printf("B - then A = A + B \n");
  //B.printMatrix();
  //A = A + B;
  //A.printMatrix();

  //E->printMatrix();
  //*E = A * B;
  //printf("Here's A * B\n");
  //E->printMatrix();

#if 0
  std::unique_ptr<Matrix> F = MatrixFactory::createUMatrix(4,"matrix_trash");
  std::unique_ptr<Matrix> G = MatrixFactory::createUMatrix(4,"matrix_trash");

  for(size_t i=0;i<4;++i){
    for(size_t j=0;j<4;++j){
      if(i == j){
        F->fillData(i,j,(double) i+j);
        G->fillData(i,j,(double) i-j);
      }else{
        F->fillData(i,j,i);
        G->fillData(i,j,j);
      }
    }
  }
  F->printMatrix();
  G->printMatrix();
  *F = *F * *G; //overload operators with ptrs instead of references? urgh....
  F->printMatrix();

  Matrix* H = MatrixFactory::createMatrix(10,"matrix_dense");
  Matrix* I = MatrixFactory::createMatrix(10,"matrix_dense");

  for(size_t i=0;i<10;++i){
    for(size_t j=0;j<10;++j){
      if(i == j){
        H->fillData(i,j,(double) i+j);
        I->fillData(i,j,(double) i*j);
      }else{
        H->fillData(i,j,(double) j-i);
        I->fillData(i,j,(double) i-2.0*j);
      }
    }
  }

  I->printMatrix();
  H->printMatrix();

  *H = *H + *I;
  H->printMatrix();
#endif



  return 0;
}

