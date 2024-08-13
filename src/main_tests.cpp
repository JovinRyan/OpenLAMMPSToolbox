#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "tests/doctest.h"
#include "tests/atom_quicksort_test.h"

TEST_CASE("Atom QuickSort Test")
{
  CHECK(atom_quicksort_test);
}
