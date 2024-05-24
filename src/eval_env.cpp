#include "./eval_env.h"
#include "./error.h"
#include "./builtins.h"
#include "./forms.h"
#include "./value.h"
#include<functional>
#include<iostream>
#include <algorithm>
#include <iterator>
EvalEnv::EvalEnv(){
  SymbolMap["+"]=std::make_shared<BuiltinProcValue>(&add);
  SymbolMap["print"]=std::make_shared<BuiltinProcValue>(&print);
  SymbolMap["*"]=std::make_shared<BuiltinProcValue>(&times);
  SymbolMap[">"]=std::make_shared<BuiltinProcValue>(&greater);
  SymbolMap["-"]=std::make_shared<BuiltinProcValue>(&minor);
  std::function<BuiltinFuncType> Apply=[this](const std::vector<ValuePtr>& params){
      std::cout<<"Apply"<<std::endl;
      if (params.size()!=2) throw LispError("SizeError");
      ValuePtr  proc=params[0];
      std::vector<ValuePtr> args(params[1]->toVector());
      return this->apply(proc,args);
  } ;
  SymbolMap["apply"]=std::make_shared<BuiltinProcValue>(Apply.target<BuiltinFuncType>());
  std::function<BuiltinFuncType> Eval=[this](const std::vector<ValuePtr>& params){
      std::cout<<"Eval"<<std::endl;
      return this->eval(params[0]);
  };
  SymbolMap["eval"]=std::make_shared<BuiltinProcValue>(Eval.target<BuiltinFuncType>());
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
      {  
        { auto it=SPECIAL_FORMS.find(*name);
          
           if(it!=SPECIAL_FORMS.end())
           { 
             return (it->second)(expr->toBack()->toVector(), *this);
           }}
        ValuePtr proc=lookupBinding(*name);
        std::vector<ValuePtr> args=evalList(expr->toBack());
        return this->apply(proc, args);
      }}
   else{
     ValuePtr proc=this->eval(expr->toHead());
     if(typeid(*proc)!=typeid(LambdaValue)&&typeid(*proc)!=typeid(BuiltinProcValue))return expr;
     std::vector<ValuePtr> args=evalList(expr->toBack());
     return this->apply(proc, args);
  } 
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
   //std::cout<<"envapply"<<std::endl;
   if (typeid(*proc) == typeid(BuiltinProcValue)){
    //std::cout<<"builtinapply"<<std::endl;
    auto Builtin{dynamic_cast<BuiltinProcValue*>(proc.get())};
    auto func=Builtin->asfunc();
    //std::cout<<"funcDone"<<std::endl;;
    std::cout<<Builtin->toString()<<std::endl;
    ValuePtr result=func(args);
    //std::cout<<"resultDone"<<std::endl;;
    return result;
   }else{
    if(typeid(*proc)==typeid(LambdaValue))
    {
      return (dynamic_cast<LambdaValue*>(proc.get()))->apply(args);
    }
    throw LispError("ApplyUnimplemented"+proc->toString());
   }
}
ValuePtr EvalEnv::lookupBinding(std::string str){
  
   if (SymbolMap.find(str)!=SymbolMap.end()){return SymbolMap[str];}
   if (parent==nullptr)  throw LispError("Variable " + str + " not defined.");
   return parent->lookupBinding(str);
}

ValuePtr EvalEnv::defineBinding(){
}
std::shared_ptr<EvalEnv> EvalEnv::createGlobal()
{
  return std::shared_ptr<EvalEnv>(new EvalEnv());
}
std::shared_ptr<EvalEnv> EvalEnv::createChild(const std::vector<std::string>& params, const std::vector<ValuePtr>& args){
  auto result=std::shared_ptr<EvalEnv>(new EvalEnv());
  result->parent=this->shared_from_this();
  int size_1=params.size();
  int size_2=args.size();
  if(size_1!=size_2) throw LispError("notMatch");
  for(int i{0};i!=size_1;i++)
  {
    result->Push_Back(params[i],args[i]);
  }
  return result;
}