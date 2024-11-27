#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <tuple>

class Colors
{
  int _red;
  int _green;
  int _blue;

  public:
  Colors(int red, int green, int blue) : _red(red), _green(green), _blue(blue) {}

  bool operator>(const Colors data)
  {
    if (_red > data.get_red() || _green > data.get_green() || _blue > data.get_blue())
    {
      return true;
    }
    else
    {
      return false;
    }
  }

  Colors max(const Colors data)
  {
    Colors result{0, 0, 0};
    result._red = std::max(_red, data.get_red());
    result._green = std::max(_green, data.get_green());
    result._blue = std::max(_blue, data.get_blue());
    return result;
  }

  int power()
  {
    return _red * _green * _blue;
  }

  void add_red(int val)   { _red    += val; }
  void add_green(int val) { _green  += val; }
  void add_blue(int val)  { _blue   += val; }
  int get_red() const     { return _red;    }
  int get_green() const   { return _green;  }
  int get_blue() const    { return _blue;   }
};

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


std::tuple<int, int> get_game_score(std::string line)
{
  int result{0};
  Colors bag_max{12, 13, 14};
  Colors game_max{0, 0, 0};

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
    int num{0};
    Colors tmp{0, 0, 0};
    std::string color;
    std::istringstream iss(set);
    
    while (iss >> num >> color)
    {
      if (std::string::npos != color.find("red"))
      {
        tmp.add_red(num);
      }
      else if (std::string::npos != color.find("green"))
      {
        tmp.add_green(num);
      }
      else if (std::string::npos != color.find("blue"))
      {
        tmp.add_blue(num);
      }
      else
      {
        printf("Cannot assign val %d to color %s\n", num, color.c_str());
      }
    }

    game_max = game_max.max(tmp);

    if (tmp > bag_max)
    {
      result = 0;
    }
  }

  return {result, game_max.power()};
}

int main(void)
{
  int result{0}, game_power{0};

  auto games = read_file("input");

  for(auto game : games)
  {
    auto score = get_game_score(game);
    result += std::get<0>(score);
    game_power += std::get<1>(score);
  }

  printf("Final result is: %d, Game power: %d\n", result, game_power);

  return 0;
}