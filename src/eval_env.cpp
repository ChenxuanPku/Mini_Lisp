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
  
  if(expr->isBoolean()||expr->isNumeric()||expr->isString())
    return std::move(expr);
  if(expr->isNil())
    throw LispError("Evaluating nil is prohibited.");
  if(expr->isPair())
  {
    using namespace std::literals; // 使用 s 后缀
    std::vector<ValuePtr> v = expr->toVector();
    if (v[0]->asSymbol() == "define"s) {
      if (auto name = v[1]->asSymbol()){
        if(auto newname=v[2]->asSymbol()) SymbolMap[*name]=SymbolMap[*newname];
        else SymbolMap[*name]=v[2];
        return std::make_shared<NilValue>();
      } else throw LispError("Unimplemented");
  }else {
     // throw LispError("Malformed define.");
     
     ValuePtr proc=this->eval(v[0]);
     
     std::vector<ValuePtr> args=evalList(expr->toBack());
     this->apply(proc, args);

  }}
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
    std::cout<<"111"<<std::endl;
    return result;
}

ValuePtr EvalEnv::apply(ValuePtr proc, std::vector<ValuePtr> args)
{
   if (typeid(*proc) == typeid(BuiltinProcValue)){
    return(dynamic_cast<BuiltinProcValue*>(proc.get()))->asFunc()(args);
    
   }else{
    throw LispError("Unimplemented");
   }
}