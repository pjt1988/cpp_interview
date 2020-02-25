#ifndef _MATRIX_H_
#define _MATRIX_H_

#if 0
Class definition of Parent Class Matrix and Children. What are some useful datafields to have? 

pjt
#endif

#include "headers.h"

//Matrix is a purely virtual base class. This is an abstract class. All functions of the base class MUST be fully defined in the children
class Matrix {
  public:
    size_t N; //dimension
    //how do we store data?

    //we'll be writing pretty code now...
    //virtual Matrix& operator+(const Matrix&) = 0;
    //virtual Matrix& operator*(const Matrix&) = 0;
    //virtual Matrix& operator=(const Matrix&) = 0;
    //virtual Matrix& operator=(const Matrix &&) = 0;
    virtual ~Matrix()=0;

    //some functions...
    virtual void fillData(size_t N, size_t M, double val) = 0; //is this efficient?
    virtual void printMatrix() = 0;
    std::string get_type() const{return type;}; //we should not be able to modify the type, but we need to know it in case we do comparisions. eg can't add a dense and a BCSR matrix together

  protected:
    std::string type;
};


class DenseMatrix : public virtual Matrix{
  public:
    DenseMatrix& operator+(const DenseMatrix&); 
    DenseMatrix& operator*(const DenseMatrix&);
    //rule of 3 - constructor, destructor, copy constructor+copy assign
    DenseMatrix(size_t dim);
    DenseMatrix(DenseMatrix&);
    ~DenseMatrix();
    DenseMatrix& operator=(const DenseMatrix&);
    //rule of 5 - rule of 3 + move constructor + move assign
    DenseMatrix(DenseMatrix &&);
    DenseMatrix& operator=(const DenseMatrix &&);

    void fillData(size_t N, size_t M, double val) override;
    void printMatrix() override;
    void copy(const DenseMatrix& A);
    std::vector<double>& get_data() {return data;}; // this is lazy, but acceptable for returning member variables

    std::vector<double> data;

  private:
};


#endif
