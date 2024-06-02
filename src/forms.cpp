#include "./forms.h"
#include "./error.h"

#include <iostream>
const std::unordered_map<std::string, SpecialFormType*> SPECIAL_FORMS{
    {"define", defineForm},{"quote",quoteForm},{"if",ifForm},{"and",andForm},{"or",orForm}
    ,{"lambda",lambdaForm},{"cond",condForm},{"begin",beginForm},{"let",letForm},
    {"quasiquote",quasiForm},{"unquote",unForm}
    };

ValuePtr defineForm(const std::vector<ValuePtr>& args, EvalEnv& env) 
{
    if (args.size()<2) throw LispError("Error");
    if (auto name = args[0]->asSymbol()) {
        env.Push_Back(*name, std::move(env.eval(args[1])));
    } else {
        if (typeid(*args[0])==typeid(PairValue))
        {
            if(auto name=args[0]->toHead()->asSymbol())
            {
                std::vector<std::string> para{};
                for(auto s:args[0]->toBack()->toVector())
                  para.push_back(s->toString());
                std::vector<ValuePtr> body(args.begin()+1,args.end());
                env.Push_Back(*name,std::make_shared<LambdaValue>(para,body,env.shared_from_this()));
            }
        }
    }
     return std::make_shared<NilValue>();
}

ValuePtr quoteForm(const std::vector<ValuePtr>& args, EvalEnv& env) 
{ 
  if (args.empty())return std::shared_ptr<NilValue>();
  return std::move(args[0]);
}
ValuePtr ifForm(const std::vector<ValuePtr>& args, EvalEnv& env) {
  auto ans=env.eval(args[0]);
  if(ans->toString()=="#f") return std::move(env.eval(args[2]));
  return std::move(env.eval(args[1]));
}
ValuePtr andForm(const std::vector<ValuePtr>& args, EvalEnv& env)
{   
    if(args.empty())return std::make_shared<BooleanValue>(true);
    for(int i{0};i!=args.size();i++)
    {
        auto ans=env.eval(args[i]);
        if(ans->isBoolean())
        if(!ans->asBool())
        return std::make_shared<BooleanValue>(false);
        if(i==args.size()-1) return std::move(ans);
    }return std::move(args[args.size()-1]);
}
ValuePtr orForm(const std::vector<ValuePtr>& args, EvalEnv& env){
    for(int i{0};i!=args.size();i++)
    {
        auto ans=env.eval(args[i]);
        if(ans->toString()!="#f")return std::move(ans);
    }
     return std::make_shared<BooleanValue>(false);
}
ValuePtr lambdaForm(const std::vector<ValuePtr>& args, EvalEnv& env) {
    std::vector<std::string>params{};
    for(auto i:args[0]->toVector())params.push_back(i->toString());
    std::vector<ValuePtr> body(args.begin()+1,args.end());
    return std::make_shared<LambdaValue>(params,body,env.shared_from_this());
}

ValuePtr condForm(const std::vector<ValuePtr>& args, EvalEnv& env) {
    for(int i{0};i!= args.size();i++)
    {
        auto son=args[i]->toVector();
        if(son.size()==0) throw LispError ("The number of parameters provided does not meet the requirements.");
        if(son[0]->toString()=="else"){
            if(i!=args.size()-1)throw LispError ("unDefined");
                for (int j{1};j!=son.size();j++)
                {
                    auto tmp=env.eval(son[j]);
                    if(j==son.size()-1) return std::move(tmp);
                }
                 if(son.size()==1) return std::move(son[0]);
        }
        auto result=env.eval(son[0]);
            if(result->toString()=="#f") continue;
            else {
                for (int j{1};j!=son.size();j++)
                {
                    auto tmp=env.eval(son[j]);
                    if(j==son.size()-1) return std::move(tmp);
                }
                if(son.size()==1) return std::move(result);
            }
        }
    
    throw LispError ("unDefined");
}

ValuePtr beginForm(const std::vector<ValuePtr>& args, EvalEnv& env)
{
    for(int i{0};i!=args.size();i++)
  {
    auto result=env.eval(args[i]);
    if(i==args.size()-1)return std::move(result);
  }
  return std::make_shared<NilValue>();
}

ValuePtr letForm(const std::vector<ValuePtr>& args, EvalEnv& env) 
{
    std::vector<std::string> newArgs;
    std::vector<ValuePtr> value;
    std::vector<ValuePtr> process;
    for(auto a:args[0]->toVector())
    {
        auto tmp=a->toVector();
        if(tmp.size()!=2) throw LispError("The number of parameters provided does not meet the requirements.");
        newArgs.push_back(tmp[0]->toString());
        value.push_back(std::move(env.eval(tmp[1])));
    }
    if(args.size()<2) throw LispError("The number of parameters provided does not meet the requirements.");
    for(int i{1};i!=args.size();i++)
      process.push_back(std::move(args[i]));
    auto Lambda=std::make_shared<LambdaValue>(newArgs,process,env.shared_from_this());
    return std::move(Lambda->apply(value));
}
ValuePtr unForm(const std::vector<ValuePtr>& args, EvalEnv& env)
{
    throw LispError("Error!");
}
ValuePtr quasiForm(const std::vector<ValuePtr>& args, EvalEnv& env) 
{
    std::vector<ValuePtr> result;
    if(args.size()!=1)throw LispError("The number of parameters provided does not meet the requirements.");
    for(auto a:args[0]->toVector())
    {
        if(a->isPair())
        {  auto tmp=a->toVector();
           if(tmp[0]->asSymbol()=="quasiquote") throw LispError("illegal!");
           if(tmp[0]->asSymbol()=="unquote"){
              // std::cout<<tmp[1]->toString();
               result.push_back(std::move(env.eval(tmp[1])));
               continue;
           }
        }
        result.push_back(a);
    }
    return std::move(list(result));
}