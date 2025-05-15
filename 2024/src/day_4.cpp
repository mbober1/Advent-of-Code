#include <input.hpp>
#include <iostream>
#include <regex>


int find_xmas(const std::string& data)
{
  int result = 0;
  {
  std::regex mul_regex("XMAS");
  
  auto begin = std::sregex_iterator(data.begin(), data.end(), mul_regex);
  auto end = std::sregex_iterator();

  for (std::sregex_iterator i = begin; i != end; ++i)
  {
    std::smatch match = *i;
    std::cout << match.prefix() << " -> " << match.str() << " <- " << match.suffix() << std::endl;
    result++;
  }
  }

  {
  std::regex mul_regex("SAMX");
  
  auto begin = std::sregex_iterator(data.begin(), data.end(), mul_regex);
  auto end = std::sregex_iterator();

  for (std::sregex_iterator i = begin; i != end; ++i)
  {
    std::smatch match = *i;
    std::cout << match.prefix() << " -> " << match.str() << " <- " << match.suffix() << std::endl;
    result++;
  }
  }

  return result;
}

std::vector<std::string> create_columns(const std::vector<std::string> &data)
{
  std::vector<std::string> results;
  int rows = data.size();
  int cols = data[0].size();

  for (size_t i = 0; i < cols; i++)
  {
    std::string column;

    for (size_t j = 0; j < rows; j++)
    {
      column.push_back(data.at(j).at(i));
    }
    results.push_back(column);
    std::cout << "Column (" << i << "): ";
  }

  return results;
}

std::vector<std::string> create_diagonals(const std::vector<std::vector<char>> &data)
{
  std::vector<std::string> results;
  int rows = data.size();
  int cols = data[0].size();

  for ( int x = 1 - cols; x <= rows - 1; x++)
  {
    std::string diagonal;
    for ( int y = std::max(x, 0); y < std::min(rows, x + cols); y++) 
    {
      diagonal.push_back(data[y-x][y]);
      std::cout << data[y-x][y] << ' ';
    }

    results.push_back(diagonal);
    std::cout << '\n'; 
  }

  return results;
}

std::vector<std::vector<char>> no_transpose(const std::vector<std::string> &data)
{
  size_t size = data.size();
  std::vector<std::vector<char>> results(size);

  for (int i = 0; i < size; ++i)
  {
    results[i].resize(size);
    for (int j = 0; j < size; ++j)
    {
      results[i][j] = data[i][j];
    }
  }

  return results;
}

std::vector<std::vector<char>> transpose(const std::vector<std::string> &data)
{
  size_t size = data.size();
  std::vector<std::vector<char>> results(size);

  for (int i = 0; i < size; ++i)
  {
    results[i].resize(size);
    for (int j = 0; j < size; ++j)
    {
      results[i][j] = data[j][i];
    }
  }

  return results;
}

int main(void)
{
  int result_1 = 0;
  int horizontal = 0;
  int vertical = 0;
  int diag1 = 0;
  int diag2 = 0;
  
  try
  {
    const auto lines = read_lines("2024/inputs/day_4.txt");

    for (auto &&line : lines)
    {
      horizontal += find_xmas(line);
    }

    const auto columns = create_columns(lines);
    for (auto &&column : columns)
    {
      vertical += find_xmas(column);
    }

    const auto no_transposed = no_transpose(lines);
    const auto diags1 = create_diagonals(no_transposed);
    for (auto &&diag : diags1)
    {
      diag1 += find_xmas(diag);
    }

    const auto transposed = transpose(lines);
    const auto diags2 = create_diagonals(no_transposed);
    for (auto &&diag : diags2)
    {
      diag2 += find_xmas(diag);
    }

    std::cout << "horizontal: " << horizontal << std::endl;
    std::cout << "vertical: " << vertical << std::endl;
    std::cout << "diag1: " << diag1 << std::endl;
    std::cout << "diag2: " << diag2 << std::endl;
    result_1 = horizontal + vertical + diag1 + diag2;
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
  }

  std::cout << "Result 1: " << result_1 << std::endl;
  
  return 0;
}
