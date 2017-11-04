#ifndef UTPARSER_H
#define UTPARSER_H

#include "parser.h"
#include "scanner.h"
#include "term.h"
#include "list.h"
#include "variable.h"
#include "number.h"

class ParserTest : public ::testing::Test {
protected:
  void SetUp() {
    symtable.clear();
  }
};

TEST_F(ParserTest, createTerm_Var){
  Scanner scanner("X");
  Parser parser(scanner);
  ASSERT_EQ("X", parser.createTerm()->symbol());
}

TEST_F(ParserTest, createTerm_Num){
  Scanner scanner("123");
  Parser parser(scanner);
  ASSERT_EQ("123", parser.createTerm()->symbol());
}

TEST_F(ParserTest, createTerm_Atom)
{
  Scanner scanner("tom");
  Parser parser(scanner);
  ASSERT_EQ("tom", parser.createTerm()->symbol());
}

TEST_F(ParserTest, createArgs)
{
  Scanner scanner("1, X, tom");
  Parser parser(scanner);
  vector<Term*> terms = parser.getArgs();
  ASSERT_EQ("1", terms[0]->symbol());
  ASSERT_EQ("X", terms[1]->symbol());
  ASSERT_EQ("tom", terms[2]->symbol());
}

TEST_F(ParserTest, createTerms)
{
  Scanner scanner("s(1, X, tom)");
  Parser parser(scanner);
  ASSERT_EQ("s(1, X, tom)", parser.createTerm()->symbol());
}

TEST_F(ParserTest, createStruct)
{
  Scanner scanner("s(s(1))");
  Parser parser(scanner);
  ASSERT_EQ("s(s(1))", parser.createTerm()->symbol());
}

// Given there is string: " 12345,  tom" in scanner.
// When parser parses all terms via scanner.
// Then it should return two terms, one is "12345", another is "tom".
TEST_F(ParserTest, listOfTermsTwo) {
  Scanner scanner(" 12345,  tom");
  Parser parser(scanner);
  vector<Term*> terms = parser.getArgs();
  ASSERT_EQ("12345", terms[0]->symbol());
  ASSERT_EQ("tom", terms[1]->symbol());
}


// Given there is string: "point(1, X, z(1,2,3))" in scanner.
// When parser parses all terms via scanner.
// Then it should return a Struct.
// And #symbol() of Strcut should return "point(1, X, z(1,2,3))".
TEST_F(ParserTest, parseStructOfStruct) {
  Scanner scanner("point(1, X, z(1, 2, 3))");
  Parser parser(scanner);
  ASSERT_EQ("point(1, X, z(1, 2, 3))", parser.createTerm()->symbol());
}


// Given there is string: " 12345,  67" in scanner.
// When parser parses all terms via scanner.
// Then it should return two terms, one is "12345", another is "67".
TEST_F(ParserTest, listOfTermsTwoNumbers) {
  Scanner scanner(" 12345,  67");
  Parser parser(scanner);
  vector<Term*> terms = parser.getArgs();
  ASSERT_EQ("12345", terms[0]->symbol());
  ASSERT_EQ("67", terms[1]->symbol());
}


// Given there is string: "point(1, X, z)" in scanner.
// When parser parses all terms via scanner.
// Then it should return a Struct.
// And #symbol() of Strcut should return "point(1, X, z)".
TEST_F(ParserTest, parseStructThreeArgs) {
  Scanner scanner("point(1, X, z)");
  Parser parser(scanner);
  ASSERT_EQ("point(1, X, z)", parser.createTerm()->symbol());
}


// Given there is string: "   [   ]" in scanner.
// When parser parses all terms via scanner.
// Then it should return a List.
// And #symbol() of List should return "[]".
TEST_F(ParserTest, parseListEmpty) {
  Scanner scanner("   [   ]");
  Parser parser(scanner);
  ASSERT_EQ("[]", parser.createTerm()->symbol());
}


// Given there is string: "_date" in scanner.
// When parser parses all terms via scanner.
// Then it should return a Variable.
// And #symbol() of Variable should return "_date".
TEST_F(ParserTest, parseVar) {
  Scanner scanner("_date");
  Parser parser(scanner);
  ASSERT_EQ("_date", parser.createTerm()->symbol());
}

/*---!!!!!!!!!!!!---*/
// Given there is not string in scanner.
// When parser parses all terms via scanner.
// Then it should return nothing.

TEST_F(ParserTest, listOfTermsEmpty) {
  Scanner scanner("");
  Parser parser(scanner);
  ASSERT_EQ(nullptr, parser.createTerm());
}


// Given there is string: "s(s(s(s(1))))" in scanner.
// When parser parses all terms via scanner.
// Then it should return a Struct.
// And #symbol() of Strcut should return "s(s(s(s(1))))".
TEST_F(ParserTest, parseStructOfStructAllTheWay) {
  Scanner scanner("s(s(s(s(1))))");
  Parser parser(scanner);
  ASSERT_EQ("s(s(s(s(1))))", parser.createTerm()->symbol());
}


// Given there is string: "   [  [1], [] ]" in scanner.
// When parser parses all terms via scanner.
// Then it should return a List.
// And #symbol() of List should return "[[1], []]".

TEST_F(ParserTest, parseListOfLists) {
  Scanner scanner("   [  [1], [] ]");
  Parser parser(scanner);
  ASSERT_EQ("[[1], []]", parser.createTerm()->symbol());
}


// Given there is string: "   [  [1], [], s(s(1)) ]   " in scanner.
// When parser parses all terms via scanner.
// Then it should return a List.
// And #symbol() of List should return "[[1], [], s(s(1))]".


TEST_F(ParserTest, parseListOfListsAndStruct) {
  Scanner scanner("   [  [1], [], s(s(1)) ]   ");
  Parser parser(scanner);
  ASSERT_EQ("[[1], [], s(s(1))]", parser.createTerm()->symbol());
}

// Given there is string: "   [1, 2]" in scanner.
// When parser parses all terms via scanner.
// Then it should return a List.
// And #symbol() of List should return "[1, 2]".
TEST_F(ParserTest, parseList) {
  Scanner scanner("   [1, 2]");
  Parser parser(scanner);
  ASSERT_EQ("[1, 2]", parser.createTerm()->symbol());
}

// Given there is string: "[1,2)" in scanner.
// When parser parses all terms via scanner.
// Then it should return a string: "unexpected token" as exception.
TEST_F(ParserTest, illegal1) {
  Scanner scanner("[1,2)");
  Parser parser(scanner);
  ASSERT_EQ("unexpected token", parser.createTerm()->symbol());
}

// Given there is string: ".(1,[])" in scanner.
// When parser parses all terms via scanner.
// Then it should return a Struct which contains two terms.
// And #arity() of the Struct should be 2.
// And #symbol() of Struct should return ".(1, [])".
// And the first term should be number: "1", the second term should be another List: "[]".
TEST_F(ParserTest, ListAsStruct) {
  Scanner scanner(".(1,[])");
  Parser parser(scanner);
  vector<Term*> terms = parser.getArgs();
  ASSERT_EQ(2, terms[0]->arity());
  ASSERT_EQ(".(1, [])", terms[0]->symbol());
  ASSERT_EQ("1", terms[0]->args(0)->symbol());
  ASSERT_EQ("[]", terms[0]->args(1)->symbol());
}


// Given there is string: ".(2,.(1,[]))" in scanner.
// When parser parses all terms via scanner.
// Then it should return a Struct which contains two terms.
// And #arity() of the Struct should be 2.
// And #symbol() of Struct should return ".(2, .(1, []))"
// And the first term should be number: "2", the second term should be another Strcut: ".(1, [])".
TEST_F(ParserTest, ListAsStruct2) {
  Scanner scanner(".(2,.(1,[]))");
  Parser parser(scanner);
  vector<Term*> terms = parser.getArgs();
  ASSERT_EQ(2, terms[0]->arity());
  ASSERT_EQ(".(2, .(1, []))", terms[0]->symbol());
  ASSERT_EQ("2", terms[0]->args(0)->symbol());
  ASSERT_EQ(".(1, [])", terms[0]->args(1)->symbol());
}


// Given there is string: "s(s(s(s(1)))), b(1,2,3)" in scanner.
// When parser parses all terms via scanner.
// Then it should return two Struct.
// And #symbol() of the first Strcut should return "s(s(s(s(1))))".
// And #symbol() of the second Strcut should return "b(1, 2, 3)".
TEST_F(ParserTest, parseStructOfStructAllTheWay2) {
  Scanner scanner("s(s(s(s(1)))), b(1,2,3)");
  Parser parser(scanner);
  vector<Term*> terms = parser.getArgs();
  ASSERT_EQ("s(s(s(s(1))))", terms[0]->symbol());
  ASSERT_EQ("b(1, 2, 3)", terms[1]->symbol());
  
}


// Given there is string: "point()" in scanner.
// When parser parses all terms via scanner.
// Then it should return a Struct.
// And #symbol() of Strcut should return "point()".

TEST_F(ParserTest, parseStructNoArg) {
  Scanner scanner("point()");
  Parser parser(scanner);
  ASSERT_EQ("point()", parser.createTerm()->symbol());
}


// Given there is string: " 12345,  tom,   Date" in scanner.
// When parser parses all terms via scanner.
// Then it should return three terms: "12345", "tom" and "Date".
TEST_F(ParserTest, listOfTermsThree) {
  Scanner scanner(" 12345,  tom,   Date");
  Parser parser(scanner);
  vector<Term*> terms = parser.getArgs();
  ASSERT_EQ("12345", terms[0]->symbol());
  ASSERT_EQ("tom", terms[1]->symbol());
  ASSERT_EQ("Date", terms[2]->symbol());
}


// Given there is string: "point(11,12)" in scanner.
// When parser parses all terms via scanner.
// Then it should return a Struct.
// And #symbol() of Strcut should return "point(11, 12)".
TEST_F(ParserTest, parseStructTwoArgs) {
  Scanner scanner("point(11,12)");
  Parser parser(scanner);
  ASSERT_EQ("point(11, 12)", parser.createTerm()->symbol());
}


// Given there is string: "...(11,12)" in scanner.
// When parser parses all terms via scanner.
// Then it should return a Struct.
// And #symbol() of Strcut should return "...(11, 12)".

TEST_F(ParserTest, parseStructDOTSTwoArgs) {
  Scanner scanner("...(11,12)");
  Parser parser(scanner);
  ASSERT_EQ("...(11, 12)", parser.createTerm()->symbol());
}


// Given there is string: "point(11)" in scanner.
// When parser parses all terms via scanner.
// Then it should return a Struct.
// And #symbol() of Strcut should return "point(11)".
TEST_F(ParserTest, parseStructOneArg) {
  Scanner scanner("point(11)");
  Parser parser(scanner);
  ASSERT_EQ("point(11)", parser.createTerm()->symbol());
}

#endif