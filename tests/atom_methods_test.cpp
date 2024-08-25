#include "tests/atom_method_test.h"

bool atom_dist_test()
{
  double x1, y1, z1, x2, y2, z2;

  double lower_bound = -100;
  double upper_bound = 100;
  std::uniform_real_distribution<double> unif(lower_bound, upper_bound);
  std::default_random_engine re;
  x1 = unif(re);
  y1 = unif(re);
  z1 = unif(re);
  x2 = unif(re);
  y2 = unif(re);
  z2 = unif(re);

  atom atom1(1, 1, x1, y1, z1), atom2(2, 1, x2, y2, z2);

  if (atom1.get_distance(atom2) == sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) + (z1 - z2) * (z1 - z2)))
  {
    return true;
  }

  return false;
}
