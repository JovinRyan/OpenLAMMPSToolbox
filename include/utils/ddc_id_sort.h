#pragma once

#include <bits/stdc++.h>

#include "containers/dump_data_container.h"

int partition(std::vector<atom> &in_atom_vec, int low, int high);

void atom_vec_quicksort(std::vector<atom> &in_atom_vec, int low, int high);

void ddc_id_quicksort(dump_data_container &in_ddc);
