#include <input.hpp>
#include <iostream>
#include <regex>


int find_mul(const std::string& data)
{
  int result = 0;
  std::regex mul_regex("mul\\(([0-9][0-9]?[0-9]?),([0-9][0-9]?[0-9]?)\\)");
  
  auto begin = std::sregex_iterator(data.begin(), data.end(), mul_regex);
  auto end = std::sregex_iterator();

  for (std::sregex_iterator i = begin; i != end; ++i)
  {
    std::smatch match = *i;
    int val_1 = std::stoi(match[1]);
    int val_2 = std::stoi(match[2]);
    result += val_1 * val_2;
  }

  return result;
}

std::string remove_garbage(std::string data)
{
  std::regex inst_regex("don't\\(\\).*?do\\(\\)|\\s+"); // remove don't()...do() and whitespaces
  std::smatch match;

  while (true == std::regex_search(data, match, inst_regex))
  {
    std::string test = data.substr(match.position(), match.length());
    data.erase(match.position(), match.length());
    std::cout << "Removing: " << test << std::endl << std::endl;
  }

  return data;
}

int main(void)
{
  int result_1 = 0;
  int result_2 = 0;
  
  try
  {
    const auto memory = read_all("2024/inputs/day_3.txt");
    result_1 = find_mul(memory);

    const auto stripped = remove_garbage(memory);
    result_2 = find_mul(stripped);
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
  }

  std::cout << "Result 1: " << result_1 << std::endl;
  std::cout << "Result 2: " << result_2 << std::endl;
  
  return 0;
}
