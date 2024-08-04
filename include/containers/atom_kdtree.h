#ifndef ATOM_KDTREE_H
#define ATOM_KDTREE_H

#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

#include "containers/atom_classes.h"

class atom_kdtree
{
private:
public:
  struct atom_node
  {
    atom atom_leaf;

    atom_node *left;
    atom_node *right;

    atom_node(const atom &new_atom) : atom_leaf(new_atom), left(nullptr), right(nullptr) {}
  };

  atom_node *root;

  // Function to pupulate kdtree
  atom_node *build_atom_kdtree(std::vector<atom> &atom_vec, int depth, int start, int end);

  void atom_kdtree_nn(atom_node *node, atom &target_atom, int depth, atom_node *&best, double &best_dist) const;

  atom_kdtree(const std::vector<atom> &atom_vec);

  atom find_nn(atom &target_atom) const;
};

#endif
