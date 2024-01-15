#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>
#include <cassert>

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

class Signpost
{
public:
  std::string _left, _right;

  Signpost(const std::string& left, const std::string& right)
  : _left(left), _right(right)
  {}

};

std::map<std::string, Signpost> parse(const std::vector<std::string>& data)
{
  std::map<std::string, Signpost>result;

  size_t line{2};

  while (false == data[line].empty())
  {
    std::istringstream iss(data[line]);
    std::string name, tmp, left, right;

    iss >> name >> tmp >> left >> right;

    left.erase(0, 1);
    left.pop_back();
    right.pop_back();

    if (result.end() == result.find(name))
    {
      result.insert({name, Signpost{left, right}});
    }
    else
    {
      assert(false);
    }
    
    line++;
  }

  return result;
}

enum class Dir
{
  LEFT,
  RIGHT,
};

Dir get_dir(const std::string& directions)
{
  static size_t last_move{0};
  Dir result = Dir::LEFT;

  switch (directions.at(last_move))
  {
  case 'L':
    result = Dir::LEFT;
    break;

  case 'R':
    result = Dir::RIGHT;
    break;
  
  default:
    assert(false);
    break;
  }

  if (directions.size() == last_move + 1)
  {
    last_move = 0;
  }
  else
  {
    last_move++;
  }

  return result;
}

class Simulation
{
public:
  std::string _node;
  Signpost _singpost;

  Simulation(const std::string& starting_node, const Signpost& signpost) 
  : _node(starting_node), _singpost(signpost) {}

  char get_last_char() const { return _node[2]; }
};

int main(void)
{
  int step{0};
  auto data = read_file("input");
  auto directions = data[0];
  auto signposts = parse(data);

  std::vector<Simulation> simulations;

  for (auto &&signpost : signposts)
  {
    auto name = signpost.first;

    if (name[2] == 'A')
    {
      simulations.push_back(Simulation{name, signposts.at(name)});
      
    }
    
  }

  bool end{false};

  while (end == false)
  {
    end = true;

    for (auto &&sim : simulations)
    {
      if (sim.get_last_char() != 'Z')
      {
        end = false;
      }
    }
    
    for (auto &&sim : simulations)
    {
      sim._singpost = signposts.at(sim._node);
    }
    
    switch (get_dir(directions))
    {
    case Dir::LEFT:
      for (auto &&sim : simulations)
      {
        sim._node = sim._singpost._left;
      }
      break;

    case Dir::RIGHT:
      for (auto &&sim : simulations)
      {
        sim._node = sim._singpost._right;
      }
      break;
    
    default:
      assert(false);
      break;
    }
    
    step++;
  }

  printf("Steps: %d\n", step-1);
  
  return 0;
}