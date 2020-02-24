#include <vector>
#include <chrono>
#include <stdio.h>
#include <random>


void add_mat(double** A, double** B, double** C, size_t N){
  for(size_t i=0;i<N;++i){
    for(size_t j=0;j<N;++j){
      C[i][j] = A[i][j] + B[i][j];
    }
  }
}

void add_mat(std::vector<double>& A, std::vector<double>& B, std::vector<double>& C){
  for(size_t i=0;i<A.size();++i){
    C[i] = A[i]*B[i];
  }
}

void mult_mat(double** A, double** B, double** C, size_t N){
  for(size_t i=0;i<N;++i){
    for(size_t j=0;j<N;++j){
      for(size_t k=0;k<N;++k){
        C[i][j] += A[i][k] * B[k][j];
      }
    }
  }
}

void mult_mat(std::vector<double>& A, std::vector<double>& B, std::vector<double>& C, size_t N){
  for(size_t i=0;i<N;++i){
    for(size_t j=0;j<N;++j){
      for(size_t k=0;k<N;++k){
        C[i+j*N] += A[i+k*N] * B[k+j*N];
      }
    }
  }
}

int main(int argc, char** argv){
  size_t n=0;
  if(argc == 2){
    n=atoi(argv[1]); //get me the matrix dim
  }else{
    printf("We'll need some matrix dims N= as an input \n");
  }

  if(n==0){
    printf("Very funny....\n");
    exit(1);
  }
  
  double lower_bound = 0;
  double upper_bound = 100;
  std::uniform_real_distribution<double> unif(lower_bound,upper_bound);
  std::default_random_engine re;

  std::chrono::time_point<std::chrono::system_clock> start1,start2,end1,end2; //and this is why people generally write a wrapper function for this..
  printf("Setting up double**, doing C = A + B, and C = A * B \n");
  start1=std::chrono::system_clock::now();
  double** A = new double*[n];
  double** B = new double*[n];
  double** C = new double*[n];
  for(size_t i=0;i<n;++i){
    A[i] = new double[n];
    B[i] = new double[n];
    C[i] = new double[n];
    for(size_t j=0;j<n;++j){
      A[i][j] = unif(re);
      B[i][j] = unif(re);
      C[i][j] = 0.0;
    }
  }
  end1 = std::chrono::system_clock::now();
  std::chrono::duration<double> elapsed = end1 - start1;
  printf("Setup - %.4f s\n", elapsed.count());

  start1=std::chrono::system_clock::now();
  add_mat(A,B,C,n);
  end1 = std::chrono::system_clock::now();
  elapsed = end1 - start1;
  printf("C = A + B - %.4f s\n", elapsed.count());

  start1=std::chrono::system_clock::now();
  mult_mat(A,B,C,n);
  end1 = std::chrono::system_clock::now();
  elapsed = end1 - start1;
  printf("C = A * B - %.4f s\n", elapsed.count());

  start2=std::chrono::system_clock::now();
  printf("Setting up vector<double>, doing C = A + B, and C = A * B \n");
  std::vector<double> Av(n*n);
  std::vector<double> Bv(n*n);
  std::vector<double> Cv(n*n, 0.0);
  for(size_t i=0;i<n*n;++i){
    Av[i] = unif(re);
    Bv[i] = unif(re);
  }

  end2 = std::chrono::system_clock::now();
  elapsed = end2 - start2;
  printf("Setup vector - %.4f s\n", elapsed.count());

  start2=std::chrono::system_clock::now();
  add_mat(Av,Bv,Cv);
  end2 = std::chrono::system_clock::now();
  elapsed = end2 - start2;
  printf("vector C = A + B - %.4f s\n", elapsed.count());

  start2=std::chrono::system_clock::now();
  mult_mat(Av,Bv,Cv,n);
  end2 = std::chrono::system_clock::now();
  elapsed = end2 - start2;
  printf("vector C = A * B - %.4f s\n", elapsed.count());

  
  //remember, in C, you have to clean up after yourself
  for(size_t i=0;i<n;++i){
    delete[] A[i];
    delete[] B[i];
    delete[] C[i];
  }
  delete[] A;
  delete[] B;
  delete[] C;

  return 0;
}

