#ifndef NODE_H
#define NODE_H
#include "term.h"
enum Operators {SEMICOLON, COMMA, EQUALITY, TERM};

class Node {
public:
  Node(Operators op):payload(op), term(0), left(0), right(0) {}
  Node(Operators op, Term *t, Node *l, Node *r):payload(op),term(t),left(l),right(r),parent(nullptr) {}
  Operators rPayLoad(){
    return payload;
  }
  bool evaluate(){
     bool rightEv,leftEv;
     switch(payload)
     {
       case SEMICOLON:
          //std::cout<<"SEMICOLON\n";
           leftEv = left->evaluate();
           rightEv = right->evaluate();
          return (rightEv || leftEv);
       break;
       case COMMA:
      // std::cout<<"COMMA\n";
           leftEv = left->evaluate();
           rightEv = right->evaluate();
          return (rightEv && leftEv);
       break;
       case EQUALITY:
       // std::cout<<"EQUALITY\n";
        return left->term->match(*right->term);
       break;
     }
  };
  Operators payload;
  Term* term;
  Node* left;
  Node* right;
  Node* parent;
};

#endif
