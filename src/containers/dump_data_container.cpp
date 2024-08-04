#include "containers/dump_data_container.h"

dump_data_container::dump_data_container(std::vector<double> t_vec, std::vector<int> ac_vec,
                                         std::vector<std::vector<atom>> fa_vec)
    : timestep_vec(t_vec), atomscount_vec(ac_vec), frame_atoms_vec(fa_vec)
{
}

std::vector<double> dump_data_container::get_timestep_vec() { return timestep_vec; }

std::vector<int> dump_data_container::get_atomscount_vec() { return atomscount_vec; }
