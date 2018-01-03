#ifndef STRUCT_H
#define STRUCT_H

#include <vector>
#include "atom.h"
using std::vector;
#include <string>
using std::string;

template <class T>
class Iterator;
template <class T>
class DFSIterator;
template <class T>
class BFSIterator;

class Struct : public Term
{
public:
  Struct(Atom name, vector<Term *> args)
      : Term([&] {
          if (args.empty())
            return name.symbol() + "()";
          else
          {
            string symbol = name.symbol() + "(";
            for (int i = 0; i < args.size() - 1; i++)
              symbol += args[i]->symbol() + ", ";
            symbol += args.back()->symbol() + ")";
            return symbol;
          }
        }()),
        _name(name),
        _args(args) {}
  string value() const
  {
    if (arity() == 0)
      return _name.symbol() + "()";
    else
    {
      string value = _name.symbol() + "(";
      for (int i = 0; i < _args.size() - 1; i++)
        value += _args[i]->value() + ", ";
      value += _args[_args.size() - 1]->value() + ")";
      return value;
    }
  }

  bool match(Term &term)
  {
    Struct *ps = dynamic_cast<Struct *>(&term);
    if (ps)
    {
      if (!_name.match(ps->_name))
        return false;
      else if (_args.size() != ps->_args.size())
        return false;
      else
      {
        for (int i = 0; i < _args.size(); i++)
          if (_args[i]->symbol() != ps->_args[i]->symbol())
            return false;
        return true;
      }
    }
    else if (term.isAssignable())
      return term.match(*this);
    else
      return symbol() == term.value();
  }

  Term *findBySymbol(string symbol)
  {
    for (int i = 0; i < _args.size(); i++)
      if (_args[i]->findBySymbol(symbol) != nullptr)
        return _args[i]->findBySymbol(symbol);
    return nullptr;
  }

  Atom name() const { return _name; }
  int arity() const { return _args.size(); }
  Term *args(int index) const { return _args[index]; }

  Iterator<Term *> *createIterator();
  Iterator<Term *> *createDFSIterator();
  Iterator<Term *> *createBFSIterator();

private:
  Atom _name;
  const vector<Term *> _args;
};

#endif