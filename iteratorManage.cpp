#include "term.h"
#include "iterator.h"
#include "struct.h"
#include "list.h"


Iterator * Term::createIterator(){
    return new NullIterator(this);
}

/*Iterator * Struct::createIterator(){
    return new StructIterator(this);
}*/
Iterator * Struct::createIterator(){
    return new StructListIterator(this);
}
Iterator * Struct::createBFSIterator(){
    return new BFSIterator(this);
}
Iterator * Struct::createDFSIterator(){
    return new DFSIterator(this);
}

/*Iterator * List::createIterator(){
   return new ListIterator(this);
}*/
Iterator * List::createIterator(){
   return new StructListIterator(this);
}
Iterator * List::createBFSIterator(){
    return new BFSIterator(this);
}
Iterator * List::createDFSIterator(){
    return new DFSIterator(this);
}