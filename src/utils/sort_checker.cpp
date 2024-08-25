#include "utils/sort_checker.h"

bool id_sort_check(std::vector<std::unique_ptr<atom>> &in_atom_vec)
{
  std::random_device rd;                                              // Only used once to initialise (seed) engine
  std::mt19937 rng(rd());                                             // Random-number engine used (Mersenne-Twister in this case)
  std::uniform_int_distribution<int> uni(1, size(in_atom_vec) * 0.9); // Guaranteed unbiased

  for (int i = 0; i < 5; i++)
  {
    int random_int = uni(rng);
    for (int j = 0; j < int(size(in_atom_vec) * 0.05); j++) // Needs change, does not work for simulations with exiting atoms
    {
      if (in_atom_vec[random_int + j]->get_id() > in_atom_vec[random_int + j + 1]->get_id())
      {
        return false;
      }
    }
  }

  return true;
}
