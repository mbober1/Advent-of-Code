#include <fstream>
#include <input.hpp>

std::vector<std::string> read_file(const std::string &filename)
{
  std::vector<std::string> results;
  std::ifstream file;
  file.exceptions(std::ifstream::failbit);
  file.open(filename);

  std::string line;
  while (std::getline(file, line))
  {
    results.push_back(line);
  }

  return results;
}