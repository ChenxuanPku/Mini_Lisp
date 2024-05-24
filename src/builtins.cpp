#include "./builtins.h"
#include "./error.h"
#include "./eval_env.h"
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

ValuePtr display(const std::vector<ValuePtr>& params){
  if (params.size()!=1) throw LispError("No");
  for (auto i:params)
  {
    
      std::cout<<i->toString();
    
  }
  return std::make_shared<NilValue>();
}

ValuePtr displayln(const std::vector<ValuePtr>& params){
  if (params.size()!=1) throw LispError("No");
  for (auto i:params)
  {
    
      std::cout<<i->toString()<<std::endl;
  }
  return std::make_shared<NilValue>();
}

ValuePtr error(const std::vector<ValuePtr>& params){
  if(params.empty())throw LispError("");
  else throw LispError(params[0]->toString());
}
ValuePtr Exit(const std::vector<ValuePtr>& params){
  if(params.empty())std::exit(0);
  std::exit(params[0]->asNumber());
}

ValuePtr newline(const std::vector<ValuePtr>& params)
{
  std::cout<<std::endl;
  return std::make_shared<NilValue>();
}
ValuePtr ifAtom(const std::vector<ValuePtr>& params)
{
  if(params.size()!=1) throw LispError("wrongSize");
  if(params[0]->isBoolean()||params[0]->isNumeric()||params[0]->isNil()||params[0]->isSymbol()||params[0]->isString())
  return std::make_shared<BooleanValue>(true);
  else return std::make_shared<BooleanValue>(false);
}
ValuePtr ifBoolean(const std::vector<ValuePtr>& params)
{
  if(params.size()!=1) throw LispError("wrongSize");
  if(params[0]->isBoolean())
  return std::make_shared<BooleanValue>(true);
  else return std::make_shared<BooleanValue>(false);
}
ValuePtr ifInteger(const std::vector<ValuePtr>& params)
{
  if(params.size()!=1) throw LispError("wrongSize");
  if(params[0]->isNumeric())
  { int integer=(params[0]->asNumber());
  if(integer==params[0]->asNumber())
  return std::make_shared<BooleanValue>(true);}
  return std::make_shared<BooleanValue>(false);
}

ValuePtr ifNumber(const std::vector<ValuePtr>& params)
{
  if(params.size()!=1) throw LispError("wrongSize");
  if(params[0]->isNumeric())
  return std::make_shared<BooleanValue>(true);
  else return std::make_shared<BooleanValue>(false);
}
ValuePtr ifNull(const std::vector<ValuePtr>& params)
{
  if(params.empty()) 
  return std::make_shared<BooleanValue>(true);
  else return std::make_shared<BooleanValue>(false);
}
ValuePtr ifPair(const std::vector<ValuePtr>& params)
{
  if(params.size()!=1) throw LispError("wrongSize");
  if(params[0]->isPair())
  return std::make_shared<BooleanValue>(true);
  else return std::make_shared<BooleanValue>(false);
}
ValuePtr ifProcedure(const std::vector<ValuePtr>& params)
{
  if(params.size()!=1) throw LispError("wrongSize");
  if(params[0]->toString()=="#<procedure>")
  return std::make_shared<BooleanValue>(true);
  else return std::make_shared<BooleanValue>(false);
}
ValuePtr ifString(const std::vector<ValuePtr>& params)
{
  if(params.size()!=1) throw LispError("wrongSize");
  if(params[0]->isString())
  return std::make_shared<BooleanValue>(true);
  else return std::make_shared<BooleanValue>(false);
}
ValuePtr ifSymbol(const std::vector<ValuePtr>& params)
{
  if(params.size()!=1) throw LispError("wrongSize");
  if(params[0]->isSymbol())
  return std::make_shared<BooleanValue>(true);
  else return std::make_shared<BooleanValue>(false);
}
