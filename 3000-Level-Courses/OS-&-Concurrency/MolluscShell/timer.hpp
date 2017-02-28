#ifndef TIMER_HPP
#define TIMER_HPP

#include <chrono>
#include <cmath>
#include <iostream>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

class Timer
{
public:
  Timer() : summed(false), dur(0), total(0) {}
  void start();
  void end();
  void addToTotal()
  {
    total += dur;
    summed = true;
  }
  std::string toString();
  long toLong();
  void push();
  void reset();
  double getAverage();
  double getStdDev();
  void printAverage() { std::cout << "Average: " << getAverage() << " microseconds" << std::endl; }
  void printStdDev() { std::cout << "Standard Deviation: " << getStdDev() << std::endl; }
private:
  std::vector<double> getSquareDifs(double);
  bool summed;
  int pushes = 0;
  const int CACHE_BUFF = 3;
  std::chrono::steady_clock::time_point startTime;
  std::chrono::steady_clock::time_point endTime;
  std::chrono::duration<double, std::micro> dur;
  std::chrono::duration<double, std::micro> total;
  std::chrono::microseconds us;
  std::vector<long> times;
};

#endif
