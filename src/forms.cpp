#include "./forms.h"
#include "./error.h"
const std::unordered_map<std::string, SpecialFormType*> SPECIAL_FORMS{
    {"define", defineForm},{"quote",quoteForm},{"if",ifForm},{"and",andForm},{"or",orForm}
    ,{"lambda",lambdaForm}
    };


ValuePtr defineForm(const std::vector<ValuePtr>& args, EvalEnv& env) 
{
    if (auto name = args[0]->asSymbol()) {
        env.Push_Back(*name, env.eval(args[1]));
    } else {
        if (typeid(*args[0])==typeid(PairValue))
        {
            if(auto name=args[0]->toHead()->asSymbol())
            {
                std::vector<std::string> para{};
                for(auto s:args[0]->toBack()->toVector())
                  para.push_back(s->toString());
                std::vector<ValuePtr> body(args.begin()+1,args.end());
                env.Push_Back(*name,std::make_shared<LambdaValue>(para,body));
            }
        }
    }
     return std::make_shared<NilValue>();
}

ValuePtr quoteForm(const std::vector<ValuePtr>& args, EvalEnv& env) 
{ 
  if (args.empty())return std::shared_ptr<NilValue>();
  //for(auto i:args)std::cout<<i->toString()<<" ";
  return std::move(args[0]);
}
ValuePtr ifForm(const std::vector<ValuePtr>& args, EvalEnv& env) {
  auto ans=env.eval(args[0]);
  //std::cout<<ans->toString()<<std::endl;
  if(ans->toString()=="#f") return env.eval(args[2]);
  return env.eval(args[1]);
}
ValuePtr andForm(const std::vector<ValuePtr>& args, EvalEnv& env)
{   
    if(args.empty())return std::make_shared<BooleanValue>(true);
    for(int i{0};i!=args.size();i++)
    {
        auto ans=env.eval(args[i]);
        if(ans->toString()=="#f")
        return std::make_shared<BooleanValue>(false);
        if(i==args.size()-1) return ans;
    }return args[args.size()-1];
}
ValuePtr orForm(const std::vector<ValuePtr>& args, EvalEnv& env){
    for(int i{0};i!=args.size();i++)
    {
        auto ans=env.eval(args[i]);
        if(ans->toString()!="#f")return ans;

    }
     return std::make_shared<BooleanValue>(false);
}
ValuePtr lambdaForm(const std::vector<ValuePtr>& args, EvalEnv& env) {
    
    std::vector<std::string>params{};
    for(auto i:args[0]->toVector())params.push_back(i->toString());
    std::vector<ValuePtr> body{args[1]->toVector()};
    return std::make_shared<LambdaValue>(params,body);
}