#include <input.hpp>
#include <iostream>

#include <sstream>
class Report
{
private:
  std::vector<int> levels;
  const int max_diff = 3;
  const int min_diff = 1;

public:
  Report(const std::string &data)
  {
    std::string level;
    std::stringstream s(data);
    while (s >> level)
    {
      levels.push_back(std::stoi(level));
    }
  }

  int levels_count()
  {
    return levels.size();
  }

  std::vector<int>& get_levels()
  {
    return levels;
  }

  bool check_safety()
  {
    if (levels.size() > 1)
    {
      if (levels.front() < levels.back()) // increasing
      {
        for (size_t i = 0; i < levels.size() - 1; i++)
        {
          int diff = levels.at(i+1) - levels.at(i);
          if (diff < min_diff || diff > max_diff)
          {
            return false;
          }
        }
        return true;
      }
      else if(levels.front() > levels.back()) // decreasing
      {
        for (size_t i = 0; i < levels.size() - 1; i++)
        {
          int diff = levels.at(i) - levels.at(i+1);
          if (diff < min_diff || diff > max_diff)
          {
            return false;
          }
        }
        return true;
      }
    }
    return false; // stay the same
  }
};

int main(void)
{
  int safe_reports = 0;

  try
  {
    const auto reports_data = read_lines("2024/inputs/day_2.txt");
    std::vector<Report> reports;

    for (const auto &report : reports_data)
    {
      reports.push_back(report);
    }

    for (auto &&report : reports)
    {
      bool safety = report.check_safety();

      if (false == safety)
      {
        for (size_t i = 0; i < report.levels_count(); i++)
        {
          auto new_report = report;
          new_report.get_levels().erase(new_report.get_levels().begin() + i);
          bool new_safelty = new_report.check_safety();
          if (true == new_safelty)
          {
            safety = true;
            break;
          }
        }
      }

      if (true == safety)
      {
        safe_reports++;
      }
    }
    
    std::cout << "Safe reports: " << safe_reports << std::endl;

  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
  }
  
  return 0;
}
