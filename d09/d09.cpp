#include <fstream>
#include <iostream>
#include <algorithm>
#include <map>

using Coordinates = std::pair<int, int>;

int distance(const Coordinates a, const Coordinates b){
  return std::max(std::abs(a.first - b.first), std::abs(a.second - b.second));
}

int getInstruction(const char *filename)
{
  std::ifstream file(filename);
  char direction{};
  int move{};
  Coordinates lastHeadPosition{0, 0};
  Coordinates lastTailPosition{0, 0};
  std::map<Coordinates, bool> head;
  std::map<Coordinates, bool> tail;
  head.insert({lastHeadPosition, true});
  tail.insert({lastTailPosition, true});
  while (file >> direction >> move)
  {
    for (int i = 1; i <= move; ++i)
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
      if(distance(lastTailPosition, lastHeadPosition)>1){
        lastTailPosition.first += (lastHeadPosition.first - lastTailPosition.first)!=0?(lastHeadPosition.first - lastTailPosition.first)/std::abs((lastHeadPosition.first - lastTailPosition.first)):0;
        lastTailPosition.second += (lastHeadPosition.second - lastTailPosition.second)!=0?(lastHeadPosition.second - lastTailPosition.second)/std::abs((lastHeadPosition.second - lastTailPosition.second)):0;
      }
      head.insert({lastHeadPosition, true});
      tail.insert({lastTailPosition, true});
    }
  }
  return tail.size();
}

int main(int argc, char const *argv[])
{
  std::cout<<getInstruction(argv[1])<<'\n';
  return 0;
}
