#ifndef TIME_HPP
#define TIME_HPP

#include <chrono>
#include <string>
#include <sstream>
#include <iostream>

class Time
{
public:
  void start();
  void end();
  std::string ms();
  std::string us();
private:
  std::chrono::high_resolution_clock::time_point m_start;
  std::chrono::high_resolution_clock::time_point m_end;
};

void Time::start()
{
  m_start = std::chrono::high_resolution_clock::now();
}


void Time::end()
{
  m_end = std::chrono::high_resolution_clock::now();
}

std::string Time::ms()
{
	std::ostringstream oss;
  auto dur = m_end - m_start;
  auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur);
  oss << ms.count() << " milliseconds";
	return oss.str();
}

std::string Time::us()
{
	std::ostringstream oss;
  auto dur = m_end - m_start;
  auto us = std::chrono::duration_cast<std::chrono::microseconds>(dur);
  oss << us.count() << " microseconds";
	return oss.str();
}

#endif
