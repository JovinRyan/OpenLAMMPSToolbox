#include "calculations/ddc_get_displacement.h"
#include "containers/dump_data_container.h"
#include "utils/sort_checker.h"
#include "utils/ddc_sort.h"

std::pair<std::vector<int>, std::vector<int>> get_displacement_vec(dump_data_container &in_dump, double disp_threshold, std::string displacement_flag) // count vector and id vector
{
  std::vector<int> displacement_vec;
  std::vector<int> displacement_atom_id_vec(0);

  if (!ddc_id_sort_check(in_dump)) // Checking and sorting
  {
    ddc_id_quicksort(in_dump);
  }

  std::vector<std::vector<std::unique_ptr<atom>>> &fa_vec = in_dump.frame_atoms_vec;

  std::cout << "Calculating # of Atoms Displaced >= " << disp_threshold << " Units." << "\n";

  // double x_periodic_dist = in_dump.get_max_boxbounds()[0].second - in_dump.get_max_boxbounds()[0].first;
  // double y_periodic_dist = in_dump.get_max_boxbounds()[1].second - in_dump.get_max_boxbounds()[1].first;
  // double z_periodic_dist = in_dump.get_max_boxbounds()[2].second - in_dump.get_max_boxbounds()[2].first;

  double min_periodic_dist = std::min({in_dump.get_max_boxbounds()[0].second - in_dump.get_max_boxbounds()[0].first,
                                       in_dump.get_max_boxbounds()[1].second - in_dump.get_max_boxbounds()[1].first,
                                       in_dump.get_max_boxbounds()[2].second - in_dump.get_max_boxbounds()[2].first});

  std::cout << "Atoms With Displacement >= " << min_periodic_dist * 0.95 << " Units Are Excluded to Account for Periodic Boundary Condition." << "\n";

  for (int i = 1; i < size(fa_vec); i++)
  {
    int count = 0;
    for (int j = 0; j < size(fa_vec[i]); j++)
    {
      if (displacement_flag == "step")
      {
        if (fa_vec[i][j]->get_distance(*fa_vec[i - 1][j]) >= disp_threshold && fa_vec[i][j]->get_distance(*fa_vec[i - 1][j]) <= min_periodic_dist * 0.95) // Reference atom is atom from previos step
        {
          count++;

          displacement_atom_id_vec.push_back(fa_vec[i][j]->get_id());
        }
      }

      else if (displacement_flag == "first_frame")
      {
        if (fa_vec[i][j]->get_distance(*fa_vec[0][j]) >= disp_threshold && fa_vec[i][j]->get_distance(*fa_vec[0][j]) <= min_periodic_dist * 0.95) // Reference atom is atom from first timestep
        {
          count++;

          displacement_atom_id_vec.push_back(fa_vec[i][j]->get_id());
        }
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

  std::cout << "Total Number of Unique Displaced Atoms: " << displacement_atom_id_vec.size() << "\n";

  return std::make_pair(displacement_vec, displacement_atom_id_vec);
}

std::pair<std::vector<int>, std::vector<int>> get_displacement_vec_from_ref(dump_data_container &in_dump, dump_data_container &ref_dump, double disp_threshold) // count vector and id vector
{
  std::vector<int> displacement_vec;
  std::vector<int> displacement_atom_id_vec(0);

  if (!ddc_id_sort_check(in_dump)) // Checking and sorting
  {
    ddc_id_quicksort(in_dump);
  }

  if (!ddc_id_sort_check(ref_dump))
  {
    ddc_id_quicksort(ref_dump);
  }

  std::vector<std::vector<std::unique_ptr<atom>>> &fa_vec = in_dump.frame_atoms_vec;

  std::vector<std::vector<std::unique_ptr<atom>>> &ref_fa_vec = ref_dump.frame_atoms_vec;

  if (fa_vec.size() > ref_fa_vec.size())
  {
    throw std::runtime_error("Reference File Has Fewer Frames Than Input File.\n");
  }

  std::cout << "Calculating # of Atoms Displaced >= " << disp_threshold << " Units." << "\n";

  // double x_periodic_dist = in_dump.get_max_boxbounds()[0].second - in_dump.get_max_boxbounds()[0].first;
  // double y_periodic_dist = in_dump.get_max_boxbounds()[1].second - in_dump.get_max_boxbounds()[1].first;
  // double z_periodic_dist = in_dump.get_max_boxbounds()[2].second - in_dump.get_max_boxbounds()[2].first;

  double min_periodic_dist = std::min({in_dump.get_max_boxbounds()[0].second - in_dump.get_max_boxbounds()[0].first,
                                       in_dump.get_max_boxbounds()[1].second - in_dump.get_max_boxbounds()[1].first,
                                       in_dump.get_max_boxbounds()[2].second - in_dump.get_max_boxbounds()[2].first});

  std::cout << "Atoms With Displacement >= " << min_periodic_dist * 0.95 << " Units Are Excluded to Account for Periodic Boundary Condition." << "\n";

  for (int i = 0; i < size(fa_vec); i++)
  {
    if (fa_vec[i].size() != ref_fa_vec[i].size())
    {
      throw std::runtime_error("Reference File Frame Does Not Have the Same Number of Atoms as Input File.\n");
    }

    int count = 0;
    for (int j = 0; j < size(fa_vec[i]); j++)
    {
      if (fa_vec[i][j]->get_distance(*ref_fa_vec[i][j]) >= disp_threshold && fa_vec[i][j]->get_distance(*ref_fa_vec[i][j]) <= min_periodic_dist * 0.95) // Reference atom is atom from previos step
      {
        count++;

        displacement_atom_id_vec.push_back(fa_vec[i][j]->get_id());
      }
    }
    displacement_vec.push_back(count);
  }

  for (int i = 0; i < size(displacement_vec); i++)
  {
    std::cout << "Timestep: " << in_dump.get_timestep_vec()[i] << " Number of Displaced Atoms: " << displacement_vec[i] << "\n";
  }

  vector_make_unique(displacement_atom_id_vec);

  displacement_atom_id_vec.erase(std::remove(displacement_atom_id_vec.begin(), displacement_atom_id_vec.end(), 0), displacement_atom_id_vec.end()); // Removing initialized values from vector

  std::cout << "Total Number of Unique Displaced Atoms: " << displacement_atom_id_vec.size() << "\n";

  return std::make_pair(displacement_vec, displacement_atom_id_vec);
}
