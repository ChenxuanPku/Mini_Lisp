#include "./builtins.h"
#include "./error.h"
#include<iostream>
ValuePtr add(const std::vector<ValuePtr>& params){
  double result=0;
  for (const auto& i:params)
  {
    if(!i->isNumeric())
      throw LispError("Cannot add a non-numeric value.");
    result+=i->asNumber();
    
  }return std::make_shared<NumericValue>(result);
}
ValuePtr print(const std::vector<ValuePtr>& params)
{
  for (const auto& i:params){
    std::cout<<i->toString()<<" ";
  }
  std::cout<<std::endl;
  return std::make_shared<NilValue>();
}