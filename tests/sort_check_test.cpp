#include "tests/sort_check_test.h"

std::pair<bool, bool> id_sort_check_test()
{
  int count = 10000;
  std::vector<std::unique_ptr<atom>> sequential_atom_vec = sequential_atom_creator(count);

  std::vector<std::unique_ptr<atom>> random_atom_vec = random_atom_creator(count);

  return std::make_pair(id_sort_check(sequential_atom_vec), id_sort_check(random_atom_vec));
}
