#include <vector>
#include <iostream>

#include "../dump_data_container.cpp"
#include "../atom.cpp"

std::vector<int> get_displacement_vec(dump_data_container in_dump, double lattice_param, double tol)
{
  std::vector<int> displacement_vec;

  double disp_threshold = lattice_param * tol;
  std::vector<std::vector<atom>> fa_vec = in_dump.frame_atoms_vec;

  for (int i = 1; i < size(fa_vec); i++)
  {
    int count = 0;
    for (int j = 0; j < size(fa_vec[i]); j++)
    {
      if (fa_vec[i][j].get_displacement(fa_vec[0][j]) > disp_threshold)
      {
        count++;
      }
    }
    displacement_vec.push_back(count);
  }

  return displacement_vec;
}
