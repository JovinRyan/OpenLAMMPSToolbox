#pragma once

#include <vector>
#include "../src/atom.cpp"

class dump_data_container
{
private:
  std::vector<double> timestep_vec;
  std::vector<int> atomscount_vec;

public:
  std::vector<std::vector<atom>> frame_atom_vec;
  dump_data_container(std::vector<double> t_vec, std::vector<int> ac_vec, std::vector<std::vector<atom>> fa_vec);
  ~dump_data_container();

  std::vector<double> get_timestep_vec();
  std::vector<int> get_atomscount_vec();
};
