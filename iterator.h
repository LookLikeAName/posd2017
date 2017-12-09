#ifndef ITERATOR_H
#define ITERATOR_H

#include "struct.h"
#include "list.h"
#include "term.h"

template<class T>
class Iterator{
public:
  virtual void first() = 0;
  virtual void next() = 0;
  virtual T currentItem() const = 0;
  virtual bool isDone() const = 0;
};


class NullIterator :public Iterator<Term *>{
public:
  NullIterator(Term *){}
  void first(){}
  void next(){}
  Term * currentItem() const{
      return nullptr;
  }
  bool isDone() const{
    return true;
  }
};


class StructIterator :public Iterator<Term *> {
public:
  StructIterator(Struct *s): _index(0), _s(s) {}
  void first() {
    _index = 0;
  }

  Term* currentItem() const {
    return _s->args(_index);
  }

  bool isDone() const {
    return _index >= _s->arity();
  }

  void next() {
    _index++;
  }
private:
  
  int _index;
  Struct* _s;
};


class ListIterator :public Iterator<Term *> {
public:
  ListIterator(List *list): _index(0), _list(list) {}

  void first() {
    _index = 0;
  }

  Term* currentItem() const {
    return _list->args(_index);
  }

  bool isDone() const {
    return _index >= _list->arity();
  }

  void next() {
    _index++;
  }
private:
  int _index;
  List* _list;
};


class StructListIterator :public Iterator<Term *> {
public:
 
  StructListIterator(Term *input): _index(0), _input(input) {}

  void first() {
    _index = 0;
  }

  Term* currentItem() const {
    return _input->args(_index);
  }

  bool isDone() const {
    return _index >= _input->arity();
  }

  void next() {
    _index++;
  }
private:
  int _index; 
  Term* _input;
};


class BFSIterator :public Iterator<Term *>{
public:
  BFSIterator(Term *input): _index(0), _input(input) {
    Iterator *it = input->createIterator();
    for(it->first();!it->isDone();it->next()){
      _content.push_back(it->currentItem());
    }
    delete it;
    for(int i=0;i<_content.size();i++){
      Iterator *it =_content[i]->createIterator();
      for(it->first();!it->isDone();it->next()){
        _content.push_back(it->currentItem());
       }
      delete it;
    }
  }

  void first() {
    _index = 0;
  }

  Term* currentItem() const {
    return _content[_index];
  }

  bool isDone() const {
    return _index >= _content.size()-1;
  }

  void next() {
    _index++;
  }
private:
  int _index;
  vector <Term *> _content;
  Term* _input;
};


class DFSIterator :public Iterator<Term *> {
public:
  DFSIterator(Term *input): _index(0), _input(input) {
    Iterator *it = input->createIterator();
    for(it->first();!it->isDone();it->next()){
      _content.push_back(it->currentItem());
    }
    delete it;
    for(int i=0;i<_content.size();i++){
      Iterator *it =_content[i]->createIterator();
      vector <Term*> temp;
      for(it->first();!it->isDone();it->next()){
        temp.push_back(it->currentItem());
       }
      delete it;
      for(int j=0;j<temp.size();j++){
        _content.insert(_content.begin()+i+j+1,temp[j]);
      }
    }
  }

  void first() {
    _index = 0;
  }

  Term* currentItem() const {
    return _content[_index];
  }

  bool isDone() const {
    return _index >= _content.size()-1;
  }

  void next() {
    _index++;
  }
private:
  int _index;
  vector <Term *> _content;
  Term* _input;
};
#endif
