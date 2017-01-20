#include <iostream>
#include "mandelbrot.hpp"
#include "timer.hpp"

namespace
{
  const auto REPEATS = 13;
}

void getColor(Mandelbrot & m)
{
  std::cout << "Now to demonstrate the single-pixel color computation function." << std::endl
    << "Enter an x-coordinate between 0 and " << m.getDimension() - 1 << ':' << std::endl;

  int x;
  std::cin >> x;

  std::cout << "And now the y-coordinate within the same bounds:" << std::endl;
  
  int y;
  std::cin >> y;

  std::cout << "The color of the pixel at those coordinates is: " << std::endl;
  m.printPx(x,y);
}

void printIntro()
{
  std::cout << "We shall now generate the Mandelbrot image 13 times" << std::endl
    << "(the first three runs will be ignored in the computation of" << std::endl
    << "the average and the standard deviation)" << std::endl;

  std::cout << "Running..." << std::endl;
}

void timeMandelbrot(Mandelbrot & m, Timer & timer)
{
  for (int k = 0; k < REPEATS; ++k)
  {
    timer.reset();
    timer.start();
    for (int i = 0; i < m.getDimension(); ++i)
    {
      for (int j = 0; j < m.getDimension(); ++j)
      {
        int iter = m.calculate(j,i);
        (void)iter;
      }
    }
    timer.end();
    std::cout << timer.toString() << std::endl;
    timer.push();
  }
}
 

int main()
{
  Mandelbrot m;
  Timer timer;
 
  printIntro();
  timeMandelbrot(m, timer);
  timer.printAverage();
  timer.printStdDev();

  getColor(m);
  m.generate();
}
