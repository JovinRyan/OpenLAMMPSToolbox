#include <iostream>
#include <fstream>
#include <vector>
#include "./utils/string_to_vec.cpp"

void getDumpDataTuple(std::ifstream &infile)
{
  std::vector<int> infileindexes;
  std::vector<int> atomscount;
  std::vector<std::pair<int, int>> frameindexpairs;
  std::vector<double> timesteps;

  std::string line;
  int line_num = 0;
  while (std::getline(infile, line))
  {
    ++line_num;
    if (line.find("Timestep:") != std::string::npos)
    {
      std::vector<std::string> line_vec = string_to_vec(line); // string_to_vec() std::string -> std::vector<std::string> from ./utils/string_to_vec.cpp
      infileindexes.push_back(line_num);
      timesteps.push_back(stod(line_vec.back()));
    }
    // Substring match to create atoms count vs timestep vector
    if (!(line.find(" ") != std::string::npos))
    {
      atomscount.push_back(stoi(line));
    }
  }

  // Creating vector of paired indexes to separate individual frames
  for (int i = 0; i < std::size(infileindexes); i++)
  {
    frameindexpairs.push_back(std::make_pair(infileindexes[i] + 1, infileindexes[i] + atomscount[0]));
  }
}

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    std::cerr << "No LAMMPS Dump File Provided!\n";

    return 1;
  }

  std::string filename = argv[1];

  if (!(filename.find(".xyz") != std::string::npos))
  {
    std::cerr << "The LAMMPS Dump File Must Be Of \".xyz\" Format.\n";
    return 1;
  }

  std::cout << "Reading File: " << argv[1] << "\n";
  std::ifstream infile(argv[1]);
  if (infile.is_open() && infile.good())
  {
    getDumpDataTuple(infile);
  }

  return 0;
}
