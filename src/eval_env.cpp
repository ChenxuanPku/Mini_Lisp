#include "./eval_env.h"
#include "./error.h"
#include<iostream>
ValuePtr EvalEnv::eval(ValuePtr expr){
  if(expr->isBoolean()||expr->isNumeric()||expr->isString())
    return expr;
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
      }else {
      throw LispError("Malformed define.");
  }
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
  throw LispError("Unimplemented");
}

