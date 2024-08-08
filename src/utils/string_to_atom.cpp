#include "utils/string_to_atom.h"

atom custom_str_to_atom(std::string in_line)
{
  std::vector<std::string> line_vec = string_to_vec(in_line);

  return atom(stoi(line_vec[0]), stoi(line_vec[1]), stod(line_vec[2]), stod(line_vec[3]), stod(line_vec[4]));
}

atom_varying custom_str_vec_to_atom_varying(std::string in_line)
{
  std::vector<std::string> line_vec = string_to_vec(in_line);
  std::vector<double> compute_vec;

  for (int i = 5; i < size(line_vec); i++)
  {
    compute_vec.push_back(stod(line_vec[i]));
  }

  return atom_varying(stoi(line_vec[0]), stoi(line_vec[1]), stod(line_vec[2]), stod(line_vec[3]), stod(line_vec[4]), compute_vec);
}

atom_pe_ke custom_str_to_atom_pe_ke(std::string in_line)
{
  std::vector<std::string> line_vec = string_to_vec(in_line);

  return atom_pe_ke(stoi(line_vec[0]), stoi(line_vec[1]), stod(line_vec[2]), stod(line_vec[3]), stod(line_vec[4]), stod(line_vec[5]), stod(line_vec[6]));
}
