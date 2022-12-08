#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <assert.h>

template <typename T>
class Grid
{
  std::vector<T> grid_;
  int rows_;
  int columns_;

public:
  Grid(int r, int c) : columns_(c), rows_(r), grid_(r * c){};
  Grid(std::string filename)
  {
    std::ifstream file(filename);
    std::string line{};
    rows_ = 0;
    while (std::getline(file, line))
    {
      ++rows_;
      for (auto c : line)
      {
        grid_.push_back(c - '0');
      }
    }
    columns_ = line.length();
  }
  auto grid() const
  {
    return grid_;
  }

  auto &grid()
  {
    return grid_;
  }

  auto rows() const
  {
    return rows_;
  }

  auto columns() const
  {
    return columns_;
  }

  template <typename U>
  friend std::ostream &operator<<(std::ostream &os, const Grid<U> &g);

  auto operator()(int r, int c)
  {
    return grid_[columns_ * r + c];
  }

  auto operator()(int r, int c) const
  {
    return grid_[columns_ * r + c];
  }
};
int getVisible(Grid<int> trees)
{
  int ans{};
  Grid<bool> visible(trees.rows(), trees.columns());
  // left
  for (int i = 0; i < trees.rows(); ++i)
  {
    int currentMax{-1};
    for (int j = 0; j < trees.columns(); ++j)
    {
      if (trees(i, j) > currentMax && !visible(i, j))
      {
        visible(i, j) = true;
        ++ans;
      }
      currentMax = std::max(currentMax, trees(i, j));
    }
  }
  // right
  for (int i = 0; i < trees.rows(); ++i)
  {
    int currentMax{-1};
    for (int j = trees.columns() - 1; j >= 0; --j)
    {
      if (trees(i, j) > currentMax && !visible(i, j))
      {
        visible(i, j) = true;
        ++ans;
      }
      currentMax = std::max(currentMax, trees(i, j));
    }
  }
  // down
  for (int i = 0; i < trees.columns(); ++i)
  {
    int currentMax{-1};
    for (int j = 0; j < trees.rows(); ++j)
    {
      if (trees(j, i) > currentMax && !visible(j, i))
      {
        visible(j, i) = true;
        ++ans;
      }
      currentMax = std::max(currentMax, trees(j, i));
    }
  }
  // up
  for (int i = 0; i < trees.columns(); ++i)
  {
    int currentMax{-1};
    for (int j = trees.rows() - 1; j >= 0; --j)
    {
      if (trees(j, i) > currentMax && !visible(j, i))
      {
        visible(j, i) = true;
        ++ans;
      }
      currentMax = std::max(currentMax, trees(j, i));
    }
  }
  return ans;
}

int getScenicScore(Grid<int> trees, int y, int x)
{
  int height{trees(y, x)};
  int l{};
  int r{};
  int u{};
  int d{};
  for (u = y - 1; trees(u, x) < height && u > 0; --u)
    ;
  for (l = x - 1; trees(y, l) < height && l > 0; --l)
    ;
  for (r = x + 1; trees(y, r) < height && r < trees.columns() - 1; ++r)
    ;
  for (d = y + 1; trees(d, x) < height && d < trees.rows() - 1; ++d)
    ;

  return (x - l) * (r - x) * (y - u) * (d - y);
}

int getMaxScore(Grid<int> trees)
{
  Grid<int> scenicScores(trees.rows(), trees.columns());
  int maxScenicScore{};
  for (int r = 0; r < trees.rows(); r++)
  {
    for (int c = 0; c < trees.columns(); c++)
    {
      maxScenicScore = std::max(maxScenicScore, getScenicScore(trees, r, c));
    }
  }
  return maxScenicScore;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const Grid<T> &g)
{

  for (int r = 0; r < g.rows_; ++r)
  {
    for (int c = 0; c < g.columns_; ++c)
      os << g(r, c) << ' ';
    os << '\n';
  }
  return os;
}

int main(int argc, const char *argv[])
{
  Grid<int> treeHeights(argv[1]);
  std::cout << getMaxScore(treeHeights);
}