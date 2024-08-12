#include "utils/vector_utils.h"

void vector_delete_from_vector(std::vector<int> &vec_a, std::vector<int> &vec_b)
{
  std::sort(begin(vec_b), end(vec_b));

  vec_a.erase(std::remove_if(begin(vec_a), end(vec_a),
                             [&](auto x)
                             { return std::find(begin(vec_b), end(vec_b), x) != end(vec_b); }),
              end(vec_a));
}

void vector_add_from_vector(std::vector<int> &vec_a, std::vector<int> &vec_b)
{
  vec_a.insert(vec_a.end(), vec_b.begin(), vec_b.end());

  std::sort(vec_a.begin(), vec_a.end());
  vec_a.erase(std::unique(vec_a.begin(), vec_a.end()), vec_a.end());
}
