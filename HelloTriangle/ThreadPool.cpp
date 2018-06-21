
#include "Defs.h"
#include "ThreadPool.h"
#include <thread>
#include <vector>

//////////////////////////////////////////////////////////////////////////////////
//
//    MyFunctor2
//

class MyFunctor2
{

  unsigned int* _pData;
  const int _n;

public:
  MyFunctor2(unsigned int* pData, const int n) : _pData(pData), _n(n)
  {
    AI_NOP;
  }


public:
  void operator()() {
    _pData[_n] = _n * 2;
  }
};


//////////////////////////////////////////////////////////////////////////////////
//
//    ThreadPool
//

ThreadPool::ThreadPool()
{
  // ...
}

//////////////////////////////////////////////////////////////////////////////////
//
//    ExecuteTest
//

void
ThreadPool::ExecuteTest()
{
  unsigned int
    nHWThreads = std::thread::hardware_concurrency();

  unsigned int* data = new unsigned int[nHWThreads];

  std::vector<std::thread> threads(nHWThreads);

  unsigned int
    uThread = 0;

  for (std::thread& t : threads)
  {
    t = std::thread(MyFunctor2(data, uThread));
    uThread++;
  }

  for (std::thread& t : threads)
  {
    t.join();
  }

  delete[] data;
  data = nullptr;


}