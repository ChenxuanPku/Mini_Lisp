#include <iostream>
#include <string>

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
int main() {
   //RJSJ_TEST(TestCtx,  Lv7Lib);
   
    std::shared_ptr<EvalEnv> env = EvalEnv::createGlobal();
  // auto tmp =env->lookupBinding("apply");
 //  auto Builtin{dynamic_cast<BuiltinProcValue*>(tmp.get())};
   //std::cout<<Builtin->asfunc()<<std::endl;
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
