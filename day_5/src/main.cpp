#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>
#include <limits.h>

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

enum Entitie
{
  SEED,
  SOIL,
  FERTILIZER,
  WATER,
  LIGHT,
  TEMPERATURE,
  HUMIDITY,
  LOCATION,

  MAX_ENTITIE
};

struct Database
{
  size_t data[MAX_ENTITIE];
};

std::vector<Database> get_seeds(const std::string& line)
{
  std::vector<Database> results;
  size_t seed;
  std::string header;
  std::istringstream iss(line);
  iss >> header;

  while (iss >> seed)
  {
    results.push_back(Database{seed, 0, 0, 0, 0, 0, 0, 0});
  }
  
  return results;
}

std::map<size_t, size_t> parse_map(const std::vector<std::string>& data, size_t& line)
{
  std::map<size_t, size_t>result;
  while (false == data[line].empty())
  {
    std::istringstream iss(data[line]);
    size_t destination_range{0};
    size_t source_range{0};
    size_t range_length{0};

    iss >> destination_range >> source_range >> range_length;

    for (size_t i = 0; i < range_length; i++)
    {
      result.insert({source_range + i, destination_range + i});
    }
    
    line++;
  }
  line+=2;

  return result;
}

size_t get_from_map(std::map<size_t, size_t> data, size_t key)
{
  if (data.end() == data.find(key))
  {
    return key;
  }
  else
  {
    return data.at(key);
  }
}



int main(void)
{
  size_t min_location{INT_MAX};
  auto data = read_file("input");

  size_t line{0};
  auto database = get_seeds(data[line]);
  line+=3; // skip

  for (size_t i = 0; i < 1; i++)
  {
    auto tmp_map = parse_map(data, line);
    printf("Map %ld parsed\n", i+1);

    for (auto &&entity : database)
    {
      entity.data[i+1] = get_from_map(tmp_map, entity.data[i]);
    }
  }

  for (auto &&entity : database)
  {
    min_location       = std::min(min_location, entity.data[8]);
    printf("Seed %ld, soil %ld, fertilizer %ld, water %ld, light %ld, temperature %ld, humidity %ld, location %ld.\n", entity.data[SEED], entity.data[SOIL], entity.data[FERTILIZER], entity.data[WATER], entity.data[LIGHT], entity.data[TEMPERATURE], entity.data[HUMIDITY], entity.data[LOCATION]);
  }

  printf("The lowest location number is: %ld\n", min_location);
  return 0;
}