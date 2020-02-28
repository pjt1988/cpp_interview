#include "headers.h"

//note, templates are stupid. they cause bloat, without generally being useful. avoid if possible
//this is an abstract template class. while there's no point in making a vector a template, it 
//is kinda fun to experiment with sparse vectors. what is a bcsr vector anyway? a banded vector?


template <class T>
class Vector{
  protected:
    std::string type;

  public:
    virtual ~Vector() = 0;
    void printVector() = 0;

};
