#ifndef ERROR_H
#define ERROR_H

#include <stdexcept>
#include <vector>

class SyntaxError : public std::runtime_error {
public:
    using runtime_error::runtime_error;
};
class LispError : public std::runtime_error {
public:
    using runtime_error::runtime_error;
};
class TypeError : public std::runtime_error {
public:
    using runtime_error::runtime_error;
};
class SizeError : public std::runtime_error{
public:
    using runtime_error::runtime_error;
};
template <typename T>
void testSize(const std::vector<T>& params, int setNum)
{
    int tmpSize=params.size();
    if(tmpSize!=setNum)
      throw SizeError("The number of parameters provided does not meet the requirements.");
}

#endif