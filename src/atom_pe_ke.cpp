#include "../include/atom_pe_ke.h"
#include "atom.cpp"

atom_pe_ke::atom_pe_ke(int ID, int Type, double x, double y, double z, double PE, double KE) : atom(ID, Type, x, y, z), pe(PE), ke(KE)
{
}
