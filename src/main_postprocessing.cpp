#include <iostream>
#include <fstream>

#include "cli/CLI11.hpp"

#include "containers/dump_data_container.h"
#include "read_write/read_file.h"
#include "calculations/ddc_get_displacement.h"
#include "utils/ddc_id_sort.h"

int main(int argc, char **argv)
{
  CLI::App olt{"OpenLAMMPSToolbox App"};

  // Defining options
  std::ifstream infile;
  std::string ftype = "";
  std::string function = "";
  double disp_threshold = 1;

  int p = 0;
  olt.add_option("--f", infile, "Required LAMMPS Dump File")
      ->required()
      ->check(CLI::ExistingFile);

  olt.add_option("--ftype", ftype, "Dump File Type");

  olt.add_option("--function", function, "Post-Processing Function");

  olt.add_option("--disp_threshold", disp_threshold, "Lattice Parameter");

  CLI11_PARSE(olt, argc, argv);

  if (ftype == "xyz" & function == "displacement")
  {
    dump_data_container xyz_ddc = xyzToDumpData(infile);

    std::vector<int> disp_vec = get_displacement_vec(xyz_ddc, disp_threshold);
  }

  if (ftype == "xyz" & function == "id_sort")
  {
    std::cerr << "Files of type XYZ are ID sorted by default.";
    return 1;
  }

  if (ftype == "custom" & function == "id_sort")
  {
    dump_data_container custom_ddc = customToDumpData(infile);

    ddc_id_quicksort(custom_ddc);
  }

  return 0;
}
