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
  return std::to_string(numericValue)
}    
StringValue:: StringValue(std::string str): stringValue(str){}
std::string StringValue::toString()
{
  return std::quoted(stringValue);
}    
std::string SymbolValue::toString()
{
  return symbolValue;
}    
SymbolValue:: SymbolValue(TokenType symbol): symbolValue(symbol){}
std::string NilValue::toString()
{
  return "()"
}    
PairValue::PairValue(ValuePtr left,ValuePtr right):Left(left),Right(right){}
std::string PairValue::toString()
{
  return
}    
