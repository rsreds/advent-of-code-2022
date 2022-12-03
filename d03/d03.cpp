#include <fstream>
#include <iostream>
#include <algorithm>

int convertChar(char inputChar){
  if (inputChar == std::toupper(inputChar))
  {
    return inputChar - 38;
  }
  return inputChar - 96;
}

int sumPriorities(const char *filename)
{
  std::ifstream file(filename);
  std::string line{};
  int sum{};
  while (std::getline(file, line))
  {
    auto lineLength = line.length();
    std::vector<char> charIntersection;
    std::sort(line.begin(), line.begin() + lineLength / 2);
    std::sort(line.begin() + lineLength / 2, line.end());
    std::set_intersection(line.begin(), line.begin() + lineLength/2,
                          line.begin() + lineLength/2, line.end(),
                          std::back_inserter(charIntersection));
    sum += convertChar(charIntersection[0]);
  }
  return sum;
}

int main(int argc, char const *argv[])
{
  std::cout << sumPriorities(argv[1]) << '\n';
  return 0;
}
