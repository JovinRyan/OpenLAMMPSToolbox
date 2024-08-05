#include "read_write/read_file.h"

dump_data_container xyzToDumpData(std::ifstream &infile)
{
  std::vector<int> infileindexes;
  std::vector<int> atomscount_vec;
  std::vector<std::pair<int, int>> frameindexpairs;
  std::vector<double> timesteps_vec;
  std::vector<std::string> parsedfile;

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

  std::vector<std::vector<atom>> frame_atoms_vec(size(frameindexpairs));

  for (int i = 0; i < size(frame_atoms_vec); i++)
  {
    int start_index = frameindexpairs[i].first, stop_index = frameindexpairs[i].second;
    for (int j = start_index - 1; j < stop_index; j++)
    {
      frame_atoms_vec[i].push_back(atom(j - (start_index - 2), stoi(string_to_vec(parsedfile[j])[0]), stod(string_to_vec(parsedfile[j])[1]), stod(string_to_vec(parsedfile[j])[2]), stod(string_to_vec(parsedfile[j])[3])));
    } /* Sloppy numbering for ID but it works */
    std::cout << "Parsing Frame " << i + 1 << "/" << size(frame_atoms_vec) << " Atom Count: " << size(frame_atoms_vec[i]) << "\n";
  }

  return dump_data_container(timesteps_vec, atomscount_vec, frame_atoms_vec);
}

dump_data_container customToDumpData(std::ifstream &infile)
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

  return dump_data_container(timesteps_vec, atomscount_vec, frame_atoms_vec);
}