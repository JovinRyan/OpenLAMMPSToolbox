#include <iostream>
#include <fstream>

#include "cli/CLI11.hpp"

#include "containers/dump_data_container.h"
#include "calculations/ddc_get_displacement.h"
#include "calculations/ddc_compute_delta_selection.h"
#include "calculations/ddc_compute_selection.h"
#include "utils/ddc_sort.h"
#include "utils/sort_checker.h"
#include "utils/ddc_subset_creator.h"
#include "utils/vector_utils.h"
#include "read_write/write_file.h"
#include "read_write/read_file.h"

int main(int argc, char **argv)
{
  CLI::App olt{"OpenLAMMPSToolbox App"};

  // Defining options
  std::ifstream infile;
  std::ifstream ref_file;
  std::string ftype = "";
  std::string atom_flag = "";
  std::string outfile;

  std::pair<std::string, double> analysis(" ", 1.0);

  std::vector<double> macro_vec;

  std::vector<std::string> selection_vec;
  bool write_file = false;
  double disp_threshold = 1;

  std::string displacement_flag = "first_frame";

  olt.add_option("--file, -f", infile, "Required LAMMPS Dump File")
      ->required()
      ->check(CLI::ExistingFile);
  olt.add_option("--ref_file", ref_file, "Reference LAMMPS Dump File")
      ->check(CLI::ExistingFile);

  olt.add_option("--file_type, -t", ftype, "Dump File Type");

  olt.add_option("--disp_threshold", disp_threshold, "Minimum Distance (Dump File Units) To Count as Atom Displacement");

  olt.add_flag("-w, --write", write_file, "Write File Flag");

  olt.add_option("--outfile", outfile, "Output File Name");

  olt.add_option("--atom_flag", atom_flag, "Data Stored For Each Atom"); // atom_flag = {varying, pe_ke, }

  olt.add_option("--selection, -s", selection_vec, "Command For All Selection/Subset Creation Processes. Selection is inclusive (>= and <=). Usage: --selection <Atom Parameter> <greater_than or less_than> <threshold>. If Atom Parameter = \"compute\" Additional <Index> Argument Required After <Atom Parameter>")
      ->expected(3, 4);

  olt.add_option("--analysis, -a", analysis, "Analyses Such as Sorting, Finding Displaced Atoms, etc.");

  olt.add_option("--displacement_flag", displacement_flag, "Reference for Calculating Atom Displacement.");

  olt.add_option("--macro", macro_vec, "Set of Predefined Macros");

  CLI11_PARSE(olt, argc, argv);

  if (outfile == "")
  {
    outfile = string_to_vec(argv[2], ".")[0] + "_processed." + string_to_vec(argv[2], ".")[1]; // must have only one "." character
  }

  // Macro 1
  // if (macro_vec[0] == 1 && write_file && atom_flag == "varying") // --macro 1 compute_index delta_threshold compute_threshold
  //                                                                // Selects delta compute greater than and creates union with compute greater than
  // {
  //   dump_data_container custom_ddc = customToDumpData(infile, atom_flag);

  //   int compute_index = macro_vec[1] - 1;

  //   std::vector<int> id_vec_a = ddc_compute_delta_selection_mag_greater_than(custom_ddc, macro_vec[2], compute_index).second;

  //   std::vector<int> id_vec_b = ddc_compute_greater_than(custom_ddc, macro_vec[3], compute_index).second;

  //   vector_add_from_vector(id_vec_a, id_vec_b);

  //   dump_data_container subset_ddc = id_vec_to_ddc(custom_ddc, id_vec_a);

  //   ddc_to_custom_dump(subset_ddc, outfile);

  //   return 0;
  // }

  if (ftype == "xyz" && analysis.first == "sort_id")
  {
    std::cerr << "Files of type XYZ are ID sorted by default.\n";
    return 1;
  }

  else if (ftype == "custom" && analysis.first == "sort_id" && write_file)
  {
    dump_data_container custom_ddc = customToDumpData(infile, atom_flag);

    ddc_id_quicksort(custom_ddc);

    ddc_to_custom_dump(custom_ddc, outfile);
  }

  else if (analysis.first == "sort_coordinate" && analysis.second == 1 && ftype == "custom" && write_file)
  {
    dump_data_container custom_ddc = customToDumpData(infile, atom_flag);

    ddc_x_quicksort(custom_ddc);

    ddc_to_custom_dump(custom_ddc, outfile);
  }

  else if (analysis.first == "sort_coordinate" && analysis.second == 2 && ftype == "custom" && write_file)
  {
    dump_data_container custom_ddc = customToDumpData(infile, atom_flag);

    ddc_y_quicksort(custom_ddc);

    ddc_to_custom_dump(custom_ddc, outfile);
  }

  else if (analysis.first == "sort_coordinate" && analysis.second == 3 && ftype == "custom" && write_file)
  {
    dump_data_container custom_ddc = customToDumpData(infile, atom_flag);

    ddc_z_quicksort(custom_ddc);

    ddc_to_custom_dump(custom_ddc, outfile);
  }

  else if (ftype == "xyz" && analysis.first == "displacement" && write_file)
  {
    dump_data_container xyz_ddc = xyzToDumpData(infile);

    std::vector<int> disp_vec = get_displacement_vec(xyz_ddc, analysis.second, displacement_flag).second;

    dump_data_container subset_ddc = id_vec_to_ddc(xyz_ddc, disp_vec);

    std::cout << "Writing \"xyz\" Type File Capability Coming Soon!\n"; // Implement xyz write file soon.

    ddc_to_custom_dump(subset_ddc, outfile); // Doesn't work for some reason, stuck at sorting.
  }

  else if (ftype == "xyz" && analysis.first == "displacement_ref" && write_file)
  {
    dump_data_container xyz_ddc = xyzToDumpData(infile);

    dump_data_container ref_xyz_ddc = xyzToDumpData(ref_file);

    std::vector<int> disp_vec = get_displacement_vec_from_ref(xyz_ddc, ref_xyz_ddc, analysis.second).second;

    dump_data_container subset_ddc = id_vec_to_ddc(xyz_ddc, disp_vec);

    std::cout << "Writing \"xyz\" Type File Capability Coming Soon!\n"; // Implement xyz write file soon.

    ddc_to_custom_dump(subset_ddc, outfile); // Doesn't work for some reason, stuck at sorting.
  }

  else if (ftype == "custom" && analysis.first == "displacement" && write_file)
  {
    dump_data_container custom_ddc = customToDumpData(infile, atom_flag);

    ddc_id_quicksort(custom_ddc);

    std::vector<int> disp_vec = get_displacement_vec(custom_ddc, analysis.second, displacement_flag).second;

    dump_data_container subset_ddc = id_vec_to_ddc(custom_ddc, disp_vec);

    ddc_to_custom_dump(subset_ddc, outfile);
  }

  else if (ftype == "xyz" && analysis.first == "displacement")
  {
    dump_data_container xyz_ddc = xyzToDumpData(infile);

    std::vector<int> disp_vec = get_displacement_vec(xyz_ddc, analysis.second, displacement_flag).second;
  }

  else if (ftype == "custom" && analysis.first == "displacement")
  {
    dump_data_container custom_ddc = customToDumpData(infile, atom_flag);

    ddc_id_quicksort(custom_ddc);

    std::vector<int> disp_vec = get_displacement_vec(custom_ddc, analysis.second, displacement_flag).second;
  }

  else if (ftype == "custom" && analysis.first == "sort_compute" && write_file)
  {
    dump_data_container custom_ddc = customToDumpData(infile, atom_flag);

    ddc_compute_quicksort(custom_ddc, analysis.second);

    ddc_to_custom_dump(custom_ddc, outfile);
  }

  // Selection type operation.

  else if (ftype == "custom" && selection_vec[0] == "compute_delta" && selection_vec[2] == "greater_than" && write_file)
  {
    int compute_index = stoi(selection_vec[1]) - 1; // 1-indexed
    double threshold = stod(selection_vec[3]);

    dump_data_container custom_ddc = customToDumpData(infile, atom_flag);

    std::vector<int> id_vec = ddc_compute_delta_selection_greater_than(custom_ddc, threshold, compute_index).second;

    dump_data_container subset_ddc = id_vec_to_ddc(custom_ddc, id_vec);

    ddc_to_custom_dump(subset_ddc, outfile);
  }

  else if (ftype == "custom" && selection_vec[0] == "compute_delta" && selection_vec[2] == "greater_than")
  {
    int compute_index = stoi(selection_vec[1]) - 1; // 1-indexed
    double threshold = stod(selection_vec[3]);

    dump_data_container custom_ddc = customToDumpData(infile, atom_flag);

    ddc_compute_delta_selection_greater_than(custom_ddc, threshold, compute_index);
  }

  else if (ftype == "custom" && selection_vec[0] == "compute_delta" && selection_vec[2] == "less_than" && write_file)
  {
    int compute_index = stoi(selection_vec[1]) - 1; // 1-indexed
    double threshold = stod(selection_vec[3]);

    dump_data_container custom_ddc = customToDumpData(infile, atom_flag);

    std::vector<int> id_vec = ddc_compute_delta_selection_less_than(custom_ddc, threshold, compute_index).second;

    dump_data_container subset_ddc = id_vec_to_ddc(custom_ddc, id_vec);

    ddc_to_custom_dump(subset_ddc, outfile);
  }

  else if (ftype == "custom" && selection_vec[0] == "compute_delta" && selection_vec[2] == "less_than")
  {
    int compute_index = stoi(selection_vec[1]) - 1; // 1-indexed
    double threshold = stod(selection_vec[3]);

    dump_data_container custom_ddc = customToDumpData(infile, atom_flag);

    ddc_compute_delta_selection_less_than(custom_ddc, threshold, compute_index);
  }

  // Magnitude based selections

  else if (ftype == "custom" && selection_vec[0] == "compute_delta" && selection_vec[2] == "magnitude_greater_than" && write_file)
  {
    int compute_index = stoi(selection_vec[1]) - 1; // 1-indexed
    double threshold = stod(selection_vec[3]);

    dump_data_container custom_ddc = customToDumpData(infile, atom_flag);

    std::vector<int> id_vec = ddc_compute_delta_selection_mag_greater_than(custom_ddc, threshold, compute_index).second;

    dump_data_container subset_ddc = id_vec_to_ddc(custom_ddc, id_vec);

    ddc_to_custom_dump(subset_ddc, outfile);
  }

  else if (ftype == "custom" && selection_vec[0] == "compute_delta" && selection_vec[2] == "magnitude_greater_than")
  {
    int compute_index = stoi(selection_vec[1]) - 1; // 1-indexed
    double threshold = stod(selection_vec[3]);

    dump_data_container custom_ddc = customToDumpData(infile, atom_flag);

    ddc_compute_delta_selection_mag_greater_than(custom_ddc, threshold, compute_index);
  }

  else if (ftype == "custom" && selection_vec[0] == "compute_delta" && selection_vec[2] == "magnitude_less_than" && write_file)
  {
    int compute_index = stoi(selection_vec[1]) - 1; // 1-indexed
    double threshold = stod(selection_vec[3]);

    dump_data_container custom_ddc = customToDumpData(infile, atom_flag);

    std::vector<int> id_vec = ddc_compute_delta_selection_mag_less_than(custom_ddc, threshold, compute_index).second;

    dump_data_container subset_ddc = id_vec_to_ddc(custom_ddc, id_vec);

    ddc_to_custom_dump(subset_ddc, outfile);
  }

  else if (ftype == "custom" && selection_vec[0] == "compute_delta" && selection_vec[2] == "magnitude_less_than")
  {
    int compute_index = stoi(selection_vec[1]) - 1; // 1-indexed
    double threshold = stod(selection_vec[3]);

    dump_data_container custom_ddc = customToDumpData(infile, atom_flag);

    ddc_compute_delta_selection_mag_less_than(custom_ddc, threshold, compute_index);
  }

  else if (ftype == "custom" && selection_vec[0] == "compute" && selection_vec[2] == "greater_than" && write_file)
  {
    int compute_index = stoi(selection_vec[1]) - 1; // 1-indexed
    double threshold = stod(selection_vec[3]);

    dump_data_container custom_ddc = customToDumpData(infile, atom_flag);

    std::vector<int> id_vec = ddc_compute_greater_than(custom_ddc, threshold, compute_index).second;

    dump_data_container subset_ddc = id_vec_to_ddc(custom_ddc, id_vec);

    ddc_to_custom_dump(subset_ddc, outfile);
  }

  else if (ftype == "custom" && selection_vec[0] == "compute" && selection_vec[2] == "greater_than")
  {
    int compute_index = stoi(selection_vec[1]) - 1; // 1-indexed
    double threshold = stod(selection_vec[3]);

    dump_data_container custom_ddc = customToDumpData(infile, atom_flag);

    ddc_compute_greater_than(custom_ddc, threshold, compute_index);
  }

  else if (ftype == "custom" && selection_vec[0] == "compute" && selection_vec[2] == "less_than" && write_file)
  {
    int compute_index = stoi(selection_vec[1]) - 1; // 1-indexed
    double threshold = stod(selection_vec[3]);

    dump_data_container custom_ddc = customToDumpData(infile, atom_flag);

    std::vector<int> id_vec = ddc_compute_less_than(custom_ddc, threshold, compute_index).second;

    dump_data_container subset_ddc = id_vec_to_ddc(custom_ddc, id_vec);

    ddc_to_custom_dump(subset_ddc, outfile);
  }

  else if (ftype == "custom" && selection_vec[0] == "compute" && selection_vec[2] == "less_than")
  {
    int compute_index = stoi(selection_vec[1]) - 1; // 1-indexed
    double threshold = stod(selection_vec[3]);

    dump_data_container custom_ddc = customToDumpData(infile, atom_flag);

    ddc_compute_less_than(custom_ddc, threshold, compute_index);
  }

  else
  {
    throw std::runtime_error("Improper Input. See User Guide at https://github.com/JovinRyan/OpenLAMMPSToolbox or Use the Help Command (--help)\n");
  }

  return 0;
}
