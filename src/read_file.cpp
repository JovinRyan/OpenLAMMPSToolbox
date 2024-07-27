#include <iostream>
#include <fstream>
#include "atom.cpp"

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    std::cerr << "No File Provided!\n";

    return 1;
  }

  std::cout << "Reading File: " << argv[1] << "\n";
  std::ifstream infile(argv[1]);
  if (infile.is_open() && infile.good())
  {
    std::cout << "File Succesfully Read\n";
    std::cout << "File Head: \n";
    std::string line = "";
    // Printing top 20 lines of the file
    for (int i = 0; i < 20; i++)
    {
      getline(infile, line);
      std::cout << line << "\n";
    }
  }

  return 0;
}
