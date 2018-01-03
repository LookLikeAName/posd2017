#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include "term.h"
using std::string;

class Variable : public Term
{
public:
  Variable(string s) : Term(s), _value(nullptr) {}
  string value() const
  {
    if (!_value)
      return symbol();
    else
      return _value->value();
  }

  bool isAssignable() { return !_value; }

  bool match(Term &term)
  {
    if (term.findBySymbol(symbol()) != nullptr &&
        term.findBySymbol(symbol()) != &term)
      return false;
    else if (&term == this)
      return true;
    else if (!_value)
    {
      _value = &term;
      return true;
    }
    else
    {
      if (term.isAssignable())
        return term.match(*this);
      else
        return _value->match(term);
    }
  }

private:
  Term *_value;
};

#endif