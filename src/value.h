#ifndef VALUE_H
#define VALUE_H
#include<string>
#include<utility>
#include<memory>
#include<vector>
#include"./token.h"

class Value{
public:
  virtual std::string toString(){
  return "";
  
} bool isBoolean();
  bool isNumeric();
  bool isString();
  bool isNil();
  bool isSymbol();
  bool isPair();
  virtual std::vector<std::shared_ptr<Value>> toVector();
  virtual std::optional<std::string> asSymbol();
  virtual double asNumber();
};
using ValuePtr = std::shared_ptr<Value>; 
class BooleanValue:public Value{
  bool booleanValue;
public:
  BooleanValue()=default;
  BooleanValue(bool boolvalue);
  std::string toString();
};

class NumericValue:public Value{
  double numericValue;
public:
  NumericValue()=default;
  NumericValue(double num);
  std::string toString();
  double asNumber();
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
  std::string symbolValue;
public:
  SymbolValue()=default;
  SymbolValue(std::string symbol);
  std::string toString();
  std::optional<std::string> asSymbol();
};
 
class PairValue:public Value{
protected:
  ValuePtr car;
  ValuePtr cdr;
public:
  PairValue()=default;
  PairValue(ValuePtr car,ValuePtr cdr);
  std::string toString();
  std::vector<ValuePtr> toVector();        
};

using BuiltinFuncType = ValuePtr(const std::vector<ValuePtr>&);
class BuiltinProcValue : public Value{
  BuiltinFuncType* func{nullptr};
public:
  BuiltinProcValue()=default;
  BuiltinProcValue(BuiltinFuncType* func);
  std::string toString() ;
};

ValuePtr add(const std::vector<ValuePtr>& params);
#endif