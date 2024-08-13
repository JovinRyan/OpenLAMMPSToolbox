#include "calculations/ddc_compute_selection.h"

std::pair<std::vector<int>, std::vector<int>> ddc_compute_greater_than(dump_data_container &in_dump, double threshold, int compute_index)
{
  std::vector<int> compute_count_vec(size(in_dump.frame_atoms_vec) - 1, 0);
  std::vector<int> compute_atoms_id_vec{0, 0}; // Initializing ro prevent free pointer error on runtime.

  std::cout << "Finding Atoms With Value of Compute Variable #" << compute_index + 1 << " >= " << threshold << "\n"; // 1-indexed to reduce complexity

  // ddc_compute_quicksort(in_dump, compute_index); // Probably not needed for delta type selections

  for (int i = 1; i < size(in_dump.frame_atoms_vec); i++)
  {
    int count = 0;

    for (int j = 0; j < size(in_dump.frame_atoms_vec[i]); j++)
    {
      if (in_dump.frame_atoms_vec[i][j]->get_compute_vec()[compute_index] >= threshold)
      {
        count++;
        compute_atoms_id_vec.push_back(in_dump.frame_atoms_vec[i][j]->get_id());
      }
    }
    compute_count_vec[i - 1] = count;
  }
  std::sort(compute_atoms_id_vec.begin(), compute_atoms_id_vec.end());
  compute_atoms_id_vec.erase(std::unique(compute_atoms_id_vec.begin(), compute_atoms_id_vec.end()), compute_atoms_id_vec.end());

  for (int k = 0; k < size(compute_count_vec); k++)
  {
    std::cout << "Timestep: " << in_dump.get_timestep_vec()[k + 1] << " Atoms Selected: " << compute_count_vec[k] << "\n";
  }

  compute_atoms_id_vec.erase(std::remove(compute_atoms_id_vec.begin(), compute_atoms_id_vec.end(), 0), compute_atoms_id_vec.end()); // Removing initialized values from vector

  std::cout << size(compute_atoms_id_vec) << " Unique Atoms Selected.\n";

  return std::make_pair(compute_count_vec, compute_atoms_id_vec);
}

std::pair<std::vector<int>, std::vector<int>> ddc_compute_less_than(dump_data_container &in_dump, double threshold, int compute_index)
{
  std::vector<int> compute_count_vec(size(in_dump.frame_atoms_vec) - 1, 0);
  std::vector<int> compute_atoms_id_vec{0, 0}; // Initializing ro prevent free pointer error on runtime.

  std::cout << "Finding Atoms With Value of Compute Variable #" << compute_index + 1 << " >= " << threshold << "\n"; // 1-indexed to reduce complexity

  // ddc_compute_quicksort(in_dump, compute_index); // Probably not needed for delta type selections

  for (int i = 1; i < size(in_dump.frame_atoms_vec); i++)
  {
    int count = 0;

    for (int j = 0; j < size(in_dump.frame_atoms_vec[i]); j++)
    {
      if (in_dump.frame_atoms_vec[i][j]->get_compute_vec()[compute_index] <= threshold)
      {
        count++;
        compute_atoms_id_vec.push_back(in_dump.frame_atoms_vec[i][j]->get_id());
      }
    }
    compute_count_vec[i - 1] = count;
  }
  std::sort(compute_atoms_id_vec.begin(), compute_atoms_id_vec.end());
  compute_atoms_id_vec.erase(std::unique(compute_atoms_id_vec.begin(), compute_atoms_id_vec.end()), compute_atoms_id_vec.end());

  for (int k = 0; k < size(compute_count_vec); k++)
  {
    std::cout << "Timestep: " << in_dump.get_timestep_vec()[k + 1] << " Atoms Selected: " << compute_count_vec[k] << "\n";
  }

  compute_atoms_id_vec.erase(std::remove(compute_atoms_id_vec.begin(), compute_atoms_id_vec.end(), 0), compute_atoms_id_vec.end()); // Removing initialized values from vector

  std::cout << size(compute_atoms_id_vec) << " Unique Atoms Selected.\n";

  return std::make_pair(compute_count_vec, compute_atoms_id_vec);
}
