#include "timing.h"

Time::Time(){
  start_time ;
  end_time ;
}

void Time::start(){
  start_time = std::chrono::steady_clock::now();
}

void Time::stop(){
  end_time = std::chrono::steady_clock::now();
}

void Time::reset(){
  start_time ;
  end_time ;
}

double Time::get_steady(){
  if(end_time > start_time){
    std::chrono::duration<double> elapsed = end_time - start_time;
    return elapsed.count();
  }
  return -1;
}

