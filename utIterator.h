#ifndef UTITERATOR_H
#define UTITERATOR_H

#include "struct.h"
#include "variable.h"
#include "atom.h"
#include "list.h"
#include "number.h"
#include "iterator.h"


TEST(iterator, first) {
    Number one(1);
    Variable X("X");
    Variable Y("Y");
    Number two(2);
    Struct t(Atom("t"), { &X, &two });
    Struct s(Atom("s"), { &one, &t, &Y });
    // StructIterator it(&s);
    Iterator *itStruct = s.createIterator();
    // Iterator& itStruct = it;
    // ASSERT_EQ(it.first()->symbol());
    itStruct->first();
    ASSERT_EQ("1", itStruct->currentItem()->symbol());
    ASSERT_FALSE(itStruct->isDone());
    itStruct->next();
    ASSERT_EQ("t(X, 2)", itStruct->currentItem()->symbol());
    ASSERT_FALSE(itStruct->isDone());
    itStruct->next();
    ASSERT_EQ("Y", itStruct->currentItem()->symbol());
    itStruct->next();
    ASSERT_TRUE(itStruct->isDone());
}

 TEST(iterator, nested_iterator) {
   Number one(1);
   Variable X("X");
   Variable Y("Y");
   Number two(2);
   Struct t(Atom("t"), { &X, &two });
   Struct s(Atom("s"), { &one, &t, &Y });
   StructIterator it(&s);
   it.first();
   it.next();
   Struct *s2 = dynamic_cast<Struct *>(it.currentItem());

   StructIterator it2(s2);
   it2.first();
   ASSERT_EQ("X", it2.currentItem()->symbol());
   ASSERT_FALSE(it2.isDone());
   it2.next();
   ASSERT_EQ("2", it2.currentItem()->symbol());
   ASSERT_FALSE(it2.isDone());
   it2.next();
   ASSERT_TRUE(it2.isDone());
 }

TEST(iterator, firstList) {
    Number one(1);
    Variable X("X");
    Variable Y("Y");
    Number two(2);
    Struct t(Atom("t"), { &X, &two });
    List l({ &one, &t, &Y });
    ListIterator it(&l);
    Iterator* itList = &it;
    itList->first();
    ASSERT_EQ("1", itList->currentItem()->symbol());
    ASSERT_FALSE(itList->isDone());
    itList->next();
    ASSERT_EQ("t(X, 2)", itList->currentItem()->symbol());
    ASSERT_FALSE(itList->isDone());
    itList->next();
    ASSERT_EQ("Y", itList->currentItem()->symbol());
    itList->next();
    ASSERT_TRUE(itList->isDone());
}

TEST(iterator, NullIterator){
  Number one(1);
  NullIterator nullIterator(&one);
  nullIterator.first();
  ASSERT_TRUE(nullIterator.isDone());
  Iterator * it = one.createIterator();
  it->first();
  ASSERT_TRUE(it->isDone());
}

/*s(1,t(X, 2),Y)
 except: 1 -> t -> Y -> X -> 2
*/
TEST(iterator, structBFSIterator){
  Number one(1);
  Number two(2);
  Variable X("X");
  Variable Y("Y");
  Struct t(Atom("t"), { &X, &two });
  Struct s(Atom("s"), { &one, &t, &Y });

  Iterator * it = s.createBFSIterator();
  it->first();
  EXPECT_EQ("1",it->currentItem()->symbol());
  it->next();
  EXPECT_EQ("t(X, 2)",it->currentItem()->symbol());
  it->next();
  EXPECT_EQ("Y",it->currentItem()->symbol());
  it->next();
  EXPECT_EQ("X",it->currentItem()->symbol());
  it->next();
  EXPECT_EQ("2",it->currentItem()->symbol());
  ASSERT_TRUE(it->isDone());
}

/*s( 1, t(v(X), 2), Y)
 except: 1 -> t -> Y -> v -> 2 ->X
*/
TEST(iterator, nestedStructBFSIterator){
  Number one(1);
  Number two(2);
  Variable X("X");
  Variable Y("Y");
  Struct v(Atom("v"),{&X});
  Struct t(Atom("t"), { &v, &two });
  Struct s(Atom("s"), { &one, &t, &Y });

  Iterator * it = s.createBFSIterator();
  it->first();
  EXPECT_EQ("1",it->currentItem()->symbol());
  it->next();
  EXPECT_EQ("t(v(X), 2)",it->currentItem()->symbol());
  it->next();
  EXPECT_EQ("Y",it->currentItem()->symbol());
  it->next();
  EXPECT_EQ("v(X)",it->currentItem()->symbol());
  it->next();
  EXPECT_EQ("2",it->currentItem()->symbol());
  it->next();
  EXPECT_EQ("X",it->currentItem()->symbol());
  ASSERT_TRUE(it->isDone());
}

/*s(1,t(X, 2),Y)
 except: 1 -> t -> X -> 2 -> Y
*/
TEST(iterator, structDFSIterator){
  Number one(1);
  Number two(2);
  Variable X("X");
  Variable Y("Y");
  Struct t(Atom("t"), { &X, &two });
  Struct s(Atom("s"), { &one, &t, &Y });

  Iterator * it = s.createDFSIterator();
  it->first();
  EXPECT_EQ("1",it->currentItem()->symbol());
  it->next();
  EXPECT_EQ("t(X, 2)",it->currentItem()->symbol());
  it->next();
  EXPECT_EQ("X",it->currentItem()->symbol());
  it->next();
  EXPECT_EQ("2",it->currentItem()->symbol());
  it->next();
  EXPECT_EQ("Y",it->currentItem()->symbol());
  ASSERT_TRUE(it->isDone());
}

/*s( 1, t(v(X), 2), Y)
 except: 1 -> t -> v -> X -> 2 ->Y
*/
TEST(iterator, nestedStructDFSIterator){
  Number one(1);
  Number two(2);
  Variable X("X");
  Variable Y("Y");
  Struct v(Atom("v"),{&X});
  Struct t(Atom("t"), { &v, &two });
  Struct s(Atom("s"), { &one, &t, &Y });

  Iterator * it = s.createDFSIterator();
  it->first();
  EXPECT_EQ("1",it->currentItem()->symbol());
  it->next();
  EXPECT_EQ("t(v(X), 2)",it->currentItem()->symbol());
  it->next();
  EXPECT_EQ("v(X)",it->currentItem()->symbol());
  it->next();
  EXPECT_EQ("X",it->currentItem()->symbol());
  it->next();
  EXPECT_EQ("2",it->currentItem()->symbol());
  it->next();
  EXPECT_EQ("Y",it->currentItem()->symbol());
  ASSERT_TRUE(it->isDone());
}

/*[1,t(X, 2),Y]
 except: 1 -> t -> Y -> X -> 2
*/
TEST(iterator, listBFSIterator){
  Number one(1);
  Number two(2);
  Variable X("X");
  Variable Y("Y");
  Struct t(Atom("t"), { &X, &two });
  List l({ &one, &t, &Y });

  Iterator * it = l.createBFSIterator();
  it->first();
  EXPECT_EQ("1",it->currentItem()->symbol());
  it->next();
  EXPECT_EQ("t(X, 2)",it->currentItem()->symbol());
  it->next();
  EXPECT_EQ("Y",it->currentItem()->symbol());
  it->next();
  EXPECT_EQ("X",it->currentItem()->symbol());
  it->next();
  EXPECT_EQ("2",it->currentItem()->symbol());
  ASSERT_TRUE(it->isDone());
}
/*[1,t(X),[Y,2]]
 except: 1 -> t -> [] -> X -> Y -> 2
*/
TEST(iterator, nestedListBFSIterator){
  Number one(1);
  Number two(2);
  Variable X("X");
  Variable Y("Y");
  Struct t(Atom("t"), { &X });
  List l0({&Y,&two});
  List l({ &one, &t, &l0 });

  Iterator * it = l.createBFSIterator();
  it->first();
  EXPECT_EQ("1",it->currentItem()->symbol());
  it->next();
  EXPECT_EQ("t(X)",it->currentItem()->symbol());
  it->next();
  EXPECT_EQ("[Y, 2]",it->currentItem()->symbol());
  it->next();
  EXPECT_EQ("X",it->currentItem()->symbol());
  it->next();
  EXPECT_EQ("Y",it->currentItem()->symbol());
  it->next();
  EXPECT_EQ("2",it->currentItem()->symbol());
  ASSERT_TRUE(it->isDone());
}
/*[1,t(X, 2),Y]
 except: 1 -> t -> Y -> X -> 2
*/
TEST(iterator, listDFSIterator){
  Number one(1);
  Number two(2);
  Variable X("X");
  Variable Y("Y");
  Struct t(Atom("t"), { &X, &two });
  List l({ &one, &t, &Y });

  Iterator * it = l.createDFSIterator();
  it->first();
  EXPECT_EQ("1",it->currentItem()->symbol());
  it->next();
  EXPECT_EQ("t(X, 2)",it->currentItem()->symbol());
  it->next();
  EXPECT_EQ("X",it->currentItem()->symbol());
  it->next();
  EXPECT_EQ("2",it->currentItem()->symbol());
  it->next();
  EXPECT_EQ("Y",it->currentItem()->symbol());
  ASSERT_TRUE(it->isDone());
}

/*[1,t(X),[Y,2]]
 except: 1 -> t -> X -> []-> Y -> 2
*/
TEST(iterator, nestedListDFSIterator){
  Number one(1);
  Number two(2);
  Variable X("X");
  Variable Y("Y");
  Struct t(Atom("t"), { &X });
  List l0({&Y,&two});
  List l({ &one, &t, &l0 });

  Iterator * it = l.createDFSIterator();
  it->first();
  EXPECT_EQ("1",it->currentItem()->symbol());
  it->next();
  EXPECT_EQ("t(X)",it->currentItem()->symbol());
  it->next();
  EXPECT_EQ("X",it->currentItem()->symbol());
  it->next();
  EXPECT_EQ("[Y, 2]",it->currentItem()->symbol());
  it->next();
  EXPECT_EQ("Y",it->currentItem()->symbol());
  it->next();
  EXPECT_EQ("2",it->currentItem()->symbol());
  ASSERT_TRUE(it->isDone());
}
#endif
