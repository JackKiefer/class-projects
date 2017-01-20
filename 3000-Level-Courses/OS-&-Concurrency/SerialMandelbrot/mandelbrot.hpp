#ifndef MANDELBROT_HPP
#define MANDELBROT_HPP

#include <fstream>

class Mandelbrot
{
public:
  Mandelbrot() :colorDepth(255), fin("input.txt"), fout("output.ppm") {}
  void generate();  
  void printPx(int,int);
  int calculate(int,int);
  int getDimension() { return dimension; }
private:
  int getMandelbrot(int,int);
  int getRed(int);
  int getBlue(int);
  int getGreen(int);
  double interpolateX(int);
  double interpolateY(int);
  void pixelOut(int);
  void headerOut();
  void getBoundaries();
  int colorDepth;
  int dimension;
  double XMin;
  double XMax;
  double YMin;
  double YMax;
  std::ifstream fin;
  std::ofstream fout;
};

#endif
