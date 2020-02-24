#include "matrix.h"

//this is a factory class. We don't need to follow the rules of 3/5 here. The sole purpose of this class is to return a properly derived pointer based on the string type

class MatrixFactory {
  public:

    static std::unique_ptr<Matrix> createUMatrix(size_t dim, const std::string& type){
      if(type == "matrix_dense")
        return std::unique_ptr<Matrix>(new DenseMatrix(dim));
    }
    static Matrix* createMatrix(size_t dim, const std::string& type){
      if(type == "matrix_dense")
        return new DenseMatrix(dim);
    }

};


