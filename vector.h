#ifndef _VECTOR_H_
#define _VECTOR_H_

#include "headers.h"

//note, templates are stupid. they cause bloat, without generally being useful. avoid if possible
//this is an abstract template class. while there's no point in making a vector a template, it 
//is kinda fun to experiment with sparse vectors. what is a bcsr vector anyway? a banded vector?


//template <class T>
class Vector{
  protected:
    std::string type;

  public:
    virtual ~Vector() = 0;
    virtual void printVector() = 0;

};


class DenseVector : public virtual Vector{

  protected:
    //std::vector<T> data;

  public:
    DenseVector(size_t dim);
    ~DenseVector();


};



#endif
