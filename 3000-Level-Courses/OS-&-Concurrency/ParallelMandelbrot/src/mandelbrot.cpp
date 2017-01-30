#include "mandelbrot.hpp"
#include <fstream>
#include <iostream>
#include <thread>
#include <vector>
#include <vector>

// Reads in data from input.txt
void Mandelbrot::getBoundaries()
{
  fin >> dimension;
  fin >> XMin;
  fin >> YMin;
  fin >> XMax;
  fin >> DIVIDES;

  YMax = YMin + (XMin - XMax);

  std::vector<std::vector<int>> temp(dimension, std::vector<int>(dimension, 1000));
  iters = temp;
}

// Writes PPM header to file
void Mandelbrot::headerOut()
{
  fout << "P3" << std::endl;
  fout << dimension << " " << dimension << std::endl;
  fout << colorDepth << std::endl;
}

// Prints the colors of a specified pixel
void Mandelbrot::printPx(int x, int y)
{
  auto iter = getMandelbrot(x, y);
  std::cout << "R: " << getRed(iter) << std::endl;
  std::cout << "G: " << getGreen(iter) << std::endl;
  std::cout << "B: " << getBlue(iter) << std::endl;
}

int Mandelbrot::getRed(int iter) { return (iter > 999) ? 0 : iter; }
int Mandelbrot::getBlue(int iter) { return (iter > 999) ? 0 : iter; }  //* iter % dimension; }
int Mandelbrot::getGreen(int iter) { return (iter > 999) ? 0 : iter; } // * iter % dimension; }

// Writes pixel to output.ppm
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

// For timing purposes
void Mandelbrot::calculate() { threadIters(); }

// Writes mandelbrot to output.ppm
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

// Calculates mandelbrot iterations and stores them in the iters vector
void Mandelbrot::calcPx(int startX, int startY, int endX, int endY)
{
  for (int y = startY; y <= endY; ++y)
  {
    for (int x = startX; x <= endX; ++x)
    {
      int iteration = getMandelbrot(x, y);
      iters[x][y] = iteration;
    }
  }
}

// Recursively divides the image in a horizontal fashion
void Mandelbrot::divideY(int startX, int startY, int endX, int endY, unsigned int divCt)
{
  if (divCt < DIVIDES)
  {
    ++divCt;
    int halfY = ((endY - startY) * 0.5) + startY;
    divideX(startX, startY, endX, halfY, divCt);
    divideX(startX, halfY + 1, endX, endY, divCt);
  }
  else
  {
    getPx(startX, startY, endX, endY, divCt);
  }
}

// Recursively divides the image in a veritcal fashion
void Mandelbrot::divideX(int startX, int startY, int endX, int endY, unsigned int divCt)
{
  if (divCt < DIVIDES)
  {
    ++divCt;
    int halfX = ((endX - startX) * 0.5) + startX;
    divideY(startX, startY, halfX, endY, divCt);
    divideY(halfX + 1, startY, endX, endY, divCt);
  }
  else
  {
    getPx(startX, startY, endX, endY, divCt);
  }
}

/* Skips calculation of pixels in the given region if the edge pixels are
 * all within the set. Otherwise, just calculates the pixels.
 */
void Mandelbrot::getPx(int startX, int startY, int endX, int endY, int divCt)
{
  if (divCt > 0 && edgesInSet(startX, startY, endX, endY))
  {
    return;
  }
  else
  {
    calcPx(startX, startY, endX, endY);
  }
}

// Commences slicing of image into separate calculatable pieces
void Mandelbrot::slice(int startY, int endY)
{
  auto divCt = 0u;
  int startX = 0;
  int endX = dimension - 1;

  divideX(startX, startY, endX, endY, divCt);
}

// Divides image into threaded segments
void Mandelbrot::threadIters()
{
  auto divs = THREAD_CT + 1;
  auto start = 0;

  for (auto i = 0u; i < divs - 1; ++i)
  {
    auto end = (dimension / divs) + start;
    threads.push_back(std::thread(
        [=]() { this->slice(start, end); }));

    start = end;
  }
  slice(start, dimension - 1);

  for (auto i = 0u; i < THREAD_CT; ++i)
    threads[i].join();
}

// Returns true if every edge pixel in the range is within the set
bool Mandelbrot::edgesInSet(int startX, int startY, int endX, int endY)
{
  // First row
  for (int x = startX; x <= endX; ++x)
  {
    if (getMandelbrot(x, startY) != 1000)
    {
      //      iters[x][startY] = 999;
      return false;
    }
  }

  // Vertical edges
  for (int y = startY; y <= endY; ++y)
  {
    if (getMandelbrot(startX, y) != 1000 || getMandelbrot(endX, y) != 1000)
    {
      //    iters[startX][y] = 999;
      //     iters[endX][y] = 999;
      return false;
    }
  }

  // Last row
  for (int x = startX; x <= endX; ++x)
  {
    if (getMandelbrot(x, endY) != 1000)
    {
      //    iters[x][endY] = 999;
      return false;
    }
  }

  return true;
}

// Makes mandelbrot
void Mandelbrot::generate()
{
  getBoundaries();
  headerOut();

  threadIters();

  write();
}
