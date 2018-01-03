#ifndef LIST_H
#define LIST_H

#include <string>
#include <vector>
#include "term.h"
#include "variable.h"
using std::string;
using std::vector;

template <class T>
class Iterator;
template <class T>
class DFSIterator;
template <class T>
class BFSIterator;

class List : public Term
{
public:
  List(vector<Term *> elements = {})
      : Term([&]() -> string {
          if (elements.empty())
            return "[]";
          else
          {
            string symbol = "[";
            for (int i = 0; i < elements.size() - 1; i++)
              symbol += elements[i]->symbol() + ", ";
            symbol += elements.back()->symbol() + "]";
            return symbol;
          }
        }()),
        _elements(elements) {}
  string value() const
  {
    if (_elements.empty())
      return "[]";
    else
    {
      string ret = "[";
      for (int i = 0; i < _elements.size() - 1; i++)
        ret += _elements[i]->value() + ", ";
      ret += _elements[_elements.size() - 1]->value() + "]";
      return ret;
    }
  }

  bool match(Term &term)
  {
    List *p = dynamic_cast<List *>(&term);
    if (p)
    {
      if (_elements.size() != p->_elements.size())
        return false;
      else
      {
        for (int i = 0; i < _elements.size(); i++)
          if (!_elements[i]->match(*(p->_elements[i])))
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
    for (int i = 0; i < _elements.size(); i++)
      if (_elements[i]->findBySymbol(symbol) != nullptr)
        return _elements[i]->findBySymbol(symbol);
    return nullptr;
  }

  Term *head() const
  {
    if (_elements.empty())
      throw string("Accessing head in an empty list");
    else
      return _elements.front();
  }
  List *tail() const
  {
    if (_elements.empty())
      throw string("Accessing tail in an empty list");
    else
    {
      vector<Term *> tail;
      for (int i = 1; i < _elements.size(); i++)
        tail.push_back(_elements[i]);
      List *l = new List(tail);
      return l;
    }
  }

  Iterator<Term *> *createIterator();
  Iterator<Term *> *createDFSIterator();
  Iterator<Term *> *createBFSIterator();

private:
  vector<Term *> _elements;
};

#endif
