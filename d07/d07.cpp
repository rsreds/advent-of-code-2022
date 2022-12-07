#include <fstream>
#include <iostream>
#include <algorithm>
#include <map>

auto getFilesMap(const char *filename)
{
  std::ifstream file(filename);
  std::string line{};
  std::map<std::string, int> files{};
  std::string basepath{"/"};
  while (std::getline(file, line))
  {
    auto firstPart = line.substr(0, line.find_last_of(' '));
    auto secondPart = line.substr(line.find_last_of(' ') + 1,
                                  line.length() - line.find_last_of(' ') + 1);
    if ((firstPart == "$" && secondPart == "ls") || firstPart == "dir")
      continue;
    if (firstPart == "$ cd")
    {
      if (secondPart == "..")
      {
        basepath.pop_back();
        basepath = basepath.substr(0, basepath.find_last_of("/")+1);
      }
      else if (secondPart == "/")
      {
        basepath = "/";
      }
      else
      {
        basepath += secondPart + "/";
      }
    }
    else
      files.emplace(basepath + secondPart, std::stoi(firstPart));
  }
  return files;
}

auto getFolderSizes(std::map<std::string, int> files){
  std::map<std::string, int> folderSizes;
  for (auto el : files)
  {
    auto path = el.first;
    while (path != "")
    {
      path = path.substr(0, path.find_last_of('/'));
      auto insertion = folderSizes.insert({path, el.second});
      if (!insertion.second)
        folderSizes[path] += el.second;
    }
  }
  return folderSizes;
}

int getTotalSize(std::map<std::string, int> folderSizes){
  int sum{};
  for (auto el : folderSizes)
  {
    if (el.second > 100000)
      continue;
    sum += el.second;
  }
  return sum;
}

int main(int argc, char const *argv[])
{
  auto files{getFilesMap(argv[1])};
  auto folderSizes{getFolderSizes(files)};
  std::cout << getTotalSize(folderSizes) << '\n';
  return 0;
}
