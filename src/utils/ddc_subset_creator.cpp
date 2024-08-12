#include "utils/ddc_subset_creator.h"

std::vector<std::unique_ptr<atom>> atom_subset_from_id(std::vector<std::unique_ptr<atom>> &frame, std::vector<int> &id_vec)
{
  std::vector<std::unique_ptr<atom>> atom_subset_vec;
  for (int i = 0; i < size(id_vec); i++)
  {
    atom_subset_vec.push_back(frame[id_vec[i] - 1]->clone());
  }

  return atom_subset_vec;
}

dump_data_container id_vec_to_ddc(dump_data_container &base_ddc, std::vector<int> &id_vec)
{
  ddc_id_quicksort(base_ddc); // making sure base ddc is sorted by ID

  std::vector<double> timestep_vec_copy = base_ddc.get_timestep_vec();

  std::vector<int> ac_vec_subset(size(timestep_vec_copy), size(id_vec)); // Atom count should remain constant

  std::vector<std::vector<std::pair<double, double>>> frame_boxbounds_vec_copy(size(timestep_vec_copy), base_ddc.get_max_boxbounds());
  // inefficient but that's how ddc->file is currently set up

  std::vector<std::vector<std::unique_ptr<atom>>> new_frame_atoms_vec;

  for (int j = 0; j < size(base_ddc.frame_atoms_vec); j++)
  {
    new_frame_atoms_vec.push_back(std::move(atom_subset_from_id(base_ddc.frame_atoms_vec[j], id_vec)));
  }

  return dump_data_container(timestep_vec_copy, ac_vec_subset, std::move(new_frame_atoms_vec), frame_boxbounds_vec_copy);
}
