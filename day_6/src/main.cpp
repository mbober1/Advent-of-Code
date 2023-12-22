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

std::vector<int> parse(const std::string& line)
{
  std::vector<int>result;
  std::istringstream iss(line);
  std::string header;
  int val;

  iss >> header;

  while (iss >> val)
  {
    result.push_back(val);
  }

  return result;
}

int main(void)
{
  constexpr int acceleration{1};

  auto data = read_file("input");
  auto times = parse(data[0]);
  auto records = parse(data[1]);

  for (size_t race = 0; race < times.size(); race++)
  {
    int ways{0};

    for (int hold_time = 0; hold_time < times[race]; hold_time++)
    {
      int speed = acceleration * hold_time;
      int time_to_run = times[race] - hold_time;
      int distance = time_to_run * speed;

      if (distance > records[race])
      {
        ways++;
      }
      
    }
    
    printf("Number of ways you can beat the record %d in race %ld\n", ways, race+1);
  }
  
  return 0;
}