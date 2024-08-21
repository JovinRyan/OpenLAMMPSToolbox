#pragma once

#include <vector>
#include <random>
#include <memory>
#include <algorithm>

#include "containers/atom_classes.h"

std::vector<std::unique_ptr<atom>> random_atom_creator(int count);

std::vector<std::unique_ptr<atom>> sequential_atom_creator(int count);
