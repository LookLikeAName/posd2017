#ifndef UTSTRUCT_H
#define UTSTRUCT_H

#include <gtest/gtest.h>
#include <vector>
#include "atom.h"
#include "number.h"
#include "struct.h"
#include "term.h"
#include "variable.h"
using std::vector;

TEST(Struct, hobby)
{
  Atom tom("tom");
  Atom chaseMouse("chaseMouse");
  vector<Term *> v = {&tom, &chaseMouse};
  Struct hobby(Atom("hobby"), v);
  ASSERT_EQ("hobby", hobby.name().symbol());
  ASSERT_EQ("tom", hobby.args(0)->symbol());
  ASSERT_EQ("chaseMouse", hobby.args(1)->symbol());
}

TEST(Struct, symbol)
{
  Atom tom("tom");
  Atom chaseMouse("chaseMouse");
  vector<Term *> v = {&tom, &chaseMouse};
  Struct hobby(Atom("hobby"), v);
  ASSERT_EQ("hobby(tom, chaseMouse)", hobby.symbol());
}

TEST(Struct, match1)
{
  Atom tom("tom");
  Atom chaseMouse("chaseMouse");
  vector<Term *> v = {&tom, &chaseMouse};
  Struct hobby(Atom("hobby"), v);
  Struct hobby2(Atom("hobby2"), v);
  EXPECT_FALSE(hobby.match(hobby2));
}

TEST(Struct, match2)
{
  Atom tom("tom");
  Atom chaseMouse("chaseMouse");
  vector<Term *> v = {&tom, &chaseMouse};
  Struct hobby(Atom("hobby"), v);
  vector<Term *> v1 = {&tom};
  Struct hobby2(Atom("hobby"), v1);
  EXPECT_FALSE(hobby.match(hobby2));
}

TEST(Struct, match3)
{
  Atom tom("tom");
  Atom chaseMouse("chaseMouse");
  vector<Term *> v = {&tom, &chaseMouse};
  Struct hobby(Atom("hobby"), v);
  vector<Term *> v1 = {&chaseMouse, &tom};
  Struct hobby2(Atom("hobby"), v1);
  EXPECT_FALSE(hobby.match(hobby2));
}

TEST(Struct, match4)
{
  Atom tom("tom");
  Atom chaseMouse("chaseMouse");
  vector<Term *> v = {&tom, &chaseMouse};
  Struct hobby(Atom("hobby"), v);
  Struct hobby2(Atom("hobby"), v);
  EXPECT_TRUE(hobby.match(hobby2));
}

TEST(Struct, match5)
{
  Atom tom("tom");
  Atom chaseMouse("chaseMouse");
  vector<Term *> v = {&tom, &chaseMouse};
  Struct hobby(Atom("hobby"), v);
  EXPECT_FALSE(hobby.match(tom));
}

// When Struct s contains a Variable X
// Then #symbol() should return "s(X)"
// and #value() should also return "s(X)"
TEST(Struct, var)
{
  Variable X("X");
  vector<Term *> v = {&X};
  Struct s(Atom("s"), v);
  EXPECT_EQ(s.symbol(), "s(X)");
  EXPECT_EQ(s.value(), "s(X)");
}

// Given there is Struct s contains a Variable X
// When Variable X matches an Atom "tom"
// Then #symbol() should return "s(X)"
// and #value() should also return "s(tom)"
TEST(Struct, var_match_atom)
{
  Atom tom("tom");
  Variable X("X");
  vector<Term *> v = {&X};
  Struct s(Atom("s"), v);
  EXPECT_TRUE(X.match(tom));
  EXPECT_EQ(s.symbol(), "s(X)");
  EXPECT_EQ(s.value(), "s(tom)");
}

// Given there are Struct s1 and Struct s2
// When Struct s1 contains Struct s2
// And Struct s2 contains a Variable X
// Then #symbol() of s1 should return "s1(s2(X))"
// and #value() of s1 should also return "s1(s2(X))"
TEST(Struct, nested_struct1)
{
  Variable X("X");
  vector<Term *> v = {&X};
  Struct s2(Atom("s2"), v);
  vector<Term *> v2 = {&s2};
  Struct s1(Atom("s1"), v2);
  EXPECT_EQ(s1.symbol(), "s1(s2(X))");
  EXPECT_EQ(s1.value(), "s1(s2(X))");
}

// Given there are Struct s1 contains Struct s2
// And Struct s2 contains Variable X
// When Variable X matches an Atom "tom"
// Then #symbol() of s1 should return "s1(s2(X))"
// and #value() of s1 should return "s1(s2(tom))"
TEST(Struct, nested_struct2)
{
  Variable X("X");
  vector<Term *> v = {&X};
  Struct s2(Atom("s2"), v);
  vector<Term *> v2 = {&s2};
  Struct s1(Atom("s1"), v2);
  Atom tom("tom");
  EXPECT_TRUE(X.match(tom));
  EXPECT_EQ(s1.symbol(), "s1(s2(X))");
  EXPECT_EQ(s1.value(), "s1(s2(tom))");
}

// Given there are Struct s1 contains Struct s2
// And Struct s2 contains Variable X
// When Variable X matches an Number pi: 3.14
// Then #symbol() of s1 should return "s1(s2(X))"
// and #value() of s1 should return "s1(s2(3.14))"
TEST(Struct, nested_struct3)
{
  Variable X("X");
  Struct s2(Atom("s2"), vector<Term *>{&X});
  Struct s1(Atom("s1"), vector<Term *>{&s2});
  Number pi(3.14);
  EXPECT_TRUE(X.match(pi));
  EXPECT_EQ(s1.symbol(), "s1(s2(X))");
  EXPECT_EQ(s1.value(), "s1(s2(3.14))");
}

// Given there are Struct s1 contains Struct s2 and Variable X
// And Struct s2 contains Variable Y
// When Variable X matches Variable Y
// And Variable X matches Atom "kent_beck"
// Then #symbol() of s1 should return "s1(s2(Y), X)"
// and #value() of s1 should return "s1(s2(kent_beck), kent_beck)"
TEST(Struct, nested_struct_and_multiVariable)
{
  Variable X("X"), Y("Y");
  Struct s2(Atom("s2"), vector<Term *>{&Y});
  Struct s1(Atom("s1"), vector<Term *>{&s2, &X});
  Atom kent_beck("kent_beck");
  EXPECT_TRUE(X.match(Y));
  EXPECT_TRUE(X.match(kent_beck));
  EXPECT_EQ(s1.symbol(), "s1(s2(Y), X)");
  EXPECT_EQ(s1.value(), "s1(s2(kent_beck), kent_beck)");
}

#endif