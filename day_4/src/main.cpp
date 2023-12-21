#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <sstream>

std::vector<std::string> read_file(const std::string &filename)
{
  std::vector<std::string> results;
  std::ifstream file(filename);

  std::string line;
  while (std::getline(file, line))
  {
    results.push_back(line);
  }

  return results;
}

int get_card_idx(std::string& line)
{
  const size_t card_prefix{4};
  const std::string idx_delimiter{": "};
  size_t idx_position = line.find(idx_delimiter);
  std::string tmp = line.substr(card_prefix, idx_position - card_prefix);
  line.erase(0, idx_position + idx_delimiter.size());

  return std::stoi(tmp);
}

std::tuple<std::string, std::string> split_data(std::string numbers)
{
  const std::string idx_delimiter{" | "};
  size_t idx_position = numbers.find(idx_delimiter);
  std::string winning_numbers = numbers.substr(0, idx_position);
  numbers.erase(0, idx_position + idx_delimiter.size());

  return {winning_numbers, numbers};
}

std::vector<int> get_numbers(const std::string& numbers)
{
  int num{0};
  std::vector<int> results;
  std::istringstream iss(numbers);
  
  while (iss >> num)
  {
    results.push_back(num);
  }

  return results;
}

int check_card(std::string line)
{
  int match{0};
  int card_idx = get_card_idx(line);
  auto data = split_data(line);

  auto winning_numbers = get_numbers(std::get<0>(data));
  auto numbers = get_numbers(std::get<1>(data));

  for (auto &&number : numbers)
  {
    for (auto &&winning_number : winning_numbers)
    {
      if (number == winning_number)
      {
        match++;
      }
    }
  }

  return (1<<match)/2;
}


int main(void)
{
  int points{0};

  for (auto &&card : read_file("input"))
  {
    points += check_card(card);
  }

  printf("Points: %d\n", points);
  return 0;
}