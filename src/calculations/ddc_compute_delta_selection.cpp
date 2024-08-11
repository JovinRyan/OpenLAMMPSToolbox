#include "calculations/ddc_compute_delta_selection.h"

std::pair<std::vector<int>, std::vector<int>> ddc_compute_delta_selection_greater_than(dump_data_container &in_dump, double threshold, int compute_index)
// Vector of count, and vector of atom IDs
{
  std::vector<int> pe_del_count_vec(size(in_dump.frame_atoms_vec) - 1, 0);
  std::vector<int> pe_del_atoms_id_vec{0, 0}; // Initializing ro prevent free pointer error on runtime.

  std::cout << "Finding Atoms With Change in Compute Variable #" << compute_index + 1 << " >= " << threshold << "\n"; // 1-indexed to reduce complexity

  // ddc_compute_quicksort(in_dump, compute_index); // Probably not needed for delta type selections

  for (int i = 1; i < size(in_dump.frame_atoms_vec); i++)
  {
    int count = 0;

    for (int j = 0; j < size(in_dump.frame_atoms_vec[i]); j++)
    {
      double delta = in_dump.frame_atoms_vec[i][j]->get_compute_vec()[compute_index] - in_dump.frame_atoms_vec[0][j]->get_compute_vec()[compute_index];

      if (delta >= threshold)
      {
        count++;
        pe_del_atoms_id_vec.push_back(in_dump.frame_atoms_vec[i][j]->get_id());
      }
    }
    pe_del_count_vec[i - 1] = count;
  }
  std::sort(pe_del_atoms_id_vec.begin(), pe_del_atoms_id_vec.end());
  pe_del_atoms_id_vec.erase(std::unique(pe_del_atoms_id_vec.begin(), pe_del_atoms_id_vec.end()));

  for (int k = 0; k < size(pe_del_count_vec); k++)
  {
    std::cout << "Timestep: " << in_dump.get_timestep_vec()[k + 1] << " Atoms Selected: " << pe_del_count_vec[k] << "\n";
  }

  pe_del_atoms_id_vec.erase(std::remove(pe_del_atoms_id_vec.begin(), pe_del_atoms_id_vec.end(), 0), pe_del_atoms_id_vec.end()); // Removing initialized values from vector

  return std::make_pair(pe_del_count_vec, pe_del_atoms_id_vec);
}
