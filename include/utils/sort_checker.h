#pragma once

#include <vector>
#include <random>
#include <iostream>
#include <memory>

#include "containers/atom_classes.h"
#include "containers/dump_data_container.h"

bool id_sort_check(std::vector<std::unique_ptr<atom>> &in_atom_vec);

bool ddc_id_sort_check(dump_data_container &in_ddc);
