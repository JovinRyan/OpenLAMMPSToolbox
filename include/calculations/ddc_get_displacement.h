#ifndef DDC_GET_DISP_H
#define DDC_GET_DISP_H

#include <vector>
#include <iostream>

#include "containers/dump_data_container.h"

std::vector<int> get_displacement_vec(dump_data_container in_dump, double disp_threshold);

#endif
