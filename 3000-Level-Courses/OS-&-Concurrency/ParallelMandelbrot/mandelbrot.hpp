#ifndef MANDELBROT_HPP
#define MANDELBROT_HPP

#include <fstream>
#include <vector>
#include <thread>

class Mandelbrot
{
public:
  Mandelbrot() :colorDepth(255), fin("input.txt"), fout("output.ppm") 
  {
    threads = std::vector<std::thread>(3);
  }
  void generate();  
  void printPx(int,int);
  int calculate(int,int);
  int getDimension() { return dimension; }
private:
  int getMandelbrot(int,int) const;
  int getRed(int);
  int getBlue(int);
  int getGreen(int);
  void write();
  double interpolateX(int);
  double interpolateY(int);
  void pixelOut(int);
  void headerOut();
  void getBoundaries();
  void getIters(int,int);
  void threadIters();
  int colorDepth;
  int dimension;
  double XMin;
  double XMax;
  double YMin;
  double YMax;
  std::ifstream fin;
  std::ofstream fout;
  std::vector< std::vector<int> > iters;
  std::vector<std::thread> threads;
};

#endif
