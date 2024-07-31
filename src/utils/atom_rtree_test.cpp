#pragma once

#include <boost/geometry.hpp>
#include <boost/geometry/index/rtree.hpp>
#include <boost/geometry/geometries/register/point.hpp>
#include <vector>
#include <iostream>
#include <cmath>

// Define the atom class
class atom
{
public:
  int id;
  int type;
  double x_coord;
  double y_coord;
  double z_coord;

  // Default constructor
  atom() : id(0), type(0), x_coord(0.0), y_coord(0.0), z_coord(0.0) {}

  // Parameterized constructor
  atom(int ID, int Type, double x, double y, double z) : id(ID), type(Type), x_coord(x), y_coord(y), z_coord(z) {}

  std::vector<double> get_coords() const
  {
    return {x_coord, y_coord, z_coord};
  }

  int get_id() const
  {
    return id;
  }

  int get_type() const
  {
    return type;
  }

  double get_displacement(const atom &ref_atom) const
  {
    const auto ref_coords = ref_atom.get_coords();
    return std::sqrt((x_coord - ref_coords[0]) * (x_coord - ref_coords[0]) +
                     (y_coord - ref_coords[1]) * (y_coord - ref_coords[1]) +
                     (z_coord - ref_coords[2]) * (z_coord - ref_coords[2]));
  }
};

// Register the atom class as a 3D point
BOOST_GEOMETRY_REGISTER_POINT_3D(atom, double, boost::geometry::cs::cartesian, x_coord, y_coord, z_coord)

namespace bg = boost::geometry;
namespace bgi = boost::geometry::index;

typedef bg::model::box<atom> Box;
typedef std::pair<atom, atom> Value;

int main()
{
  // Create the R-tree
  bgi::rtree<Value, bgi::quadratic<16>> rtree;

  // Insert atom objects into the R-tree
  atom atom1(1, 1, 0.0, 0.0, 0.0);
  atom atom2(2, 1, 1.0, 1.0, 1.0);
  atom atom3(3, 2, 2.0, 2.0, 2.0);

  rtree.insert(std::make_pair(atom1, atom1));
  rtree.insert(std::make_pair(atom2, atom2));
  rtree.insert(std::make_pair(atom3, atom3));

  // Iterate over the objects in the R-tree
  for (auto it = rtree.begin(); it != rtree.end(); ++it)
  {
    std::cout << "ID: " << it->second.get_id() << ", Type: " << it->second.get_type() << std::endl;
  }

  // Define a query region (e.g., a box)
  Box query_box(atom(0, 0, 0.0, 0.0, 0.0), atom(0, 0, 2.0, 2.0, 2.0));

  // Perform the query and iterate over the results
  std::vector<Value> result;
  rtree.query(bgi::intersects(query_box), std::back_inserter(result));

  for (const auto &v : result)
  {
    std::cout << "Queried ID: " << v.second.get_id() << ", Type: " << v.second.get_type() << std::endl;
  }

  return 0;
}
