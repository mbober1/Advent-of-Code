#include <input.hpp>
#include <iostream>
#include <memory>

constexpr char UP         = '^';
constexpr char DOWN       = 'v';
constexpr char LEFT       = '<';
constexpr char RIGHT      = '>';
constexpr char OBSTACLE   = '#';
constexpr char CLEAR      = '.';
constexpr char VISITED    = 'X';

class Position
{
  size_t _x;
  size_t _y;
public:
  explicit Position(const size_t x, const size_t y) : _x(x), _y(y) {}

  size_t get_x() const
  {
    return _x;
  }
  size_t get_y() const
  {
    return _y;
  }
};


class Player
{
  Position _position;
  char direction = UP;

public:
  explicit Player() : _position(0,0) {}
  explicit Player(Position pos) : _position(pos) {}

  void set_position(Position pos)
  {
    _position = pos;
  }

  void turn_right()
  {
    switch (direction)
    {
    case UP:
      direction = RIGHT;
      break;

    case RIGHT:
      direction = DOWN;
      break;

    case DOWN:
      direction = LEFT;
      break;

    case LEFT:
      direction = UP;
      break;
    
    default:
      break;
    }
  }

  Position get_new_position()
  {
    switch (direction)
    {
    case UP:
      return Position(_position.get_x(), _position.get_y() - 1);
      break;
    
    case DOWN:
      return Position(_position.get_x(), _position.get_y() + 1);
      break;
    
    case LEFT:
      return Position(_position.get_x() - 1, _position.get_y());
      break;
    
    case RIGHT:
      return Position(_position.get_x() + 1, _position.get_y());
      break;
    
    default:
      return _position;
      break;
    }
  }

};

class Map
{
public:
  int obstructions = 0;
  int traveled = 0;
  size_t width;
  size_t height;

  std::vector<std::vector<char>> map;
  Player player;

  explicit Map(const std::vector<std::string>& data)
  : width(data.at(0).size()), height(data.size())
  {
    map.resize(height);

    for (size_t y = 0; y < height; y++)
    {
      map.at(y).resize(width);

      for (size_t x = 0; x < width; x++)
      {
        char dot = data.at(y).at(x);
        switch (dot)
        {
        case OBSTACLE:
        {
          obstructions++;
          map.at(y).at(x) = dot;
          break;
        }

        case CLEAR:
        {
          map.at(y).at(x) = dot;
          break;
        }

        case UP:
        {
          auto pos = Position(x,y);
          player.set_position(pos);
          mark_visited(pos);
          break;
        }
        
        default:
          break;
        }
      }
    }
  }

  bool check_end(const Position& pos)
  {
    size_t x = pos.get_x();
    size_t y = pos.get_y();

    if  (x >= width || y >= height)
    {
      return true;
    }
    else
    {
      return false;
    }
  }

  bool check_clear(const Position& pos)
  {
    size_t x = pos.get_x();
    size_t y = pos.get_y();
    if (OBSTACLE == map.at(y).at(x))
    {
      return false;
    }
    else
    {
      return true;
    }
  }

  void mark_visited(const Position& pos)
  {
    size_t x = pos.get_x();
    size_t y = pos.get_y();

    if (map.at(y).at(x) == CLEAR)
    {
      map.at(y).at(x) = VISITED;
      traveled++;
    }
  }

  bool play()
  {
    auto pos = player.get_new_position();

    if (true == check_end(pos))
    {
      return true;
    }
    else if (true == check_clear(pos))
    {
      mark_visited(pos);
      player.set_position(pos);
    }
    else
    {
      player.turn_right();
    }

    return false;
  }

  bool add_obstacle(const Position& pos)
  {
    if (true == check_clear(pos))
    {
      size_t x = pos.get_x();
      size_t y = pos.get_y();
      map.at(y).at(x) = OBSTACLE;
      return true;
    }
    else
    {
      return false;
    }
  }

  bool check_stuck()
  {
    int attempt = 0;
    int old_traveled = this->traveled;
    while (false == this->play()) 
    {
      if (this->traveled > old_traveled)
      {
        attempt = 0;
        old_traveled = this->traveled;
      }
      else
      {
        attempt++;
      }

      if (attempt > 5000)
      {
        return true;
      }
    }

    return false;
  }
};

int count_visied_positions(Map map)
{
  while (false == map.play()) {}
  return map.traveled + 1;
}

int count_obstacle_position(Map map)
{
  int result;

  for (size_t y = 0; y < map.height; y++)
  {
    for (size_t x = 0; x < map.width; x++)
    {
      Map new_map = map;
      auto pos = Position(x, y);
      if (true == new_map.add_obstacle(pos))
      {
        if (true == new_map.check_stuck())
        {
          result++;
        }
      }
    }
  }
  result--; // remove placed at the guard's starting position
  return result;
}

int main(void)
{
  int result_1 = 0;
  int result_2 = 0;

  try
  {
    const auto data = read_lines("2024/inputs/day_6.txt");
    Map map(data);

    result_1 = count_visied_positions(map);
    result_2 = count_obstacle_position(map);
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
  }

  std::cout << "Result 1: " << result_1 << std::endl;
  std::cout << "Result 2: " << result_2 << std::endl;
  return 0;
}
