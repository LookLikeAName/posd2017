#ifndef PARSER_H
#define PARSER_H
#include <string>
using std::string;

#include "atom.h"
#include "variable.h"
#include "number.h"
#include "global.h"
#include "scanner.h"
#include "struct.h"
#include "list.h"
class unexpectedToken:public std::exception
{
  virtual const char* what() const throw()
  {
    return "unexpected token";
  }
}unexpectedToken;

class Parser{
public:
  Parser(Scanner scanner) : _scanner(scanner){}
  Term* createTerm(){
    int token = _scanner.nextToken();
    if(token == VAR){
      return new Variable(symtable[_scanner.tokenValue()].first);
    }else if(token == NUMBER){
      return new Number(_scanner.tokenValue());
    }else if(token == ATOM||token == ATOMSC){
        Atom* atom = new Atom(symtable[_scanner.tokenValue()].first);
        if(_scanner.currentChar() == '(' ) {
          _currentToken=_scanner.nextToken() ;
          if(_scanner.currentChar()==')'){
            _currentToken=_scanner.nextToken() ;
            return new Struct(*atom);
          }
          vector<Term*> terms = getArgs();
          if(_currentToken == ')')
          {
            return new Struct(*atom, terms);
          }
          else if(_currentToken == ']')
          {
           throw unexpectedToken;
          }
        }
        else
        {
          return atom;
        }
    }
    else if(token=='['){
      _scanner.skipLeadingWhiteSpace();
      if(_scanner.currentChar()==']'){
        _currentToken=_scanner.nextToken();
        return new List();
      }
      vector<Term*> terms = getArgs();
      if(_currentToken == ']')
      {
        return new List(terms);
      }
      else if(_currentToken == ')')
      {
        throw unexpectedToken;
      }
    }
    return nullptr;
  }

  vector<Term*> getArgs()
  {
    
    vector<Term*> args;
    Term* term = createTerm();
    if(term!=nullptr)
    {
      args.push_back(term);
    }
   
    while((_currentToken = _scanner.nextToken()) == ',') 
    {
     args.push_back(createTerm());
    }
     return args;
      
     
  }



private:
  Scanner _scanner;
  int _currentToken;
};


#endif
