#include <iostream>
#include <fstream>
#include <vector>

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

bool is_num(const char val)
{
  return (val >= '0' && val <= '9');
}

bool is_symbols(const char val)
{
  return (val != '.');
}

bool is_gear(const char val)
{
  return (val == '*');
}

struct Number
{
  int val;
  size_t len;
  size_t begin_idx;
  size_t end_idx;
  size_t line_idx;
};

struct Gear
{
  Number number;
  size_t line;
  size_t idx;
};

std::vector<Number> get_numbers(const std::vector<std::string>& data)
{
  std::vector<Number> results;

  for (size_t line = 0; line < data.size(); line++)
  {
    for (size_t cursor = 0; cursor < data[line].size(); ++cursor)
    {
      char num_char = data[line][cursor];

      if (true == is_num(num_char))
      {
        size_t num_idx_begin{cursor};

        while (true == is_num(num_char))
        {
          cursor++;
          num_char = data[line][cursor];
        }

        size_t num_idx_end{cursor};
        size_t num_len = num_idx_end - num_idx_begin;
        std::string num_str = data[line].substr(num_idx_begin, num_len);
        int num = std::stoi(num_str);
        results.push_back(Number{num, num_len, num_idx_begin, num_idx_end, line});
      }
    }
  }

  return results;
}

bool check_number(const Number& number, const std::vector<std::string>& data, std::vector<Gear>& gears)
{
  size_t this_line = number.line_idx;
  size_t next_line = this_line +1;
  size_t prev_line = this_line -1;

  size_t this_char = number.begin_idx;
  size_t next_char = number.end_idx   ;
  size_t prev_char = number.begin_idx -1;

  bool left_condition   = (this_char > 0);
  bool right_condition  = (next_char < data[this_line].size());
  bool top_condition    = (this_line > 0);
  bool bottom_condition = (next_line < data.size());

  // LEFT
  if (left_condition)
  {
    char val = data[this_line][prev_char];
    if (is_gear(val)) gears.push_back(Gear{number, this_line, prev_char});
    if (is_symbols(val)) return true;
  }

  // RIGHT
  if (right_condition)
  {
    char val = data[this_line][next_char];
    if (is_gear(val)) gears.push_back(Gear{number, this_line, next_char});
    if (is_symbols(val)) return true;
  }

  // DIAGONALLY TOP LEFT
  if (left_condition && top_condition)
  {
    char val = data[prev_line][prev_char];
    if (is_gear(val)) gears.push_back(Gear{number, prev_line, prev_char});
    if (is_symbols(val)) return true;
  }

  // DIAGONALLY TOP RIGHT
  if (right_condition && top_condition)
  {
    char val = data[prev_line][next_char];
    if (is_gear(val)) gears.push_back(Gear{number, prev_line, next_char});
    if (is_symbols(val)) return true;
  }

  // DIAGONALLY BOTTOM LEFT
  if (left_condition && bottom_condition)
  {
    char val = data[next_line][prev_char];
    if (is_gear(val)) gears.push_back(Gear{number, next_line, prev_char});
    if (is_symbols(val)) return true;
  }

  // DIAGONALLY BOTTOM RIGHT
  if (right_condition && bottom_condition)
  {
    char val = data[next_line][next_char];
    if (is_gear(val)) gears.push_back(Gear{number, next_line, next_char});
    if (is_symbols(val)) return true;
  }


  for (size_t idx = number.begin_idx; idx < number.end_idx; idx++)
  {
    // UP
    if (top_condition)
    {
      char val = data[prev_line][idx];
      if (is_gear(val)) gears.push_back(Gear{number, prev_line, idx});
      if (is_symbols(val)) return true;
    }

    // DOWN
    if (bottom_condition)
    {
      char val = data[next_line][idx];
      if (is_gear(val)) gears.push_back(Gear{number, next_line, idx});
      if (is_symbols(val)) return true;
    }
  }
  
  return false;
}

int main(void)
{
  int results{0}, gear_ratios{0};
  std::vector<Gear> gears;

  auto data = read_file("input");

  auto numbers = get_numbers(data);

  for (auto &&number : numbers)
  {
    if (check_number(number, data, gears))
    {
      results += number.val;
    }
  }

  for (auto &&gear1 : gears)
  {
    for (auto &&gear2 : gears)
    {
      if ((&gear1.number) != (&gear2.number) && gear1.idx == gear2.idx && gear1.line == gear2.line)
      {
        gear_ratios += gear1.number.val * gear2.number.val;
      }
    }
  }

  printf("Parts sum %d, Gear ratios: %d\n", results, gear_ratios/2);
  return 0;
}