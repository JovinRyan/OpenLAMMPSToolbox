#ifndef DDC_GET_DISP_H
#define DDC_GET_DISP_H

#include <vector>
#include <iostream>
#include <algorithm>

#include "containers/dump_data_container.h"
#include "utils/vector_utils.h"

std::pair<std::vector<int>, std::vector<int>> get_displacement_vec(dump_data_container &in_dump, double disp_threshold, std::string displacement_flag);

std::pair<std::vector<int>, std::vector<int>> get_displacement_vec_from_ref(dump_data_container &in_dump, dump_data_container &ref_dump, double disp_threshold);

#endif
