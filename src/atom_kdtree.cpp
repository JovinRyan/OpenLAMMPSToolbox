#include <iostream>
#include <algorithm>

#include "./atom.cpp"
#include "../include/atom_kdtree.h"

class atom_node
{
public:
  atom_node(atom new_atom);
  atom atom_leaf;

  atom_node *left;
  atom_node *right;
};

atom_node::atom_node(atom new_atom) : atom_leaf(new_atom), left(nullptr), right(nullptr)
{
}

atom_node *new_atom_node(atom new_atom)
{
  atom_node *node = new atom_node(new_atom);
  node->atom_leaf = new_atom;
  node->left = node->right = nullptr;

  return node;
}

atom_node *insert_atom_node(atom_node *root, atom new_atom, unsigned depth)
{
  if (root == nullptr)
  {
    return new_atom_node(new_atom);
  }

  unsigned k = size(new_atom.get_coords());

  unsigned cd = depth % k;

  if (new_atom.get_coords()[cd] < (root->atom_leaf.get_coords()[cd]))
  {
    root->left = insert_atom_node(root->left, new_atom, depth + 1);
  }
  else
  {
    root->right = insert_atom_node(root->right, new_atom, depth + 1);
  }

  return root;
}

int main()
{

  return 0;
}
