#include "./eval_env.h"
#include "./error.h"
#include "./builtins.h"
#include "./forms.h"
#include "./value.h"
#include<iostream>
#include <algorithm>
#include <iterator>
EvalEnv::EvalEnv(){
  SymbolMap["+"]=std::make_shared<BuiltinProcValue>(&add);
  SymbolMap["print"]=std::make_shared<BuiltinProcValue>(&print);
}

void EvalEnv::Push_Back(std::string str,ValuePtr valueptr){
  SymbolMap[str]=valueptr;
}
ValuePtr EvalEnv::eval(ValuePtr expr){
  if(expr->isSymbol()){ 
  if (auto name=expr->asSymbol())
  {
    return lookupBinding(*name);
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
      if(auto name=expr->toHead()->asSymbol())
      {    auto it=SPECIAL_FORMS.find(*name);
           if(it!=SPECIAL_FORMS.end())
           { //std::cout<<*name<<std::endl;
             return (it->second)(expr->toBack()->toVector(), *this);
            //(SPECIAL_FORMS[*name].second)(expr->toBack()->toVector(), *this);
           }
else{
   
    ValuePtr proc=this->eval(expr->toHead());
    //std::cout<<expr->toBack()->toString()<<std::endl;
     std::vector<ValuePtr> args=evalList(expr->toBack());
     //for (auto i:args)std::cout<<"apply"<<i->toString()<<std::endl;
     return this->apply(proc, args);
  }}else throw LispError("Unimplement");
  }else return expr; 
  }
  
 
  if(expr->isBuiltin())
  {
    return std::move(expr);
  }
  throw LispError("Unimplemented");
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
    throw LispError("Unimplemented");
   }
}
ValuePtr EvalEnv::lookupBinding(std::string str){
   if (SymbolMap.find(str)!=SymbolMap.end())return SymbolMap[str];
   if (parent==nullptr)  throw LispError("Variable " + str + " not defined.");
   return parent->lookupBinding(str);
}

ValuePtr EvalEnv::defineBinding(){
  
}
