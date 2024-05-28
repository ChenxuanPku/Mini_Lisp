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
 
  std::function<BuiltinFuncType> Apply=[this](const std::vector<ValuePtr>& params){
      //std::cout<<"Apply"<<std::endl;
      if (params.size()!=2) throw LispError("The number of parameters provided does not meet the requirements.");
     // ValuePtr  proc=params[0];
     // std::vector<ValuePtr> args(params[1]->toVector());
      return this->apply(params[0],params[1]->toVector());
  } ;
 
  std::function<BuiltinFuncType> Eval=[this](const std::vector<ValuePtr>& params){
     
     return this->eval(params[0]);
  };
  std::function<BuiltinFuncType> Map=[this](const std::vector<ValuePtr>& params){
    if (params.size()!=2) throw LispError("The number of parameters provided does not meet the requirements.");
    std::vector<ValuePtr> result;
    for(auto a:params[1]->toVector())
    {
       std::vector<ValuePtr> tmp{a};
       result.push_back(this->apply(params[0],tmp));
    }
    return list(result);
  }; 
  std::function<BuiltinFuncType> Filter=[this](const std::vector<ValuePtr>& params){
   if (params.size()!=2) throw LispError("The number of parameters provided does not meet the requirements.");
   std::vector<ValuePtr> result{};
    for(auto a:params[1]->toVector())
    {  
       std::vector<ValuePtr> tmp{a};
       auto ans=this->apply(params[0],tmp);
       
       if(typeid(*ans)==typeid(BooleanValue))
       {
        if(ans->toString()=="#t")
        result.push_back(a);}
       
    }
    return list(result);
  };
   std::function<BuiltinFuncType> Reduce=[this](const std::vector<ValuePtr>& params){
    if (params.size()!=2) throw LispError("The number of parameters provided does not meet the requirements.");
    if (typeid(*params[1])==typeid(NilValue)) throw LispError("Empty!");
    std::vector<ValuePtr> vec=params[1]->toVector();
   // if(vec.size()==1)return vec[0];else 
    for(int i{vec.size()-2};i!=-1;i--)
    {
      std::vector<ValuePtr>tmp{vec[i],vec[i+1]};
      vec[i]=this->apply(params[0],tmp);
    }
    return vec[0];
   };
  std::function<BuiltinFuncType> NotVal=[this](const std::vector<ValuePtr>& params){
   if (params.size()!=1) throw LispError("The number of parameters provided does not meet the requirements.");
   //auto ans=this->eval(params[0]);
   if(typeid(*params[0])==typeid(BooleanValue))
        if(params[0]->toString()=="#f")
          return std::make_shared<BooleanValue>(true);
    return std::make_shared<BooleanValue>(false);
  };
  

  SymbolMap["eval"]=std::make_shared<BuiltinProcValue>(Eval); 
  SymbolMap["apply"]=std::make_shared<BuiltinProcValue>(Apply);
  SymbolMap["+"]=std::make_shared<BuiltinProcValue>(&add);
  SymbolMap["print"]=std::make_shared<BuiltinProcValue>(&print);
  SymbolMap["*"]=std::make_shared<BuiltinProcValue>(&times);
  SymbolMap[">"]=std::make_shared<BuiltinProcValue>(&greater);
  SymbolMap["<"]=std::make_shared<BuiltinProcValue>(&smaller);
  SymbolMap[">="]=std::make_shared<BuiltinProcValue>(&ge);
  SymbolMap["<="]=std::make_shared<BuiltinProcValue>(&le);
  SymbolMap["="]=std::make_shared<BuiltinProcValue>(&EEqual);
  SymbolMap["-"]=std::make_shared<BuiltinProcValue>(&minor);
  SymbolMap["/"]=std::make_shared<BuiltinProcValue>(&divide);
  SymbolMap["display"]=std::make_shared<BuiltinProcValue>(&display);
  SymbolMap["displayln"]=std::make_shared<BuiltinProcValue>(&displayln);
  SymbolMap["error"]=std::make_shared<BuiltinProcValue>(&error);
  SymbolMap["exit"]=std::make_shared<BuiltinProcValue>(&Exit);
  SymbolMap["newline"]=std::make_shared<BuiltinProcValue>(&newline);
  SymbolMap["atom?"]=std::make_shared<BuiltinProcValue>(&ifAtom);
  SymbolMap["boolean?"]=std::make_shared<BuiltinProcValue>(&ifBoolean);
  SymbolMap["integer?"]=std::make_shared<BuiltinProcValue>(&ifInteger);
  SymbolMap["list?"]=std::make_shared<BuiltinProcValue>(&ifList);
  SymbolMap["number?"]=std::make_shared<BuiltinProcValue>(&ifNumber);
  SymbolMap["null?"]=std::make_shared<BuiltinProcValue>(&ifNull);
  SymbolMap["pair?"]=std::make_shared<BuiltinProcValue>(&ifPair);
  SymbolMap["procedure?"]=std::make_shared<BuiltinProcValue>(&ifProcedure);
  SymbolMap["string?"]=std::make_shared<BuiltinProcValue>(&ifString);
  SymbolMap["symbol?"]=std::make_shared<BuiltinProcValue>(&ifSymbol);
  SymbolMap["car"]=std::make_shared<BuiltinProcValue>(&Rcar);
  SymbolMap["cdr"]=std::make_shared<BuiltinProcValue>(&Rcdr);
  SymbolMap["cons"]=std::make_shared<BuiltinProcValue>(&cons);
  SymbolMap["append"]=std::make_shared<BuiltinProcValue>(&append);
  SymbolMap["length"]=std::make_shared<BuiltinProcValue>(&length);
  SymbolMap["list"]=std::make_shared<BuiltinProcValue>(&list);
  SymbolMap["map"]=std::make_shared<BuiltinProcValue>(Map);
  SymbolMap["filter"]=std::make_shared<BuiltinProcValue>(Filter);
  SymbolMap["reduce"]=std::make_shared<BuiltinProcValue>(Reduce);
  SymbolMap["abs"]=std::make_shared<BuiltinProcValue>(&Abs);
  SymbolMap["expt"]=std::make_shared<BuiltinProcValue>(&expt);
  SymbolMap["quotient"]=std::make_shared<BuiltinProcValue>(&quotient);
  SymbolMap["modulo"]=std::make_shared<BuiltinProcValue>(&modulo);
  SymbolMap["remainder"]=std::make_shared<BuiltinProcValue>(&remainder);
  SymbolMap["eq?"]=std::make_shared<BuiltinProcValue>(&ifEq);
  SymbolMap["equal?"]=std::make_shared<BuiltinProcValue>(&ifEqual);
  SymbolMap["not"]=std::make_shared<BuiltinProcValue>(NotVal);
  SymbolMap["even?"]=std::make_shared<BuiltinProcValue>(&ifEven);
  SymbolMap["odd?"]=std::make_shared<BuiltinProcValue>(&ifOdd);
  SymbolMap["zero?"]=std::make_shared<BuiltinProcValue>(&ifZero);
  SymbolMap["num?"]=std::make_shared<BuiltinProcValue>(&ifNumbers);
  SymbolMap["int?"]=std::make_shared<BuiltinProcValue>(&ifInt);
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
       
        {
          
        return this->apply(proc, args);}
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
   if (typeid(*proc) == typeid(BuiltinProcValue)){
    
    auto Builtin{dynamic_cast<BuiltinProcValue*>(proc.get())};
    auto func=Builtin->asfunc();
    
    ValuePtr result=func(args);
    
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
  
   if (SymbolMap.find(str)!=SymbolMap.end()){
    return SymbolMap[str];}
   if (parent==nullptr)  throw LispError("Variable " + str + " not defined.");
   return parent->lookupBinding(str);
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
  if(size_1!=size_2) throw LispError("The number of parameters provided does not meet the requirements.");
  for(int i{0};i!=size_1;i++)
  {
    result->Push_Back(params[i],args[i]);
  }
  return result;
}