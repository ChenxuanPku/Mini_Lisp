#ifndef VALUE_H
#define VALUE_H
#include<string>
#include<utility>
#include<memory>
#include<vector>
#include"./token.h"
#include<functional>

class Value{
public:
  
  bool isBoolean();
  bool isNumeric();
  bool isString();
  bool isNil();
  bool isSymbol();
  bool isPair();
  bool isBuiltin();
  bool isList();
  virtual std::string toString(){return "";}
  virtual std::vector<std::shared_ptr<Value>> toVector();
  virtual std::optional<std::string> asSymbol();
  virtual double asNumber();
  virtual bool asBool();
  virtual std::shared_ptr<Value> toHead();
  virtual std::shared_ptr<Value> toBack();
  virtual std::string asString();
};
using ValuePtr = std::shared_ptr<Value>; 
class BooleanValue:public Value{
  bool booleanValue;
public:
  BooleanValue()=default;
  BooleanValue(bool boolvalue);
  std::string toString();
  bool asBool();
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
  std::string asString();
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
  ValuePtr toHead();   
  ValuePtr toBack();   
 
};

using BuiltinFuncType = ValuePtr(const std::vector<ValuePtr>&);
class BuiltinProcValue : public Value{
  std::function<BuiltinFuncType> func{nullptr};
public:
  BuiltinProcValue()=default;
  BuiltinProcValue(std::function<BuiltinFuncType> func);
  std::string toString() ;
  std::function<BuiltinFuncType> asfunc();
};
class EvalEnv;
class LambdaValue :public Value{
private:
    std::vector<std::string> params;
    std::vector<ValuePtr> body;
    std::shared_ptr<EvalEnv> env;
public:
     LambdaValue()=default;
     LambdaValue(std::vector<std::string>& params,std::vector<ValuePtr>& body,std::shared_ptr<EvalEnv> env);
     std::string toString(); 
     ValuePtr apply(const std::vector<ValuePtr>& args);
};


#endif