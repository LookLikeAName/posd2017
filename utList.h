#ifndef UTLIST_H
#define UTLIST_H

#include "atom.h"
#include "list.h"
#include "number.h"
#include "struct.h"
#include "variable.h"

#include <gtest/gtest.h>
#include <string>
using std::string;

// When create a new list without any item
// Then #symbol() of the list should return "[]"
TEST(List, constructor)
{
  List l;
  EXPECT_EQ("[]", l.symbol());
}

// Given there are two perfect Numbers: 8128, 496
// When create a new list with the perfect Number
// Then #symbol() of the list should return "[496, 8128]"
TEST(List, Numbers)
{
  Number n1(496), n2(8128);
  List l(vector<Term *>{&n1, &n2});
  EXPECT_EQ("[496, 8128]", l.symbol());
}

// Given there are two atoms: "terence_tao", "alan_mathison_turing"
// When create a new list with the Atoms
// Then #symbol() of the list should return "[terence_tao,
// alan_mathison_turing]"
TEST(List, Atoms)
{
  Atom a1("terence_tao"), a2("alan_mathison_turing");
  List l(vector<Term *>{&a1, &a2});
  EXPECT_EQ("[terence_tao, alan_mathison_turing]", l.symbol());
}

// Given there are two variables: X, Y
// When create a new list with the variables
// Then #symbol() of the list should return "[X, Y]"
TEST(List, Vars)
{
  Variable X("X"), Y("Y");
  List l(vector<Term *>{&X, &Y});
  EXPECT_EQ("[X, Y]", l.symbol());
}

// ?- tom = [496, X, terence_tao].
// false.
TEST(List, matchToAtomShouldFail)
{
  Atom tom("tom"), terence_tao("terence_tao");
  Number n(496);
  Variable X("X");
  List l(vector<Term *>{&n, &X, &terence_tao});
  EXPECT_FALSE(tom.match(l));
}

// ?- 8128 = [496, X, terence_tao].
// false.
TEST(List, matchToNumberShouldFail)
{
  Atom terence_tao("terence_tao");
  Number n1(8128), n2(496);
  Variable X("X");
  List l(vector<Term *>{&n2, &X, &terence_tao});
  EXPECT_FALSE(n1.match(l));
}

// ?- s(X) = [496, X, terence_tao].
// false.
TEST(List, matchToStructShouldFail)
{
  Atom terence_tao("terence_tao");
  Number n(496);
  Variable X("X");
  Struct s(Atom("s"), vector<Term *>{&X});
  List l(vector<Term *>{&n, &X, &terence_tao});
  EXPECT_FALSE(s.match(l));
}

// ?- Y = [496, X, terence_tao].
// Y = [496, X, terence_tao].
TEST(List, matchToVarShouldSucceed)
{
  Atom terence_tao("terence_tao");
  Number n(496);
  Variable X("X"), Y("Y");
  List l(vector<Term *>{&n, &X, &terence_tao});
  EXPECT_TRUE(Y.match(l));
  EXPECT_TRUE(l.match(Y));
  EXPECT_EQ("[496, X, terence_tao]", Y.value());
}

// ?- X = [496, X, terence_tao].
// false.
TEST(List, matchToVarOccuredInListShouldFail)
{
  Atom terence_tao("terence_tao");
  Number n(496);
  Variable X("X");
  List l(vector<Term *>{&n, &X, &terence_tao});
  EXPECT_FALSE(l.match(X));
  EXPECT_FALSE(X.match(l));
}

// ?- [496, X, terence_tao] = [496, X, terence_tao].
// true.
TEST(List, matchToSameListShouldSucceed)
{
  Atom terence_tao("terence_tao");
  Number n(496);
  Variable X("X");
  List l(vector<Term *>{&n, &X, &terence_tao});
  EXPECT_TRUE(l.match(l));
}

// ?- [496, X, terence_tao] = [496, Y, terence_tao].
// true.
TEST(List, matchToSameListWithDiffVarNameShouldSucceed)
{
  Atom terence_tao("terence_tao");
  Number n(496);
  Variable X("X"), Y("Y");
  List l1(vector<Term *>{&n, &X, &terence_tao}),
      l2(vector<Term *>{&n, &Y, &terence_tao});
  EXPECT_TRUE(l1.match(l2));
}

// ?- [496, X, terence_tao] = [496, 8128, terence_tao].
// X = 8128.
TEST(List, matchToVarToAtominListShouldSucceed)
{
  Atom terence_tao("terence_tao");
  Number n(496), n2(8128);
  Variable X("X");
  List l1(vector<Term *>{&n, &X, &terence_tao}),
      l2(vector<Term *>{&n, &n2, &terence_tao});
  EXPECT_TRUE(l1.match(l2));
  EXPECT_EQ("8128", X.value());
}

// ?- Y = [496, X, terence_tao], X = alan_mathison_turing.
// Y = [496, alan_mathison_turing, terence_tao],
// X = alan_mathison_turing.
TEST(List, matchVarinListToAtomShouldSucceed)
{
  Number n(496);
  Atom a1("terence_tao"), a2("alan_mathison_turing");
  Variable X("X"), Y("Y");
  List l(vector<Term *>{&n, &X, &a1});
  EXPECT_TRUE(Y.match(l));
  EXPECT_EQ("[496, X, terence_tao]", Y.value());
  EXPECT_TRUE(X.match(a2));
  EXPECT_EQ("[496, alan_mathison_turing, terence_tao]", Y.value());
  EXPECT_EQ("alan_mathison_turing", X.value());
}

// Example:
// ?- [first, second, third] = [H|T].
// H = first, T = [second, third].
TEST(List, headAndTailMatching1)
{
  Atom f("first"), s("second"), t("third");
  vector<Term *> args = {&f, &s, &t};
  List l(args);

  EXPECT_EQ(string("first"), l.head()->value());
  EXPECT_EQ(string("[second, third]"), l.tail()->value());
}

// Example:
// ?- [first, second, third] = [first, H|T].
// H = second, T = [third].
TEST(List, headAndTailMatching2)
{
  Atom f("first"), s("second"), t("third");
  vector<Term *> args = {&f, &s, &t};
  List l(args);

  EXPECT_EQ(string("second"), l.tail()->head()->value());
  EXPECT_EQ(string("[third]"), l.tail()->tail()->value());
}

// ?- [[first], second, third] = [H|T].
// H = [first], T = [second, third].
TEST(List, headAndTailMatching3)
{
  Atom f("first"), s("second"), t("third");
  List l1(vector<Term *>{&f}), l2(vector<Term *>{&l1, &s, &t});
  EXPECT_EQ("[first]", l2.head()->symbol());
  EXPECT_EQ("[second, third]", l2.tail()->symbol());
}

// ?- [first, second, third] = [first, second, H|T].
// H = third, T = [].
TEST(List, headAndTailMatching4)
{
  Atom f("first"), s("second"), t("third");
  List l(vector<Term *>{&f, &s, &t});
  EXPECT_EQ("third", l.tail()->tail()->head()->value());
  EXPECT_EQ("[]", l.tail()->tail()->tail()->value());
}

// Given there is a empty list
// When client still want to get the head of list
// Then it should throw a string: "Accessing head in an empty list" as an
// exception.
TEST(List, emptyExecptionOfHead)
{
  List l(vector<Term *>{});
  try
  {
    l.head();
  }
  catch (string e)
  {
    EXPECT_EQ("Accessing head in an empty list", e);
  }
}

// Given there is a empty list
// When client still want to get the head of list
// Then it should throw a string: "Accessing tail in an empty list" as an
// exception.
TEST(List, emptyExecptionOfTail)
{
  List l(vector<Term *>{});
  try
  {
    l.tail();
  }
  catch (string e)
  {
    EXPECT_EQ("Accessing tail in an empty list", e);
  }
}

#endif
