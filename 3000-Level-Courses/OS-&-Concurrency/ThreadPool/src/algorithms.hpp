#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include <vector>
#include <iostream>
#include <algorithm>
#include <thread>
#include "threadpool.hpp"

template <typename T>
int partition(std::vector<T>& vec, int start, int end, int pivot)
{
  std::swap(vec[pivot],vec[end]);
  int firstGreater = start;
  for (int i = start; i < end; ++i)
  {
    if (vec[i] <= vec[end])
    {
      std::swap(vec[i], vec[firstGreater]);
      ++firstGreater;
    }
  }
  std::swap(vec[end], vec[firstGreater]);
  return firstGreater;
}

template <typename T>
int getPivot(std::vector<T> & vec, int start, int end)
{
  auto first = vec[start];
  auto last = vec[end];
  auto mid = vec[(start + end) / 2];

  if ((first <= last && last <= mid)  || (mid <= last && last <= first)) return end;
  else if ((last <= first && first <= mid) || (mid <= first && first <= last)) return start;
  else return (start + end) / 2;
}

template <typename T>
void serialQuickSort(std::vector<T> & vec, int start, int end)
{
  if (end - start <= 1) return;
  auto pivot = getPivot(vec, start, end);
  pivot = partition(vec, start, end, pivot);

  serialQuickSort(vec, start, pivot - 1);
  serialQuickSort(vec, pivot, end - 1);
}

template <typename T>
bool serialLinearSearch(std::vector<T> & vec, T target)
{
  for (auto&& e : vec) if (e == target) return true;
  return false;
}

template <typename T>
bool linearSearch(std::vector<T> & vec, int target, int start, int end)
{
  for (int i = start; i <= end; ++i)
  {
    if (vec[i] == target) return true;
  }
  return false;
}

template <typename T>
bool parallelLinearSearch(std::vector<T> & vec, T target, int threadCt)
{
  bool foundInVec = false;

  {
    ThreadPool pool(threadCt);
    auto segSize = vec.size() / 4;

    int start = 0;
    int end = segSize - 1;

    for (int i = 0; i < 4; ++i)
    {
      pool.post([=, &vec, &foundInVec](){ 

        bool foundInSeg = linearSearch(vec, target, start, end); 
        if (foundInSeg) foundInVec = true;

        });
      start = end + 1;
      end += segSize;
    }
  }
  return foundInVec;
}

template <typename T>
void parallelQuickSort(std::vector<T> & vec, int start, int end, ThreadPool & pool)
{
  if (end - start <= 1) return;
  auto pivot = getPivot(vec, start, end);
  pivot = partition(vec, start, end, pivot);

  pool.post([=, &vec, &pool](){
  parallelQuickSort(vec, start, pivot - 1, pool); 
  });

  pool.post([=, &vec, &pool](){
  parallelQuickSort(vec, pivot, end - 1, pool);
  });
}

template <typename T>
void parallelQuickSort(std::vector<T> & vec, int threadCt) 
{
  ThreadPool pool(threadCt);
  pool.post([&](){ parallelQuickSort(vec, 0, vec.size(), pool); });
}

template <typename T>
void serialQuickSort(std::vector<T> & vec) { serialQuickSort(vec, 0, vec.size()); }

#endif
