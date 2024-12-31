#include <iostream>
#include <thread>
#include <string>
#include <fstream>
#include <algorithm>
#include <readline/readline.h>

#include "containers/dump_data_container.h"
#include "calculations/ddc_get_displacement.h"
#include "calculations/ddc_compute_delta_selection.h"
#include "calculations/ddc_compute_selection.h"
#include "calculations/ddc_bulk_selection.h"
#include "calculations/ddc_get_defects.h"
#include "utils/ddc_sort.h"
#include "utils/sort_checker.h"
#include "utils/ddc_subset_creator.h"
#include "utils/vector_utils.h"
#include "read_write/write_file.h"
#include "read_write/read_file.h"

int main()
{
  std::string filename;
  std::string file_type = "lammps_dump";
  std::string atom_flag = "";
  bool outf_ddc_bool = false;

  dump_data_container infile_ddc;
  dump_data_container outfile_ddc;
  dump_data_container reffile_ddc;

  std::cout << "OpenLAMMPSToolbox\n";
  std::cout << "A project by Jovin Ryan Joseph\n";
  std::cout << "For more info check out https://github.com/JovinRyan/OpenLAMMPSToolbox\n\n";
  std::cout << "Enter the file for post-processing: \n";

  char *input = readline(">>> ");
  if (!input)
  {
    std::cerr << "Error: No input provided.\n";
    return 1;
  }

  filename = input;
  free(input);
  filename.erase(std::remove_if(filename.begin(), filename.end(), isspace), filename.end());

  std::cout << "Attempting to open file: '" << filename << "'\n";

  std::ifstream infile(filename);
  if (!infile)
  {
    std::cerr << "Error: Unable to open file '" << filename << "'\n";
    return 1;
  }

  std::cout << "File '" << filename << "' opened successfully.\n";

  if (string_to_vec(filename, ".")[1] == "xyz")
  {
    file_type = "xyz";
  }
  std::cout << "Detected file type: " << file_type << "\n";

  if (file_type == "xyz")
  {
    infile_ddc = xyzToDumpData(infile);
  }
  else
  {
    std::string atom_flag_string;
    std::cout << "Store per atom compute data? Y/N\n";
    std::cout << ">>> ";
    std::cin >> atom_flag_string;

    if (atom_flag_string == "Y" or "y")
    {
      atom_flag = "varying";
    }

    infile_ddc = customToDumpData(infile, atom_flag);
  }

  infile.close();

  std::cout << "Enter post-processing function: \n";
  std::cout << "Implemented functions: CONVERSION, DEFECT, DISPLACEMENT, SORT, SUBSET\n";

  std::vector<std::vector<int>> varying_defect_atom_id_vec;

  input = readline(">>> ");
  if (!input)
  {
    std::cerr << "Error: No input provided.\n";
    return 1;
  }

  std::string pp_function = input;
  free(input);

  std::cout << "Post-processing function selected: " << pp_function << "\n";

  if (pp_function == "CONVERSION")
  {
    std::cout << "Conversion to 'xyz' file type capability coming soon!" << "\n";

    if (file_type == "lammps_dump")
    {
      std::cerr << "Error: Conversion to 'xyz' file type not yet implemented\n";
      return 1;
    }
  }

  else if (pp_function == "DEFECT")
  {
    std::cout << "Defect selection criteria: type reference threshhold\n";
    std::cout << "Note: implemented types are 'VOID&INTERSTITIAL'\n";
    std::cout << "Note: implemented references are 'EXTERNAL'\n";

    input = readline(">>> ");
    if (!input)
    {
      std::cerr << "Error: No input provided.\n";
      return 1;
    }

    std::vector<std::string> defect_input_str = string_to_vec(input);
    double defect_threshold = stod(defect_input_str[2]);
    free(input);

    if (defect_input_str[1] == "EXTERNAL")
    {
      // Reference file hangling begins
      std::cout << "Enter reference file: \n";
      input = readline(">>> ");
      if (!input)
      {
        std::cerr << "Error: No input provided.\n";
        return 1;
      }

      filename = input;
      free(input);
      filename.erase(std::remove_if(filename.begin(), filename.end(), isspace), filename.end());

      std::cout << "Attempting to open file: '" << filename << "'\n";

      std::ifstream reffile(filename);

      if (string_to_vec(filename, ".")[1] == "xyz")
      {
        file_type = "xyz";
      }
      std::cout << "Detected file type: " << file_type << "\n";

      if (!reffile)
      {
        std::cerr << "Error: Unable to open file '" << filename << "'\n";
        return 1;
      }

      std::cout << "File '" << filename << "' opened successfully.\n";

      if (file_type == "xyz")
      {
        reffile_ddc = xyzToDumpData(reffile);
      }
      else
      {
        reffile_ddc = customToDumpData(reffile, atom_flag);
      }
      // Reference file handling ends
    }

    else
    {
    }

    if (defect_input_str[0] == "VOID&INTERSTITIAL")
    {
      std::cout << "Selected defect type: " << defect_input_str[0] << " with threshhold: " << defect_threshold << " units\n";

      varying_defect_atom_id_vec = ddc_get_void_interstitial_from_ref(infile_ddc, reffile_ddc, defect_threshold).second;
    }

    outfile_ddc = varying_id_vec_to_combine_ddc(infile_ddc, reffile_ddc, varying_defect_atom_id_vec);

    outf_ddc_bool = true;
  }

  else if (pp_function == "DISPLACEMENT")
  {
    std::cout << "Displacement criteria: reference threshhold\n";
    std::cout << "Note: Implemented reference methods are 'STEP', 'FIRST_FRAME', and 'EXTERNAL'\n";
    input = readline(">>> ");
    if (!input)
    {
      std::cerr << "Error: No input provided.\n";
      return 1;
    }
    std::vector<std::string> input_str_vec = string_to_vec(input);
    free(input);

    double disp_threshhold = stod(input_str_vec[1]);

    if (input_str_vec[0] == "EXTERNAL")
    {
      // Reference file hangling begins
      std::cout << "Enter reference file: \n";
      input = readline(">>> ");
      if (!input)
      {
        std::cerr << "Error: No input provided.\n";
        return 1;
      }

      filename = input;
      free(input);
      filename.erase(std::remove_if(filename.begin(), filename.end(), isspace), filename.end());

      std::cout << "Attempting to open file: '" << filename << "'\n";

      std::ifstream reffile(filename);

      if (string_to_vec(filename, ".")[1] == "xyz")
      {
        file_type = "xyz";
      }
      std::cout << "Detected file type: " << file_type << "\n";

      if (!reffile)
      {
        std::cerr << "Error: Unable to open file '" << filename << "'\n";
        return 1;
      }

      std::cout << "File '" << filename << "' opened successfully.\n";

      if (file_type == "xyz")
      {
        reffile_ddc = xyzToDumpData(reffile);
      }
      else
      {
        reffile_ddc = customToDumpData(reffile, atom_flag);
      }
      // Reference file handling ends

      std::vector<int> disp_id_vec = get_displacement_vec_from_ref(infile_ddc, reffile_ddc, disp_threshhold).second;

      outfile_ddc = id_vec_to_ddc(infile_ddc, disp_id_vec);
    }
    else if (input_str_vec[0] == "FIRST_FRAME")
    {
      std::vector<int> disp_id_vec = get_displacement_vec(infile_ddc, disp_threshhold, "first_frame").second;
      outfile_ddc = id_vec_to_ddc(infile_ddc, disp_id_vec);
    }
    else if (input_str_vec[0] == "STEP")
    {
      std::vector<int> disp_id_vec = get_displacement_vec(infile_ddc, disp_threshhold, "step").second;
      outfile_ddc = id_vec_to_ddc(infile_ddc, disp_id_vec);
    }

    outf_ddc_bool = true;
  }

  else if (pp_function == "SORT")
  {
    std::string criteria;
    int index = 0;

    std::cout << "Sorting criteria: parameter index<if parameter == 'COMPUTE' or 'COORDINATE'>\n";
    std::cout << "Note: 'index' is 1-indexed.\n";
    input = readline(">>> ");
    if (!input)
    {
      std::cerr << "Error: No input provided.\n";
      return 1;
    }
    std::vector<std::string> input_str_vec = string_to_vec(input);
    free(input);

    criteria = input_str_vec[0];
    if (size(input_str_vec) > 1)
    {
      index = stoi(input_str_vec[1]);
    }

    if ((criteria == "ID") and (file_type == "xyz"))
    {
      std::cout << "'xyz' type files do not contain an ID parameter for atoms.";

      return 1;
    }

    else if (criteria == "ID")
    {
      ddc_id_quicksort(infile_ddc);
    }

    else if ((criteria == "COORDINATE") and (index == 1))
    {
      ddc_x_quicksort(infile_ddc);
    }
    else if ((criteria == "COORDINATE") and (index == 2))
    {
      ddc_y_quicksort(infile_ddc);
    }
    else if ((criteria == "COORDINATE") and (index == 3))
    {
      ddc_z_quicksort(infile_ddc);
    }

    else if (criteria == "COMPUTE")
    {
      ddc_compute_quicksort(infile_ddc, index);
    }
  }

  else if (pp_function == "SUBSET")
  {
    std::cout << "Subset selection criteria: parameter index <=/>= threshhold\n";
    std::cout << "Note: COORDINATE and COMPUTE type parameters are 1-indexed. Logic modifiers 'DELTA' or 'DELTAMAG' to be added before inequality (eg. DELTAMAG>=)\n";

    input = readline(">>> ");
    if (!input)
    {
      std::cerr << "Error: No input provided.\n";

      return 1;
    }
    std::string subset_selection_string = input;
    free(input);

    std::vector<std::string> subset_selection_string_vec = string_to_vec(subset_selection_string);

    int index = stoi(subset_selection_string_vec[1]) - 1; // 1-indexed
    double threshhold = stod(subset_selection_string_vec[3]);

    std::vector<int> subset_id_vec;

    if (subset_selection_string_vec[0] == "COORDINATE")
    {
    }
    else if (subset_selection_string_vec[0] == "COMPUTE")
    {
      if (subset_selection_string_vec[2] == "DELTA<=")
      {
        subset_id_vec = ddc_compute_delta_selection_less_than(infile_ddc, threshhold, index).second;
      }
      else if (subset_selection_string_vec[2] == "DELTA>=")
      {
        subset_id_vec = ddc_compute_delta_selection_greater_than(infile_ddc, threshhold, index).second;
      }
      else if (subset_selection_string_vec[2] == "DELTAMAG>=")
      {
        subset_id_vec = ddc_compute_delta_selection_mag_greater_than(infile_ddc, threshhold, index).second;
      }
      else if (subset_selection_string_vec[2] == "DELTAMAG<=")
      {
        subset_id_vec = ddc_compute_delta_selection_mag_less_than(infile_ddc, threshhold, index).second;
      }
      else
      {
        std::cerr << "Error: Improper input\n";
        return 1;
      }

      outfile_ddc = id_vec_to_ddc(infile_ddc, subset_id_vec);
      outf_ddc_bool = true;
    }
  }

  else
  {
    std::cerr << "Error: Improper selection \n";
    return 1;
  }

  std::cout << "Provide name for output file: \n";
  input = readline(">>> ");
  if (!input)
  {
    std::cerr << "Error: No input provided.\n";
    free(input);
    input = readline(">>> ");
  }
  std::string outputfile_name = input;
  free(input);

  std::cout << "Attempting to write file: " << outputfile_name << "\n";

  if (outf_ddc_bool) // For functions like displacement which create a new ddc
  {
    ddc_to_custom_dump(outfile_ddc, outputfile_name);
  }
  else // For functions like sort which modify the original ddc
  {
    ddc_to_custom_dump(infile_ddc, outputfile_name);
  }

  return 0;
}
