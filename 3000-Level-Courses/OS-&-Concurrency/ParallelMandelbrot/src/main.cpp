#include "mandelbrot.hpp"
#include "timer.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>

int main()
{
  const auto REPEATS = 12;
  const auto MAX_THREADS = 7;

  std::ofstream avg;
  avg.open("avg.data");

  float firstAvg = 0;

  for (int k = 0; k <= MAX_THREADS; ++k)
  {

    std::cout << k + 1 << " threads " << std::endl;

    Timer timer;

    for (int i = 0; i < REPEATS; ++i)
    {
      Mandelbrot m;
      m.getBoundaries();
      m.setThreads(k);
      timer.reset();
      timer.start();
      m.calculate();
      timer.end();
      timer.push();
      std::cout << timer.toString() << std::endl;
    }

    auto average = timer.getAverage();
    avg << k + 1 << ' ' << average << ' ' << std::endl;

    if (k == 0)
    {
      firstAvg = average;
    }

    float speedup = firstAvg / average;

    timer.printAverage();
    timer.printStdDev();
    std::cout << "Speedup: " << speedup << std::endl;
    std::cout << std::endl;
  }

  Mandelbrot image;
  image.generate();
}
