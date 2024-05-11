#ifndef PARSER_H
#define PARSER_H
#include<deque>
#include"./token.h"
#include"./value.h"
class Parser{
private:
  std::deque<TokenPtr> tokens;
public:
  Parser(std::deque<TokenPtr> tokens):tokens{tokens}
  {}
  ValuePtr parse();

};
#endif