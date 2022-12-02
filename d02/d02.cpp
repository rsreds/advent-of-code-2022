#include <iostream>
#include <fstream>

int get_score(const char *filename)
{
  std::ifstream file(filename);
  int score{0};
  char first;
  char second;
  while (file>>first>>second)
  {
    switch (second)
    {
    case 'X':
      switch (first)
      {
      case 'A':
        score += 3;
        break;
      case 'B':
        score += 0;
        break;
      case 'C':
      default:
        score += 6;
        break;
      }
      score += 1;
      break;
    case 'Y':
      switch (first)
      {
      case 'A':
        score += 6;
        break;
      case 'B':
        score += 3;
        break;
      case 'C':
      default:
        score += 0;
        break;
      }
      score += 2;
      break;
    case 'Z':
    default:
      switch (first)
      {
      case 'A':
        score += 0;
        break;
      case 'B':
        score += 6;
        break;
      case 'C':
      default:
        score += 3;
        break;
      }
      score += 3;
      break;
    }
  }
  return score;
}

int main(int argc, const char *argv[])
{
  if (argc < 2)
  {
    std::cout << "Usage: d02 [FILE]\n";
    return 0;
  }
  int score = get_score(argv[1]);
  std::cout << score << '\n';
  return 0;
}
