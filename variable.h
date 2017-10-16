#ifndef VARIABLE_H
#define VARIABLE_H

#define debug 0
#include <string>
#include "term.h"
using std::string;

class Variable:public Term{
public:
  Variable(string s) :_symbol(s), _className("Variable"){}
  string symbol()const{return _symbol;}
  string value()const{ 
    if(_varMatched)
    {
      return _matchedVar->value();
    }
    else
    {
      if(_assignable)
      {
        return _symbol;
      }
      return _value;
    }
  }
  string getClassName()const{return _className;}
  bool isAssignable(){return _assignable;}
  bool match( Term &term ){   
    if(_assignable){
      if(term.getClassName()=="Variable"||term.getClassName()=="Struct"){
        if(_symbol==term.symbol())
        {
          return true;
        }       
        _matchedVar=&term;

        #if debug
        std::cout<<_matchedVar->symbol()<<" "<<_matchedVar->value()<<" isVar\n";
        #endif
        
        _assignable=term.isAssignable();
        _varMatched=true;
        return true;
      }
      else
      {
        if(_varMatched)
        {
          _matchedVar->match(term);
        }
        else
        {

          #if debug
          std::cout<<"matchVar "<<_symbol<<": "<<term.value()<<"\n";
          #endif

          _value = term.value() ;
        }
       _assignable = false;
       return true;
      }
    }
    if(_varMatched)
    {
      return term.match(*_matchedVar);
    }
    else
    {
     return _value==term.value();
    }
  }
private:
  Term * _matchedVar;
  bool _varMatched=false;
  string const _symbol;
  string _value;
  bool _assignable = true;
  string const _className;
};

#endif
