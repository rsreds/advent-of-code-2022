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
    int firstSectionStart{};
    int firstSectionEnd{};
    int secondSectionStart{};
    int secondSectionEnd{};

    std::sscanf(line.c_str(), "%i-%i,%i-%i", &firstSectionStart, &firstSectionEnd, &secondSectionStart, &secondSectionEnd);

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
