#include <input.hpp>
#include <iostream>

int main(void)
{
  int result_1 = 0;
  int result_2 = 0;

  try
  {
    const auto data = read_lines("2024/inputs/day_7.txt");
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
  }

  std::cout << "Result 1: " << result_1 << std::endl;
  std::cout << "Result 2: " << result_2 << std::endl;
  return 0;
}
