#ifndef NUMBER_H
#define NUMBER_H

#include <string>
#include "atom.h"
#include "variable.h"
using std::string;

class Number{
public:
  Number(string s ,string v) :_symbol(s), _value(v), _className("Number"){}
  string symbol(){return _symbol;}
  string value(){ return _value; }
  bool setValue(string input){}
  string getClassName(){return _className;}
  template <class T>
  bool match(T atom){
    if(atom.getClassName()=="Variable")
    {
       return atom.setValue(_value);
    }
    else
    {

      return _value == atom.value();
    }

  }
private:
  string const _symbol;
  string _value;
  string const _className;
};

#endif