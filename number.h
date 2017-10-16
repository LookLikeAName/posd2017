#ifndef NUMBER_H
#define NUMBER_H

#include <string>
#include <sstream>
#include "term.h"
using std::string;
using std::ostringstream ;
class Number:public Term{
public:
  template <class T>
  Number(T s) :_symbol(numToStr(s)), _value(numToStr(s)), _className("Number"){}
  string symbol()const{return _symbol;}
  string value()const{ return _value; }
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
  template <class T>
  string numToStr(T i) {
  ostringstream  oss;
  oss << i;
  return oss.str();
}
};

#endif