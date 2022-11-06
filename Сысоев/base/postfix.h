#ifndef __POSTFIX_H__
#define __POSTFIX_H__

#include <string>
#include <stack>
#include <utility>

using namespace std;

class TPostfix
{
  string infix;
  string postfix;
public:
  explicit TPostfix(string s="")
  {
    infix = s;
  }
  string GetInfix() { return infix; }
  string GetPostfix() { return postfix; }
  string ToPostfix();
  static short Priority(char operation); // Приоритет операции
  double Calculate(); // Ввод переменных, вычисление по постфиксной форме
};

#endif

