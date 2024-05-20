#ifndef EVALENV_H
#define EVALENV_H

#include<unordered_map>
#include "./value.h"
#include "./builtins.h"
class EvalEnv {
private:
    std::unordered_map<std::string,ValuePtr> SymbolMap;
    std::vector<ValuePtr> evalList(ValuePtr expr);
    ValuePtr apply(ValuePtr proc, std::vector<ValuePtr> args);
   // std::vector<ValuePtr> ToVector(ValuePtr expr);
public:
    EvalEnv();
    ValuePtr eval(ValuePtr expr);
    void Push_Back(std::string str,ValuePtr valueptr );
    
};
using SpecialFormType = ValuePtr(const std::vector<ValuePtr>&, EvalEnv&);
ValuePtr defineForm(const std::vector<ValuePtr>& args, EvalEnv& env) ;
ValuePtr quoteForm(const std::vector<ValuePtr>& args, EvalEnv& env) ;
#endif