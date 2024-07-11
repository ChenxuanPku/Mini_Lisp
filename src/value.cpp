
#include "./value.h"

#include <iomanip>
#include <iostream>

#include "./error.h"
#include "./eval_env.h"
BooleanValue::BooleanValue(bool boolvalue) : booleanValue{boolvalue} {}
std::string BooleanValue::toString() {
    return booleanValue ? "#t" : "#f";
}
NumericValue::NumericValue(double num) : numericValue(num) {}
std::string NumericValue::toString() {
    std::string str = std::to_string(numericValue);
    size_t pos = str.find_last_not_of('0');
    if (pos != std::string::npos) {
        str = str.substr(0, pos + 1);
    }
    if (!str.empty() && str.back() == '.') {
        str.pop_back();
    }
    return str;
}
StringValue::StringValue(std::string str) : stringValue{str} {}
std::string StringValue::toString() {
    std::ostringstream os;
    os << 2;
    return os.str();
}
std::string SymbolValue::toString() {
    return symbolValue;
}
SymbolValue::SymbolValue(std::string symbol) : symbolValue(symbol) {}
std::string NilValue::toString() {
    return "()";
}
PairValue::PairValue(ValuePtr car, ValuePtr cdr) : car(car), cdr(cdr) {}
std::string PairValue::toString() {
    std::ostringstream os;
    os << "(" << car->toString();
    ValuePtr pnow = cdr;
    while (typeid(*pnow) == typeid(PairValue)) {
        auto& pair = static_cast<const PairValue&>(*pnow);
        os << " " << (pair.car->toString());
        pnow = pair.cdr;
    }
    if (typeid(*pnow) != typeid(NilValue)) os << " . " << pnow->toString();
    os << ")";
    return os.str();
}
bool Value::isBoolean() {
    return (typeid(*this) == typeid(BooleanValue));
}
bool Value::isNumeric() {
    return (typeid(*this) == typeid(NumericValue));
}
bool Value::isString() {
    return (typeid(*this) == typeid(StringValue));
}
bool Value::isNil() {
    return (typeid(*this) == typeid(NilValue));
}
bool Value::isSymbol() {
    return (typeid(*this) == typeid(SymbolValue));
}
bool Value::isPair() {
    return (typeid(*this) == typeid(PairValue));
}
bool Value::isBuiltin() {
    return (typeid(*this) == typeid(BuiltinProcValue));
}
bool Value::isLambda() {
    return (typeid(*this) == typeid(LambdaValue));
}
std::vector<ValuePtr> Value::toVector() {
    std::vector<ValuePtr> Vec{};
    if (typeid(*this) == typeid(NilValue))
        return Vec;
    else
        throw LispError(this->toString() + " should be a list.");
}
std::vector<ValuePtr> PairValue::toVector() {
    std::vector<ValuePtr> Vec{};
    if (typeid(*this) == typeid(NilValue)) return Vec;
    if (car != nullptr) {
        Vec.push_back(car);
    }
    if (cdr != nullptr)
        if (typeid(*cdr) != typeid(NilValue)) {
            if (typeid(*cdr) != typeid(PairValue))
                Vec.push_back(cdr);
            else {
                for (auto i : cdr->toVector())
                    if (typeid(*i) != typeid(NilValue)) Vec.push_back(i);
            }
        }

    return Vec;
}
std::optional<std::string> Value::asSymbol() {
    return std::nullopt;
}
std::optional<std::string> SymbolValue::asSymbol() {
    return symbolValue;
}
BuiltinProcValue::BuiltinProcValue(std::function<BuiltinFuncType> func)
    : func(func) {}

std::string BuiltinProcValue::toString() {
    return "#<procedure>";
}
double Value::asNumber() {
    throw LispError("It should be a numerical value.");
}
double NumericValue::asNumber() {
    return numericValue;
}

bool Value::asBool() {
    throw TypeError("It should be a booleanvalue.");
}
bool BooleanValue::asBool() {
    return booleanValue;
}
std::function<BuiltinFuncType> BuiltinProcValue::asfunc() {
    if (func == nullptr) throw LispError("emptyPtr");
    return func;
}
ValuePtr Value::toBack() {
    throw LispError("It should be a pair value.");
}
ValuePtr Value::toHead() {
    throw LispError("It should be a pair value.");
}
ValuePtr PairValue::toHead() {
    return car;
}

ValuePtr PairValue::toBack() {
    return cdr;
}

LambdaValue::LambdaValue(std::vector<std::string>& params,
                         std::vector<ValuePtr>& body,
                         std::shared_ptr<EvalEnv> env)
    : params(params), body(body), env(env) {}
std::string LambdaValue::toString() {
    return "#<procedure>";
}
ValuePtr LambdaValue::apply(const std::vector<ValuePtr>& args) {
    std::shared_ptr<EvalEnv> NewEnv = env->createChild(params, args);
    for (int i{0}; i != body.size(); i++) {
        auto result = NewEnv->eval(body[i]);
        if (i == body.size() - 1) return result;
    }
    throw LispError("unDefined");
}

std::string Value::asString() {
    throw TypeError("It should be a string value.");
}
std::string StringValue::asString() {
    return stringValue;
}

bool Value::isList() {
    if (isNil()) return true;
    if (isPair()) {
        ValuePtr now{toBack()};
        while (now->isPair()) {
            now = now->toBack();
            if (now->isNil()) return true;
        }
        if (now->isNil()) return true;
        return false;
    } else
        return true;
}