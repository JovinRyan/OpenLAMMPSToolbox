#include "utils/ddc_id_sort.h"
#include "containers/atom_classes.h"

int main()
{
  std::cout << "Atom QuickSort Test." << "\n";

  atom atom1(4, 1, 0.0, 0.0, 0.0), atom2(2, 1, 0.0, 1.0, 1.0), atom3(3, 1, 1.0, 1.0, 1.0), atom4(1, 1, 0.0, 0.0, 1.0);
  std::vector<atom> atom_vec;
  atom_vec.push_back(atom1);
  atom_vec.push_back(atom2);
  atom_vec.push_back(atom3);
  atom_vec.push_back(atom4);

  atom_vec_quicksort(atom_vec, 0, size(atom_vec) - 1);
  std::cout << "Sorted Vector: " << "\n";
  for (int i = 0; i < size(atom_vec); i++)
  {
    std::cout << "Atom ID: " << atom_vec[i].get_id() << "\n";
  }

  return 0;
}
