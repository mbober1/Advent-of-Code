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


int main(void)
{
  long int min_location{INT_MAX};
  auto data = read_file("input");

  size_t line{0};
  auto database = get_seeds(data[line]);
  line+=3; // skip

  auto seed_to_soil             = parse_map(data, line);
  auto soil_to_fertilizer       = parse_map(data, line);
  auto fertilizer_to_water      = parse_map(data, line);
  auto water_to_light           = parse_map(data, line);
  auto light_to_temperature     = parse_map(data, line);
  auto temperature_to_humidity  = parse_map(data, line);
  auto humidity_to_location     = parse_map(data, line);
  
  for (auto &&entity : database)
  {
    entity.soil        = get_from_map(seed_to_soil, entity.seed);
    entity.fertilizer  = get_from_map(soil_to_fertilizer, entity.soil);
    entity.water       = get_from_map(fertilizer_to_water, entity.fertilizer);
    entity.light       = get_from_map(water_to_light, entity.water);
    entity.temperature = get_from_map(light_to_temperature, entity.light);
    entity.humidity    = get_from_map(temperature_to_humidity, entity.temperature);
    entity.location    = get_from_map(humidity_to_location, entity.humidity);
    min_location       = std::min(min_location, entity.location);
    printf("Seed %ld, soil %ld, fertilizer %ld, water %ld, light %ld, temperature %ld, humidity %ld, location %ld.\n", entity.seed, entity.soil, entity.fertilizer, entity.water, entity.light, entity.temperature, entity.humidity, entity.location);
  }
  
  printf("The lowest location number is: %ld\n", min_location);
  return 0;
}