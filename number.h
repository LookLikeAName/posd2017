#ifndef NUMBER_H
#define NUMBER_H

#include <string>
#include <sstream>
using std::string;
using std::stringstream;
class Number{
public:
  Number(int s) :_symbol(intToStr(s)), _value(intToStr(s)), _className("Number"){}
  string symbol(){return _symbol;}
  string value(){ return _value; }
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
  string intToStr(int i) {
  stringstream ss;
  ss << i;
  return ss.str();
}
};

#endif