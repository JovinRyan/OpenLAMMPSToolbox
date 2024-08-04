#include "utils/string_to_vec.h"

std::vector<std::string> string_to_vec(std::string s, std::string delimiter)
{
  size_t pos_start = 0, pos_end, delim_len = delimiter.length();
  std::string token;
  std::vector<std::string> str_vect;

  while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos)
  {
    token = s.substr(pos_start, pos_end - pos_start);
    pos_start = pos_end + delim_len;
    str_vect.push_back(token);
  }

  str_vect.push_back(s.substr(pos_start));
  return str_vect;
}
