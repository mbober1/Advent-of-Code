#include <iostream>
#include <fstream>
#include <vector>
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

std::vector<std::string> split_to_sets(std::string line)
{
  const std::string delimiter{"; "};
  std::vector<std::string> results;

  size_t position = line.find(delimiter);

  while (std::string::npos != position)
  {
    results.push_back(line.substr(0, position));
    line.erase(0, position + delimiter.size());
    position = line.find(delimiter);
  }

  results.push_back(line);
  return results;
}

bool check_conditions(const int red, const int green, const int blue)
{
  constexpr int max_red{12};
  constexpr int max_green{13};
  constexpr int max_blue{14};

  if (red <= max_red && green <= max_green && blue <= max_blue)
  {
    return true;
  }
  else
  {
    return false;
  }
}

int get_game_score(std::string line)
{
  int result{0};

  { // get game idx
    const size_t game_prefix{4};
    const std::string idx_delimiter{": "};
    size_t idx_position = line.find(idx_delimiter);
    std::string tmp = line.substr(game_prefix, idx_position - game_prefix);
    result = std::stoi(tmp);
    line.erase(0, idx_position + idx_delimiter.size());
  }

  for (auto &&set : split_to_sets(line))
  {
    int red{0}, green{0}, blue{0}, num{0};
    std::string color;
    std::istringstream iss(set);
    
    while (iss >> num >> color)
    {
      if (std::string::npos != color.find("red"))
      {
        red += num;
      }
      else if (std::string::npos != color.find("green"))
      {
        green += num;
      }
      else if (std::string::npos != color.find("blue"))
      {
        blue += num;
      }
      else
      {
        printf("Cannot assign val %d to color %s\n", num, color.c_str());
      }
    }

    if (false == check_conditions(red, green, blue))
    {
      return 0;
    }
  }

  return result;
}

int main(void)
{
  int result{0};

  auto games = read_file("input");

  for(auto game : games)
  {
    result += get_game_score(game);
  }

  printf("Final result is: %d\n", result);

  return 0;
}