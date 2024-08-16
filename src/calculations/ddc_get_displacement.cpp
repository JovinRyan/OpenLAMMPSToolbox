#include "calculations/ddc_get_displacement.h"
#include "containers/dump_data_container.h"

std::pair<std::vector<int>, std::vector<int>> get_displacement_vec(dump_data_container &in_dump, double disp_threshold) // count vector and id vector
{
  std::vector<int> displacement_vec;
  std::vector<int> displacement_atom_id_vec(0);

  std::vector<std::vector<std::unique_ptr<atom>>> &fa_vec = in_dump.frame_atoms_vec;

  std::cout << "Calculating # of Atoms Displaced >= " << disp_threshold << " units." << "\n";

  for (int i = 1; i < size(fa_vec); i++)
  {
    int count = 0;
    for (int j = 0; j < size(fa_vec[i]); j++)
    {
      if (fa_vec[i][j]->get_distance(*fa_vec[0][j]) >= disp_threshold)
      {
        count++;

        displacement_atom_id_vec.push_back(fa_vec[i][j]->get_id());
      }
    }
    displacement_vec.push_back(count);
  }

  for (int i = 0; i < size(displacement_vec); i++)
  {
    std::cout << "Timestep: " << in_dump.get_timestep_vec()[1 + i] << " Number of Displaced Atoms: " << displacement_vec[i] << "\n";
  }

  vector_make_unique(displacement_atom_id_vec);

  displacement_atom_id_vec.erase(std::remove(displacement_atom_id_vec.begin(), displacement_atom_id_vec.end(), 0), displacement_atom_id_vec.end()); // Removing initialized values from vector

  return std::make_pair(displacement_vec, displacement_atom_id_vec);
}
