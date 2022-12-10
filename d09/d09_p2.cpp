#include <fstream>
#include <iostream>
#include <algorithm>
#include <set>

using Coordinates = std::pair<int, int>;

int distance(const Coordinates a, const Coordinates b)
{
  return std::max(std::abs(a.first - b.first), std::abs(a.second - b.second));
}

int getInstruction(const char *filename)
{
  std::ifstream file(filename);
  char direction{};
  int move{};
  std::array<std::vector<Coordinates>, 10> rope;
  Coordinates lastHeadPosition{0, 0};
  for (int i = 0; i < 10; ++i)
  {
    rope[i].push_back({0,0});
  }
  while (file >> direction >> move)
  {
    for (int step = 1; step <= move; ++step)
    {
      switch (direction)
      {
      case 'U':
        --lastHeadPosition.second;
        break;
      case 'L':
        --lastHeadPosition.first;
        break;
      case 'R':
        ++lastHeadPosition.first;
        break;
      case 'D':
      default:
        ++lastHeadPosition.second;
        break;
      }
      rope[0].push_back(lastHeadPosition);
      for (int i = 1; i < 10; ++i)
      {
        Coordinates lastPosition = rope[i - 1].back();
        Coordinates newPosition = rope[i].back();
        if (distance(newPosition, lastPosition) > 1)
        {
          newPosition.first += (lastPosition.first - newPosition.first) != 0 ? (lastPosition.first - newPosition.first) / std::abs((lastPosition.first - newPosition.first)) : 0;
          newPosition.second += (lastPosition.second - newPosition.second) != 0 ? (lastPosition.second - newPosition.second) / std::abs((lastPosition.second - newPosition.second)) : 0;
        }
        rope[i].push_back(newPosition);
      }
    }
  }
  std::set<Coordinates> s(rope[9].begin(), rope[9].end());
  return s.size();
}

int main(int argc, char const *argv[])
{
  std::cout << getInstruction(argv[1]) << '\n';
  return 0;
}
