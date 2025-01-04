#pragma once

#include <vector>
#include <iostream>
#include <math.h>

#include "containers/dump_data_container.h"
#include "utils/ddc_sort.h"
#include "utils/sort_checker.h"

std::pair<std::vector<int>, std::vector<int>> ddc_compute_greater_than(dump_data_container &in_dump, double threshold, int compute_index);

std::pair<std::vector<int>, std::vector<int>> ddc_compute_less_than(dump_data_container &in_dump, double threshold, int compute_index);
