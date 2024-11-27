#include <input.hpp>
#include <iostream>

int main(void)
{
  try
  {
    auto file = read_file("day_1.txt");
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
  }
  
  return 0;
}
