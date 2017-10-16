#ifndef STRUCT_H
#define STRUCT_H

#include "atom.h"
#include "term.h"
#include <vector>
#include <string>

using std::string;

class Struct:public Term
{
public:
  Struct(Atom const & name, std::vector<Term *> args):_name(name), _args(args) ,_className("Struct"){
  }

  Term * args(int index) {
    return _args[index];
  }

  Atom const & name() {
    return _name;
  }
    string value() const{
        string ret =_name.symbol() + "(";
        for(int i = 0; i < _args.size() - 1 ; i++){
          ret += _args[i]-> value() + ", ";
        }
        ret += _args[_args.size()-1]-> value() + ")";
        return  ret;
    };

  string symbol() const{
    string ret =_name.symbol() + "(";
    for(int i = 0; i < _args.size() - 1 ; i++){
      ret += _args[i]-> symbol() + ", ";
    }
    ret += _args[_args.size()-1]-> symbol() + ")";
    return  ret;
  }
  string getClassName()const{return _className;}
  bool match(Term &term){
    Struct * ps = dynamic_cast<Struct *>(&term);
    if (ps){
      if (!_name.match(ps->_name))
        return false;
      if(_args.size()!= ps->_args.size())
        return false;
      for(int i=0;i<_args.size();i++){
        if(_args[i]->value() != ps->_args[i]->value())
            return false;
      }
      return true;
    }
    return false;
  }
private:
  Atom _name;
  std::vector<Term *> _args;
  string const _className;
};

#endif