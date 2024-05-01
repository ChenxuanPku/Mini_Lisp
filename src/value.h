#ifndef VALUE_H
#define VALUE_H
#include<string>
#include<utility>
#include<memory>
#include"./token.h"
using ValuePtr = std::shared_ptr<Value>; 
class Value{
public:
  virtual std::string toString();
};
class BooleanValue: Value{

  bool booleanValue;
public:
  BooleanValue()=default;
  BooleanValue(bool boolvalue);
  std::string toString();
};
class NumericValue: Value{
  double numericValue;
public:
  NumericValue()=default;
  NumericValue(double num);
  std::string toString();
};
class StringValue: Value{
  std::string stringValue;
public:
  StringValue()=default;
  StringValue(std::string str);
  std::string toString();
};
class NilValue: Value{
public:
  NilValue()=default;
  std::string toString();
};
class SymbolValue: Value{
  TokenType symbolValue;
public:
  SymbolValue()=default;
  SymbolValue(TokenType symbol);
  std::string toString();
};

class PairValue: Value{
  
  ValuePtr car;
  ValuePtr cdr;
public:
  PairValue()=default;
  PairValue(ValuePtr car,ValuePtr cdr);
  std::string toString();         
};

#endif