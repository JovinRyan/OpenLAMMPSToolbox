#include "utils/atom_creator.h"

std::vector<std::unique_ptr<atom>> random_atom_creator(int count)
{
  std::vector<std::unique_ptr<atom>> random_atom_vec;

  std::random_device rd;                                 // Only used once to initialise (seed) engine
  std::mt19937 rng(rd());                                // Random-number engine used (Mersenne-Twister in this case)
  std::uniform_real_distribution<double> und(-100, 100); // Guaranteed unbiased double

  std::vector<int> id_vec(count);

  std::iota(id_vec.begin(), id_vec.end(), 1);

  std::shuffle(id_vec.begin(), id_vec.end(), rng);

  for (int i = 0; i < count; i++)
  {
    random_atom_vec.push_back(std::make_unique<atom>(atom(id_vec[i], 1, und(rng), und(rng), und(rng))));
  }

  return random_atom_vec;
}

std::vector<std::unique_ptr<atom>> sequential_atom_creator(int count)
{
  std::vector<std::unique_ptr<atom>> sequential_atom_vec;

  std::random_device rd;                                 // Only used once to initialise (seed) engine
  std::mt19937 rng(rd());                                // Random-number engine used (Mersenne-Twister in this case)
  std::uniform_real_distribution<double> und(-100, 100); // Guaranteed unbiased double

  for (int i = 1; i < count; i++)
  {
    sequential_atom_vec.push_back(std::make_unique<atom>(atom(i, 1, und(rng), und(rng), und(rng))));
  }

  return sequential_atom_vec;
}
