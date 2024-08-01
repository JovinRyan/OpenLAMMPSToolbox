#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
#include <random>
#include <vector>

#include "./atom.cpp"

class atom_kdtree
{
private:
  struct atom_node
  {
    atom atom_leaf;

    atom_node *left;
    atom_node *right;

    atom_node(const atom &new_atom) : atom_leaf(new_atom), left(nullptr), right(nullptr) {}
  };

  atom_node *root;

  // Function to pupulate kdtree
  atom_node *build_atom_kdtree(std::vector<atom> &atom_vec, int depth, int start, int end)
  {
    if (start >= end)
    {
      return nullptr;
    }

    int axis = depth % 3;
    int mid = start + (end - start) / 2;

    // Sort atom leaves in tree based on axis
    std::nth_element(atom_vec.begin() + start, atom_vec.begin() + mid, atom_vec.begin() + end,
                     [axis](atom &atom_a, atom &atom_b)
                     { return atom_a.get_coords()[axis] < atom_b.get_coords()[axis]; });

    atom_node *node = new atom_node(atom_vec[mid]);
    node->left = build_atom_kdtree(atom_vec, depth + 1, start, mid);    // Recursive left tree
    node->right = build_atom_kdtree(atom_vec, depth + 1, mid + 1, end); // Recursive right tree

    return node;
  }

  void atom_kdtree_nn(atom_node *node, atom &target_atom, int depth, atom_node *&best, double &best_dist)
      const
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

public:
  atom_kdtree(const std::vector<atom> &atom_vec)
  {
    std::vector<atom> atom_vec_copy = atom_vec;

    root = build_atom_kdtree(atom_vec_copy, 0, 0, size(atom_vec_copy));
  }

  atom find_nn(atom &target_atom)
      const
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
};

int main()
{

  std::vector<atom> atoms = {
      atom(1, 1, 2.0, 3.0, 4.0),
      atom(2, 1, 5.0, 4.0, 3.0),
      atom(3, 1, 9.0, 6.0, 2.0),
      atom(4, 1, 4.0, 7.0, 8.0),
      atom(5, 1, 8.0, 1.0, 5.0),
      atom(6, 1, 7.0, 2.0, 9.0)};

  atom_kdtree tree(atoms);

  atom target(0, 1, 9.0, 2.0, 1.0);
  atom nearest = tree.find_nn(target);

  std::cout << "Target Atom: x: " << target.get_coords()[0] << " y: " << target.get_coords()[1] << " z: " << target.get_coords()[2] << '\n';
  std::cout << "Nearest Atom: " << nearest.get_coords()[0] << " y: " << nearest.get_coords()[1] << " z: " << nearest.get_coords()[2] << '\n';
  std::cout << "Distance: " << nearest.get_distance(target) << '\n';

  return 0;
}
