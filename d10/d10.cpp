#include <fstream>
#include <iostream>
#include <algorithm>
#include <map>

int getInstruction(const char *filename)
{
  std::ifstream file(filename);
  std::string instruction{};
  int value{};
  std::vector<int> signal{1};
  while (file >> instruction)
  {

    signal.push_back(signal.back());
    if (instruction=="noop"){
      continue;
    }
    file >> value;
    signal.push_back(signal.back()+value);
  }
  int sum{};
  for (int i = 19; i <= 220; i+=40)
  {
    sum += (i+1) * signal[i];
    std::cout << signal[i] << '\n';
  }
  return sum;
}

int main(int argc, char const *argv[])
{
  std::cout<<getInstruction(argv[1])<<'\n';
  return 0;
}
