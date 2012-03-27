// TODO: include your classes here.
// #include "your_class"

// just for example
#include "strtk/strtk.hpp"

// gtest
#include <gtest/gtest.h>

// std lib
#include <string>

TEST(TheGameClient, AnswerParserCorrect)
{
  std::string answer = "ok PARAM";

  // TODO test your answer parser
  // TODO don't forget to add your ObjectUnderTest to
  //      TEST_OBJECTS list in Makefile e.g TEST_OBJECTS = AnswerParser.o
  //      AnswerParser.[hh|cpp] have to be in the src directory.
  
  //--- example
  std::string respCode;
  std::string respParam;

  // see http://code.google.com/p/googletest/wiki/V1_6_Primer for EXPECT*()
  
  EXPECT_TRUE( strtk::parse(answer, " ", respCode, respParam) );
  
  EXPECT_TRUE( respCode == "ok" );
  EXPECT_FALSE( respParam == "PaRaMeTeR" );
  //-----
}

TEST(TheGameClient, ClassTest)
{
  //--- example
  std::string answer = "ok PARAM";
  
  EXPECT_TRUE( answer == "WRONG" );
  //-----
}


int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
