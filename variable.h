#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include "atom.h"
#include "number.h"
using std::string;

class Variable{
public:
  Variable(string s) :_symbol(s), _className("Variable"){}
  string symbol(){return _symbol;}
  string value(){ return _value; }
  string getClassName(){return _className;}
  bool setValue(string input){
   // std::cout<<"setValue "<<(_assignable?"true":"false")<<"\n";
    if(_assignable){
   //   std::cout<<_value<<" "<<input<<"\n";
      _value = input ;
    //  std::cout<<_value<<" "<<input<<"\n";
      _assignable = false;
      return true;
    }
     return _value==input;
  }

  template <class T>
  bool match( T atom ){
    if(_assignable){
      _value = atom.value() ;
      _assignable = false;
      return true;
    }
    return _value==atom.value();
  }
private:
  string const _symbol;
  string _value;
  bool _assignable = true;
  string const _className;
};

#endif
