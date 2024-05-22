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
ValuePtr minor(const std::vector<ValuePtr>& params){
  double result=0;
  for (int i{0};i!=params.size();i++)
  {
    if(!params[i]->isNumeric())
      throw LispError("Cannot add a non-numeric value.");
    if(i!=0)
    result-=params[i]->asNumber();
    else result=params[i]->asNumber();
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

ValuePtr times(const std::vector<ValuePtr>& params){
  double result=1;
  for (auto i:params)
  {
    if (i->isNumeric())
      result*=i->asNumber();
    else throw LispError("NotNumerical");
  }
  return std::make_shared<NumericValue>(result);
}
ValuePtr greater(const std::vector<ValuePtr>& params){
  if (params.size()!=2)
    throw LispError("not Two to compare");
  if(params[0]->isNumeric()&&params[0]->isNumeric())
  {
    return std::make_shared<BooleanValue>(params[0]->asNumber()>params[1]->asNumber());
  }
  else throw LispError("notNumerical");
}