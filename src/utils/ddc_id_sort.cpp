#include "utils/ddc_id_sort.h"

int partition(std::vector<atom> &in_atom_vec, int low, int high)
{
  int pivot = in_atom_vec[low].get_id();
  int i = low - 1;
  int j = high + 1;

  while (true)
  {
    do
    {
      i++;
    } while (in_atom_vec[i].get_id() < pivot);
    do
    {
      j--;
    } while (in_atom_vec[j].get_id() > pivot);

    if (i >= j)
      return j;

    std::swap(in_atom_vec[i], in_atom_vec[j]);
  }
}

void atom_vec_quicksort(std::vector<atom> &in_atom_vec, int low, int high)
{
  if (low < high)
  {
    int pi = partition(in_atom_vec, low, high);

    atom_vec_quicksort(in_atom_vec, low, pi);
    atom_vec_quicksort(in_atom_vec, pi + 1, high);
  }
}

void ddc_id_quicksort(dump_data_container &in_ddc)
{
  std::cout << "Sorting Atoms By ID." << "\n";

  for (int i = 0; i < size(in_ddc.frame_atoms_vec); i++)
  {
    std::cout << "Sorting Frame " << i + 1 << "/" << size(in_ddc.frame_atoms_vec) << "\n";

    atom_vec_quicksort(in_ddc.frame_atoms_vec[i], 0, size(in_ddc.frame_atoms_vec[i]) - 1);
  }
}
