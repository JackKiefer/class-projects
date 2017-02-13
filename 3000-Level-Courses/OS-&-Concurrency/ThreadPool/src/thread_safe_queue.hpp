#ifndef THREAD_SAFE_QUEUE_HPP
#define THREAD_SAFE_QUEUE_HPP

#include <queue>
#include <mutex>


template <typename T>
class ThreadSafeQueue
{
public:
  void enqueue(T t) 
  { 
    std::lock_guard<std::mutex> lock(m);
    que.push(t); 
  } 

  bool try_dequeue(T & item) 
  {
    std::lock_guard<std::mutex> lock(m);
    if (que.empty()) return false;
    item = que.front();
    que.pop();
    return true;
  }
  
  bool empty() { return que.empty(); }

//  template<typename Ts..>
//  void emplace(..Ts args){ T(..args) }
  
private:
  std::queue<T> que;
  std::mutex m;
};


/*
class ThreadPool
{
public:
  ThreadPool(int n) :que(), pool(n), shouldContinue(false)
  {
    for(auto && t : pool)
    {
      t = std::thread([que&]()
      {
        while(shouldContinue)
        {
          std::function<void(void)> task;
          auto hasTask = que.dequeue(task);
          if (!shouldContinue) return;
          if (hasTask) task();
        }
      })
    }
  }
  ~ThreadPool
  {
    for (auto&& thread : pool) thread.join();
  }

  void post(std::function<void(void)> f, int id)
  {
    {// CRITICAL SECTION
      std::lock_guard lock(m);
      counts[id] += 1;
    }
    que.enqueue(f);
  void then(std::function<void(void)> f, int id)
  {

  void stop() { shouldContinue = false; }

private:
  ThreadSafeQueue<std::function<void(void)>> que;
  std::vector<std::thread> pool;
  std::atomic<bool> shouldContinue;
  std::map<int,int> counts;
  std::map<int,std::function<void(void)> f, int i
};
*/

#endif
