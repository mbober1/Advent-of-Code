#include <input.hpp>
#include <iostream>

#include <limits.h>
size_t find_smallest_idx(std::vector<int> list)
{
  size_t idx;
  int nubmer = INT_MAX;

  for (size_t i = 0; i < list.size(); i++)
  {
    if (list.at(i) < nubmer)
    {
      idx = i;
      nubmer = list.at(i);
    }
  }
  
  return idx;
}

int find_occurrences(std::vector<int> list, const int val)
{
  int result = 0;

  for (auto &&i : list)
  {
    if (i == val)
    {
      result++;
    }
  }
  
  return result;
}

int total_distance(const std::vector<std::string>& file)
{
  int result = 0;
  std::vector<int> column1, column2;

  for (size_t i = 0; i < file.size();)
  {
    column1.push_back(std::stoi(file.at(i++)));
    column2.push_back(std::stoi(file.at(i++)));
  }

  while (false == column1.empty() || false == column2.empty())
  {
    size_t idx1 = find_smallest_idx(column1);
    size_t idx2 = find_smallest_idx(column2);
    int val1 = column1.at(idx1);
    int val2 = column2.at(idx2);
    int distance = std::abs( val1 - val2 );
    column1.erase(column1.begin() + static_cast<std::vector<int>::difference_type>(idx1));
    column2.erase(column2.begin() + static_cast<std::vector<int>::difference_type>(idx2));
    result += distance;
  }

  return result;
}

int similarity_score(const std::vector<std::string>& file)
{
  int result = 0;
  std::vector<int> column1, column2;

  for (size_t i = 0; i < file.size();)
  {
    column1.push_back(std::stoi(file.at(i++)));
    column2.push_back(std::stoi(file.at(i++)));
  }

  for (auto &&val : column1)
  {
    int n = find_occurrences(column2, val);
    int score = n * val;
    result += score;
  }
  
  return result;
}


int main(void)
{
  try
  {
    auto words = read_words("2024/inputs/day_1.txt");

    auto result1 = total_distance(words);
    std::cout << "Total distance is " << result1 << std::endl;

    auto result2 = similarity_score(words);
    std::cout << "Similarity score is " << result2 << std::endl;

  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
  }
  
  return 0;
}
