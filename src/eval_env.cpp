#include "./eval_env.h"

#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>

#include "./builtins.h"
#include "./error.h"
#include "./forms.h"
#include "./value.h"
EvalEnv::EvalEnv() {
    std::function<BuiltinFuncType> Apply =
        [this](const std::vector<ValuePtr>& params) {
            if (params.size() != 2)
                throw LispError(
                    "The number of parameters provided does not meet the "
                    "requirements.");
            if (params[1]->isList())
                return this->apply(params[0], params[1]->toVector());
            else
                throw TypeError("It should be a list.");
        };

    std::function<BuiltinFuncType> Eval =
        [this](const std::vector<ValuePtr>& params) {
            return this->eval(params[0]);
        };
    std::function<BuiltinFuncType> Map =
        [this](const std::vector<ValuePtr>& params) {
            if (params.size() != 2)
                throw LispError(
                    "The number of parameters provided does not meet the "
                    "requirements.");
            std::vector<ValuePtr> result;
            if (params[1]->isList()) {
                for (auto a : params[1]->toVector()) {
                    std::vector<ValuePtr> tmp{a};
                    result.push_back(this->apply(params[0], tmp));
                }
                return list(result);
            } else
                throw TypeError("It should be a list.");
        }

    ;
    std::function<BuiltinFuncType> Filter =
        [this](const std::vector<ValuePtr>& params) {
            if (params.size() != 2)
                throw LispError(
                    "The number of parameters provided does not meet the "
                    "requirements.");
            std::vector<ValuePtr> result{};
            if (params[1]->isList()) {
                for (auto a : params[1]->toVector()) {
                    std::vector<ValuePtr> tmp{a};
                    auto ans = this->apply(params[0], tmp);

                    if (ans->isBoolean()) {
                        if (ans->asBool()) result.push_back(a);
                    }
                }
                return list(result);
            } else
                throw TypeError("It should be a list.");
        };
    std::function<BuiltinFuncType> Reduce =
        [this](const std::vector<ValuePtr>& params) {
            if (params.size() != 2)
                throw LispError(
                    "The number of parameters provided does not meet the "
                    "requirements.");
            if (params[1]->isNil())
                throw LispError("Cannot act on a empty value.");
            std::vector<ValuePtr> vec = params[1]->toVector();
            for (auto i{vec.size() - 2}; i != -1; i--) {
                std::vector<ValuePtr> tmp{vec[i], vec[i + 1]};
                vec[i] = this->apply(params[0], tmp);
            }
            return vec[0];
        };
    std::function<BuiltinFuncType> NotVal =
        [this](const std::vector<ValuePtr>& params) {
            if (params.size() != 1)
                throw LispError(
                    "The number of parameters provided does not meet the "
                    "requirements.");
            // auto ans=this->eval(params[0]);
            if (params[0]->isBoolean())
                if (!params[0]->asBool())
                    return std::make_shared<BooleanValue>(true);
            return std::make_shared<BooleanValue>(false);
        };

    SymbolMap["eval"] = std::make_shared<BuiltinProcValue>(Eval);
    SymbolMap["apply"] = std::make_shared<BuiltinProcValue>(Apply);
    SymbolMap["+"] = std::make_shared<BuiltinProcValue>(&add);
    SymbolMap["print"] = std::make_shared<BuiltinProcValue>(&print);
    SymbolMap["*"] = std::make_shared<BuiltinProcValue>(&times);
    SymbolMap[">"] = std::make_shared<BuiltinProcValue>(&greater);
    SymbolMap["<"] = std::make_shared<BuiltinProcValue>(&smaller);
    SymbolMap[">="] = std::make_shared<BuiltinProcValue>(&ge);
    SymbolMap["<="] = std::make_shared<BuiltinProcValue>(&le);
    SymbolMap["="] = std::make_shared<BuiltinProcValue>(&EEqual);
    SymbolMap["-"] = std::make_shared<BuiltinProcValue>(&minor);
    SymbolMap["/"] = std::make_shared<BuiltinProcValue>(&divide);
    SymbolMap["display"] = std::make_shared<BuiltinProcValue>(&display);
    SymbolMap["displayln"] = std::make_shared<BuiltinProcValue>(&displayln);
    SymbolMap["error"] = std::make_shared<BuiltinProcValue>(&error);
    SymbolMap["exit"] = std::make_shared<BuiltinProcValue>(&Exit);
    SymbolMap["newline"] = std::make_shared<BuiltinProcValue>(&newline);
    SymbolMap["atom?"] = std::make_shared<BuiltinProcValue>(&ifAtom);
    SymbolMap["boolean?"] = std::make_shared<BuiltinProcValue>(&ifBoolean);
    SymbolMap["integer?"] = std::make_shared<BuiltinProcValue>(&ifInteger);
    SymbolMap["list?"] = std::make_shared<BuiltinProcValue>(&ifList);
    SymbolMap["number?"] = std::make_shared<BuiltinProcValue>(&ifNumber);
    SymbolMap["null?"] = std::make_shared<BuiltinProcValue>(&ifNull);
    SymbolMap["pair?"] = std::make_shared<BuiltinProcValue>(&ifPair);
    SymbolMap["procedure?"] = std::make_shared<BuiltinProcValue>(&ifProcedure);
    SymbolMap["string?"] = std::make_shared<BuiltinProcValue>(&ifString);
    SymbolMap["symbol?"] = std::make_shared<BuiltinProcValue>(&ifSymbol);
    SymbolMap["car"] = std::make_shared<BuiltinProcValue>(&Rcar);
    SymbolMap["cdr"] = std::make_shared<BuiltinProcValue>(&Rcdr);
    SymbolMap["cons"] = std::make_shared<BuiltinProcValue>(&cons);
    SymbolMap["append"] = std::make_shared<BuiltinProcValue>(&append);
    SymbolMap["length"] = std::make_shared<BuiltinProcValue>(&length);
    SymbolMap["list"] = std::make_shared<BuiltinProcValue>(&list);
    SymbolMap["map"] = std::make_shared<BuiltinProcValue>(Map);
    SymbolMap["filter"] = std::make_shared<BuiltinProcValue>(Filter);
    SymbolMap["reduce"] = std::make_shared<BuiltinProcValue>(Reduce);
    SymbolMap["abs"] = std::make_shared<BuiltinProcValue>(&Abs);
    SymbolMap["expt"] = std::make_shared<BuiltinProcValue>(&expt);
    SymbolMap["quotient"] = std::make_shared<BuiltinProcValue>(&quotient);
    SymbolMap["modulo"] = std::make_shared<BuiltinProcValue>(&modulo);
    SymbolMap["remainder"] = std::make_shared<BuiltinProcValue>(&remainder);
    SymbolMap["eq?"] = std::make_shared<BuiltinProcValue>(&ifEq);
    SymbolMap["equal?"] = std::make_shared<BuiltinProcValue>(&ifEqual);
    SymbolMap["not"] = std::make_shared<BuiltinProcValue>(NotVal);
    SymbolMap["even?"] = std::make_shared<BuiltinProcValue>(&ifEven);
    SymbolMap["odd?"] = std::make_shared<BuiltinProcValue>(&ifOdd);
    SymbolMap["zero?"] = std::make_shared<BuiltinProcValue>(&ifZero);
    SymbolMap["num?"] = std::make_shared<BuiltinProcValue>(&ifNumbers);
    SymbolMap["int?"] = std::make_shared<BuiltinProcValue>(&ifInt);
}

void EvalEnv::Push_Back(std::string str, ValuePtr valueptr) {
    SymbolMap[str] = valueptr;
}
ValuePtr EvalEnv::eval(ValuePtr expr) {
    if (expr->isSymbol()) {
        if (auto name = expr->asSymbol()) {
            return lookupBinding(*name);
        }
    }
    if (expr->isBoolean() || expr->isNumeric() || expr->isString())
        return std::move(expr);
    if (expr->isNil()) throw LispError("Evaluating nil is prohibited.");
    if (expr->isPair()) {
        using namespace std::literals;  // 使用 s 后缀
        if (expr->toHead()->isSymbol()) {
            if (auto name = expr->toHead()->asSymbol()) {
                {
                    auto it = SPECIAL_FORMS.find(*name);

                    if (it != SPECIAL_FORMS.end()) {
                        if ((expr->toBack()->isList()))
                            return (it->second)(expr->toBack()->toVector(),
                                                *this);
                        else
                            throw TypeError("It should be a list.");
                    }
                }
                ValuePtr proc = lookupBinding(*name);
                if (!expr->toBack()->isList())
                    throw TypeError("It should be a list.");
                std::vector<ValuePtr> args = evalList(expr->toBack());
                { return this->apply(proc, args); }
            }
        } else {
            ValuePtr proc = this->eval(expr->toHead());
            if (!proc->isLambda() && !proc->isBuiltin())
                throw LispError(proc->toString() + " not a procedure.");
            if (!expr->toBack()->isList())
                throw TypeError("It should be a list.");
            std::vector<ValuePtr> args = evalList(expr->toBack());
            return this->apply(proc, args);
        }
    }
    if (expr->isBuiltin()) {
        return std::move(expr);
    }
    throw LispError("Undefined type.");
}

std::vector<ValuePtr> EvalEnv::evalList(ValuePtr expr) {
    std::vector<ValuePtr> result;
    std::ranges::transform(expr->toVector(), std::back_inserter(result),
                           [this](ValuePtr v) { return this->eval(v); });
    return result;
}

ValuePtr EvalEnv::apply(ValuePtr proc, std::vector<ValuePtr> args) {
    if (proc->isBuiltin()) {
        auto Builtin{dynamic_cast<BuiltinProcValue*>(proc.get())};
        auto func = Builtin->asfunc();

        ValuePtr result = func(args);

        return result;
    } else {
        if (proc->isLambda()) {
            return (dynamic_cast<LambdaValue*>(proc.get()))->apply(args);
        }
        throw LispError("Apply Unimplemented " + proc->toString());
    }
}
ValuePtr EvalEnv::lookupBinding(std::string str) {
    if (SymbolMap.find(str) != SymbolMap.end()) {
        return SymbolMap[str];
    }
    if (parent == nullptr) throw LispError("Variable " + str + " not defined.");
    return parent->lookupBinding(str);
}
std::shared_ptr<EvalEnv> EvalEnv::createGlobal() {
    return std::shared_ptr<EvalEnv>(new EvalEnv());
}
std::shared_ptr<EvalEnv> EvalEnv::createChild(
    const std::vector<std::string>& params, const std::vector<ValuePtr>& args) {
    auto result = std::shared_ptr<EvalEnv>(new EvalEnv());
    result->parent = this->shared_from_this();
    int size_1 = params.size();
    int size_2 = args.size();
    if (size_1 != size_2)
        throw LispError(
            "The number of parameters provided does not meet the "
            "requirements.");
    for (int i{0}; i != size_1; i++) {
        result->Push_Back(params[i], args[i]);
    }
    return result;
}
