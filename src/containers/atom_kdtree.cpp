#include "containers/atom_kdtree.h"
#include <algorithm>
#include <cmath>

atom_kdtree::atom_node *atom_kdtree::build_atom_kdtree(std::vector<atom> &atom_vec, int depth, int start, int end)
{
  if (start >= end)
  {
    return nullptr;
  }

  int axis = depth % 3;
  int mid = start + (end - start) / 2;

  std::nth_element(atom_vec.begin() + start, atom_vec.begin() + mid, atom_vec.begin() + end,
                   [axis](atom &atom_a, atom &atom_b)
                   { return atom_a.get_coords()[axis] < atom_b.get_coords()[axis]; });

  atom_node *node = new atom_node(atom_vec[mid]);
  node->left = build_atom_kdtree(atom_vec, depth + 1, start, mid);
  node->right = build_atom_kdtree(atom_vec, depth + 1, mid + 1, end);

  return node;
}

void atom_kdtree::atom_kdtree_nn(atom_node *node, atom &target_atom, int depth, atom_node *&best, double &best_dist) const
{
  if (node == nullptr)
  {
    return;
  }

  double d = node->atom_leaf.get_distance(target_atom);
  if (d < best_dist)
  {
    best_dist = d;
    best = node;
  }

  int axis = depth % 3;
  double diff = target_atom.get_coords()[axis] - node->atom_leaf.get_coords()[axis];

  atom_node *near_branch = diff < 0 ? node->left : node->right;
  atom_node *far_branch = diff < 0 ? node->right : node->left;

  atom_kdtree_nn(near_branch, target_atom, depth + 1, best, best_dist);

  if (std::abs(diff) < best_dist)
  {
    atom_kdtree_nn(far_branch, target_atom, depth + 1, best, best_dist);
  }
}

atom_kdtree::atom_kdtree(const std::vector<atom> &atom_vec)
{
  std::vector<atom> atom_vec_copy = atom_vec;
  root = build_atom_kdtree(atom_vec_copy, 0, 0, atom_vec_copy.size());
}

atom atom_kdtree::find_nn(atom &target_atom) const
{
  if (root == nullptr)
  {
    throw std::logic_error("Atom KDTree is not populated.");
  }

  atom_node *best = nullptr;
  double best_dist = std::numeric_limits<double>::max();
  atom_kdtree_nn(root, target_atom, 0, best, best_dist);

  if (best == nullptr)
  {
    throw std::runtime_error("No nearest neighboring atom found.");
  }

  return best->atom_leaf;
}
