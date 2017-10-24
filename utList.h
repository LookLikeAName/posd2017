#ifndef UTLIST_H
#define UTLIST_H

#include <string>
using std::string;
#include <vector>
using std::vector;

#include "list.h"
#include "struct.h"
#include "atom.h"
#include "number.h"
#include "variable.h"

#define debugConstruct 1
#define debugMatch 1
#define debugHT 1

#if debugConstruct

// When create a new list without any item
// Then #symbol() of the list should return "[]"
TEST (List, constructor) {
  List l;
  ASSERT_EQ("[]",l.symbol());
}

// Given there are two perfect Numbers: 8128, 496
// When create a new list with the perfect Number
// Then #symbol() of the list should return "[8128,496]"
TEST(List, Numbers) {
  Number num1(8128), num2(496);
  vector<Term *> args = {&num1, &num2};
  List l(args);
  ASSERT_EQ("[8128, 496]",l.symbol());
}

// Given there are two atoms: "terence_tao", "alan_mathison_turing"
// When create a new list with the Atoms
// Then #symbol() of the list should return "[terence_tao, alan_mathison_turing]"
TEST(List, Atoms) {
  Atom terence_tao("terence_tao"), alan_mathison_turing("alan_mathison_turing");
  vector<Term *> args = {&terence_tao, &alan_mathison_turing};
  List l(args);
  ASSERT_EQ("[terence_tao, alan_mathison_turing]",l.symbol());
}

// Given there are two variables: X, Y
// When create a new list with the variables
// Then #symbol() of the list should return "[X, Y]"
TEST(List, Vars) {
  Variable X("X"), Y("Y");
  vector<Term *> args = {&X, &Y};
  List l(args);
  ASSERT_EQ("[X, Y]",l.symbol());
}

#endif

#if debugMatch
// ?- tom = [496, X, terence_tao].
// false.
TEST(List, matchToAtomShouldFail) {
Atom tom("tom") ,terence_tao("terence_tao");
Number num(496);
Variable X("X");
vector<Term *> args = {&num, &X, &terence_tao};
List l(args);
ASSERT_FALSE(tom.match(l));
}

// ?- 8128 = [496, X, terence_tao].
// false.
TEST(List, matchToNumberShouldFail) {
  Atom terence_tao("terence_tao");
  Number num1(496),num2(8128);
  Variable X("X");
  vector<Term *> args = {&num1, &X, &terence_tao};
  List l(args);
  ASSERT_FALSE(num2.match(l));
}

// ?- s(X) = [496, X, terence_tao].
// false.
TEST(List, matchToStructShouldFail) {
  Variable X("X");
  vector<Term *> v = {&X};
  Struct s(Atom("s"), v);

  Atom terence_tao("terence_tao");
  Number num1(496);
  vector<Term *> args = {&num1, &X, &terence_tao};
  List l(args);

  ASSERT_FALSE(s.match(l));
}

// ?- Y = [496, X, terence_tao].
// Y = [496, X, terence_tao].
TEST(List, matchToVarShouldSucceed) {
  Variable Y("Y");
  Atom terence_tao("terence_tao");
  Number num1(496);
  Variable X("X");
  vector<Term *> args = {&num1, &X, &terence_tao};
  List l(args);
  Y.match(l);
  ASSERT_EQ("[496, X, terence_tao]",Y.value());
}

// ?- X = [496, X, terence_tao].
// false.
TEST(List, matchToVarOccuredInListShouldFail) {
  Atom terence_tao("terence_tao");
  Number num1(496);
  Variable X("X");
  vector<Term *> args = {&num1, &X, &terence_tao};
  List l(args);

  ASSERT_FALSE(X.match(l));
}

// ?- [496, X, terence_tao] = [496, X, terence_tao].
// true.
TEST(List, matchToSameListShouldSucceed) {
  Atom terence_tao("terence_tao");
  Number num1(496);
  Variable X("X");
  vector<Term *> args = {&num1, &X, &terence_tao};
  List l(args);
  ASSERT_TRUE(l.match(l));
}

// ?- [496, X, terence_tao] = [496, Y, terence_tao].
// true.
TEST(List, matchToSameListWithDiffVarNameShouldSucceed) {
  Atom terence_tao("terence_tao");
  Number num1(496);
  Variable X("X"),Y("Y");
  vector<Term *> args0 = {&num1, &X, &terence_tao};
  List l1(args0);
  vector<Term *> args1 = {&num1, &Y, &terence_tao};
  List l2(args1);
  ASSERT_TRUE(l1.match(l2));
}

// ?- [496, X, terence_tao] = [496, 8128, terence_tao].
// X = 8128.
TEST(List, matchToVarToAtominListShouldSucceed) {
  Atom terence_tao("terence_tao");
  Number num1(496),num2(8128);
  Variable X("X");
  vector<Term *> args0 = {&num1, &X, &terence_tao};
  List l1(args0);
  vector<Term *> args1 = {&num1, &num2, &terence_tao};
  List l2(args1);
  l1.match(l2);
  ASSERT_EQ("8128",X.value());
}

// ?- Y = [496, X, terence_tao], X = alan_mathison_turing.
// Y = [496, alan_mathison_turing, terence_tao],
// X = alan_mathison_turing.
TEST(List, matchVarinListToAtomShouldSucceed) {
  Variable Y("Y");
  Atom terence_tao("terence_tao"),alan_mathison_turing("alan_mathison_turing");
  Number num1(496);
  Variable X("X");
  vector<Term *> args = {&num1, &X, &terence_tao};
  List l(args);
  Y.match(l);
  X.match(alan_mathison_turing);
  EXPECT_EQ("[496, alan_mathison_turing, terence_tao]",Y.value());
  ASSERT_EQ("alan_mathison_turing",X.value());
}
#endif

#if debugHT
// Example: 
// ?- [first, second, third] = [H|T].
// H = first, T = [second, third].
TEST(List, headAndTailMatching1) {
  Atom f("first"), s("second"), t("third");
  vector<Term *> args = {&f, &s, &t};
  List l(args);

  EXPECT_EQ(string("first"), l.head()->symbol());
  EXPECT_EQ(string("[second, third]"), l.tail()->value());
}

// Example:
// ?- [first, second, third] = [first, H|T].
// H = second, T = [third].
TEST(List, headAndTailMatching2) {
  Atom f("first"), s("second"), t("third");
  vector<Term *> args = {&f, &s, &t};
  List l(args);

  EXPECT_EQ(string("second"), l.tail()->head()->value());
  EXPECT_EQ(string("[third]"), l.tail()->tail()->value());
}

// ?- [[first], second, third] = [H|T].
// H = [first], T = [second, third].
TEST(List, headAndTailMatching3) {
  Atom f("first"), s("second"), t("third");
  vector<Term *> args0 = {&f};
  List l1(args0);
  vector<Term *> args1 = {&l1, &s, &t};
  List l2(args1);

  EXPECT_EQ(string("[first]"), l2.head()->value());
  EXPECT_EQ(string("[second, third]"), l2.tail()->value());
}

// ?- [first, second, third] = [first, second, H|T].
// H = third, T = [].
TEST(List, headAndTailMatching4) {
  Atom f("first"), s("second"), t("third");
  vector<Term *> args = {&f, &s, &t};
  List l(args);

  EXPECT_EQ(string("third"), l.tail()->tail()->head()->value());
  EXPECT_EQ(string("[]"), l.tail()->tail()->tail()->value());
}
 
// Given there is a empty list
// When client still want to get the head of list
// Then it should throw a string: "Accessing head in an empty list" as an exception.
TEST (List, emptyExecptionOfHead) {
  List l;
  ASSERT_EQ("Accessing head in an empty list",l.head()->value());
}

// Given there is a empty list
// When client still want to get the head of list
// Then it should throw a string: "Accessing tail in an empty list" as an exception.
TEST (List, emptyExecptionOfTail) {
  List l;
  ASSERT_EQ("Accessing tail in an empty list",l.tail()->value());
}
#endif



#endif
