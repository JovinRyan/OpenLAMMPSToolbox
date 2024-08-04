#include "CLI/CLI.hpp"
#include <iostream>

int main(int argc, char **argv)
{
  CLI::App olt{"OpenLAMMPSToolbox App"};

  // Defining options
  std::string infile;
  std::string ftype;

  int p = 0;
  olt.add_option("-f", infile, "Required LAMMPS Dump File")
      ->required()
      ->check(CLI::ExistingFile);

  olt.add_option("-ftype", ftype, "Dump File Type.");

  CLI11_PARSE(olt, argc, argv);

  return 0;
}
