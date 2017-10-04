#ifndef ATOM_H
#define ATOM_H

#include <string>
using std::string;

class Atom {
public:
  Atom (string s):_symbol(s), _value(s), _className("Atom"){}
  string value(){ return _value; }
  string symbol(){return _symbol;}
  string getClassName(){return _className;}
  template <class T>
 bool match(T &atom){
    if(atom.getClassName()=="Variable")
    {
       return atom.match(*this); 
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
