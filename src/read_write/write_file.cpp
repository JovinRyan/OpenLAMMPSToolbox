#include "read_write/write_file.h"

void ddc_to_custom_dump(dump_data_container &in_dump, std::string fname)
{
  std::cout << "Writing File: " << fname << "\n";

  std::ofstream outfile(fname);

  for (int i = 0; i < size(in_dump.frame_atoms_vec); i++)
  {
    outfile << "ITEM: TIMESTEP\n";
    outfile << in_dump.get_timestep_vec()[i] << "\n";

    outfile << "ITEM: NUMBER OF ATOMS\n";
    outfile << size(in_dump.frame_atoms_vec[i]) << "\n";

    outfile << "ITEM: BOX BOUNDS pp pp pp\n";
    outfile << in_dump.get_max_boxbounds()[0].first << " " << in_dump.get_max_boxbounds()[0].second << "\n";
    outfile << in_dump.get_max_boxbounds()[1].first << " " << in_dump.get_max_boxbounds()[1].second << "\n";
    outfile << in_dump.get_max_boxbounds()[2].first << " " << in_dump.get_max_boxbounds()[2].second << "\n";

    outfile << "ITEM: ATOMS id type x y z\n";

    for (int j = 0; j < size(in_dump.frame_atoms_vec[i]); j++)
    {
      outfile << in_dump.frame_atoms_vec[i][j].get_id() << " " << in_dump.frame_atoms_vec[i][j].get_type() << " "
              << in_dump.frame_atoms_vec[i][j].get_coords()[0] << " " << in_dump.frame_atoms_vec[i][j].get_coords()[1] << " "
              << in_dump.frame_atoms_vec[i][j].get_coords()[2] << "\n";
    }
  }
}