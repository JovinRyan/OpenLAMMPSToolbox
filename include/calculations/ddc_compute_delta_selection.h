#ifndef DDC_GET_E_DEL_H
#define DDC_GET_E_DEL_H

#include <vector>
#include <iostream>

#include "containers/dump_data_container.h"
#include "utils/ddc_sort.h"

std::pair<std::vector<int>, std::vector<int>> ddc_compute_delta_selection_greater_than(dump_data_container &in_dump, double threshold, int compute_index);

#endif
