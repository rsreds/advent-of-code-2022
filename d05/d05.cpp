#include <fstream>
#include <iostream>
#include <algorithm>

std::vector<char> getTopCrates(const char *filename)
{
  std::ifstream file(filename);
  std::string line{};
  std::vector<std::vector<char>> stacks;
  int numStacks;
  while (std::getline(file, line))
  {
    numStacks = (line.length() + 1) / 4;
    if (line.empty())
      break;
    if (line[1] == '1')
      continue;
    stacks.resize(numStacks);
    int column{0};
    for (int i = 1; i < line.length(); i += 4)
    {
      if (line[i] == ' ')
      {
        column++;
        continue;
      }
      stacks[column].insert(stacks[column++].begin(), line[i]);
    }
  }
  while (std::getline(file, line))
  {
    int howMany{};
    int fromStack{};
    int toStack{};

    std::sscanf(line.c_str(), "move %i from %i to %i", &howMany, &fromStack, &toStack);
    for (int i = 0; i < howMany; ++i)
    {
      stacks[toStack - 1].push_back(stacks[fromStack - 1].back());
      stacks[fromStack - 1].pop_back();
    }
  }

  std::vector<char> topCrates;
  for (auto &s : stacks)
  {
    topCrates.push_back(s.back());
    for (auto &c : s)
      std::cout << c;
    std::cout << '\n';
  }
  std::cout << '\n';
  return topCrates;
}

int main(int argc, char const *argv[])
{
  for (auto c : getTopCrates(argv[1]))
    std::cout << c;
  std::cout << '\n';
  return 0;
}
