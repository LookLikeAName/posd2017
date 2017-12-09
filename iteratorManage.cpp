#include "term.h"
#include "iterator.h"
#include "struct.h"
#include "list.h"


Iterator<Term*> * Term::createIterator(){
    return new NullIterator(this);
}
Iterator<Term*> * Term::createBFSIterator(){
    return new NullIterator(this);
}
Iterator<Term*> * Term::createDFSIterator(){
    return new NullIterator(this);
}
/*Iterator * Struct::createIterator(){
    return new StructIterator(this);
}*/
Iterator<Term*> * Struct::createIterator(){
    return new StructListIterator(this);
}
Iterator<Term*> * Struct::createBFSIterator(){
    return new BFSIterator(this);
}
Iterator<Term*> * Struct::createDFSIterator(){
    return new DFSIterator(this);
}

/*Iterator * List::createIterator(){
   return new ListIterator(this);
}*/
Iterator<Term*> * List::createIterator(){
   return new StructListIterator(this);
}
Iterator<Term*> * List::createBFSIterator(){
    return new BFSIterator(this);
}
Iterator<Term*> * List::createDFSIterator(){
    return new DFSIterator(this);
}