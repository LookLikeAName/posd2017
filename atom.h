#ifndef ATOM_H
#define ATOM_H

#include <string>
#include "term.h"
using std::string;

class Atom :public Term{
public:
  Atom (string s):_symbol(s), _value(s), _className("Atom"){}
  string value()const{ return _value; }
  string symbol()const{return _symbol;}
  string getClassName()const{return _className;}
  bool match( Term &term ){ 
    if(term.getClassName()=="Variable")
    {
       return term.match(*this); 
    }
    else
    {
      return _value == term.value();
    }

  }
 private:
  string const _symbol;
  string _value;
  string const _className;

};

#endif
