#include <vector>
#include <iostream>
#include <boost/geometry.hpp>
#include <boost/geometry/index/rtree.hpp>
#include <boost/geometry/geometries/register/point.hpp>

#include "../dump_data_container.cpp"
#include "../atom.cpp"

std::vector<int> get_displacement_vec(dump_data_container in_dump, double lattice_param, double tol)
{
  std::vector<int> displacement_vec;

  double disp_threshold = lattice_param * tol;
  std::vector<boost::geometry::index::rtree<atom, boost::geometry::index::rstar<16>>> fa_rT = in_dump.frame_atoms_rT;

  for (int i = 1; i < size(fa_rT); i++)
  {
    int count = 0;
    for (auto &a : fa_rT[i])
    {
      count++;
      if (count == 1 or count == 2 or count == 3 or count == 4 or count == 5)
      {
        std::cout << "ID: " << a.get_id() << "\n";
      }
    }
  }

  return displacement_vec;
}
