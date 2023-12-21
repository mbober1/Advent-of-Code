#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <sstream>
#include <list>

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

int get_card_idx(std::string& line)
{
  const size_t card_prefix{4};
  const std::string idx_delimiter{": "};
  size_t idx_position = line.find(idx_delimiter);
  std::string tmp = line.substr(card_prefix, idx_position - card_prefix);
  line.erase(0, idx_position + idx_delimiter.size());

  return std::stoi(tmp);
}

std::tuple<std::string, std::string> split_data(std::string numbers)
{
  const std::string idx_delimiter{" | "};
  size_t idx_position = numbers.find(idx_delimiter);
  std::string winning_numbers = numbers.substr(0, idx_position);
  numbers.erase(0, idx_position + idx_delimiter.size());

  return {winning_numbers, numbers};
}

std::vector<int> get_numbers(const std::string& numbers)
{
  int num{0};
  std::vector<int> results;
  std::istringstream iss(numbers);
  
  while (iss >> num)
  {
    results.push_back(num);
  }

  return results;
}

class Scratchcard
{
  int _id;
  int _points;
  int _matchs;

public:
  Scratchcard(std::string line) : _id{0}, _points{0}, _matchs{0}
  {
    _id = get_card_idx(line);
    auto data = split_data(line);

    auto winning_numbers = get_numbers(std::get<0>(data));
    auto numbers = get_numbers(std::get<1>(data));

    for (auto &&number : numbers)
    {
      for (auto &&winning_number : winning_numbers)
      {
        if (number == winning_number)
        {
          _matchs++;
        }
      }
    }

    _points =  (1<<_matchs)/2;
  }

  int points() const { return _points; }
  int matchs() const { return _matchs; }
  int id() const { return _id; }
};

int main(void)
{
  int points{0}, processed_cards{0};
  std::vector<Scratchcard> cards;
  std::list<Scratchcard> process_queue;

  for (auto &&line : read_file("input"))
  {
    cards.push_back(Scratchcard{line});
  }

  for (auto &&card : cards)
  {
    points += card.points();
    process_queue.push_back(card);
  }

  while (false == process_queue.empty())
  {
    auto card = process_queue.front();
    process_queue.pop_front();

    for (int new_card = card.matchs(); new_card > 0; new_card--)
    {
      int card_id = card.id() + new_card;
      process_queue.push_front(cards.at(card_id -1));
    }
    processed_cards++;
  }
  
  printf("Points: %d, Processed cards: %d\n", points, processed_cards);
  return 0;
}