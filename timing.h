#include <chrono>

class Time{
  public:
    Time();
    double get_steady();
    void start();
    void stop();
    void reset();

  private:
    std::chrono::time_point<std::chrono::steady_clock> start_time;
    std::chrono::time_point<std::chrono::steady_clock> end_time;

};

