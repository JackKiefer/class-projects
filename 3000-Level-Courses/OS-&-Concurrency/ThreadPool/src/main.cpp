#include <iostream>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include "threadpool.hpp"
#include "algorithms.hpp"
#include "timer.hpp"

std::vector<int> getVec(int size)
{
  std::vector<int> vec;
  for (int i = 0; i < size; ++i)
  {
    vec.push_back(rand());
  }
  return vec;
}

void printBar(float prog, int total, std::string message)
{
  float progress = prog / total;
  int barWidth = 70;

  if (message != "")
  {
  std::cout << std::setw(barWidth + 7) << std::left << message << std::endl;
  }
  
  std::cout << "[";
  int pos = barWidth * progress;
  for (int i = 0; i < barWidth; ++i) 
  {
      if (i < pos) std::cout << "\033[32m#\033[0m";
      else if (i == pos) std::cout << ">";
      else std::cout << " ";
  }
  std::cout << "] " << int(progress * 100.0) << " %\r";
  std::cout.flush();
}

int main()
{
  std::ofstream sorting;
  sorting.open("sorting.data");
  sorting << "Vector Size,std::sort,serial,1 thread,2 threads,3 threads,4 threads,5 threads,6 threads,7 threads,8 threads" << std::endl;

  std::ofstream searching;
  searching.open("searching.data");
  searching << "Vector Size,std::find,serial,1 thread,2 threads,3 threads,4 threads,5 threads,6 threads,7 threads,8 threads" << std::endl;
  Timer timer;
  float prog = 0;

  
  std::cout << std::endl << "Obtaining searching averages, please wait..." << std::endl;


  for (int size = 100; size <= 1000000; size *= 10)
  {
    ++prog;
    std::string message = "std::find, vector size: " + std::to_string(size);
    printBar(prog, 295, message);
    searching << size << ',';
      
    // std::find
    for (int i = 0; i < 5; ++i)
    {
      ++prog;
      printBar(prog, 295, "");
      auto vec = getVec(size);
      timer.reset();
      timer.start(); 
      std::find(vec.begin(), vec.end(), rand() % size);
      timer.end();
      timer.push();
    }

    searching << timer.getAverage() << ',';
    timer.clear();


    message = "Linear search, vector size: " + std::to_string(size);
    printBar(prog, 295, message);
    // Serial linear search
    for (int i = 0; i < 5; ++i)
    {
      ++prog;
      printBar(prog, 295, "");
      auto vec = getVec(size);
      timer.reset();
      timer.start(); 
      serialLinearSearch(vec, rand() % size);
      timer.end();
      timer.push();
    }

    searching << timer.getAverage() << ',';
    timer.clear();

    // Parallel linear search with threadpool
    for (int threadCt = 1; threadCt <= 8; ++threadCt)
    {
      ++prog;
      std::string message = "Parallel search, vector size: " + std::to_string(size) + ", threads: " + std::to_string(threadCt);
      printBar(prog, 295, message);
      for (int i = 0; i < 5; ++i)
      {
        ++prog;
        printBar(prog, 295, ""); 
        auto vec = getVec(size);
        timer.reset();
        timer.start();
        parallelLinearSearch(vec, rand() % size, threadCt);
        timer.end();
        timer.push();
      }

      searching << timer.getAverage() << ',';
      timer.clear();
    }
    searching << std::endl;
  }
  std::cout << std::setw(87) << std::left << "\033[32m[SUCCESS]\033[0m" << std::endl;
  std::cout << std::endl;

  std::cout << std::endl << "Obtaining sorting averages, please wait..." << std::endl;

  prog = 0;
  for (int size = 100; size <= 1000000; size *= 10)
  {
    ++prog;
    std::string message = "std::sort, vector size: " + std::to_string(size);
    printBar(prog, 295, message);
    sorting << size << ',';

    // std::sort
    for (int i = 0; i < 5; ++i)
    {
      ++prog;
      printBar(prog, 295, ""); 
      auto vec = getVec(size);
      timer.reset();
      timer.start(); 
      std::sort(vec.begin(),vec.end());
      timer.end();
      timer.push();
    }

    sorting << timer.getAverage() << ',';
    timer.clear();

    
    message = "Serial quicksort, vector size: " + std::to_string(size);
    printBar(prog, 295, message);
    // Serial quicksort
    for (int i = 0; i < 5; ++i)
    {
      ++prog;
      printBar(prog, 295, ""); 
      auto vec = getVec(size);
      timer.reset();
      timer.start(); 
      serialQuickSort(vec);
      timer.end();
      timer.push();
    }

    sorting << timer.getAverage() << ',';
    timer.clear();

    // Parallel quicksort with threadpool
    for (int threadCt = 1; threadCt <= 8; ++threadCt)
    {
      ++prog;
      std::string message = "Parallel quicksort, vector size: " + std::to_string(size) + ", threads: " + std::to_string(threadCt);
      printBar(prog, 295, message);
      for (int i = 0; i < 5; ++i)
      {
        ++prog;
        printBar(prog, 295, "");
        auto vec = getVec(size);
        timer.reset();
        timer.start();
        parallelQuickSort(vec, threadCt);
        timer.end();
        timer.push();
      }

      sorting << timer.getAverage() << ',';
      timer.clear();
    }
    sorting << std::endl;
  }

  std::cout << std::setw(87) << std::left << "\033[32m[SUCCESS]\033[0m" << std::endl;
}

