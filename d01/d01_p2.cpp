#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

int get_most_calories(const char *filename)
{
  std::ifstream file(filename);
  std::string line{};
  std::vector<int> calories{};
  int sum{0};
  while (std::getline(file, line))
  {
    if (line.empty())
    {
      calories.push_back(sum);
      sum = 0;
    }
    else
      sum += std::stoi(line);
  }
  calories.push_back(sum);
  int total{};
  for (int i = 0; i < 3;++i){
    auto max = std::max_element(calories.begin(), calories.end());
    total += *max;
    calories.erase(max);
  }

  return total;
}

int main(int argc, const char *argv[])
{
  if (argc < 2)
  {
    std::cout << "Usage: d01_p2 [FILE]\n";
    return 0;
  }
  int max = get_most_calories(argv[1]);
  std::cout << max;
  return 0;
}
