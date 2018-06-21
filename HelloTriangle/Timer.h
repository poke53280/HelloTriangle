#pragma once

#include <chrono>
#include <string>


class Timer
{

  const std::chrono::time_point <std::chrono::steady_clock> _begin;
  const std::string _desc;

public:
          Timer(const std::string& desc);
  void    LogSeconds();
  void    LogBandwidth(uint64_t uByteCount);
  void    LogBandwidth(uint64_t uByteCount, uint64_t uReadBytes, uint64_t reportThreshold);

};


