#include "./eval_env.h"
#include "./error.h"
#include "./builtins.h"
#include<iostream>
#include <algorithm>
#include <iterator>
EvalEnv::EvalEnv(){
  SymbolMap["+"]=std::make_shared<BuiltinProcValue>(&add);
}

ValuePtr EvalEnv::eval(ValuePtr expr){
  if(expr->isSymbol()){ 
  if (auto name=expr->asSymbol())
  {
    auto value=SymbolMap.find(*name);
    if(value!=SymbolMap.end()){
      return value->second;
    }else {
        throw LispError("Variable " + *name + " not defined.");
    }
  }}
  //std::cout<<"eval"<<expr->toString()<<std::endl;
  if(expr->isBoolean()||expr->isNumeric()||expr->isString())
    return std::move(expr);
  if(expr->isNil())
    throw LispError("Evaluating nil is prohibited.");
  if(expr->isPair())
  {
    using namespace std::literals; // 使用 s 后缀
    
    if(expr->toHead()->isSymbol())
    {
      if (expr->toHead()->asSymbol() == "define"s) 
      {
        std::cout<<expr->toHead()->toString()<<std::endl;
        std::vector<ValuePtr> v = (expr->toBack())->toVector();
        for (ValuePtr vp:v)std::cout<<vp->toString()<<" ";
        if (auto name = v[0]->asSymbol()){
          if(auto newname=v[1]->asSymbol()) SymbolMap[*name]=SymbolMap[*newname];
          else SymbolMap[*name]=eval(v[1]);
          return std::make_shared<NilValue>();
         }
      else throw LispError("Malformed define.");
     } else{
   
    ValuePtr proc=this->eval(expr->toHead());
    std::cout<<expr->toBack()->toString()<<std::endl;
     std::vector<ValuePtr> args=evalList(expr->toBack());
     //for (auto i:args)std::cout<<"apply"<<i->toString()<<std::endl;
     return this->apply(proc, args);
  }}
  }else return expr; 
  
  
 
  if(expr->isBuiltin())
  {
    return std::move(expr);
  }
  throw LispError("NotMatchUnimplemented");
}

std::vector<ValuePtr> EvalEnv::evalList(ValuePtr expr) {
    
    std::vector<ValuePtr> result;
    std::ranges::transform(expr->toVector(),
                           std::back_inserter(result),
                           [this](ValuePtr v) { return this->eval(v); });
   
    return result;
}

ValuePtr EvalEnv::apply(ValuePtr proc, std::vector<ValuePtr> args)
{
   if (typeid(*proc) == typeid(BuiltinProcValue)){
    return(dynamic_cast<BuiltinProcValue*>(proc.get()))->asfunc()(args);
    
   }else{
    throw LispError(proc->toString()+"Unimplemented");
   }
}/*
std::vector<ValuePtr> ToVector(ValuePtr expr){
  if (expr==nullptr)
    throw LispError("Empty");
  if (typeid(*expr)!=typeid(PairValue))
    throw LispError("NotList");

  ValuePtr newCar{expr->toHead()},newCdr{expr->toBack()};
  std::vector<ValuePtr> Vec{};
  if(newCar!=nullptr){
  if (typeid(*newCar)==typeid(PairValue))
  { 
   
    //Vec.push_back(env.eval(car));
  }
  else if(typeid(*newCar)!=typeid(NilValue))Vec.push_back(newCar);}
  if(newCdr!=nullptr){
  if (typeid(*newCdr)==typeid(PairValue))
  {
    //Vec.push_back(env.eval(cdr));
  }
  else if(typeid(newCdr)!=typeid(NilValue))Vec.push_back(newCdr);
  
  }
  return Vec;
}*/