#include "./builtins.h"
#include "./error.h"
ValuePtr add(const std::vector<ValuePtr>& params){
  double result=0;
  for (const auto& i:params)
  {
    if(!i->isNumeric())
      throw LispError("Cannot add a non-numeric value.");
    result+=i->asNumber();
    
  }return std::make_shared<NumericValue>(result);
}