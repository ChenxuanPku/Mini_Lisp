#include "./builtins.h"
#include "./error.h"
#include "./eval_env.h"
#include <iostream>
#include <cmath>
#include <math.h>
ValuePtr add(const std::vector<ValuePtr>& params){
  double result=0;
  for (const auto& i:params)
  {
    if(!i->isNumeric())
      throw LispError("TypeError, should be a numeric value.");
    result+=i->asNumber();
    
  }return std::make_shared<NumericValue>(result);
}
ValuePtr minor(const std::vector<ValuePtr>& params){
  double result=0;
  if(params.size()==1)
  {
    if(!params[0]->isNumeric())
      throw LispError("TypeError, should be a numeric value.");
    return std::make_shared<NumericValue>(-params[0]->asNumber()) ;
  }
  for (int i{0};i!=params.size();i++)
  {
    if(!params[i]->isNumeric())
      throw LispError("TypeError, should be a numeric value.");
    if(i!=0)
    result-=params[i]->asNumber();
    else result=params[i]->asNumber();
  }return std::make_shared<NumericValue>(result);
}
ValuePtr divide(const std::vector<ValuePtr>& params)
{
  if(params.size()==1)
  {
     if(!params[0]->isNumeric())
      throw LispError("TypeError, should be a numeric value.");
     if(params[0]->asNumber()==0)
      throw LispError("0 cannot be the denominator");
     return std::make_shared<NumericValue>(1/params[0]->asNumber());
  }
  if(params.size()==2)
  {
     if(!(params[0]->isNumeric()&&params[1]->isNumeric()))
      throw LispError("TypeError, should be a numeric value.");
     if(params[1]->asNumber()==0)
      throw LispError("0 cannot be the denominator");
     return std::make_shared<NumericValue>(params[0]->asNumber()/params[1]->asNumber());
  }
  throw LispError("The number of parameters provided does not meet the requirements.");
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
    else throw LispError("TypeError, should be a numeric value.");
  }
  return std::make_shared<NumericValue>(result);
}
ValuePtr greater(const std::vector<ValuePtr>& params){
  if (params.size()!=2)
    throw LispError("The number of parameters provided does not meet the requirements.");
  if(params[0]->isNumeric()&&params[0]->isNumeric())
  {
    return std::make_shared<BooleanValue>(params[0]->asNumber()>params[1]->asNumber());
  }
  else throw LispError("TypeError, should be a numeric value.");
}

ValuePtr display(const std::vector<ValuePtr>& params){
  if (params.size()!=1) throw LispError("The number of parameters provided does not meet the requirements.");
  for (auto i:params)
  {
    
      std::cout<<i->toString();
  }
  return std::make_shared<NilValue>();
}

ValuePtr displayln(const std::vector<ValuePtr>& params){
  if (params.size()!=1) throw LispError("The number of parameters provided does not meet the requirements.");
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
  if(params.size()!=1) throw LispError("The number of parameters provided does not meet the requirements.");
  if(params[0]->isBoolean()||params[0]->isNumeric()||params[0]->isNil()||params[0]->isSymbol()||params[0]->isString())
  return std::make_shared<BooleanValue>(true);
  else return std::make_shared<BooleanValue>(false);
}
ValuePtr ifBoolean(const std::vector<ValuePtr>& params)
{
  if(params.size()!=1) throw LispError("The number of parameters provided does not meet the requirements.");
  if(params[0]->isBoolean())
  return std::make_shared<BooleanValue>(true);
  else return std::make_shared<BooleanValue>(false);
}
ValuePtr ifInteger(const std::vector<ValuePtr>& params)
{
  if(params.size()!=1) throw LispError("The number of parameters provided does not meet the requirements.");
  if(params[0]->isNumeric())
  { int integer=(params[0]->asNumber());
  if(integer==params[0]->asNumber())
  return std::make_shared<BooleanValue>(true);}
  return std::make_shared<BooleanValue>(false);
}

ValuePtr ifNumber(const std::vector<ValuePtr>& params)
{
  if(params.size()!=1) throw LispError("The number of parameters provided does not meet the requirements.");
  if(params[0]->isNumeric())
  return std::make_shared<BooleanValue>(true);
  else return std::make_shared<BooleanValue>(false);
}
ValuePtr ifNull(const std::vector<ValuePtr>& params)
{
  if(params.empty()) 
  return std::make_shared<BooleanValue>(true);

  else if(params.size()==1&&params[0]->isNil())
  return std::make_shared<BooleanValue>(true);
  return std::make_shared<BooleanValue>(false);
}
ValuePtr ifPair(const std::vector<ValuePtr>& params)
{
  if(params.size()!=1) throw LispError("The number of parameters provided does not meet the requirements.");
  if(params[0]->isPair())
  return std::make_shared<BooleanValue>(true);
  else return std::make_shared<BooleanValue>(false);
}
ValuePtr ifProcedure(const std::vector<ValuePtr>& params)
{
  if(params.size()!=1) throw LispError("The number of parameters provided does not meet the requirements.");
  if(params[0]->toString()=="#<procedure>")
  return std::make_shared<BooleanValue>(true);
  else return std::make_shared<BooleanValue>(false);
}
ValuePtr ifString(const std::vector<ValuePtr>& params)
{
  if(params.size()!=1) throw LispError("The number of parameters provided does not meet the requirements.");
  if(params[0]->isString())
  return std::make_shared<BooleanValue>(true);
  else return std::make_shared<BooleanValue>(false);
}
ValuePtr ifSymbol(const std::vector<ValuePtr>& params)
{
  if(params.size()!=1) throw LispError("The number of parameters provided does not meet the requirements.");
  if(params[0]->isSymbol())
  return std::make_shared<BooleanValue>(true);
  else return std::make_shared<BooleanValue>(false);
}

ValuePtr Rcar(const std::vector<ValuePtr>& params)
{
  if(params.size()!=1) throw LispError("The number of parameters provided does not meet the requirements.");
  return params[0]->toHead();
}
ValuePtr Rcdr(const std::vector<ValuePtr>& params)
{
  if(params.size()!=1) throw LispError("The number of parameters provided does not meet the requirements.");
  return params[0]->toBack();
}

ValuePtr ifList(const std::vector<ValuePtr>& params)
{
  if(params.size()!=1) throw LispError("The number of parameters provided does not meet the requirements.");
  if(params[0]->isNil())return std::make_shared<BooleanValue>(true);
  if(params[0]->isPair())
  { ValuePtr now{params[0]};
  
    while(now->isPair())
    {
      now=now->toBack();
      if(now->isNil())return std::make_shared<BooleanValue>(true);
      
    }
    return std::make_shared<BooleanValue>(false);}
  else return std::make_shared<BooleanValue>(false);
}
ValuePtr cons(const std::vector<ValuePtr>& params)
{
  if(params.size()!=2) throw LispError("The number of parameters provided does not meet the requirements.");
  return std::make_shared<PairValue>(params[0],params[1]);
}
ValuePtr append(const std::vector<ValuePtr>& params)
{
  
  std::vector<ValuePtr> vec{};
  for( auto v:params)
  {
    for(auto a:v->toVector())
    vec.push_back(a);
  }
  
  int length=vec.size();
  if(length==0) return std::make_shared<NilValue>();
  ValuePtr result=std::make_shared<PairValue>(vec[length-1],std::make_shared<NilValue>());
  for(int i{length-2};i>=0;i--)
  result=std::make_shared<PairValue>(vec[i],result);
  return result;
}

ValuePtr length(const std::vector<ValuePtr>& params)
{if(params.size()!=1) throw LispError("The number of parameters provided does not meet the requirements.");
  return std::make_shared<NumericValue>((params[0]->toVector()).size());
}

ValuePtr list(const std::vector<ValuePtr>& params)
{
  if(params.empty()) return std::make_shared<NilValue>();
  int length=params.size();
  ValuePtr result=std::make_shared<PairValue>(params[length-1],std::make_shared<NilValue>());
  for(int i{length-2};i>=0;i--)
  result=std::make_shared<PairValue>(params[i],result);
  return result;
}
ValuePtr Abs(const std::vector<ValuePtr>& params)
{  if(params.size()!=1) throw LispError("The number of parameters provided does not meet the requirements.");
   if(!params[0]->isNumeric())
      throw LispError("TypeError, should be a numeric value.");
   int sig=(params[0]->asNumber()>=0)?1:-1;
   return std::make_shared<NumericValue>(sig*params[0]->asNumber());
}
ValuePtr expt(const std::vector<ValuePtr>& params)
{
  if(params.size()!=2) throw LispError("The number of parameters provided does not meet the requirements.");
   if(!params[0]->isNumeric())
      throw LispError("TypeError, should be a numeric value.");
   if(!params[1]->isNumeric())
      throw LispError("TypeError, should be a numeric value.");
  double x=params[0]->asNumber();
  double y=params[1]->asNumber();
  if (x==0&&y==0) throw LispError("arithmetic irregularity");
  return std::make_shared<NumericValue>(pow(x,y));
}
ValuePtr quotient(const std::vector<ValuePtr>& params)
{ if(params.size()!=2) throw LispError("The number of parameters provided does not meet the requirements.");
  if(!(params[0]->isNumeric()&&params[1]->isNumeric()))
      throw LispError("TypeError, should be a numeric value.");
  if(params[1]->asNumber()==0)
      throw LispError("0");
  return std::make_shared<NumericValue>(round(params[0]->asNumber()/params[1]->asNumber()));
}
ValuePtr modulo(const std::vector<ValuePtr>& params)
{
   if(params.size()!=2) throw LispError("The number of parameters provided does not meet the requirements.");
   if(!(params[0]->isNumeric()&&params[1]->isNumeric()))
      throw LispError("TypeError, should be a numeric value.");
  if(params[1]->asNumber()==0)
      throw LispError("0 cannot be the denominator");
  if(static_cast<int>(params[0]->asNumber())!=params[0]->asNumber()) 
      throw LispError("Not int");
  if(static_cast<int>(params[1]->asNumber())!=params[1]->asNumber()) 
      throw LispError("Not int");
  double ans=static_cast<int>(params[0]->asNumber())%static_cast<int>(params[1]->asNumber());
  if(ans*static_cast<int>(params[1]->asNumber())>=0 )return std::make_shared<NumericValue>(ans);
  else return std::make_shared<NumericValue>(ans+params[1]->asNumber());
  
}
ValuePtr remainder(const std::vector<ValuePtr>& params)
{
   if(params.size()!=2) throw LispError("The number of parameters provided does not meet the requirements.");
   if(!(params[0]->isNumeric()&&params[1]->isNumeric()))
      throw LispError("TypeError, should be a numeric value.");
   if(params[1]->asNumber()==0)
      throw LispError("0 cannot be the denominator");
   if(static_cast<int>(params[0]->asNumber())!=params[0]->asNumber()) 
      throw LispError("Not int");
   if(static_cast<int>(params[1]->asNumber())!=params[1]->asNumber()) 
      throw LispError("Not int");
  double ans=static_cast<int>(params[0]->asNumber())%static_cast<int>(params[1]->asNumber());
  return std::make_shared<NumericValue>(ans);
}
ValuePtr ifEq(const std::vector<ValuePtr>& params)
{
  if(params.size()!=2) throw LispError("The number of parameters provided does not meet the requirements.");
  if(typeid(*params[0])!=typeid(*params[1]))
    return std::make_shared<BooleanValue>(false);
  if(params[0]->isPair()||params[0]->toString()=="#<procedure>"||params[0]->isString())
    return std::make_shared<BooleanValue>(params[0]==params[1]);
  else return std::make_shared<BooleanValue>(params[0]->toString()==params[1]->toString());
}
ValuePtr ifEqual(const std::vector<ValuePtr>& params)
{
  if(params.size()!=2) throw LispError("The number of parameters provided does not meet the requirements.");
  if(params[0]->toString()=="#<procedure>"&&params[0]->toString()=="#<procedure>")
  {
    return std::make_shared<BooleanValue>(params[0]==params[1]);
  }
  else return std::make_shared<BooleanValue>(params[0]->toString()==params[1]->toString());
}
ValuePtr EEqual(const std::vector<ValuePtr>& params)
{
  if(params.size()!=2) throw LispError("The number of parameters provided does not meet the requirements.");
  if(!(params[0]->isNumeric()&&params[1]->isNumeric()))
      throw LispError("TypeError, should be a numeric value.");
  return std::make_shared<BooleanValue>(params[0]->asNumber()==params[1]->asNumber());
}

ValuePtr ge(const std::vector<ValuePtr>& params)
{
  if(params.size()!=2) throw LispError("The number of parameters provided does not meet the requirements.");
  if(!(params[0]->isNumeric()&&params[1]->isNumeric()))
      throw LispError("TypeError, should be a numeric value.");
  return std::make_shared<BooleanValue>(params[0]->asNumber()>=params[1]->asNumber());
}
ValuePtr le(const std::vector<ValuePtr>& params)
{
  if(params.size()!=2) throw LispError("The number of parameters provided does not meet the requirements.");
  if(!(params[0]->isNumeric()&&params[1]->isNumeric()))
      throw LispError("TypeError, should be a numeric value.");
  return std::make_shared<BooleanValue>(params[0]->asNumber()<=params[1]->asNumber());
}
ValuePtr smaller(const std::vector<ValuePtr>& params)
{
  if(params.size()!=2) throw LispError("The number of parameters provided does not meet the requirements.");
  if(!(params[0]->isNumeric()&&params[1]->isNumeric()))
      throw LispError("TypeError, should be a numeric value.");
  return std::make_shared<BooleanValue>(params[0]->asNumber()<params[1]->asNumber());
}

ValuePtr ifEven(const std::vector<ValuePtr>& params)
{ 
  if(params.size()!=1) throw LispError("The number of parameters provided does not meet the requirements.");
  if(!(params[0]->isNumeric()))
      throw LispError("TypeError, should be a numeric value.");
  if(static_cast<int>(params[0]->asNumber())!=params[0]->asNumber()) 
      throw LispError("Not int");
  if(static_cast<int>(params[0]->asNumber())%2==0)
    return std::make_shared<BooleanValue>(true);
    return std::make_shared<BooleanValue>(false);
}
ValuePtr ifOdd(const std::vector<ValuePtr>& params)
{
  if(params.size()!=1) throw LispError("The number of parameters provided does not meet the requirements.");
  if(!(params[0]->isNumeric()))
      throw LispError("TypeError, should be a numeric value.");
  if(static_cast<int>(params[0]->asNumber())!=params[0]->asNumber()) 
      throw LispError("Not int");
    if(static_cast<int>(params[0]->asNumber())%2==0)
    return std::make_shared<BooleanValue>(false);
    return std::make_shared<BooleanValue>(true);
}

ValuePtr ifZero(const std::vector<ValuePtr>& params)
{
  if(params.size()!=1) throw LispError("The number of parameters provided does not meet the requirements.");
  if(params[0]->isNumeric())
  { if(params[0]->asNumber()!=0)
    return std::make_shared<BooleanValue>(false);
    return std::make_shared<BooleanValue>(true);}
  else throw LispError("TypeError, should be a numeric value.");
}