#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include "utils/string_to_vec.h"
#include "containers/atom_classes.h"

atom custom_str_to_atom(std::string in_line);

atom_varying custom_str_to_atom_varying(std::string in_line);
