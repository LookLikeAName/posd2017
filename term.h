#ifndef TERM_H
#define TERM_H

#include <string>
using std::string;

template <class T>
class Iterator;
template <class T>
class DFSIterator;
template <class T>
class BFSIterator;

class Term
{
public:
  virtual string symbol() const { return _symbol; }
  virtual string value() const { return symbol(); }
  virtual bool isAssignable() { return false; }

  virtual bool match(Term &term)
  {
    if (term.isAssignable())
      return term.match(*this);
    else
      return symbol() == term.value();
  }

  virtual Term *findBySymbol(string symbol)
  {
    if (symbol == this->symbol())
      return this;
    else
      return nullptr;
  }

  virtual Iterator<Term *> *createIterator();
  virtual Iterator<Term *> *createDFSIterator();
  virtual Iterator<Term *> *createBFSIterator();

protected:
  Term(string s) : _symbol(s) {}
  string _symbol;
};

#endif