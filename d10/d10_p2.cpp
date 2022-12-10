#include <fstream>
#include <iostream>
#include <algorithm>
#include <map>

void getInstruction(const char *filename)
{
  std::ifstream file(filename);
  std::string instruction{};
  int value{};
  std::vector<int> signal{1};
  // std::array<char, 40> pixelRow{'.'};
  while (file >> instruction)
  {
    signal.push_back(signal.back());
    if (instruction=="noop"){
      continue;
    }
    file >> value;
    signal.push_back(signal.back()+value);
  }
  int position{};
  for (int i = 0; i < signal.size()-1; ++i)
  {
    if (std::abs(position - signal[i]) <= 1)
      std::cout << '#';
    else
      std::cout << '.';
    if (++position==40){
      position = 0;
      std::cout << '\n';
    }
  }
}

int main(int argc, char const *argv[])
{
  getInstruction(argv[1]);
  return 0;
}
