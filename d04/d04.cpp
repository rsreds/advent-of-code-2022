#include <fstream>
#include <iostream>
#include <algorithm>

int getOverlappingPairs(const char *filename)
{
  std::ifstream file(filename);
  std::string line{};
  int sum{};
  while (std::getline(file, line))
  {
    auto firstSeparatorPos = line.find('-');
    auto secondSeparatorPos = line.find(',');
    auto thirdSeparatorPos = line.find_last_of('-');
    
    auto firstSectionStart = std::stoi(line.substr(0, firstSeparatorPos));
    auto firstSectionEnd = std::stoi(line.substr(firstSeparatorPos +1 , secondSeparatorPos - firstSeparatorPos -1));
    auto secondSectionStart = std::stoi(line.substr(secondSeparatorPos +1, thirdSeparatorPos -secondSeparatorPos -1));
    auto secondSectionEnd= std::stoi(line.substr(thirdSeparatorPos +1, line.length() - thirdSeparatorPos -1));

    auto firstSectionLenght = firstSectionEnd - firstSectionStart;
    auto secondSectionLenght = secondSectionEnd - secondSectionStart;

    if (firstSectionLenght > secondSectionLenght){
      std::swap(firstSectionEnd, secondSectionEnd);
      std::swap(firstSectionStart, secondSectionStart);
      std::swap(firstSectionLenght, secondSectionLenght);
    }
    if (secondSectionStart <= firstSectionStart && secondSectionEnd >= firstSectionEnd)
      ++sum;
  }
  return sum;
}

int main(int argc, char const *argv[])
{
  std::cout << getOverlappingPairs(argv[1]) << '\n';
  return 0;
}
