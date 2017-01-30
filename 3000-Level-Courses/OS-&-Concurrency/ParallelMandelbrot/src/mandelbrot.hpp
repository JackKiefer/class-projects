#ifndef MANDELBROT_HPP
#define MANDELBROT_HPP

#include <fstream>
#include <thread>
#include <vector>

class Mandelbrot
{
public:
  Mandelbrot() : colorDepth(255), fin("input.txt"), fout("output.ppm")
  {
    //    auto n = std::thread::hardware_concurrency();
    //    THREAD_CT = n - 1;
  }
  void generate();
  void printPx(int, int);
  void calculate();
  void getBoundaries();
  int getDimension() { return dimension; }
  void setThreads(int n) { THREAD_CT = n; }
private:
  bool edgesInSet(int, int, int, int);
  int getMandelbrot(int, int) const;
  void threadIters();
  void getPx(int, int, int, int, int);
  void fill(int, int, int, int);
  int getRed(int);
  int getBlue(int);
  int getGreen(int);
  void divideY(int, int, int, int, unsigned int);
  void divideX(int, int, int, int, unsigned int);
  void write();
  double interpolateX(int);
  double interpolateY(int);
  void pixelOut(int);
  void headerOut();
  void slice(int, int);
  void calcPx(int, int, int, int);
  int colorDepth;
  int dimension;
  double XMin;
  double XMax;
  double YMin;
  double YMax;
  unsigned int THREAD_CT = 0;
  unsigned int DIVIDES;
  std::ifstream fin;
  std::ofstream fout;
  std::vector<std::vector<int>> iters;
  std::vector<std::thread> threads;
};

#endif
