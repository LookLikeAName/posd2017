#ifndef ITERATOR_H
#define ITERATOR_H

#include <queue>
#include <stack>
#include "list.h"
#include "struct.h"
#include "term.h"
using std::queue;
using std::stack;

template <class T>
class Iterator
{
public:
  virtual void first() = 0;
  virtual void next() = 0;
  virtual Term *currentItem() const = 0;
  virtual bool isDone() const = 0;
  virtual Term *currentTerm() const = 0;
};

template <class T>
class NullIterator : public Iterator<T>
{
public:
  friend class Term;

  void first(){};
  void next(){};
  Term *currentItem() const { return nullptr; };
  bool isDone() const { return true; };
  Term *currentTerm() const { return _t; };

private:
  NullIterator(T t) : _t(t) {}
  T _t;
};

template <class T>
class StructIterator : public Iterator<T>
{
public:
  friend class Struct;

  void first() { _index = 0; }
  void next() { _index++; }
  Term *currentItem() const { return _s->args(_index); }
  bool isDone() const { return _index >= _s->arity(); }
  Term *currentTerm() const { return _s; };

private:
  StructIterator(Struct *s) : _index(0), _s(s) {}
  int _index;
  Struct *_s;
};

template <class T>
class ListIterator : public Iterator<T>
{
public:
  friend class List;

  void first() { _tailList = *_l; }
  void next()
  {
    try
    {
      _tailList = *(_tailList.tail());
    }
    catch (string e)
    {
    }
  }
  Term *currentItem() const { return _tailList.head(); }
  bool isDone() const
  {
    try
    {
      _tailList.head();
    }
    catch (string e)
    {
      return true;
    }
    return false;
  }
  Term *currentTerm() const { return _l; };

private:
  ListIterator(List *l) : _l(l), _tailList(*l) {}
  List *_l, _tailList;
};

template <class T>
class DFSIterator : public Iterator<T>
{
public:
  friend class Struct;
  friend class List;

  void first()
  {
    while (!_iteratorStack.empty())
      _iteratorStack.pop();
    _iteratorStack.push(_t->createIterator());
  }
  void next()
  {
    if (!isDone())
    {
      if (isLeaf())
      {
        _iteratorStack.top()->next();
        while (!isDone() && _iteratorStack.top()->isDone())
        {
          _iteratorStack.pop();
          if (!isDone())
            _iteratorStack.top()->next();
        }
      }
      else
        _iteratorStack.push(currentItem()->createIterator());
    }
  }
  Term *currentItem() const { return _iteratorStack.top()->currentItem(); }
  bool isDone() const { return _iteratorStack.empty(); };
  Term *currentTerm() const { return _t; };

private:
  DFSIterator(T t) : _t(t) { _iteratorStack.push(_t->createIterator()); }
  bool isLeaf() const { return currentItem()->createIterator()->isDone(); }

  stack<Iterator<Term *> *> _iteratorStack;
  T _t;
};

template <class T>
class BFSIterator : public Iterator<T>
{
public:
  friend class Struct;
  friend class List;

  void first()
  {
    while (!_iteratorQueue.empty())
      _iteratorQueue.pop();
    _iteratorQueue.push(_t->createIterator());
  }
  void next()
  {
    if (!isDone())
    {
      if (isLeaf())
      {
        _iteratorQueue.front()->next();
        if (_iteratorQueue.front()->isDone())
          _iteratorQueue.pop();
      }
      else
      {
        _iteratorQueue.push(currentItem()->createIterator());
        _iteratorQueue.front()->next();
        if (_iteratorQueue.front()->isDone())
          _iteratorQueue.pop();
      }
    }
  }
  Term *currentItem() const { return _iteratorQueue.front()->currentItem(); }
  bool isDone() const { return _iteratorQueue.empty(); };
  Term *currentTerm() const { return _t; };

private:
  BFSIterator(T t) : _t(t) { _iteratorQueue.push(_t->createIterator()); }
  bool isLeaf() const { return currentItem()->createIterator()->isDone(); }

  queue<Iterator<Term *> *> _iteratorQueue;
  T _t;
};

#endif