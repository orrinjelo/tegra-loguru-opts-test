#include <iostream>
#define LOGURU_IMPLEMENTATION 1
#define LOGURU_WITH_STREAMS 1
#include "loguru.hpp"

int main()
{
  LOG_S(info) << "There are no threads named here." << std::endl;
  LOG_S(error) << "Something has ceased to work." << std::endl;
  LOG_S(info) << "Whatever.  This has to fail sometime." << std::endl;

  for (int i=0; i<20; ++i)
    LOG_S(warning) << "The number is " << i << std::endl;
  return 0;
}
