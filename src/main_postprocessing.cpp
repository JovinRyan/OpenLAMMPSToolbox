#include <iostream>
#include <fstream>

#include "cli/CLI11.hpp"

#include "containers/dump_data_container.h"
#include "calculations/ddc_get_displacement.h"
#include "calculations/ddc_compute_delta_selection.h"
#include "utils/ddc_sort.h"
#include "utils/sort_checker.h"
#include "read_write/write_file.h"
#include "read_write/read_file.h"

int main(int argc, char **argv)
{
  CLI::App olt{"OpenLAMMPSToolbox App"};

  // Defining options
  std::ifstream infile;
  std::string ftype = "";
  std::string function = "";
  std::string atom_flag = "";

  std::vector<std::string> selection_vec;
  bool write_file = false;
  double disp_threshold = 1;

  int p = 0;
  olt.add_option("--file, -f", infile, "Required LAMMPS Dump File")
      ->required()
      ->check(CLI::ExistingFile);

  olt.add_option("--file_type, -t", ftype, "Dump File Type");

  olt.add_option("--function, --func", function, "Post-Processing Function");

  olt.add_option("--disp_threshold", disp_threshold, "Lattice Parameter");

  olt.add_flag("-w", write_file, "Write File Flag");

  olt.add_option("--atom_flag", atom_flag, "Data Stored For Each Atom"); // atom_flag = {varying, pe_ke, }

  olt.add_option("--selection, -s", selection_vec, "Command For All Selection/Subset Creation Processes. Selection is inclusive (>= and <=). Usage: --selection <Atom Parameter> <greater_than or less_than> <threshold>. If Atom Parameter = \"compute\" Additional <Index> Argument Required After <Atom Parameter>")
      ->expected(3, 4);

  CLI11_PARSE(olt, argc, argv);

  if (ftype == "xyz" & function == "displacement")
  {
    dump_data_container xyz_ddc = xyzToDumpData(infile);

    std::vector<int> disp_vec = get_displacement_vec(xyz_ddc, disp_threshold);
  }

  else if (ftype == "xyz" & function == "id_sort")
  {
    std::cerr << "Files of type XYZ are ID sorted by default.";
    return 1;
  }

  else if (ftype == "custom" & function == "id_sort" & write_file)
  {
    dump_data_container custom_ddc = customToDumpData(infile, atom_flag);

    ddc_id_quicksort(custom_ddc);

    ddc_to_custom_dump(custom_ddc, "test_custom_ddc.lmp");
  }

  else if (ftype == "custom" & function == "x_sort" & write_file)
  {
    dump_data_container custom_ddc = customToDumpData(infile, atom_flag);

    ddc_x_quicksort(custom_ddc);

    ddc_to_custom_dump(custom_ddc, "test_custom_ddc.lmp");
  }

  else if (ftype == "custom" & function == "compute_sort" & write_file)
  {
    dump_data_container custom_ddc = customToDumpData(infile, atom_flag);

    ddc_compute_quicksort(custom_ddc, 0);

    ddc_to_custom_dump(custom_ddc, "test_custom_ddc.lmp");
  }

  else if (ftype == "custom" & selection_vec[0] == "compute" & selection_vec[2] == "greater_than")
  {
    int compute_index = stoi(selection_vec[1]) - 1; // 1-indexed
    double threshold = stod(selection_vec[3]);

    dump_data_container custom_ddc = customToDumpData(infile, atom_flag);

    ddc_compute_delta_selection_greater_than(custom_ddc, threshold, compute_index);
  }

  // else
  // {
  //   for (int i = 0; i < size(selection_vec); i++)
  //   {
  //     std::cout << selection_vec[i] << " ";
  //   }
  // }

  return 0;
}
