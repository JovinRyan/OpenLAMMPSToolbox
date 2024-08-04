#include <iostream>
#include <fstream>
#include <vector>
#include "./utils/string_to_vec.cpp"
#include "dump_data_container.cpp"

void customToDumpData(std::ifstream &infile)
{
  std::vector<int> infileindexes;
  std::vector<int> atomscount_vec;
  std::vector<double> timesteps_vec;
  std::vector<std::pair<int, int>> frameindexpairs;
  std::vector<std::string> parsedfile;

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
  }

  for (int i = 0; i < size(infileindexes); i++)
  {
    frameindexpairs.push_back(std::make_pair(infileindexes[i], infileindexes[i] + atomscount_vec[i])); // Should account for varying atom count, needs testing
  }

  std::vector<std::vector<atom>> frame_atoms_vec(size(frameindexpairs));

  for (int i = 0; i < size(frame_atoms_vec); i++)
  {
    int start_index = frameindexpairs[i].first, stop_index = frameindexpairs[i].second;

    for (int j = start_index; j < stop_index; j++)
    {
      std::vector<std::string> temp_vec = string_to_vec(parsedfile[j]);

      frame_atoms_vec[i].push_back(atom(stoi(temp_vec[0]), stoi(temp_vec[1]), stod(temp_vec[2]), stod(temp_vec[3]), stod(temp_vec[4])));
    }
    std::cout << "Parsing Frame " << i + 1 << "/" << size(frame_atoms_vec) << " Atom Count: " << size(frame_atoms_vec[i]) << "\n";
  }
}

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    std::cerr << "No LAMMPS Dump File Provided!\n";

    return 1;
  }

  std::cout << "Reading Custom Dump File: " << argv[1] << "\n";
  std::ifstream infile(argv[1]);
  if (infile.is_open() && infile.good())
  {
    customToDumpData(infile);
  }

  return 0;
}
