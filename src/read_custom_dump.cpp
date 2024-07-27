#include <iostream>
#include <fstream>
#include <vector>

void getDumpDataTuple(std::ifstream &infile)
{
  std::vector<int> infileindexes;
  std::vector<int> atomscount;
  std::vector<int> frameindexpairs;

  std::string line;
  int line_num = 0;
  while (std::getline(infile, line))
  {
    ++line_num;
    if (line.find("ITEM: ATOMS") != std::string::npos)
    {
      infileindexes.push_back(line_num);
    }
    // Substring match to create atoms count vs timestep vector
    if (line.find("ITEM: NUMBER OF ATOMS") != std::string::npos)
    {
      std::getline(infile, line);
      atomscount.push_back(std::stoi(line));
    }
  }

  for (int i = 0; i < infileindexes.size(); i++)
  {
    frameindexpairs.push_back(infileindexes[i]);
  }
}

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    std::cerr << "No LAMMPS Dump File Provided!\n";

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
