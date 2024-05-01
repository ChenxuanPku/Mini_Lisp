#ifndef VALUE_H
#define VALUE_H
#include<string>
#include<utility>
#include<memory>
#include"./token.h"

class Value{
public:
  virtual std::string toString(){
  return "";
}
};
class BooleanValue:public Value{

  bool booleanValue;
public:
  BooleanValue()=default;
  BooleanValue(bool boolvalue);
  std::string toString();
};
using ValuePtr = std::shared_ptr<Value>; 
class NumericValue:public Value{
  double numericValue;
public:
  NumericValue()=default;
  NumericValue(double num);
  std::string toString();
};
class StringValue:public Value{
  std::string stringValue;
public:
  StringValue()=default;
  StringValue(std::string str);
  std::string toString();
};
class NilValue:public Value{
public:
  NilValue()=default;
  std::string toString();
};
class SymbolValue:public Value{
  TokenType symbolValue;
public:
  SymbolValue()=default;
  SymbolValue(TokenType symbol);
  std::string toString();
};
 
class PairValue:public Value{
  
  ValuePtr car;
  ValuePtr cdr;
public:
  PairValue()=default;
  PairValue(ValuePtr car,ValuePtr cdr);
  std::string toString();         
};

#endif