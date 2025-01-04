#include "calculations/ddc_bulk_selection.h"

std::pair<std::vector<int>, std::vector<int>> ddc_bulk_selection_explicit(dump_data_container &in_dump, std::vector<double> min_max_vec)
{
  std::vector<int> count_vec(size(in_dump.frame_atoms_vec), 0);
  std::vector<int> atoms_id_vec{0, 0}; // Initializing ro prevent free pointer error on runtime.

  if (!ddc_id_sort_check(in_dump)) // Checking and sorting
  {
    ddc_id_quicksort(in_dump);
  }

  for (int i = 0; i < size(in_dump.frame_atoms_vec); i++)
  {
    int count = 0;

    for (int j = 0; j < size(in_dump.frame_atoms_vec[i]); j++)
    {
      if (in_dump.frame_atoms_vec[i][j]->get_coords()[0] >= min_max_vec[0] && in_dump.frame_atoms_vec[i][j]->get_coords()[0] <= min_max_vec[1] && in_dump.frame_atoms_vec[i][j]->get_coords()[1] >= min_max_vec[2] && in_dump.frame_atoms_vec[i][j]->get_coords()[1] <= min_max_vec[3] && in_dump.frame_atoms_vec[i][j]->get_coords()[2] >= min_max_vec[4] && in_dump.frame_atoms_vec[i][j]->get_coords()[2] <= min_max_vec[5])
      {
        count++;
        atoms_id_vec.push_back(in_dump.frame_atoms_vec[i][j]->get_id());
      }
    }
    count_vec[i] = count;
  }

  std::sort(atoms_id_vec.begin(), atoms_id_vec.end());
  atoms_id_vec.erase(std::unique(atoms_id_vec.begin(), atoms_id_vec.end()), atoms_id_vec.end());

  for (int k = 0; k < size(atoms_id_vec); k++)
  {
    std::cout << "Timestep: " << in_dump.get_timestep_vec()[k] << " Atoms Selected: " << count_vec[k] << "\n";
  }

  atoms_id_vec.erase(std::remove(atoms_id_vec.begin(), atoms_id_vec.end(), 0), atoms_id_vec.end()); // Removing initialized values from vector

  std::cout << size(atoms_id_vec) << " Unique Atoms Selected.\n";

  return std::make_pair(count_vec, atoms_id_vec);
}
