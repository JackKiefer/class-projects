#ifndef THREAD_POOL_HPP
#define THREAD_POOL_HPP

#include <mutex>
#include <thread>
#include <functional>
#include <atomic>
#include "thread_safe_queue.hpp"

class ThreadPool
{
public:

  using func = std::function<void(void)>;

  ThreadPool(int n) :pool(n), queue(), taskMutex(), shouldContinue(true), taskCt(0)
  {
    for (auto&& thread : pool)
    {
      thread = std::thread([=]{this->run();});
    }
  }
  ~ThreadPool()
  {
    join_all();
  }

  void join_all() { for (auto&& thread : pool) thread.join(); };

  void stop() { shouldContinue = false; }

  void post(func f)
  { 
    { // Critical section
      std::lock_guard<std::mutex> lock(taskMutex);
      ++taskCt;
    }
    queue.enqueue(f); 
  } 

  void run()
  {
    while (shouldContinue)
    {
      func task;

      while (!queue.try_dequeue(task)) 
      {
        if (!shouldContinue) return;  
      }

      if (task)
      {
        task();
        { // Critical section
          std::lock_guard<std::mutex> lock(taskMutex);
          --taskCt;
          if (taskCt == 0) stop();
        }
      }
    }
  }

private:
  std::vector<std::thread> pool;
  ThreadSafeQueue<func> queue;
  std::mutex taskMutex;
  std::atomic<bool> shouldContinue;
  unsigned int taskCt;
};

#endif
