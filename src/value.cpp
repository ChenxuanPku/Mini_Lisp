
#include"./value.h"
#include"./error.h"
#include<iomanip>
#include<iostream>
BooleanValue:: BooleanValue(bool boolvalue):booleanValue{boolvalue} {}
std::string BooleanValue::toString()
{
  return booleanValue?"#t":"#f";
}             
NumericValue:: NumericValue(double num): numericValue(num){}
std::string NumericValue::toString()
{
  std::string str=std::to_string(numericValue);
  size_t pos = str.find_last_not_of('0');
  if (pos != std::string::npos) {
        str = str.substr(0, pos + 1);
  }
  if (!str.empty() && str.back() == '.') {
        str.pop_back();
  }
  return str;
  
}    
StringValue:: StringValue(std::string str): stringValue{str}{}
std::string StringValue::toString()
{
  std::ostringstream os;
  os << std::quoted(stringValue);
  return os.str();
}    
std::string SymbolValue::toString()
{
  return symbolValue;
}    
SymbolValue:: SymbolValue(std::string symbol):symbolValue(symbol){}
std::string NilValue::toString()
{
  return "()";
}    
PairValue::PairValue(ValuePtr car,ValuePtr cdr):car(car),cdr(cdr){}
std::string PairValue::toString()
{
  
  std::ostringstream os;
  os<<"("<<car->toString()<<" ";
  ValuePtr pnow=cdr;
  while(typeid(*pnow)==typeid(PairValue))
  {
   auto& pair = static_cast<const PairValue&>(*pnow);
   os<<(pair.car->toString())<<" ";
   pnow=pair.cdr;
  }
  if(typeid(*pnow)!=typeid(NilValue))
  os<<". "<<pnow->toString();
  os<<")";
  return os.str();
}    
bool Value::isBoolean(){
  return (typeid(*this)==typeid(BooleanValue));
}
bool Value::isNumeric(){return (typeid(*this)==typeid(NumericValue));}
bool Value::isString(){return (typeid(*this)==typeid(StringValue));}
bool Value::isNil(){return (typeid(*this)==typeid(NilValue));}
bool Value::isSymbol(){return (typeid(*this)==typeid(SymbolValue));}
bool Value::isPair(){return (typeid(*this)==typeid(PairValue));}
std::vector<ValuePtr> Value::toVector(){
  
  throw LispError("notList");
}
std::vector<ValuePtr> PairValue::toVector(){
  std::vector<ValuePtr> Vec{};
  if (typeid(*car)==typeid(PairValue))
  {
    for (ValuePtr vPtr:car->toVector())
    Vec.push_back(std::move(vPtr));
  }
  else Vec.push_back(std::move(car));
  if (typeid(*cdr)==typeid(PairValue))
  {
    for (ValuePtr vPtr:cdr->toVector())
    Vec.push_back(std::move(vPtr));
  }
  else Vec.push_back(std::move(cdr));
  
  return Vec;
}
std::optional<std::string> Value::asSymbol(){
  return std::nullopt;
}
std::optional<std::string> SymbolValue::asSymbol(){
  return symbolValue;
}
BuiltinProcValue::BuiltinProcValue(BuiltinFuncType* func):func(func){}

double NumericValue::asNumber()
{
  return numericValue;
}

ValuePtr add(const std::vector<ValuePtr>& params){
  double result=0;
  for (const auto& i:params)
  {
    if(!i->isNumeric())
      throw LispError("Cannot add a non-numeric value.");
    result+=i->asNumber();
    return std::make_shared<NumericValue>(result);
  }
}