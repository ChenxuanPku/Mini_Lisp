#include <iostream>
#include <string>
#include <fstream>
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
bool CheckParen(const std::string& line) {
    int count = 0;
    for (char c : line) {
        if (c == '(') {
            count++;
        } else if (c == ')') {
            count--;
        }
    }
    return count == 0;
}
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
    
   
    std::shared_ptr<EvalEnv> env = EvalEnv::createGlobal();
    std::string line;
    std::string result;
    std::ifstream inputFile(filename);
    int num{0};
    while(std::getline(inputFile,line))
    {   
        
        if (line.empty()) {
            continue;
        }
        result += line;
        if(CheckParen(result))
        {  
           if(!result.empty())
           {
            auto tokens = Tokenizer::tokenize(result);
            Parser parser(std::move(tokens)); 
            auto value = parser.parse();
            auto Result = env->eval(std::move(value));
           result.clear();}
        }if (!result.empty()) {
                result[result.length() - 1]=' ';  
        }
        

    }
    
}
int main(int argc, char** argv) {
      
     // RJSJ_TEST(TestCtx, Lv2, Lv3, Lv4, Lv5, Lv5Extra, Lv6, Lv7, Lv7Lib, Sicp);
   try { if (argc==2)
    {
       if (strcmp(argv[1],"-r")==0) REPL();
       else throw SyntaxError("wrong mode");
    }
    else if(argc==3)
    {
      if (strcmp(argv[1],"-f")==0) FileMode(argv[2]);
      else throw SyntaxError("wrong mode");
    }
    else throw SyntaxError("wrong mode");
    }catch (std::runtime_error& e) {
            std::cerr << "Error: " << e.what() << std::endl;}
   
    return 0;
}

