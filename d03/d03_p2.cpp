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
  std::string line1;
  std::string line2;
  std::string line3;
  while (file>>line1>>line2>>line3)
  {
    std::vector<char> firstIntersection;
    std::vector<char> secondIntersection;
    std::sort(line1.begin(), line1.end());
    std::sort(line2.begin(), line2.end());
    std::sort(line3.begin(), line3.end());
    std::set_intersection(line1.begin(), line1.end(),
                          line2.begin(), line2.end(),
                          std::back_inserter(firstIntersection));
    std::set_intersection(firstIntersection.begin(), firstIntersection.end(),
                          line3.begin(), line3.end(),
                          std::back_inserter(secondIntersection));
    sum += convertChar(secondIntersection[0]);
  }
  return sum;
}

int main(int argc, char const *argv[])
{
  std::cout << sumPriorities(argv[1]) << '\n';
  return 0;
}
