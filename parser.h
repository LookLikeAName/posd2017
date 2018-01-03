#ifndef PARSER_H
#define PARSER_H

#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <stack>
#include "atom.h"
#include "list.h"
#include "number.h"
#include "scanner.h"
#include "struct.h"
#include "term.h"
#include "variable.h"
#include "exp.h"

using std::stack;
using std::string;
using std::vector;


class Parser
{
public:
  Parser(Scanner scanner) : _scanner(scanner), _scopeStartIndex(0) {}

  Term *createTerm()
  {
    int token = _scanner.nextToken();
    _currentToken = token;
    if (token == VAR)
    {
      for (int i = _scopeStartIndex; i < _varTable.size(); i++)
        if (symtable[_scanner.tokenValue()].first == _varTable[i]->symbol())
          return _varTable[i];
      Variable *variable = new Variable(symtable[_scanner.tokenValue()].first);
      _varTable.push_back(variable);
      return variable;
    }
    else if (token == NUMBER)
      return new Number(_scanner.tokenValue());
    else if (token == ATOM || token == ATOMSC)
    {
      Atom *atom = new Atom(symtable[_scanner.tokenValue()].first);
      if (_scanner.currentChar() == '(')
        return structure();
      else
        return atom;
    }
    else if (token == '[')
      return list();
    else
      return nullptr;
  }

  vector<Term *> &getTerms() { return _terms; }

  void buildExpression()
  {
    if (_scanner.getContext().find(";.") != string::npos)
      throw string("Unexpected ';' before '.'");
    if (_scanner.getContext().find(",.") != string::npos)
      throw string("Unexpected ',' before '.'");
    disjunctionMatch();
    restDisjunctionMatch();
    if (createTerm() != nullptr || _currentToken != '.')
      throw string("Missing token '.'");
  }

  Exp *getExpressionTree() { return _expStack.top(); }

  string excute(){
    return this->getExpressionTree()->getResult()+".";
  }
private:
  void createTerms()
  {
    Term *term = createTerm();
    if (term != nullptr)
    {
      _terms.push_back(term);
      while ((_currentToken = _scanner.nextToken()) == ',')
        _terms.push_back(createTerm());
    }
  }

  Term *structure()
  {
    Atom structName = Atom(symtable[_scanner.tokenValue()].first);
    int startIndexOfStructArgs = _terms.size();
    _scanner.nextToken();
    createTerms();
    if (_currentToken == ')')
    {
      vector<Term *> args(_terms.begin() + startIndexOfStructArgs,
                          _terms.end());
      _terms.erase(_terms.begin() + startIndexOfStructArgs, _terms.end());
      return new Struct(structName, args);
    }
    else if (_currentToken == ';')
      throw string("Unbalanced operator");
    else
      throw string("unexpected token");
  }

  Term *list()
  {
    int startIndexOfListArgs = _terms.size();
    createTerms();
    if (_currentToken == ']')
    {
      vector<Term *> args(_terms.begin() + startIndexOfListArgs, _terms.end());
      _terms.erase(_terms.begin() + startIndexOfListArgs, _terms.end());
      return new List(args);
    }
    else if (_currentToken == ';')
      throw string("Unbalanced operator");
    else
      throw string("unexpected token");
  }

  void restDisjunctionMatch()
  {
    if (_scanner.currentChar() == ';')
    {
      _scopeStartIndex = _varTable.size();
      createTerm();
      disjunctionMatch();
      Exp *right = _expStack.top();
      _expStack.pop();
      Exp *left = _expStack.top();
      _expStack.pop();
      _expStack.push(new DisjExp(left, right));
      restDisjunctionMatch();
    }
  }

  void disjunctionMatch()
  {
    conjunctionMatch();
    restConjunctionMatch();
  }

  void restConjunctionMatch()
  {
    if (_scanner.currentChar() == ',')
    {
      createTerm();
      conjunctionMatch();
      Exp *right = _expStack.top();
      _expStack.pop();
      Exp *left = _expStack.top();
      _expStack.pop();
      _expStack.push(new ConjExp(left, right));
      restConjunctionMatch();
    }
  }

  void conjunctionMatch()
  {
    Term *left = createTerm();
    if (createTerm() == nullptr && _currentToken == '=')
    {
      Term *right = createTerm();
      _expStack.push(new MatchExp(left, right));
    }
    else
      throw string(left->symbol() + " does never get assignment");
  }

  Scanner _scanner;
  int _currentToken;
  vector<Term *> _terms;
  vector<Variable *> _varTable;
  int _scopeStartIndex;
  stack<Exp *> _expStack;

  FRIEND_TEST(ParserTest, createArgs);
  FRIEND_TEST(ParserTest, ListOfTermsEmpty);
  FRIEND_TEST(ParserTest, listofTermsTwoNumber);
  FRIEND_TEST(ParserTest, createTerm_nestedStruct3);
};
#endif
