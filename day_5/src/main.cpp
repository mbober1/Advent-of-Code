#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>
#include <limits.h>
#include <thread>

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

struct Database
{
  long int seed;
  long int soil;
  long int fertilizer;
  long int water;
  long int light;
  long int temperature;
  long int humidity;
  long int location;
};

struct Map_rule
{
  long int range_begin;
  long int range_end;
  long int shift;
};

std::vector<Database> get_seeds(const std::string& line)
{
  std::vector<Database> results;
  long int seed;
  std::string header;
  std::istringstream iss(line);
  iss >> header;

  while (iss >> seed)
  {
    results.push_back(Database{seed, 0, 0, 0, 0, 0, 0, 0});
  }
  
  return results;
}

std::vector<Map_rule> get_seeds_part2(const std::string& line)
{
  std::vector<Map_rule> results;
  long int seed, range;
  std::string header;
  std::istringstream iss(line);
  iss >> header;

  while (iss >> seed >> range)
  {
    results.push_back(Map_rule{seed, seed + range, 0});
  }
  
  return results;
}

std::vector<Map_rule> parse_map(const std::vector<std::string>& data, size_t& line)
{
  std::vector<Map_rule>result;
  while (false == data[line].empty())
  {
    std::istringstream iss(data[line]);
    long int destination_range{0};
    long int source_range{0};
    long int range_length{0};

    iss >> destination_range >> source_range >> range_length;

    long int range_begin = source_range;
    long int range_end = source_range + range_length;
    long int shift = source_range - destination_range;

    result.push_back(Map_rule{range_begin, range_end, shift});
    
    line++;
  }
  line+=2;

  return result;
}

long int get_from_map(const std::vector<Map_rule>& data, long int key)
{
  for (auto &&rule : data)
  {
    if (key >= rule.range_begin && key <= rule.range_end)
    {
      return key - rule.shift;
    }
  }

  return key;
}

enum Map_name
{
  SEED_TO_SOIL,
  SOIL_TO_FERTILIZER,
  FERTILIZER_TO_WATER,
  WATER_TO_LIGHT,
  LIGHT_TO_TEMPERATURE,
  TEMPERATURE_TO_HUMIDITY,
  HUMIDITY_TO_LOCATION,

  MAX_NAME,
};

void compute(const Map_rule& entity, const std::vector<Map_rule> almanac[], long int* min_location)
{
  for (long int seed = entity.range_begin; seed < entity.range_end; seed++)
  {
    long int soil        = get_from_map(almanac[SEED_TO_SOIL], seed);
    long int fertilizer  = get_from_map(almanac[SOIL_TO_FERTILIZER], soil);
    long int water       = get_from_map(almanac[FERTILIZER_TO_WATER], fertilizer);
    long int light       = get_from_map(almanac[WATER_TO_LIGHT], water);
    long int temperature = get_from_map(almanac[LIGHT_TO_TEMPERATURE], light);
    long int humidity    = get_from_map(almanac[TEMPERATURE_TO_HUMIDITY], temperature);
    long int location    = get_from_map(almanac[HUMIDITY_TO_LOCATION], humidity);
    *min_location         = std::min(*min_location, location);
  }
}


int main(void)
{
  long int min_location = {INT_MAX};
  auto data = read_file("input");

  size_t line{0};
  // auto database = get_seeds(data[line]);
  auto database = get_seeds_part2(data[line]);
  line+=3; // skip

  std::vector<Map_rule> almanac[MAX_NAME];
  std::vector<std::thread> threads;
  std::vector<long int*> min_locations;

  for (auto &&map : almanac)
  {
    map = parse_map(data, line);
  }

  for (size_t i = 0; i < database.size(); i++)
  {
    long int* val = new long int{INT_MAX};
    min_locations.push_back(val);
    threads.emplace_back([&](){compute(database.at(i), almanac, val);});
  }
  
  for (auto &&thread : threads)
  {
    thread.join();
  }

  for (auto &&location : min_locations)
  {
    min_location = std::min(*location, min_location);
  }
  
  printf("The lowest location number is: %ld\n", min_location);
  return 0;
}