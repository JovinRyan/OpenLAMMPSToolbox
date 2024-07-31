#include <iostream>
#include <vector>
#include <boost/geometry.hpp>
#include <boost/geometry/index/rtree.hpp>
#include <boost/geometry/geometries/register/point.hpp>

#include "../atom.h"
#include "../../src/utils/string_to_vec.cpp"

std::vector<boost::geometry::index::rtree<atom, boost::geometry::index::linear<16>>> frameToRtree();
