#ifndef UTTERM_H
#define UTTERM_H


#define numberDebug 1
#define AtomDebug 1
#define varDebug 1


#include "atom.h"
#include "variable.h"
#include "number.h"

#if numberDebug
//test Number.value()
TEST (Number,ctor) {
  Number Number("Number","25");
  ASSERT_EQ("25", Number.value());
}
//test Number.symbol()
TEST (Number, symbol) {
  Number Number("Number","25");
  ASSERT_EQ("Number", Number.symbol());
}
//?- 25=25.
//true.
TEST (Number, matchSuccess) {
  Number Number0("Number0","25");
  Number Number1("Number1","25");
  ASSERT_TRUE(Number0.match(Number1));
}
//?- 25=0.
//false.
TEST (Number, matchFailureDiffValue) {
  Number Number0("Number0","25");
  Number Number1("Number1","0");
  ASSERT_FALSE(Number0.match(Number1));
}
//?- 25=tom.
//false.
TEST (Number, matchFailureDiffConstant) {
  Number Number0("Number0","25");
  Atom   tom("tom");
  ASSERT_FALSE(Number0.match(tom));
}
//?- 25=X.
//true.
TEST (Number, matchSuccessToVar) {
  Number Number0("Number0","25");
  Variable X("X");
  ASSERT_TRUE(Number0.match(X));
 //EXPECT_EQ("25",X.value());
}
#endif

#if AtomDebug
//?- tom=25.
//false.
TEST (Atom, matchFailureDiffConstant) {
Atom tom("tom");
Number Number0("Number0","25");
ASSERT_FALSE(tom.match(Number0));
}

// ?- tom = X.
// X = tom.
TEST (Atom, matchSuccessToVar) {
  Atom tom("tom");
  Variable X("X");
  X.match(tom);
  ASSERT_EQ( "tom", X.value());
}

// ?- X=tom, tom=X.
// X = tom.
TEST (Atom, matchSuccessToVarInstantedToDiffConstant) {
 Atom tom("tom");
  Variable X("X");
  X.match(tom);
  tom.match(X);
  ASSERT_EQ( "tom", X.value());
}

// ?- X=jerry, tom=X.
// false.
TEST (Atom, matchFailureToVarInstantedToDiffConstant) {
 Atom tom ("tom");
 Atom jerry ("jerry");
 Variable X("X");
 X.match(tom);
 ASSERT_FALSE(X.match(jerry));
}
#endif

#if varDebug
// ?- X = 5.
// X = 5.
TEST (Var, matchSuccessToNumber) {
 Variable X("X");
 Number Number0("Number0","5");
 X.match(Number0);
 ASSERT_EQ( "5", X.value());
}

// ?- X=25, X= 100.
// false.
TEST (Var, matchFailureToTwoDiffNumbers) {
 Number Number0("Number0","25");
 Number Number1("Number1","100");
 Variable X("X");
 X.match(Number0);
 ASSERT_FALSE(X.match(Number1));
}

// ?- X=tom, X= 25.
// false.
TEST (Var, matchSuccessToAtomThenFailureToNumber) {
  Atom tom("tom");
  Number Number0("Number0","25");
  Variable X("X");
  X.match(tom);
  ASSERT_FALSE(X.match(Number0));
}
//?- tom=X, 25=X.
//false.          ****can't figure out how to done this without passing by reference****
TEST (Var, matchSuccessToAtomThenFailureToNumber2) {
  Atom tom("tom");
  Number Number0("Number0","25");
  Variable X("X");
  EXPECT_TRUE(tom.match(X));
  EXPECT_EQ("tom",X.value());
  ASSERT_FALSE(Number0.match(X));
}
//?- X=tom, X=tom.
//true.
TEST(Var, reAssignTheSameAtom){
Variable X("X");
Atom tom("tom");
X.match(tom);
ASSERT_TRUE(X.match(tom));
}
#endif

#endif