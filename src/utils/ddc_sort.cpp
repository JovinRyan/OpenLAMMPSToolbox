#include "utils/ddc_sort.h"

// ID

int id_partition(std::vector<std::unique_ptr<atom>> &in_atom_vec, int low, int high)
{
  int pivot = in_atom_vec[low].get()->get_id();
  int i = low - 1;
  int j = high + 1;

  while (true)
  {
    do
    {
      i++;
    } while (in_atom_vec[i].get()->get_id() < pivot);
    do
    {
      j--;
    } while (in_atom_vec[j].get()->get_id() > pivot);

    if (i >= j)
      return j;

    std::swap(in_atom_vec[i], in_atom_vec[j]);
  }
}

void atom_vec_quicksort_by_id(std::vector<std::unique_ptr<atom>> &in_atom_vec, int low, int high)
{
  if (low < high)
  {
    int pi = id_partition(in_atom_vec, low, high);

    atom_vec_quicksort_by_id(in_atom_vec, low, pi);
    atom_vec_quicksort_by_id(in_atom_vec, pi + 1, high);
  }
}

void ddc_id_quicksort(dump_data_container &in_ddc)
{
  std::cout << "Sorting Atoms By ID." << "\n";

  for (int i = 0; i < size(in_ddc.frame_atoms_vec); i++)
  {
    std::cout << "Sorting Frame " << i + 1 << "/" << size(in_ddc.frame_atoms_vec) << "\n";

    atom_vec_quicksort_by_id(in_ddc.frame_atoms_vec[i], 0, size(in_ddc.frame_atoms_vec[i]) - 1);
  }
}

// X Coord

int x_partition(std::vector<std::unique_ptr<atom>> &in_atom_vec, int low, int high)
{
  double pivot = in_atom_vec[low]->get_coords()[0];
  int i = low - 1;
  int j = high + 1;

  while (true)
  {
    do
    {
      i++;
    } while (in_atom_vec[i]->get_coords()[0] < pivot);
    do
    {
      j--;
    } while (in_atom_vec[j]->get_coords()[0] > pivot);

    if (i >= j)
      return j;

    std::swap(in_atom_vec[i], in_atom_vec[j]);
  }
}

void atom_vec_quicksort_by_x(std::vector<std::unique_ptr<atom>> &in_atom_vec, int low, int high)
{
  if (low < high)
  {
    int pi = x_partition(in_atom_vec, low, high);

    atom_vec_quicksort_by_x(in_atom_vec, low, pi);
    atom_vec_quicksort_by_x(in_atom_vec, pi + 1, high);
  }
}

void ddc_x_quicksort(dump_data_container &in_ddc)
{
  std::cout << "Sorting Atoms By X Coordinate." << "\n";

  for (int i = 0; i < size(in_ddc.frame_atoms_vec); i++)
  {
    std::cout << "Sorting Frame " << i + 1 << "/" << size(in_ddc.frame_atoms_vec) << "\n";

    atom_vec_quicksort_by_x(in_ddc.frame_atoms_vec[i], 0, size(in_ddc.frame_atoms_vec[i]) - 1);
  }
}

// Y Coord

int y_partition(std::vector<std::unique_ptr<atom>> &in_atom_vec, int low, int high)
{
  double pivot = in_atom_vec[low]->get_coords()[1];
  int i = low - 1;
  int j = high + 1;

  while (true)
  {
    do
    {
      i++;
    } while (in_atom_vec[i]->get_coords()[1] < pivot);
    do
    {
      j--;
    } while (in_atom_vec[j]->get_coords()[1] > pivot);

    if (i >= j)
      return j;

    std::swap(in_atom_vec[i], in_atom_vec[j]);
  }
}

void atom_vec_quicksort_by_y(std::vector<std::unique_ptr<atom>> &in_atom_vec, int low, int high)
{
  if (low < high)
  {
    int pi = y_partition(in_atom_vec, low, high);

    atom_vec_quicksort_by_y(in_atom_vec, low, pi);
    atom_vec_quicksort_by_y(in_atom_vec, pi + 1, high);
  }
}

void ddc_y_quicksort(dump_data_container &in_ddc)
{
  std::cout << "Sorting Atoms By Y Coordinate." << "\n";

  for (int i = 0; i < size(in_ddc.frame_atoms_vec); i++)
  {
    std::cout << "Sorting Frame " << i + 1 << "/" << size(in_ddc.frame_atoms_vec) << "\n";

    atom_vec_quicksort_by_y(in_ddc.frame_atoms_vec[i], 0, size(in_ddc.frame_atoms_vec[i]) - 1);
  }
}

// Z Coord

int z_partition(std::vector<std::unique_ptr<atom>> &in_atom_vec, int low, int high)
{
  double pivot = in_atom_vec[low]->get_coords()[2];
  int i = low - 1;
  int j = high + 1;

  while (true)
  {
    do
    {
      i++;
    } while (in_atom_vec[i]->get_coords()[2] < pivot);
    do
    {
      j--;
    } while (in_atom_vec[j]->get_coords()[2] > pivot);

    if (i >= j)
      return j;

    std::swap(in_atom_vec[i], in_atom_vec[j]);
  }
}

void atom_vec_quicksort_by_z(std::vector<std::unique_ptr<atom>> &in_atom_vec, int low, int high)
{
  if (low < high)
  {
    int pi = z_partition(in_atom_vec, low, high);

    atom_vec_quicksort_by_z(in_atom_vec, low, pi);
    atom_vec_quicksort_by_z(in_atom_vec, pi + 1, high);
  }
}

void ddc_z_quicksort(dump_data_container &in_ddc)
{
  std::cout << "Sorting Atoms By Z Coordinate." << "\n";

  for (int i = 0; i < size(in_ddc.frame_atoms_vec); i++)
  {
    std::cout << "Sorting Frame " << i + 1 << "/" << size(in_ddc.frame_atoms_vec) << "\n";

    atom_vec_quicksort_by_z(in_ddc.frame_atoms_vec[i], 0, size(in_ddc.frame_atoms_vec[i]) - 1);
  }
}
