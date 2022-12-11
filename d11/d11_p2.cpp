#include <fstream>
#include <iostream>
#include <algorithm>
#include <map>
#include <sstream>
#include <numeric>

class Monkey
{
  std::vector<unsigned long long> heldItems_;
  char operation_;
  int operand_;
  int test_;
  int monkeyIfTrue_;
  int monkeyIfFalse_;
  unsigned long long inspected_{0};

public:
  Monkey(std::string itemsLine, char operation, int operand, int test, int monkeyIfTrue, int monkeyIfFalse) : operand_{operand}, test_{test}, monkeyIfTrue_{monkeyIfTrue}, monkeyIfFalse_{monkeyIfFalse}
  {
    if (operand == 0 && operation == '*')
      operation_ = '^';
    else
      operation_ = operation;
    itemsLine = itemsLine.substr(itemsLine.find_first_of(":"));
    itemsLine = itemsLine.substr(itemsLine.find_first_of(" "));
    std::stringstream ss(itemsLine);
    for (int i; ss >> i;)
    {
      heldItems_.push_back(i);
      if (ss.peek() == ',')
        ss.ignore();
    }
  }
  void toss(unsigned long long item,unsigned long long newItem, Monkey &receiver)
  {
    heldItems_.erase(std::find(heldItems_.begin(), heldItems_.end(), item));
    receiver.receive(newItem);
  }
  void receive(unsigned long long item)
  {
    heldItems_.push_back(item);
  }
  auto heldItems() const
  {
    return heldItems_;
  }
  auto operation() const
  {
    return operation_;
  }
  auto operand() const
  {
    return operand_;
  }
  auto test() const
  {
    return test_;
  }
  auto ifTrue() const
  {
    return monkeyIfTrue_;
  }
  auto ifFalse() const
  {
    return monkeyIfFalse_;
  }
  void inspect(){
    ++inspected_;
  }
  auto inspected() const{
    return inspected_;
  }
};

unsigned long long getMonkeyBusiness(const char *filename)
{
  std::ifstream file(filename);
  std::vector<Monkey> monkeys;
  while (file.good())
  {
    std::string line;
    std::getline(file, line);
    int monkeyIndex{};
    std::sscanf(line.c_str(), "Monkey %i:", &monkeyIndex);
    std::string itemsLine;
    std::getline(file, itemsLine);
    char operation{};
    int operand{};
    std::getline(file, line);
    std::sscanf(line.c_str(), "  Operation: new = old %c %i", &operation, &operand);
    int test{};
    std::getline(file, line);
    std::sscanf(line.c_str(), "  Test: divisible by %i", &test);
    int ifTrue{};
    std::getline(file, line);
    std::sscanf(line.c_str(), "    If true: throw to monkey %i", &ifTrue);
    int ifFalse{};
    std::getline(file, line);
    std::sscanf(line.c_str(), "    If false: throw to monkey %i", &ifFalse);
    std::getline(file, line);
    Monkey newMonkey(itemsLine, operation, operand, test, ifTrue, ifFalse);
    monkeys.push_back(newMonkey);
  }
  int lcm{1};
  for (auto &monkey : monkeys)
  {
    lcm *= monkey.test();
  }
  for (int i = 0; i < 10000;++i){
    for (auto &monkey : monkeys)
    {
      for (auto item : monkey.heldItems())
      {
        unsigned long long newItem{};
        switch (monkey.operation())
        {
        case '*':
          newItem = item * monkey.operand();
          break;
        case '+':
          newItem = item + monkey.operand();
          break;
        case '^':
        default:
          newItem = item * item;
          break;
        }
        monkey.inspect();
        newItem = newItem % lcm;
        // newItem = newItem / 3;
        if (newItem % monkey.test() == 0)
          monkey.toss(item, newItem, monkeys[monkey.ifTrue()]);
        else
          monkey.toss(item, newItem, monkeys[monkey.ifFalse()]);
      }
    }
  }
  std::sort(monkeys.begin(), monkeys.end(), [](Monkey a, Monkey b)
            { return a.inspected() > b.inspected(); });
  return monkeys[0].inspected() * monkeys[1].inspected();
}

int main(int argc, char const *argv[])
{
  std::cout << getMonkeyBusiness(argv[1]) << '\n';
  return 0;
}
