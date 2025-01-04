#include "calculations/ddc_get_defects.h"

std::pair<std::vector<int>, std::vector<std::vector<int>>> ddc_get_void_interstitial_from_ref(dump_data_container &in_dump, dump_data_container &ref_dump, double disp_threshhold)
{
  std::vector<int> displacement_vec;
  std::vector<std::vector<int>> varying_displaced_atom_id_vec(size(in_dump.frame_box_bounds_vec));

  if (!ddc_id_sort_check(in_dump)) // Checking and sorting
  {
    ddc_id_quicksort(in_dump);
  }

  if (!ddc_id_sort_check(ref_dump)) // Checking and sorting
  {
    ddc_id_quicksort(ref_dump);
  }

  std::vector<std::vector<std::unique_ptr<atom>>> &in_fa_vec = in_dump.frame_atoms_vec;
  std::vector<std::vector<std::unique_ptr<atom>>> &ref_fa_vec = ref_dump.frame_atoms_vec;

  if (in_fa_vec.size() > ref_fa_vec.size())
  {
    throw std::runtime_error("Reference File Has Fewer Frames Than Input File.\n");
  }

  std::cout << "Calculating # of Atoms Displaced >= " << disp_threshhold << " Units." << "\n";

  double min_periodic_dist = std::min({in_dump.get_max_boxbounds()[0].second - in_dump.get_max_boxbounds()[0].first,
                                       in_dump.get_max_boxbounds()[1].second - in_dump.get_max_boxbounds()[1].first,
                                       in_dump.get_max_boxbounds()[2].second - in_dump.get_max_boxbounds()[2].first});

  std::cout << "Atoms With Displacement >= " << min_periodic_dist * 0.95 << " Units Are Excluded to Account for Periodic Boundary Condition." << "\n";

  for (int i = 0; i < size(in_fa_vec); i++)
  {
    if (in_fa_vec[i].size() != ref_fa_vec[i].size())
    {
      throw std::runtime_error("Reference File Frame Does Not Have the Same Number of Atoms as Input File.\n");
    }

    int count = 0;
    for (int j = 0; j < size(in_fa_vec[i]); j++)
    {
      if (in_fa_vec[i][j]->get_distance(*ref_fa_vec[i][j]) >= disp_threshhold && in_fa_vec[i][j]->get_distance(*ref_fa_vec[i][j]) <= min_periodic_dist * 0.95) // Reference atom is atom from previos step
      {
        count++;

        varying_displaced_atom_id_vec[i].push_back(in_fa_vec[i][j]->get_id());
      }
    }
    displacement_vec.push_back(count * 2); // 1 displaced atom = 1 void + 1 interstitial
  }

  for (int i = 0; i < size(displacement_vec); i++)
  {
    std::cout << "Timestep: " << in_dump.get_timestep_vec()[i] << " Number of Intersitial Atoms and Voids: " << displacement_vec[i] << "\n";
  }

  return std::make_pair(displacement_vec, varying_displaced_atom_id_vec);
}
