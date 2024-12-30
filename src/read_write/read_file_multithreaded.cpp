#include "read_write/read_file_multithreaded.h"

void DoWork()
{
}

int main()
{
  std::thread worker(DoWork);

  worker.join();

  return 0;
}
