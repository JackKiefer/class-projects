#include <fstream>
#include <iostream>
#include "mandelbrot.hpp"

void Mandelbrot::getBoundaries()
{
  fin >> dimension;
  fin >> XMin;
  fin >> YMin;
  fin >> XMax;

  YMax = YMin + (XMin - XMax);
}

void Mandelbrot::headerOut()
{
  fout << "P3" << std::endl;
  fout << dimension << " " << dimension << std::endl;
  fout << colorDepth << std::endl;
}

void Mandelbrot::printPx(int x, int y)
{
  auto iter = calculate(x, y);
  std::cout << "R: " << getRed(iter) << std::endl;
  std::cout << "G: " << getGreen(iter) << std::endl;
  std::cout << "B: " << getBlue(iter) << std::endl;
}

int Mandelbrot::getRed(int iter) { return (iter > 999) ? 0 : iter; }
int Mandelbrot::getBlue(int iter) { return (iter > 999) ? 0 : iter * iter % dimension; }
int Mandelbrot::getGreen(int iter) { return (iter > 999) ? 0 : iter * iter % dimension; }

void Mandelbrot::pixelOut(int iter)
{
  fout << getRed(iter) << " " << getGreen(iter) << " " << getBlue(iter) << "\t";
}

double Mandelbrot::interpolateX(int pixel) { return (pixel * ((XMax - XMin) / dimension)) + XMin; }

double Mandelbrot::interpolateY(int pixel) { return (pixel * ((YMax - YMin) / dimension)) + YMin; }

// from en.wikipedia.org/wiki/Mandelbrot_set
int Mandelbrot::getMandelbrot(int Px, int Py)
{
  double x0 = interpolateX(Px);
  double y0 = interpolateY(Py);
  double x = 0.0;
  double y = 0.0;
  int iteration = 0;
  int max_iteration = 1000;
  while (x * x + y * y < 2 * 2 && iteration < max_iteration)
  {
    auto xtemp = x * x - y * y + x0;
    y = 2 * x * y + y0;
    x = xtemp;
    iteration = iteration + 1;
  }
  return iteration;
}

int Mandelbrot::calculate(int i, int j) { getBoundaries(); return getMandelbrot(i,j); }

void Mandelbrot::generate()
{
  getBoundaries();
  headerOut();

  for (int i = 0; i < dimension; ++i)
  {
    for (int j = 0; j < dimension; ++j)
    {
      int iteration = getMandelbrot(j, i);
      pixelOut(iteration);
    }
    fout << std::endl;
  }
}
