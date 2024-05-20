#include "./eval_env.h"
#include "./error.h"
#include "./builtins.h"
#include "./forms.h"
#include<iostream>
#include <algorithm>
#include <iterator>
EvalEnv::EvalEnv(){
  SymbolMap["+"]=std::make_shared<BuiltinProcValue>(&add);
  SymbolMap["print"]=std::make_shared<BuiltinProcValue>(&print);
}

void EvalEnv::Push_Back(std::string str,ValuePtr valueptr){
  SymbolMap[str]=std::make_shared<Value>(valueptr);
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
      if(auto name=expr->toHead()->asSymbol())
      {    auto it=SPECIAL_FORMS.find(*name);
           if(it!=SPECIAL_FORMS.end())
           {
              (it->second)(expr->toBack()->toVector(), *this);
            //(SPECIAL_FORMS[*name].second)(expr->toBack()->toVector(), *this);
           }
/*
      if (expr->toHead()->asSymbol() == "define"s) 
      {
       
        std::vector<ValuePtr> v = (expr->toBack())->toVector();
        //for (ValuePtr vp:v)std::cout<<vp->toString()<<" ";
        if (auto name = v[0]->asSymbol()){
          if(auto newname=v[1]->asSymbol()) SymbolMap[*name]=SymbolMap[*newname];
          else SymbolMap[*name]=eval(v[1]);
          return std::make_shared<NilValue>();
         }
      else throw LispError(v[0]->toString()+"Malformed define.");
     }*/ }else{
   
    ValuePtr proc=this->eval(expr->toHead());
    //std::cout<<expr->toBack()->toString()<<std::endl;
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
}

ValuePtr defineForm(const std::vector<ValuePtr>& args, EvalEnv& env) 
{
    if (auto name = args[0]->asSymbol()) {
        env.Push_Back(*name, args[1]);
    } else {
        throw LispError("Unimplemented");
    }
     return std::make_shared<NilValue>();
}

ValuePtr quoteForm(const std::vector<ValuePtr>& args, EvalEnv& env) 
{
  return args[1];
}