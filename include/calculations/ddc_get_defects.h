#pragma once

#include <vector>
#include <iostream>
#include <algorithm>

#include "containers/dump_data_container.h"
#include "utils/sort_checker.h"
#include "utils/ddc_sort.h"

std::pair<std::vector<int>, std::vector<std::vector<int>>> ddc_get_void_interstitial_from_ref(dump_data_container &in_dump, dump_data_container &ref_dump, double disp_threshhold);
// returns vector containing number of atoms, and vector containing vector of atom IDs for each frame (vector of vector of integers)
