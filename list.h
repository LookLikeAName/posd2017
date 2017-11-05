#ifndef LIST_H
#define LIST_H

#include "term.h"
#include "atom.h"
#include <vector>
using std::vector;

class List : public Term {
public:
  List (): _elements(),_className("List"){}
  List (vector<Term *> elements):_elements(elements),_haveElement(true),_className("List"){
  }
  
  string symbol()const{
    string ret ="[";
    if(_haveElement){
    for(int i = 0; i < _elements.size() - 1 ; i++){
      ret += _elements[i]-> symbol() + ", ";
    }
    ret += _elements[_elements.size()-1]-> symbol() + "]";
    }
    else
    {
      ret+="]";
    }
    return  ret;
  }
  string value()const{ 
  string ret ="[";
  if(_haveElement){
  for(int i = 0; i < _elements.size() - 1 ; i++){
    ret += _elements[i]-> value() + ", ";
  }
  ret += _elements[_elements.size()-1]-> value() + "]";
  }
  else
  {
    ret+="]";
  }
  return  ret;
 }
  string getClassName()const{return _className;}
  
  bool match(Term & term){
    if(term.getClassName()=="Variable")
    {
        return term.match(*this);
    }
    else
    {
      List * ps = dynamic_cast<List *>(&term);
      if (ps){
        if(_elements.size()!= ps->_elements.size())
          return false;
        for(int i=0;i<_elements.size();i++){
          if(_elements[i]->value() != ps->_elements[i]->value()){
                if(_elements[i]->getClassName()=="Variable"||ps->_elements[i]->getClassName()=="Variable")
                {
                  if(_elements[i]->match(*ps->_elements[i])){
                    continue;
                  }
                }
                return false;
          }
        }

        return true;
      }
      return false;
    }
  };

  Term * head() const{
    if(_haveElement){
        return _elements[0];
    }
    throw string("Accessing head in an empty list"); 
  };
  List * tail() const
  {
    List *l;
    vector<Term *> tails;
    if(_haveElement){
      for(int i=1;i<_elements.size();i++){
        tails.push_back(_elements[i]);
      }     
      if(tails.size()!=0){
        l=new List(tails);
      }
      else
      {
        l=new List();
      }
      return l;
    }
    throw string("Accessing tail in an empty list");
  };
private:
  vector<Term *> _elements;
  bool _haveElement=false;
  string const _className;
};

#endif
