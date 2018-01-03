#ifndef UTSHELL_H
#define UTSHELL_H

#include "parser.h"
#include "scanner.h"
#include "exp.h"

/**
 * 
 * Here are some examples for exception handling,
 * the actual testing way is base on your implementation.
 * 
 */

TEST(Shell, varMatchAtomSuc)
{
  Scanner s("FILCO=awesome.");
  Parser p(s);
  try
  {
    p.buildExpression();
    string result = p.excute();
    ASSERT_EQ("FILCO = awesome.", result);
  }
  catch (std::string &msg)
  {
    FAIL() << msg;
  }
}

TEST(Shell, atomMatchAtomFail)
{
  Scanner s("smog=natural_disaster.");
  Parser p(s);
  try
  {
    p.buildExpression();
    string result = p.excute();
    ASSERT_EQ("false.", result);
  }
  catch (std::string &msg)
  {
    FAIL() << msg;
  }
}

TEST(Shell, varMatchList)
{
  Scanner s("Painful=[Clerk,forgot,pipette].");
  Parser p(s);
  try
  {
    p.buildExpression();
    string result = p.excute();
    ASSERT_EQ("Painful = [Clerk, forgot, pipette].", result);
  }
  catch (std::string &msg)
  {
    FAIL() << msg;
  }
}

TEST(Shell, varMatchStruct)
{
  Scanner s("Pitiful=binding([rope,rope,rope], Turtle, oil).");
  Parser p(s);
  try
  {
    p.buildExpression();
    string result = p.excute();
    ASSERT_EQ("Pitiful = binding([rope, rope, rope], Turtle, oil).", result);
  }
  catch (std::string &msg)
  {
    FAIL() << msg;
  }
}

TEST(Shell, varMatchItself)
{
  Scanner s("Taiwan=Taiwan.");
  Parser p(s);
  try
  {
    p.buildExpression();
    string result = p.excute();
    ASSERT_EQ("true.", result);
  }
  catch (std::string &msg)
  {
    FAIL() << msg;
  }
}

TEST(Shell, varMachingListThatIncludeVar)
{
  Scanner s("X=[Y,tom], Y=marry.");
  Parser p(s);
  try
  {
    p.buildExpression();
    string result = p.excute();
    ASSERT_EQ("X = [marry, tom], Y = marry.", result);
  }
  catch (std::string &msg)
  {
    FAIL() << msg;
  }
}

TEST(Shell, varMachingStructThatIncludeVar)
{
  Scanner s("X=s(Y,marry), Y=tom.");
  Parser p(s);
  try
  {
    p.buildExpression();
    string result = p.excute();
    ASSERT_EQ("X = s(tom, marry), Y = tom.", result);
  }
  catch (std::string &msg)
  {
    FAIL() << msg;
  }
}

TEST(Shell, conjunctionMatching_false)
{
  Scanner s("X=1, X=2.");
  Parser p(s);
  try
  {
   p.buildExpression();
    string result = p.excute();
    ASSERT_EQ("false.", result);
  }
  catch (std::string &msg)
  {
    FAIL() << msg;
  }
}

TEST(Shell, conjunctionMatching_diffExp)
{
  Scanner s("X=1, Y=2.");
  Parser p(s);
  try
  {
    p.buildExpression();
    string result = p.excute();
    ASSERT_EQ("X = 1, Y = 2.", result);
  }
  catch (std::string &msg)
  {
    FAIL() << msg;
  }
}

TEST(Shell, conjunctionMatching_sameExp)
{
  Scanner s("X=1, X=1.");
  Parser p(s);
  try
  {
    p.buildExpression();
    string result = p.excute();
    ASSERT_EQ("X = 1.", result);
  }
  catch (std::string &msg)
  {
    FAIL() << msg;
  }
}

TEST(Shell, conjunctionMatching_true)
{
  Scanner s("X=X, X=X.");
  Parser p(s);
  try
  {
    p.buildExpression();
    string result = p.excute();
    ASSERT_EQ("true.", result);
  }
  catch (std::string &msg)
  {
    FAIL() << msg;
  }
}

TEST(Shell, conjunctionMatching_trueAndExp)
{
  Scanner s("X=X, Y=1.");
  Parser p(s);
  try
  {
    p.buildExpression();
    string result = p.excute();
    ASSERT_EQ("Y = 1.", result);
  }
  catch (std::string &msg)
  {
    FAIL() << msg;
  }
}

TEST(Shell, conjunctionMatching_expAndtrue)
{
  Scanner s("Y=1, X=X.");
  Parser p(s);
  try
  {
   p.buildExpression();
    string result = p.excute();
    ASSERT_EQ("Y = 1.", result);
  }
  catch (std::string &msg)
  {
    FAIL() << msg;
  }
}

TEST(Shell, conjunctionMatching_trueAndfalse)
{
  Scanner s("X=X, 1=2.");
  Parser p(s);
  try
  {
    p.buildExpression();
    string result = p.excute();
    ASSERT_EQ("false.", result);
  }
  catch (std::string &msg)
  {
    FAIL() << msg;
  }
}

TEST(Shell, conjunctionMatching_falseAndtrue)
{
  Scanner s("3=2, X=X.");
  Parser p(s);
  try
  {
   p.buildExpression();
    string result = p.excute();
    ASSERT_EQ("false.", result);
  }
  catch (std::string &msg)
  {
    FAIL() << msg;
  }
}

TEST(Shell, conjunctionMatching_falseAndfalse)
{
  Scanner s("X=1, X=2, 1=2.");
  Parser p(s);
  try
  {
    p.buildExpression();
    string result = p.excute();
    ASSERT_EQ("false.", result);
  }
  catch (std::string &msg)
  {
    FAIL() << msg;
  }
}

TEST(Shell, conjunctionMatching_duplicateExp)
{
  Scanner s("Y=1, X=2, X=2.");
  Parser p(s);
  try
  {
   p.buildExpression();
    string result = p.excute();
    ASSERT_EQ("Y = 1, X = 2.", result);
  }
  catch (std::string &msg)
  {
    FAIL() << msg;
  }
}

TEST(Shell, conjunctionMatching)
{
  Scanner s("Y=1, X=2, X=2.");
  Parser p(s);
  try
  {
    p.buildExpression();
    string result = p.excute();
    ASSERT_EQ("Y = 1, X = 2.", result);
  }
  catch (std::string &msg)
  {
    FAIL() << msg;
  }
}

TEST(Shell, disjunctionMatching1)
{
  Scanner s("X=1; X=2.");
  Parser p(s);
  try
  {
    p.buildExpression();
    string result = p.excute();
    ASSERT_EQ("X = 1; X = 2.", result);
  }
  catch (std::string &msg)
  {
    FAIL() << msg;
  }
}

TEST(Shell, disjunctionMatching2)
{
  Scanner s("X=1; X=1, X=2.");
  Parser p(s);
  try
  {
    p.buildExpression();
    string result = p.excute();
    ASSERT_EQ("X = 1.", result);
  }
  catch (std::string &msg)
  {
    FAIL() << msg;
  }
}

TEST(Shell, disjunctionMatching3)
{
  Scanner s("X=1; X=1, Y=2.");
  Parser p(s);
  try
  {
   p.buildExpression();
    string result = p.excute();
    ASSERT_EQ("X = 1; X = 1, Y = 2.", result);
  }
  catch (std::string &msg)
  {
    FAIL() << msg;
  }
}

TEST(Shell, disjunctionMatching4)
{
  Scanner s("X=1; X=3, X=X.");
  Parser p(s);
  try
  {
    p.buildExpression();
    string result = p.excute();
    ASSERT_EQ("X = 1; X = 3.", result);
  }
  catch (std::string &msg)
  {
    FAIL() << msg;
  }
}

TEST(Shell, disjunctionMatching5)
{
  Scanner s("X=1; X=X; Y=2.");
  Parser p(s);
  try
  {
    p.buildExpression();
    string result = p.excute();
    ASSERT_EQ("X = 1; Y = 2.", result);
  }
  catch (std::string &msg)
  {
    FAIL() << msg;
  }
}

TEST(Shell, disjunctionMatching6)
{
  Scanner s("X=1; X=1, X=2; Z=3.");
  Parser p(s);
  try
  {
    p.buildExpression();
    string result = p.excute();
    ASSERT_EQ("X = 1; Z = 3.", result);
  }
  catch (std::string &msg)
  {
    FAIL() << msg;
  }
}

TEST(Shell, exceptionMissingPeriodToken)
{
  Scanner s("X=1");
  Parser p(s);
  try
  {
    p.buildExpression();
    string result = p.excute();
    FAIL() << "It should throw an exception: Missing token '.'";
  }
  catch (std::string &msg)
  {
    ASSERT_EQ("Missing token '.'", msg);
  }
}


/**
 * 
 * Here are some examples for exception handling,
 * the actual testing way is base on your implementation.
 * 
 */

TEST(Shell, exception_OnlyVariable)
{
    Scanner s("X."); // this is our wrong expression.
    Parser p(s);
    try
    {
         p.buildExpression();
        string result = p.excute();
        FAIL() << "It should throw an exception: X does never get assignment"; // fail if not exception is thrown.
    }
    catch (std::string &msg)
    {
        ASSERT_EQ("X does never get assignment", msg); // it should throw an exception like this.
    }
}

TEST(Shell, exceptionMissingPeriodToken2)
{
    Scanner s("X=1");
    Parser p(s);
    try
    {
        p.buildExpression();
        string result = p.excute();
        FAIL() << "It should throw an exception: Missing token '.'";
    }
    catch (std::string &msg)
    {
        ASSERT_EQ("Missing token '.'", msg);
    }
}

TEST(Shell, exception_UnexpectedDisjTokenBeforePeriod)
{
    Scanner s("X;.");
    Parser p(s);
    try
    {
        p.buildExpression();
        FAIL() << "It should throw an exception: Unexpected ';' before '.'";
    }
    catch (std::string &msg)
    {
        ASSERT_EQ("Unexpected ';' before '.'", msg);
    }
}

TEST(Shell, exception_UnexpectedConjTokenBeforePeriod1)
{
    Scanner s("X,.");
    Parser p(s);
    try
    {
        p.buildExpression();
        FAIL() << "It should throw an exception: Unexpected ',' before '.'";
    }
    catch (std::string &msg)
    {
        ASSERT_EQ("Unexpected ',' before '.'", msg);
    }
}

TEST(Shell, exception_UnexpectedConjTokenBeforePeriod2)
{
    Scanner s("X=1,.");
    Parser p(s);
    try
    {
        p.buildExpression();
        FAIL() << "It should throw an exception: Unbalanced operator";
    }
    catch (std::string &msg)
    {
        ASSERT_EQ("Unexpected ',' before '.'", msg);
    }
}

TEST(Shell, exception_UnbalancedOperator1)
{
    Scanner s("X = match(tom, marry;)");
    Parser p(s);
    try
    {
        p.buildExpression();
        FAIL() << "It should throw an exception: Unbalanced operator";
    }
    catch (std::string &msg)
    {
        ASSERT_EQ("Unbalanced operator", msg);
    }
}

TEST(Shell, exception_UnbalancedOperator2)
{
    Scanner s("X = [tom, marry ;]");
    Parser p(s);
    try
    {
        p.buildExpression();
        FAIL() << "It should throw an exception: Unbalanced operator";
    }
    catch (std::string &msg)
    {
        ASSERT_EQ("Unbalanced operator", msg);
    }
}

#endif