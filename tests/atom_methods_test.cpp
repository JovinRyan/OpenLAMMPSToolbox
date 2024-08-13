#include <iostream>
#include "containers/atom_classes.h"

int main()
{
  atom atom1(1, 1, 1.0, 1.0, 1.0), refatom(1, 1, 0.0, 0.0, 0.0);

  std::cout << "Displacement: " << atom1.get_distance(refatom) << "\n";

  return 0;
}
