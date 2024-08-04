#include <iostream>
#include "containers/dump_data_container.h"
#include "read_write/read_file.h"

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    std::cerr << "No LAMMPS Dump File Provided!\n";

    return 1;
  }

  std::cout << "Reading Custom Dump File: " << argv[1] << "\n";
  std::ifstream infile(argv[1]);
  if (infile.is_open() && infile.good())
  {
    dump_data_container test = customToDumpData(infile);
  }

  return 0;
}
