#include <fstream>
#include <iostream>
#include <algorithm>
#include <set>

int getPacketStart(const char *filename, int messageLength)
{
  std::ifstream file(filename);
  std::string buffer;
  std::getline(file, buffer);
  for (auto it = buffer.begin() + messageLength; it != buffer.end(); ++it){
    std::set<char> uniques;
    uniques.insert(it - messageLength, it);
    if (uniques.size()<messageLength)
      continue;
    return std::distance(buffer.begin(), it);
  }
  return std::distance(buffer.begin(), buffer.end());
}

int main(int argc, char const *argv[])
{
  std::cout << getPacketStart(argv[1], std::stoi(argv[2])) << '\n';
  return 0;
}
