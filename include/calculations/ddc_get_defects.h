#pragma once

#include <vector>
#include <iostream>
#include <algorithm>

#include "containers/dump_data_container.h"
#include "utils/sort_checker.h"
#include "utils/ddc_sort.h"
#include "utils/vector_utils.h"

std::pair<std::vector<int>, std::vector<std::vector<int>>> ddc_get_vacancy_interstitial_from_ref(dump_data_container &in_dump, dump_data_container &ref_dump, double disp_threshhold);
// returns vector containing number of atoms, and vector containing vector of atom IDs for each frame (vector of vector of integers)

std::pair<std::vector<int>, std::vector<std::vector<int>>> ddc_get_vacancy_interstitial_recombination(dump_data_container &in_dump, double disp_threshhold);

void vacancy_interstitial_vec_remove_recombinations(std::vector<std::vector<int>> &vacancy_interstitial_vec, std::vector<std::vector<int>> &recombination_vec);
