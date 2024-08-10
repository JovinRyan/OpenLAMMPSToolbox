#include "utils/ddc_reset_id.h"

void atom_vec_reset_id(std::vector<std::unique_ptr<atom>> &in_atom_vec)
{
  for (int i = 0; i < size(in_atom_vec); i++)
  {
    in_atom_vec[i]->id = i + 1;
  }
}

void ddc_reset_id(dump_data_container &in_dump)
{
  for (int j = 0; j < size(in_dump.frame_atoms_vec); j++) // CHanging i to j just in case there's some weird behavior with the loop counter.
  {
    atom_vec_reset_id(in_dump.frame_atoms_vec[j]);
  }
}
