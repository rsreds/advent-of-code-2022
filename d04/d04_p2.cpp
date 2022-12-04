#include <fstream>
#include <iostream>
#include <algorithm>
#include <numeric>

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

    auto firstSectionLenght = static_cast<size_t>(firstSectionEnd - firstSectionStart);
    auto secondSectionLenght = static_cast<size_t>(secondSectionEnd - secondSectionStart);

    std::vector<int> firstSection(firstSectionLenght+1);
    std::vector<int> secondSection(secondSectionLenght+1);

    std::iota(firstSection.begin(), firstSection.end(), firstSectionStart);
    std::iota(secondSection.begin(), secondSection.end(), secondSectionStart);

    std::vector<int> intersection{};
    std::set_intersection(firstSection.begin(), firstSection.end(), secondSection.begin(), secondSection.end(), std::back_inserter(intersection));
    if (intersection.size() > 0)
      ++sum;
  }
  return sum;
}

int main(int argc, char const *argv[])
{
  std::cout << getOverlappingPairs(argv[1]) << '\n';
  return 0;
}
