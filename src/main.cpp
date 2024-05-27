#include <iostream>
#include <string>
#include "./error.h"
#include "./tokenizer.h"
#include "./value.h"
#include "./parser.h"
#include "./eval_env.h"
#include "./builtins.h"
#include "rjsj_test.hpp"

struct TestCtx {
    std::shared_ptr<EvalEnv> env = EvalEnv::createGlobal();
    std::string eval(std::string input) {
        auto tokens = Tokenizer::tokenize(input);
        Parser parser(std::move(tokens));
        auto value = parser.parse();
        auto result = env->eval(std::move(value));
        return result->toString();
    }
};
void  REPL()
{
    std::shared_ptr<EvalEnv> env = EvalEnv::createGlobal();
    while (true) {
        try {
            std::cout << ">>> " ;
            std::string line;
            std::getline(std::cin, line);
            if (std::cin.eof()) {
                std::exit(0);
            }
            auto tokens = Tokenizer::tokenize(line);
            Parser parser(std::move(tokens)); // TokenPtr 不支持复制
            auto value = parser.parse();
            auto result = env->eval(std::move(value));
            std::cout << result->toString() << std::endl;
        } catch (std::runtime_error& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
}
void FileMode(const char* filename)
{

}
int main(int argc, char** argv) {
     // RJSJ_TEST(TestCtx, Lv2, Lv3, Lv4, Lv5, Lv5Extra, Lv6, Lv7, Lv7Lib, Sicp);
   try { if (argc==2)
    {
       if (argv[1]=="-r") REPL();
       else throw SyntaxError("wrong mode");
    }
    else if(argc==3)
    {
      if (argv[1]=="-f") FileMode(argv[2]);
      else throw SyntaxError("wrong mode");
    }
    else throw SyntaxError("wrong mode");
    }catch (std::runtime_error& e) {
            std::cerr << "Error: " << e.what() << std::endl;}
    return;
}

