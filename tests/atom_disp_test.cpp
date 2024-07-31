#include <iostream>
#include "../src/atom.cpp"

int main()
{
  atom atom1(1, 1, 1.0, 1.0, 1.0), refatom(1, 1, 0.0, 0.0, 0.0);

  std::cout << "Displacement: " << atom1.get_displacement(refatom) << "\n";

  return 0;
}
