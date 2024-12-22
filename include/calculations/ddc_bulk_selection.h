#pragma once

#include <vector>
#include <iostream>
#include <math.h>

#include "containers/dump_data_container.h"
#include "utils/ddc_sort.h"

std::pair<std::vector<int>, std::vector<int>> ddc_bulk_selection_explicit(dump_data_container &in_dump, std::vector<double> min_max_vec);
