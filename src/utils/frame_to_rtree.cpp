// #include <iostream>
// #include <vector>
// #include <boost/geometry.hpp>
// #include <boost/geometry/index/rtree.hpp>
// #include <boost/geometry/geometries/register/point.hpp>

// #include "../../include/atom.h"
// #include "./string_to_vec.cpp"

#include "../../include/utils/frame_to_rtree.h"

BOOST_GEOMETRY_REGISTER_POINT_3D(atom, double, boost::geometry::cs::cartesian, x_coord, y_coord, z_coord)

std::vector<boost::geometry::index::rtree<atom, boost::geometry::index::rstar<16>>> frameToRtree(std::vector<std::string> parsedfile, std::vector<std::pair<int, int>> frameindexpairs_vec)
{
  std::vector<std::vector<atom>> frame_atoms_vec(size(frameindexpairs_vec));

  std::vector<boost::geometry::index::rtree<atom, boost::geometry::index::rstar<16>>> frame_atoms_rT;

  for (int i = 0; i < std::size(frame_atoms_vec); i++)
  {
    boost::geometry::index::rtree<atom, boost::geometry::index::rstar<16>> atom_rT;

    int start_index = frameindexpairs_vec[i].first, stop_index = frameindexpairs_vec[i].second;
    for (int j = start_index - 1; j < stop_index; j++)
    {
      atom_rT.insert(atom(j - (start_index - 2), stoi(string_to_vec(parsedfile[j])[0]), stod(string_to_vec(parsedfile[j])[1]), stod(string_to_vec(parsedfile[j])[2]), stod(string_to_vec(parsedfile[j])[3])));
    } /* Sloppy numbering for ID but it works */
    frame_atoms_rT.push_back(atom_rT);

    std::cout << "Parsing Frame " << i + 1 << "/" << std::size(frame_atoms_vec) << " Atom Count: " << boost::size(atom_rT) << "\n";
  }

  return frame_atoms_rT;
}
