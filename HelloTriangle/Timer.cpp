
#include "Timer.h"
#include <iomanip>
#include <sstream>
#include "Defs.h"

//////////////////////////////////////////////////////////////////////////////////
//
//    Timer
//

Timer::Timer(const std::string& desc) : _begin (std::chrono::high_resolution_clock::now()), _desc(desc)
{
  AI_NOP;
}

//////////////////////////////////////////////////////////////////////////////////
//
//    LogSeconds
//

void 
Timer::LogSeconds()
{

  std::chrono::time_point <std::chrono::steady_clock>
    now = std::chrono::high_resolution_clock::now();

  uint64_t
    microseconds = std::chrono::duration_cast<std::chrono::microseconds>(now - _begin).count();

  float
    rSeconds = microseconds / 1000.f / 1000.f;

  std::string s;
  std::ostringstream os;

  os << _desc << ": " << std::setprecision(2) << std::fixed << rSeconds << "s." << std::endl;

  s = os.str();

}

//////////////////////////////////////////////////////////////////////////////////
//
//    LogBandwidth
//

void
Timer::LogBandwidth(uint64_t uByteCount)
{
  std::chrono::time_point <std::chrono::steady_clock>
    end_time = std::chrono::high_resolution_clock::now();

  uint64_t
    microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end_time - _begin).count();

  float
    rSeconds = microseconds / 1000.f / 1000.f;

  float
    rBPerSecond = uByteCount / rSeconds;

  float
    rKiBPerSecond = rBPerSecond / 1024.f;

  float
    rMiBPerSecond = rKiBPerSecond / 1024.f;

  float
    rGiBPerSecond = rMiBPerSecond / 1024.f;

  float
    rTiBPerSecond = rGiBPerSecond / 1024.f;

  float
    rDataPerSecond;

  std::string
    unit;

  if (rTiBPerSecond > 1.f)
  {
    rDataPerSecond = rTiBPerSecond;
    unit = "TiB/s";
  }
  else if (rGiBPerSecond > 1.f)
  {
    rDataPerSecond = rGiBPerSecond;
    unit = "GiB/s";
  }
  else if (rMiBPerSecond > 1.f)
  {
    rDataPerSecond = rMiBPerSecond;
    unit = "MiB/s";
  }
  else if (rKiBPerSecond > 1.f)
  {
    rDataPerSecond = rKiBPerSecond;
    unit = "KiB/s";
  }
  else
  {
    rDataPerSecond = rBPerSecond;
    unit = "B/s";
  }

  std::ostringstream
    os;

  os << _desc << ": " << std::setfill(' ') << std::setw(5) << std::setprecision(1) << std::fixed << rDataPerSecond << unit << std::endl;


  
}

//////////////////////////////////////////////////////////////////////////////////
//
//    LogBandwidth
//

void
Timer::LogBandwidth(uint64_t uByteCount, uint64_t uReadBytes, uint64_t reportThreshold)
{

  if ((uByteCount + uReadBytes) / reportThreshold > uByteCount / reportThreshold)
  {
    LogBandwidth(uByteCount);
  }
}





