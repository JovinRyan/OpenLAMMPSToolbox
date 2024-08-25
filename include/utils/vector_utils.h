#pragma once

#include <vector>
#include <algorithm>
#include <concepts>

void vector_delete_from_vector(std::vector<int> &vec_a, std::vector<int> &vec_b);

void vector_add_from_vector(std::vector<int> &vec_a, std::vector<int> &vec_b);

void vector_make_unique(std::vector<int> &in_vec);
