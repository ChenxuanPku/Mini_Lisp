
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
