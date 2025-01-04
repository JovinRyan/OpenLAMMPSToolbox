#pragma once

#include "containers/dump_data_container.h"
#include "utils/ddc_sort.h"

dump_data_container id_vec_to_ddc(dump_data_container &base_ddc, std::vector<int> &id_vec);

dump_data_container varying_id_vec_to_ddc(dump_data_container &base_ddc, std::vector<std::vector<int>> &varying_id_vec);

dump_data_container varying_id_vec_to_combine_ddc(dump_data_container &base_ddc, dump_data_container &ref_ddc, std::vector<std::vector<int>> &varying_id_vec);
