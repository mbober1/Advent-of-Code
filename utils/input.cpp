#include <input.hpp>
#include <fstream>
#include <stdexcept>

std::vector<std::string> read_lines(const std::string &filename)
{
  std::vector<std::string> results;
  std::string line;

  std::ifstream file(filename);
  if(!file) throw std::runtime_error("Cannot open file: " + filename);

  while (std::getline(file, line))
  {
    results.push_back(line);
  }

  file.close();
  return results;
}

std::vector<std::string> read_words(const std::string &filename)
{
  std::vector<std::string> results;
  std::string word;

  std::ifstream file(filename);
  if(!file) throw std::runtime_error("Cannot open file: " + filename);

  while (file >> word)
  {
    results.push_back(word);
  }

  file.close();
  return results;
}