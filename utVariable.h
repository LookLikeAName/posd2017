#ifndef UTVARIABLE_H
#define UTVARIABLE_H

#include <gtest/gtest.h>
#include <vector>
#include "atom.h"
#include "number.h"
#include "struct.h"
#include "variable.h"
using std::vector;

TEST(Variable, constructor)
{
  Variable X("X");
  ASSERT_EQ("X", X.symbol());
}

TEST(Variable, matching)
{
  Atom tom("tom");
  Variable X("X");
  X.match(tom);
  ASSERT_EQ("tom", X.value());
}

TEST(Variable, haveValue)
{
  Atom tom("tom");
  Atom jerry("jerry");
  Variable X("X");
  ASSERT_TRUE(X.match(tom));
  ASSERT_FALSE(X.match(jerry));
}

// ?- X=2.7182.
// X=2.7182
TEST(Variable, numE_to_varX)
{
  Number E(2.7182);
  Variable X("X");
  ASSERT_TRUE(X.match(E));
  ASSERT_EQ(X.value(), "2.7182");
}

// ?- X=Y, X=1.
// Y=1
TEST(Variable, varY_to_varX_and_num1_to_varX)
{
  Variable X("X"), Y("Y");
  Number one(1);
  ASSERT_TRUE(X.match(Y));
  ASSERT_TRUE(X.match(one));
  ASSERT_EQ(Y.value(), "1");
}

// ?- X=Y, Y=1.
// X=1
TEST(Variable, varY_to_varX_and_num1_to_varY)
{
  Variable X("X"), Y("Y");
  Number one(1);
  ASSERT_TRUE(X.match(Y));
  ASSERT_TRUE(Y.match(one));
  ASSERT_EQ(X.value(), "1");
}

// ?- X=X, X=1.
// X=1
TEST(Variable, varX_match_varX_and_num1_to_varX)
{
  Variable X("X");
  Number one(1);
  ASSERT_TRUE(X.match(X));
  ASSERT_TRUE(X.match(one));
  ASSERT_EQ(X.value(), "1");
}

// ?- Y=1, X=Y.
// X=1
TEST(Variable, num1_to_varY_and_varX_match_varY)
{
  Variable X("X"), Y("Y");
  Number one(1);
  ASSERT_TRUE(Y.match(one));
  ASSERT_TRUE(X.match(Y));
  ASSERT_EQ(X.value(), "1");
}

// ?- Y=1, Y=X.
// X=1
TEST(Variable, num1_to_varY_and_varX_match_varY2)
{
  Variable X("X"), Y("Y");
  Number one(1);
  ASSERT_TRUE(Y.match(one));
  ASSERT_TRUE(Y.match(X));
  ASSERT_EQ(X.value(), "1");
}

// ?- X=Y, Y=Z, Z=1
// X=1, Y=1, Z=1
TEST(Variable, num1_to_varZ_to_varY_to_varX)
{
  Variable X("X"), Y("Y"), Z("Z");
  Number one(1);
  ASSERT_TRUE(X.match(Y));
  ASSERT_TRUE(Y.match(Z));
  ASSERT_TRUE(Z.match(one));
  ASSERT_EQ(X.value(), "1");
  ASSERT_EQ(Y.value(), "1");
  ASSERT_EQ(Z.value(), "1");
}

// ?- X=Y, X=Z, Z=1
// X=1, Y=1, Z=1
TEST(Variable, num1_to_varZ_to_varX_and_varY_to_varX)
{
  Variable X("X"), Y("Y"), Z("Z");
  Number one(1);
  ASSERT_TRUE(X.match(Y));
  ASSERT_TRUE(X.match(Z));
  ASSERT_TRUE(Z.match(one));
  ASSERT_EQ(X.value(), "1");
  ASSERT_EQ(Y.value(), "1");
  ASSERT_EQ(Z.value(), "1");
}

// Give there is a Struct s contains Variable X
// And another Variable Y
// When Y matches Struct s
// Then #symbol() of Y should return "Y"
// And #value() of Y should return "s(X)"
TEST(Variable, Struct1)
{
  Variable X("X"), Y("Y");
  Struct s(Atom("s"), vector<Term *>{&X});
  EXPECT_TRUE(Y.match(s));
  EXPECT_EQ(Y.symbol(), "Y");
  EXPECT_EQ(Y.value(), "s(X)");
}

// Give there is a Struct s contains Variable X
// And another Variable Y
// When Y matches Struct s
// And X matches Atom "teddy"
// Then #symbol() of Y should return "Y"
// And #value() of Y should return "s(teddy)"
TEST(Variable, Struct2)
{
  Variable X("X"), Y("Y");
  Struct s(Atom("s"), vector<Term *>{&X});
  Atom teddy("teddy");
  EXPECT_TRUE(Y.match(s));
  EXPECT_TRUE(X.match(teddy));
  EXPECT_EQ(Y.symbol(), "Y");
  EXPECT_EQ(Y.value(), "s(teddy)");
}

#endif