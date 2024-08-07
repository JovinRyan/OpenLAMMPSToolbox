#pragma once

#include <fstream>
#include <vector>
#include <iostream>

#include "containers/dump_data_container.h"

void ddc_to_custom_dump(dump_data_container &in_dump, std::string fname);
