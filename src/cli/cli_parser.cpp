#include "CLI/CLI.hpp"
#include <iostream>

int main(int argc, char **argv)
{
  CLI::App olt{"OpenLAMMPSToolbox App"};

  // Define options
  std::string infile;
  int p = 0;
  olt.add_option("-f", infile, "Required LAMMPS Dump File")
      ->required()
      ->check(CLI::ExistingFile);

  CLI11_PARSE(olt, argc, argv);

  return 0;
}
