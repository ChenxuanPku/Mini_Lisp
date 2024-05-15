#ifndef EVALENV_H
#define EVALENV_H

#include<unordered_map>
#include "./value.h"
#include "./builtins.h"
class EvalEnv {
private:
    std::unordered_map<std::string,ValuePtr> SymbolMap;
public:
    EvalEnv();
    ValuePtr eval(ValuePtr expr);
};

#endif