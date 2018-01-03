#ifndef UTITERATOR_H
#define UTITERATOR_H

#include <gtest/gtest.h>
#include "atom.h"
#include "iterator.h"
#include "number.h"
#include "variable.h"

// 1
TEST(Iterator, nullIterator)
{
  Number one(1);
  Iterator<Term *> *itr = one.createIterator();
  EXPECT_EQ("1", itr->currentTerm()->symbol());
  EXPECT_TRUE(itr->isDone());
}

// s(1, t(X, 2), Y)
TEST(Iterator, structIterator)
{
  Number one(1), two(2);
  Variable X("X"), Y("Y");
  Struct t(Atom("t"), {&X, &two});
  Struct s(Atom("s"), {&one, &t, &Y});

  Iterator<Term *> *itr = s.createIterator();
  EXPECT_EQ("1", itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_EQ("t(X, 2)", itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_EQ("Y", itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_TRUE(itr->isDone());

  itr->next();
  EXPECT_TRUE(itr->isDone());
}

// s(1, t(X, 2), Y)
TEST(Iterator, nestedStructIterator)
{
  Number one(1), two(2);
  Variable X("X"), Y("Y");
  Struct t(Atom("t"), {&X, &two});
  Struct s(Atom("s"), {&one, &t, &Y});

  Iterator<Term *> *itr = s.createIterator();
  itr->next();
  Struct *s2 = dynamic_cast<Struct *>(itr->currentItem());
  Iterator<Term *> *itr2 = s2->createIterator();

  EXPECT_EQ("X", itr2->currentItem()->symbol());
  EXPECT_FALSE(itr2->isDone());

  itr2->next();
  EXPECT_EQ("2", itr2->currentItem()->symbol());
  EXPECT_FALSE(itr2->isDone());

  itr2->next();
  EXPECT_TRUE(itr2->isDone());
}

//[1, t(X, 2), Y]
TEST(Iterator, listIterator)
{
  Number one(1), two(2);
  Variable X("X"), Y("Y");
  Struct t(Atom("t"), {&X, &two});
  List l({&one, &t, &Y});

  Iterator<Term *> *itr = l.createIterator();

  EXPECT_EQ("1", itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_EQ("t(X, 2)", itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_EQ("Y", itr->currentItem()->symbol());

  itr->next();
  EXPECT_TRUE(itr->isDone());

  itr->next();
  EXPECT_TRUE(itr->isDone());
}

// s(1, t(2, 3), X, [a, b], 4, Y)
TEST(DFSIterator, DFSStructIterator)
{
  Atom a("a"), b("b");
  Number one(1), two(2), three(3), four(4);
  Variable X("X"), Y("Y");
  Struct t(Atom("t"), {&two, &three});
  List l({&a, &b});
  Struct s(Atom("s"), {&one, &t, &X, &l, &four, &Y});

  Iterator<Term *> *itr = s.createDFSIterator();
  EXPECT_EQ("1", itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_EQ("t(2, 3)", itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_EQ("2", itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_EQ("3", itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_EQ("X", itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_EQ("[a, b]", itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_EQ("a", itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_EQ("b", itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_EQ("4", itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_EQ("Y", itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_TRUE(itr->isDone());

  itr->next();
  EXPECT_TRUE(itr->isDone());
}

// combo1(bigMac(bun, beefPatty, shreddedLettuce, sauce, cheese, [pickleSlice1,
// pickleSlice2], [onions1, onions2]), coke, [fries1, fries2])
TEST(DFSIterator, DFSBigMacStructIterator)
{
  Atom bun("bun"), beefPatty("beefPatty"), shreddedLettuce("shreddedLettuce"),
      sauce("sauce"), cheese("cheese"), pickleSlice1("pickleSlice1"),
      pickleSlice2("pickleSlice2"), onions1("onions1"), onions2("onions2"),
      coke("coke"), fries1("fries1"), fries2("fries2");
  List pickleSlice({&pickleSlice1, &pickleSlice2});
  List onions({&onions1, &onions2});
  Struct bigMac(Atom("bigMac"), {&bun, &beefPatty, &shreddedLettuce, &sauce,
                                 &cheese, &pickleSlice, &onions});
  List fries({&fries1, &fries2});
  Struct combo1(Atom("Combo1"), {&bigMac, &coke, &fries});

  Iterator<Term *> *itr = combo1.createDFSIterator();
  EXPECT_EQ(
      "bigMac(bun, beefPatty, shreddedLettuce, sauce, cheese, [pickleSlice1, "
      "pickleSlice2], [onions1, onions2])",
      itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_EQ("bun", itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_EQ("beefPatty", itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_EQ("shreddedLettuce", itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_EQ("sauce", itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_EQ("cheese", itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_EQ("[pickleSlice1, pickleSlice2]", itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_EQ("pickleSlice1", itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_EQ("pickleSlice2", itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_EQ("[onions1, onions2]", itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_EQ("onions1", itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_EQ("onions2", itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_EQ("coke", itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_EQ("[fries1, fries2]", itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_EQ("fries1", itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_EQ("fries2", itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_TRUE(itr->isDone());

  itr->next();
  EXPECT_TRUE(itr->isDone());
}

//[1, t(2, 3), X, [a, b], 4, Y]
TEST(DFSIterator, DFSListIterator)
{
  Atom a("a"), b("b");
  Number one(1), two(2), three(3), four(4);
  Variable X("X"), Y("Y");
  Struct t(Atom("t"), {&two, &three});
  List l({&a, &b});
  List l2({&one, &t, &X, &l, &four, &Y});

  Iterator<Term *> *itr = l2.createDFSIterator();
  EXPECT_EQ("1", itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_EQ("t(2, 3)", itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_EQ("2", itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_EQ("3", itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_EQ("X", itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_EQ("[a, b]", itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_EQ("a", itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_EQ("b", itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_EQ("4", itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_EQ("Y", itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_TRUE(itr->isDone());

  itr->next();
  EXPECT_TRUE(itr->isDone());
}

//[bigMac(bun, beefPatty, shreddedLettuce, sauce, cheese, [pickleSlice1,
//pickleSlice2], [onions1, onions2]), coke, [fries1, fries2]]
TEST(DFSIterator, DFSBigMacListIterator)
{
  Atom bun("bun"), beefPatty("beefPatty"), shreddedLettuce("shreddedLettuce"),
      sauce("sauce"), cheese("cheese"), pickleSlice1("pickleSlice1"),
      pickleSlice2("pickleSlice2"), onions1("onions1"), onions2("onions2"),
      coke("coke"), fries1("fries1"), fries2("fries2");
  List pickleSlice({&pickleSlice1, &pickleSlice2});
  List onions({&onions1, &onions2});
  Struct bigMac(Atom("bigMac"), {&bun, &beefPatty, &shreddedLettuce, &sauce,
                                 &cheese, &pickleSlice, &onions});
  List fries({&fries1, &fries2});
  List combo1({&bigMac, &coke, &fries});

  Iterator<Term *> *itr = combo1.createDFSIterator();
  EXPECT_EQ(
      "bigMac(bun, beefPatty, shreddedLettuce, sauce, cheese, [pickleSlice1, "
      "pickleSlice2], [onions1, onions2])",
      itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_EQ("bun", itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_EQ("beefPatty", itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_EQ("shreddedLettuce", itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_EQ("sauce", itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_EQ("cheese", itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_EQ("[pickleSlice1, pickleSlice2]", itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_EQ("pickleSlice1", itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_EQ("pickleSlice2", itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_EQ("[onions1, onions2]", itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_EQ("onions1", itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_EQ("onions2", itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_EQ("coke", itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_EQ("[fries1, fries2]", itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_EQ("fries1", itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_EQ("fries2", itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_TRUE(itr->isDone());

  itr->next();
  EXPECT_TRUE(itr->isDone());
}

// s(1, t(2, 3), X, [a, b], 4, Y)
TEST(BFSIterator, BFSStructIterator)
{
  Atom a("a"), b("b");
  Number one(1), two(2), three(3), four(4);
  Variable X("X"), Y("Y");
  Struct t(Atom("t"), {&two, &three});
  List l({&a, &b});
  Struct s(Atom("s"), {&one, &t, &X, &l, &four, &Y});

  Iterator<Term *> *itr = s.createBFSIterator();
  EXPECT_EQ("1", itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_EQ("t(2, 3)", itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_EQ("X", itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_EQ("[a, b]", itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_EQ("4", itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_EQ("Y", itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_EQ("2", itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_EQ("3", itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_EQ("a", itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_EQ("b", itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_TRUE(itr->isDone());

  itr->next();
  EXPECT_TRUE(itr->isDone());
}

// combo1(bigMac(bun, beefPatty, shreddedLettuce, sauce, cheese, [pickleSlice1,
// pickleSlice2], [onions1, onions2]), coke, [fries1, fries2])
TEST(BFSIterator, BFSBigMacStructIterator)
{
  Atom bun("bun"), beefPatty("beefPatty"), shreddedLettuce("shreddedLettuce"),
      sauce("sauce"), cheese("cheese"), pickleSlice1("pickleSlice1"),
      pickleSlice2("pickleSlice2"), onions1("onions1"), onions2("onions2"),
      coke("coke"), fries1("fries1"), fries2("fries2");
  List pickleSlice({&pickleSlice1, &pickleSlice2});
  List onions({&onions1, &onions2});
  Struct bigMac(Atom("bigMac"), {&bun, &beefPatty, &shreddedLettuce, &sauce,
                                 &cheese, &pickleSlice, &onions});
  List fries({&fries1, &fries2});
  Struct combo1(Atom("Combo1"), {&bigMac, &coke, &fries});

  Iterator<Term *> *itr = combo1.createBFSIterator();
  EXPECT_EQ(
      "bigMac(bun, beefPatty, shreddedLettuce, sauce, cheese, [pickleSlice1, "
      "pickleSlice2], [onions1, onions2])",
      itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_EQ("coke", itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_EQ("[fries1, fries2]", itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_EQ("bun", itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_EQ("beefPatty", itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_EQ("shreddedLettuce", itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_EQ("sauce", itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_EQ("cheese", itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_EQ("[pickleSlice1, pickleSlice2]", itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_EQ("[onions1, onions2]", itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_EQ("fries1", itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_EQ("fries2", itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_EQ("pickleSlice1", itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_EQ("pickleSlice2", itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_EQ("onions1", itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_EQ("onions2", itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_TRUE(itr->isDone());

  itr->next();
  EXPECT_TRUE(itr->isDone());
}

//[1, t(2, 3), X, [a, b], 4, Y]
TEST(BFSIterator, BFSListIterator)
{
  Atom a("a"), b("b");
  Number one(1), two(2), three(3), four(4);
  Variable X("X"), Y("Y");
  Struct t(Atom("t"), {&two, &three});
  List l({&a, &b});
  List l2({&one, &t, &X, &l, &four, &Y});

  Iterator<Term *> *itr = l2.createBFSIterator();
  EXPECT_EQ("1", itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_EQ("t(2, 3)", itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_EQ("X", itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_EQ("[a, b]", itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_EQ("4", itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_EQ("Y", itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_EQ("2", itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_EQ("3", itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_EQ("a", itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_EQ("b", itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_TRUE(itr->isDone());

  itr->next();
  EXPECT_TRUE(itr->isDone());
}

//[bigMac(bun, beefPatty, shreddedLettuce, sauce, cheese, [pickleSlice1,
//pickleSlice2], [onions1, onions2]), coke, [fries1, fries2]]
TEST(BFSIterator, BFSBigMacListIterator)
{
  Atom bun("bun"), beefPatty("beefPatty"), shreddedLettuce("shreddedLettuce"),
      sauce("sauce"), cheese("cheese"), pickleSlice1("pickleSlice1"),
      pickleSlice2("pickleSlice2"), onions1("onions1"), onions2("onions2"),
      coke("coke"), fries1("fries1"), fries2("fries2");
  List pickleSlice({&pickleSlice1, &pickleSlice2});
  List onions({&onions1, &onions2});
  Struct bigMac(Atom("bigMac"), {&bun, &beefPatty, &shreddedLettuce, &sauce,
                                 &cheese, &pickleSlice, &onions});
  List fries({&fries1, &fries2});
  List combo1({&bigMac, &coke, &fries});

  Iterator<Term *> *itr = combo1.createBFSIterator();
  EXPECT_EQ(
      "bigMac(bun, beefPatty, shreddedLettuce, sauce, cheese, [pickleSlice1, "
      "pickleSlice2], [onions1, onions2])",
      itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_EQ("coke", itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_EQ("[fries1, fries2]", itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_EQ("bun", itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_EQ("beefPatty", itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_EQ("shreddedLettuce", itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_EQ("sauce", itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_EQ("cheese", itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_EQ("[pickleSlice1, pickleSlice2]", itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_EQ("[onions1, onions2]", itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_EQ("fries1", itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_EQ("fries2", itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_EQ("pickleSlice1", itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_EQ("pickleSlice2", itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_EQ("onions1", itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_EQ("onions2", itr->currentItem()->symbol());
  EXPECT_FALSE(itr->isDone());

  itr->next();
  EXPECT_TRUE(itr->isDone());

  itr->next();
  EXPECT_TRUE(itr->isDone());
}

#endif