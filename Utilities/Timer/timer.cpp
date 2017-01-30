#include "timer.hpp"
#include <chrono>
#include <cmath>
#include <iostream>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

void Timer::push()
{
  ++pushes;
  if (pushes > CACHE_BUFF)
    times.push_back(toLong());
}

void Timer::reset()
{
  dur = std::chrono::duration<double, std::milli>::zero();
  total = std::chrono::duration<double, std::milli>::zero();
}

double Timer::getAverage()
{
  auto sum = static_cast<double>(std::accumulate(times.begin(), times.end(), 0));
  auto size = static_cast<double>(times.size());
  return sum / size;
}

std::vector<double> Timer::getSquareDifs(double avg)
{
  std::vector<double> squareDifs;
  for (auto &&n : times)
  {
    auto dif = static_cast<double>(n - avg);
    squareDifs.push_back(dif * dif);
  }
  return squareDifs;
}

double Timer::getStdDev()
{
  auto avg = getAverage();
  std::vector<double> squareDifs = getSquareDifs(avg);
  auto sum = std::accumulate(squareDifs.begin(), squareDifs.end(), 0);
  auto size = static_cast<double>(squareDifs.size());
  double mean = sum / size;
  return std::sqrt(mean);
}

void Timer::start()
{
  startTime = std::chrono::steady_clock::now();
}

void Timer::end()
{
  endTime = std::chrono::steady_clock::now();
  dur = endTime - startTime;
}

std::string Timer::toString()
{
  std::ostringstream oss;
  oss << toLong() << " milliseconds";
  return oss.str();
}

long Timer::toLong()
{
  if (!summed)
    total = dur;
  us = std::chrono::duration_cast<std::chrono::milliseconds>(total);
  return us.count();
}
