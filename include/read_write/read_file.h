#include <iostream>
#include <fstream>
#include <vector>
#include "utils/string_to_vec.h"
#include "containers/dump_data_container.h"

#ifndef FUNCTIONS_READ_FILE_INCLUDED
#define FUNCTIONS_READ_FILE_INCLUDED

dump_data_container xyzToDumpData(std::ifstream &infile);

dump_data_container customToDumpData(std::ifstream &infile);

#endif
