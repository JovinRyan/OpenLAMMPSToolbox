#include <vector>
#include "../src/atom.cpp"
#include <boost/geometry.hpp>
#include <boost/geometry/index/rtree.hpp>
#include <boost/geometry/geometries/register/point.hpp>

class dump_data_container
{
private:
  std::vector<double> timestep_vec;
  std::vector<int> atomscount_vec;

public:
  // std::vector<std::vector<atom>> frame_atom_vec;
  std::vector<boost::geometry::index::rtree<atom, boost::geometry::index::linear<16>>> frame_atoms_rT;
  dump_data_container(std::vector<double> t_vec, std::vector<int> ac_vec,
                      std::vector<boost::geometry::index::rtree<atom, boost::geometry::index::linear<16>>> fa_rT);

  std::vector<double> get_timestep_vec();
  std::vector<int> get_atomscount_vec();
  std::vector<boost::geometry::index::rtree<atom, boost::geometry::index::linear<16>>> get_frame_atoms_rT();
};
