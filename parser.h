#ifndef PARSER_H
#define PARSER_H
#include <string>
using std::string;

#include "term.h"
#include "atom.h"
#include "variable.h"
#include "number.h"
#include "global.h"
#include "scanner.h"
#include "struct.h"
#include "list.h"
#include "node.h"

#include "utParser.h"

class Parser{
public:
  Parser(Scanner scanner) : _scanner(scanner), _terms(){}

  Term* createTerm(){
    int token = _scanner.nextToken();
    _currentToken = token;
    if(token == VAR){
              for(int i=0;i<_varList.size();i++){
                if(_varList[i]->symbol()==symtable[_scanner.tokenValue()].first)
                {
                  //std::cout<<_varList[i]->symbol()<<i<<"same\n";
                  return _varList[i];
                  break;
                }
              }
              _varList.push_back(new Variable(symtable[_scanner.tokenValue()].first));   
            return _varList.back();
    }else if(token == NUMBER){
      return new Number(_scanner.tokenValue());
    }else if(token == ATOM || token == ATOMSC){
      Atom* atom = new Atom(symtable[_scanner.tokenValue()].first);
      if(_scanner.currentChar() == '(' ) {
        return structure();
      }
      else
        return atom;
    }
    else if(token == '['){
      return list();
    }

    return nullptr;
  }



  Term * structure() {
    Atom structName = Atom(symtable[_scanner.tokenValue()].first);
    int startIndexOfStructArgs = _terms.size();
    _currentToken=_scanner.nextToken();
    createTerms();
    if(_currentToken == ')')
    {
     
      vector<Term *> args(_terms.begin() + startIndexOfStructArgs, _terms.end());
      _terms.erase(_terms.begin() + startIndexOfStructArgs, _terms.end());
      if(args.size()==0)
      {
        return new Struct(structName);
      }
      return new Struct(structName, args);
    } else {
      throw string("unexpected token");
    }
  }

  Term * list() {
    int startIndexOfListArgs = _terms.size();
    createTerms();
    if(_currentToken == ']')
    {
      vector<Term *> args(_terms.begin() + startIndexOfListArgs, _terms.end());
      _terms.erase(_terms.begin() + startIndexOfListArgs, _terms.end());
      if(args.size()==0)
      {
        return new List();
      }
      return new List(args);
    } else {
      throw string("unexpected token");
    }
  }

  vector<Term *> & getTerms() {
    return _terms;
  }

  void matchings(){
    Term *currentTerm=createTerm() ;
    _terms.push_back(currentTerm);
    if(_currentToken==VAR){
      _varList.push_back(currentTerm);
    }
    _nodeList.push_back(new Node(TERM,currentTerm,nullptr,nullptr));
    while((_currentToken = _scanner.currentChar())!='.'){
     
       bool isInvarList =false; 
      switch(_currentToken){
        case '=':
          _currentToken = _scanner.nextToken();
          _nodeList.push_back(new Node(EQUALITY,nullptr,nullptr,nullptr));
          break;
        case ',':
          _currentToken = _scanner.nextToken();
          _nodeList.push_back(new Node(COMMA,nullptr,nullptr,nullptr));
          break;
        case ';':
           _varList.erase(_varList.begin() , _varList.end());
          _currentToken = _scanner.nextToken();
          _nodeList.push_back(new Node(SEMICOLON,nullptr,nullptr,nullptr));
          break;
        default:
          currentTerm = createTerm();
             _terms.push_back(currentTerm);
             _nodeList.push_back(new Node(TERM,currentTerm,nullptr,nullptr));
          
      }
    }
   /* for(int i=0;i<_varList.size();i++){
            std::cout<<_varList[i]->symbol()<<" ";
           }
    std::cout<<"\n";
    for(int i=0;i<_nodeList.size();i++){
      std::cout<<_nodeList[i]->payload<<" ";
    }
    std::cout<<"\n";
    */
    inToPostfix();
   /* 
   for(int i=0;i<_nodeList.size();i++){
      std::cout<<_nodeList[i]->payload<<":";
      if(_nodeList[i]->payload==TERM)
      {
        std::cout<<_nodeList[i]->term->symbol()<<" ";
      }
      else
      {
        std::cout<<" ";
      }
    }
    std::cout<<"\n";
    */
    creatTree();
    //std::cout<<_root->payload<<" "<<_root->left->left->payload<<" "<<_root->right->right->payload<<"\n";
  }

  Node * expressionTree(){
    return _root;
  }

private:
  FRIEND_TEST(ParserTest, my_test0);
  FRIEND_TEST(ParserTest, createArgs);
  FRIEND_TEST(ParserTest,ListOfTermsEmpty);
  FRIEND_TEST(ParserTest,listofTermsTwoNumber);
  FRIEND_TEST(ParserTest, createTerm_nestedStruct3);

  void createTerms() {
    
    Term* term = createTerm();
    if(term!=nullptr)
    {
      _terms.push_back(term);
      while((_currentToken = _scanner.nextToken()) == ',') {
        _terms.push_back(createTerm());
      }
    }
    
  } 

  void inToPostfix(){
    vector <Node *>postFix;
    vector <Node *> nodeStack={nullptr};
    int top;
    for(int i=0;i<_nodeList.size();i++){
      switch(_nodeList[i]->payload)
      {
        case SEMICOLON:case COMMA:case EQUALITY:
        if(nodeStack.back()==nullptr){
           nodeStack[0]=_nodeList[i]; 
           break;
        }
        while(_nodeList[i]->payload<=nodeStack.back()->payload){
          postFix.push_back(nodeStack.back());
          nodeStack.pop_back();
          if(nodeStack.size()==0){
            nodeStack[0]=nullptr;
            break;
          }
         
        }
         nodeStack.push_back(_nodeList[i]);
        break;
        case TERM:
          postFix.push_back(_nodeList[i]);
        break;
      }
    }
    while(nodeStack.back()!=nullptr){
      postFix.push_back(nodeStack.back());
      nodeStack.pop_back();
      if(nodeStack.size()==0){
            nodeStack[0]=nullptr;
            break;
      }
    }
    _nodeList=postFix;
  }
  void creatTree(){
   
    _root=_nodeList.back();
  
    Node *currentNode=_root;

    for(int i=_nodeList.size()-2;i>=0;i--)
    {
     
     if(currentNode->right==nullptr)
        {
          currentNode->right=_nodeList[i];
          _nodeList[i]->parent= currentNode;
        }
        else if(currentNode->left==nullptr)
        {
          currentNode->left=_nodeList[i];
          _nodeList[i]->parent= currentNode;         
        }
        else
        {
          if(currentNode->parent!=nullptr)
          {
            currentNode=currentNode->parent;
          }
          else
          {
            currentNode=_root;
          }
          currentNode->left=_nodeList[i];
        }    
      if(_nodeList[i]->payload!=TERM)
      {  
        currentNode=_nodeList[i];      
      }
      
    }
    
  }
  vector <Term *> _varList;
  vector<Term *> _terms;
  vector <Node *> _nodeList;
  Scanner _scanner;
  int _currentToken;
  Node *_root;
};
#endif