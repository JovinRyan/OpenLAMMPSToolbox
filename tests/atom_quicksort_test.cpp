#include "tests/atom_quicksort_test.h"

bool atom_quicksort_test()
{
  std::cout << "Atom QuickSort Test." << "\n";

  atom atom1(4, 1, 0.0, 0.0, 0.0), atom2(2, 1, 0.0, 1.0, 1.0), atom3(3, 1, 1.0, 1.0, 1.0), atom4(1, 1, 0.0, 0.0, 1.0);
  std::vector<std::unique_ptr<atom>> atom_vec;

  atom_vec.push_back(std::make_unique<atom>(atom1));
  atom_vec.push_back(std::make_unique<atom>(atom2));
  atom_vec.push_back(std::make_unique<atom>(atom3));
  atom_vec.push_back(std::make_unique<atom>(atom4));

  atom_vec_quicksort_by_id(atom_vec, 0, size(atom_vec) - 1);

  for (int i = 0; i < size(atom_vec); i++)
  {
    if (atom_vec[i]->get_id() != i + 1)
    {
      return false;
    }
  }

  return true;
}
