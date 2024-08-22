#include "read_write/read_file.h"

dump_data_container xyzToDumpData(std::ifstream &infile)
{
  std::vector<int> infileindexes;
  std::vector<int> atomscount_vec;
  std::vector<std::pair<int, int>> frameindexpairs;
  std::vector<double> timesteps_vec;
  std::vector<std::string> parsedfile;
  std::vector<std::vector<std::pair<double, double>>> frame_boxbounds_vec;

  std::string line;
  int line_num = 0;
  while (std::getline(infile, line))
  {
    parsedfile.push_back(line);
    ++line_num;
    if (line.find("Timestep:") != std::string::npos)
    {
      std::vector<std::string> line_vec = string_to_vec(line); // string_to_vec() std::string -> std::vector<std::string> from ./utils/string_to_vec.cpp
      infileindexes.push_back(line_num);
      timesteps_vec.push_back(stod(line_vec.back()));
    }
    // Substring match to create atoms count vs timestep vector
    if (!(line.find(" ") != std::string::npos))
    {
      atomscount_vec.push_back(stoi(line));
    }
  }

  // Creating vector of paired indexes to separate individual frames
  for (int i = 0; i < std::size(infileindexes); i++)
  {
    frameindexpairs.push_back(std::make_pair(infileindexes[i] + 1, infileindexes[i] + atomscount_vec[0]));
  }

  std::vector<std::vector<std::unique_ptr<atom>>> frame_atoms_vec(size(frameindexpairs));

  for (int i = 0; i < size(frame_atoms_vec); i++)
  {
    int start_index = frameindexpairs[i].first, stop_index = frameindexpairs[i].second;
    for (int j = start_index - 1; j < stop_index; j++)
    {
      frame_atoms_vec[i].push_back(std::make_unique<atom>(atom(j - (start_index - 2), stoi(string_to_vec(parsedfile[j])[0]), stod(string_to_vec(parsedfile[j])[1]),
                                                               stod(string_to_vec(parsedfile[j])[2]), stod(string_to_vec(parsedfile[j])[3]))));
    } /* Sloppy numbering for ID but it works */
    std::cout << "Parsing Frame " << i + 1 << "/" << size(frame_atoms_vec) << " Atom Count: " << size(frame_atoms_vec[i]) << "\n";

    frame_boxbounds_vec.push_back({std::make_pair(frame_atoms_vec[i][0]->get_coords()[0], frame_atoms_vec[i][atomscount_vec[i] - 1]->get_coords()[0]),
                                   std::make_pair(frame_atoms_vec[i][0]->get_coords()[1], frame_atoms_vec[i][atomscount_vec[i] - 1]->get_coords()[1]),
                                   std::make_pair(frame_atoms_vec[i][0]->get_coords()[2], frame_atoms_vec[i][atomscount_vec[i] - 1]->get_coords()[2])});
  }

  return dump_data_container(timesteps_vec, atomscount_vec, std::move(frame_atoms_vec), frame_boxbounds_vec);
}

dump_data_container customToDumpData(std::ifstream &infile, std::string atom_flag)
{
  std::vector<int> infileindexes;
  std::vector<int> atomscount_vec;
  std::vector<double> timesteps_vec;
  std::vector<std::pair<int, int>> frameindexpairs;
  std::vector<std::string> parsedfile;
  std::vector<std::vector<std::pair<double, double>>> frame_boxbounds_vec;

  std::string line;
  int line_num = 0;
  while (std::getline(infile, line))
  {
    parsedfile.push_back(line);
    ++line_num;
    if (line.find("ITEM: ATOMS") != std::string::npos)
    {
      infileindexes.push_back(line_num);
    }
    // Substring match to create atoms count vs timestep vector
    if (line.find("ITEM: NUMBER OF ATOMS") != std::string::npos)
    {
      std::getline(infile, line);
      parsedfile.push_back(line);
      ++line_num;
      atomscount_vec.push_back(std::stoi(line));
    }
    // Finding timestep to create timestep vector
    if (line.find("ITEM: TIMESTEP") != std::string::npos)
    {
      std::getline(infile, line);
      parsedfile.push_back(line);
      ++line_num;
      timesteps_vec.push_back(std::stod(line));
    }
    // Finding box bounds
    // Explicitly given in the custom dump files
    if (line.find("ITEM: BOX BOUNDS") != std::string::npos)
    {
      std::vector<std::pair<double, double>> frame_bb;
      for (int i = 0; i < 3; i++)
      {
        std::getline(infile, line);
        parsedfile.push_back(line);
        ++line_num;

        frame_bb.push_back(std::make_pair(stod(string_to_vec(line)[0]), stod(string_to_vec(line)[1])));
      }

      frame_boxbounds_vec.push_back(frame_bb);
    }
  }

  for (int i = 0; i < size(infileindexes); i++)
  {
    frameindexpairs.push_back(std::make_pair(infileindexes[i], infileindexes[i] + atomscount_vec[i])); // Should account for varying atom count, needs testing
  }

  std::vector<std::vector<std::unique_ptr<atom>>> frame_atoms_vec(size(frameindexpairs));

  for (int i = 0; i < size(frame_atoms_vec); i++)
  {
    int start_index = frameindexpairs[i].first, stop_index = frameindexpairs[i].second;

    for (int j = start_index; j < stop_index; j++)
    {
      std::vector<std::string> temp_vec = string_to_vec(parsedfile[j]);

      if (atom_flag == "varying")
      {
        frame_atoms_vec[i].push_back(std::make_unique<atom_varying>(custom_str_to_atom_varying(parsedfile[j])));
      }

      else
      {
        frame_atoms_vec[i].push_back(std::make_unique<atom>(custom_str_to_atom(parsedfile[j])));
      }
    }
    std::cout << "Parsing Frame " << i + 1 << "/" << size(frame_atoms_vec) << " Atom Count: " << size(frame_atoms_vec[i]) << "\n";
  }

  return dump_data_container(timesteps_vec, atomscount_vec, std::move(frame_atoms_vec), frame_boxbounds_vec);
}
