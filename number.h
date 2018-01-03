#ifndef NUMBER_H
#define NUMBER_H

#include <string>
#include "term.h"
#include "variable.h"
using std::string;

class Number : public Term
{
public:
  Number(double d)
      : Term([&] {
          string symbol = std::to_string(d);
          int i = symbol.size();
          while (symbol[--i] == '0')
            ;
          if (symbol[i] == '.')
            i--;
          symbol.resize(i + 1);
          return symbol;
        }()) {}
};

#endif