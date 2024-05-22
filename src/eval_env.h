#ifndef EVALENV_H
#define EVALENV_H

#include<unordered_map>
//#include "./value.h"
#include "./builtins.h"
class Value;
using ValuePtr = std::shared_ptr<Value>; 
class EvalEnv : public std::enable_shared_from_this<EvalEnv>  {
private:
    
    std::vector<ValuePtr> evalList(ValuePtr expr);
    ValuePtr apply(ValuePtr proc, std::vector<ValuePtr> args);
   
   // std::vector<ValuePtr> ToVector(ValuePtr expr);

    std::unordered_map<std::string,ValuePtr> SymbolMap;
    EvalEnv();
public:
    static std::shared_ptr<EvalEnv> createGlobal();
    std::shared_ptr<EvalEnv> createChild(const std::vector<std::string>& params, const std::vector<ValuePtr>& args);
    ValuePtr eval(ValuePtr expr);
    void Push_Back(std::string str,ValuePtr valueptr );
    ValuePtr lookupBinding(std::string str);
    ValuePtr defineBinding(); 
    std::shared_ptr<EvalEnv> parent{nullptr};
};

#endif