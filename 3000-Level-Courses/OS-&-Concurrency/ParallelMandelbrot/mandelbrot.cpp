#include <fstream>
#include <iostream>
#include <vector>
#include <vector>
#include "mandelbrot.hpp"

void Mandelbrot::getBoundaries()
{
  fin >> dimension;
  fin >> XMin;
  fin >> YMin;
  fin >> XMax;

  YMax = YMin + (XMin - XMax);

  std::vector< std::vector<int> > temp( dimension, std::vector<int>(dimension));
  iters = temp;
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

// from en.wikipedia.org/wiki/Mandelbrot_set
int Mandelbrot::getMandelbrot(int Px, int Py) const
{
  double x0 = (Px * ((XMax - XMin) / dimension)) + XMin;
  double y0 = (Py * ((YMax - YMin) / dimension)) + YMin; 
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


void Mandelbrot::write()
{
  for (int i = 0; i < dimension; ++i)
  {
    for (int j = 0; j < dimension; ++j)
    {
      pixelOut(iters[j][i]);
    }
    fout << std::endl;
  }
}

void Mandelbrot::getIters(int begin, int end)
{
  for (int y = begin; y < end; ++y)
  {
    for (int x = 0; x < dimension; ++x)
    {
      int iteration = getMandelbrot(x, y);
      iters[x][y] = iteration;
    }
  }
}

void Mandelbrot::threadIters()
{
  auto divs = threads.size() + 1;
  auto start = 0;

  for(auto i = 0u; i < divs - 1; ++i)
  {
    auto end = (dimension / divs) + start;
    getIters(start, end);
    start = end;
  }
}

void Mandelbrot::generate()
{
  getBoundaries();
  headerOut();

  threadIters();

  write();
}

