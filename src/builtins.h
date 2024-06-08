#ifndef BUILTINS_H
#define BUILTINS_H
#include "./value.h"

ValuePtr add(const std::vector<ValuePtr>& params);      //
ValuePtr minor(const std::vector<ValuePtr>& params);    //
ValuePtr print(const std::vector<ValuePtr>& params);    //
ValuePtr times(const std::vector<ValuePtr>& params);    //
ValuePtr greater(const std::vector<ValuePtr>& params);  //
ValuePtr smaller(const std::vector<ValuePtr>& params);
ValuePtr display(const std::vector<ValuePtr>& params);    //
ValuePtr displayln(const std::vector<ValuePtr>& params);  //
ValuePtr error(const std::vector<ValuePtr>& params);      //

ValuePtr Exit(const std::vector<ValuePtr>& params);       //
ValuePtr newline(const std::vector<ValuePtr>& params);    //
ValuePtr ifAtom(const std::vector<ValuePtr>& params);     //
ValuePtr ifBoolean(const std::vector<ValuePtr>& params);  //
ValuePtr ifInteger(const std::vector<ValuePtr>& params);  //
ValuePtr ifList(const std::vector<ValuePtr>& params);
ValuePtr ifNumber(const std::vector<ValuePtr>& params);
ValuePtr ifNumbers(const std::vector<ValuePtr>& params);    //
ValuePtr ifNull(const std::vector<ValuePtr>& params);       //
ValuePtr ifPair(const std::vector<ValuePtr>& params);       //
ValuePtr ifProcedure(const std::vector<ValuePtr>& params);  //
ValuePtr ifString(const std::vector<ValuePtr>& params);     //
ValuePtr ifSymbol(const std::vector<ValuePtr>& params);     //
ValuePtr ifEven(const std::vector<ValuePtr>& params);
ValuePtr ifOdd(const std::vector<ValuePtr>& params);
ValuePtr ifZero(const std::vector<ValuePtr>& params);
ValuePtr ifInt(const std::vector<ValuePtr>& params);
ValuePtr append(const std::vector<ValuePtr>& params);  // list
ValuePtr Rcar(const std::vector<ValuePtr>& params);
ValuePtr Rcdr(const std::vector<ValuePtr>& params);
ValuePtr cons(const std::vector<ValuePtr>& params);
ValuePtr length(const std::vector<ValuePtr>& params);
ValuePtr list(const std::vector<ValuePtr>& params);
// ValuePtr map(const std::vector<ValuePtr>& params);
// ValuePtr filter(const std::vector<ValuePtr>& params);
// ValuePtr reduce(const std::vector<ValuePtr>& params);
ValuePtr divide(const std::vector<ValuePtr>& params);
ValuePtr Abs(const std::vector<ValuePtr>& params);
ValuePtr expt(const std::vector<ValuePtr>& params);
ValuePtr quotient(const std::vector<ValuePtr>& params);
ValuePtr modulo(const std::vector<ValuePtr>& params);
ValuePtr remainder(const std::vector<ValuePtr>& params);
ValuePtr ifEq(const std::vector<ValuePtr>& params);
ValuePtr ifEqual(const std::vector<ValuePtr>& params);
// ValuePtr notVal(const std::vector<ValuePtr>& params);
ValuePtr EEqual(const std::vector<ValuePtr>& params);
ValuePtr ge(const std::vector<ValuePtr>& params);
ValuePtr le(const std::vector<ValuePtr>& params);

#endif
