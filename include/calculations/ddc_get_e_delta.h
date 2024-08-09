#ifndef DDC_GET_E_DEL_H
#define DDC_GET_E_DEL_H

#include <vector>
#include <iostream>

#include "containers/dump_data_container.h"

std::pair<std::vector<int>, std::vector<atom>> get_pe_del(dump_data_container in_dump, double e_threshold);

#endif
