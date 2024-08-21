#include "utils/sort_checker.h"

bool id_sort_check_no_exit(std::vector<std::unique_ptr<atom>> &in_atom_vec)
{
  std::random_device rd;                                        // Only used once to initialise (seed) engine
  std::mt19937 rng(rd());                                       // Random-number engine used (Mersenne-Twister in this case)
  std::uniform_int_distribution<int> uni(1, size(in_atom_vec)); // Guaranteed unbiased

  for (int i = 0; i < int(size(in_atom_vec) * 0.05); i++) // Needs change, does not work for simulations with exiting atoms
  {
    int random_int = uni(rng);
    if (int(in_atom_vec[random_int]->get_id()) != random_int + 1)
    {
      return false;
    }
  }

  return true;
}

bool id_sort_check(std::vector<std::unique_ptr<atom>> &in_atom_vec)
{
  std::random_device rd;                                              // Only used once to initialise (seed) engine
  std::mt19937 rng(rd());                                             // Random-number engine used (Mersenne-Twister in this case)
  std::uniform_int_distribution<int> uni(1, size(in_atom_vec) * 0.6); // Guaranteed unbiased

  for (int i = 0; i < 5; i++)
  {
    int random_int = uni(rng);
    for (int j = 0; j < int(size(in_atom_vec) * 0.05); j++) // Needs change, does not work for simulations with exiting atoms
    {
      if (int(in_atom_vec[j + random_int]->get_id()) != random_int + j)
      {
        return false;
      }
    }
  }

  return true;
}
