#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "tests/doctest.h"
#include "tests/atom_quicksort_test.h"
#include "tests/atom_method_test.h"
#include "tests/sort_check_test.h"

TEST_CASE("Atom QuickSort Test")
{
  CHECK(atom_quicksort_test);
}

TEST_CASE("Atom Get Distance Test")
{
  CHECK(atom_dist_test());
}

TEST_CASE("Atom ID Sort Check Test")
{
  CHECK(id_sort_check_test().first);

  CHECK(!(id_sort_check_test().second));
}
