#pragma once

#include <bits/stdc++.h>

#include "containers/dump_data_container.h"

// ID

int id_partition(std::vector<atom> &in_atom_vec, int low, int high);

void atom_vec_quicksort_by_id(std::vector<atom> &in_atom_vec, int low, int high);

void ddc_id_quicksort(dump_data_container &in_ddc);

// X Coord

int x_partition(std::vector<atom> &in_atom_vec, int low, int high);

void atom_vec_quicksort_by_x(std::vector<atom> &in_atom_vec, int low, int high);

void ddc_x_quicksort(dump_data_container &in_ddc);

// Y Coord

int y_partition(std::vector<atom> &in_atom_vec, int low, int high);

void atom_vec_quicksort_by_y(std::vector<atom> &in_atom_vec, int low, int high);

void ddc_y_quicksort(dump_data_container &in_ddc);

// Z Coord

int z_partition(std::vector<atom> &in_atom_vec, int low, int high);

void atom_vec_quicksort_by_z(std::vector<atom> &in_atom_vec, int low, int high);

void ddc_z_quicksort(dump_data_container &in_ddc);

// Figure out how to do pe, ke, total e, etc.

int compute_partition(std::vector<atom> &in_atom_vec, int low, int high, int compute_index);

void atom_vec_quicksort_by_compute(std::vector<atom> &in_atom_vec, int low, int high, int compute_index);

void ddc_compute_quicksort(dump_data_container &in_ddc, int compute_index);
