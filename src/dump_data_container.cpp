#include "../include/dump_data_container.h"

dump_data_container::dump_data_container(std::vector<double> t_vec, std::vector<int> ac_vec, std::vector<boost::geometry::index::rtree<atom, boost::geometry::index::linear<16>>> fa_rT)
    : timestep_vec(t_vec), atomscount_vec(ac_vec), frame_atoms_rT(fa_rT)
{
}

std::vector<double> dump_data_container::get_timestep_vec() { return timestep_vec; }

std::vector<int> dump_data_container::get_atomscount_vec() { return atomscount_vec; }

std::vector<boost::geometry::index::rtree<atom, boost::geometry::index::linear<16>>>
dump_data_container::get_frame_atoms_rT() { return frame_atoms_rT; }
