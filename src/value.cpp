#ifndef VALUE_CPP
#define VALUE_CPP
#include"./value.h"
#include<iomanip>

BooleanValue:: BooleanValue(bool boolvalue):booleanValue{boolvalue} {}
std::string BooleanValue::toString()
{
  return booleanValue?"#t":"#f";
}             
NumericValue:: NumericValue(double num): numericValue(num){}
std::string NumericValue::toString()
{
  return std::to_string(numericValue);
}    
StringValue:: StringValue(std::string str): stringValue(str){}
std::string StringValue::toString()
{
  return "\"" + stringValue + "\"";
}    
std::string SymbolValue::toString()
{
  return "";
}    
SymbolValue:: SymbolValue(TokenType symbol): symbolValue(symbol){}
std::string NilValue::toString()
{
  return "()";
}    
PairValue::PairValue(ValuePtr car,ValuePtr cdr):car(car),cdr(cdr){}
std::string PairValue::toString()
{
  std::string ans{};
  if (typeid(*cdr)==typeid(PairValue))
  {return car->toString()+" "+cdr->toString();}
  else{
    return car->toString()+" ."+cdr->toString();
  }
  
}    
#endif