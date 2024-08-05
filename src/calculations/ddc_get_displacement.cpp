#include "calculations/ddc_get_displacement.h"

std::vector<int> get_displacement_vec(dump_data_container in_dump, double disp_threshold)
{
  std::vector<int> displacement_vec;

  std::vector<std::vector<atom>> fa_vec = in_dump.frame_atoms_vec;

  std::cout << "Calculating # of Atoms Displaced >= " << disp_threshold << " units." << "\n";

  for (int i = 1; i < size(fa_vec); i++)
  {
    int count = 0;
    for (int j = 0; j < size(fa_vec[i]); j++)
    {
      if (fa_vec[i][j].get_distance(fa_vec[0][j]) >= disp_threshold)
      {
        count++;
      }
    }
    displacement_vec.push_back(count);
  }

  for (int i = 0; i < size(displacement_vec); i++)
  {
    std::cout << "Timestep: " << in_dump.get_timestep_vec()[1 + i] << " Number of Displaced Atoms: " << displacement_vec[i] << "\n";
  }

  return displacement_vec;
}
