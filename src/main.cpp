#include <fstream>
#include <iostream>
#include <string>

#include "./builtins.h"
#include "./error.h"
#include "./eval_env.h"
#include "./parser.h"
#include "./tokenizer.h"
#include "./value.h"
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
    bool doubleQuote = true;
    int count = 0;
    bool ttt = false;
    for(int i{0};i!=line.size();i++)
    {
        if (line[i] == '"') 
        {if(i==0)doubleQuote = !doubleQuote;
        else if(line[i-1]!='\\')doubleQuote = !doubleQuote;
        }
        if (doubleQuote) {
            if (line[i] == '(') {
                count++;
            } else if (line[i] == ')') {
                count--;
            }
        }
    }
    return count == 0;
}
void REPL() {
    std::shared_ptr<EvalEnv> env = EvalEnv::createGlobal();

    while (true) try {
            std::cout << ">>> ";
            std::string line;
            std::string str;
            while (true) {
                std::getline(std::cin, line);
                if (std::cin.eof()) {
                    std::exit(0);
                }
                str += " ";
                str += line;
                if (CheckParen(str)) {
                    if (!str.empty()) {
                        auto tokens = Tokenizer::tokenize(str);
                        Parser parser(
                            std::move(tokens));  // TokenPtr 不支持复制
                        auto value = parser.parse();
                        auto result = env->eval(std::move(value));
                        std::cout << result->toString() << std::endl;
                    }
                    break;
                } else
                    std::cout << "```";
            }
        } catch (std::runtime_error& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
}
void FileMode(const char* filename) {
    std::shared_ptr<EvalEnv> env = EvalEnv::createGlobal();
    std::string line;
    std::string result;
    std::ifstream inputFile(filename);
    int num{0};
    while (std::getline(inputFile, line)) {
        if (line.empty()) {
            continue;
        }
        result += line;
        if (CheckParen(result)) {
            if (!result.empty()) {
                // std::cout<<result<<std::endl;
                auto tokens = Tokenizer::tokenize(result);
                Parser parser(std::move(tokens));
                auto value = parser.parse();
                env->eval(std::move(value));
                result.clear();
            }
        }
    }
}
int main(int argc, char** argv) {
     RJSJ_TEST(TestCtx, Lv2, Lv3, Lv4, Lv5, Lv5Extra, Lv6, Lv7, Lv7Lib, Sicp);
    try {
        if (argc == 2) {
            if (strcmp(argv[1], "-r") == 0)
                REPL();
            else
                throw SyntaxError("wrong mode");
        } else if (argc == 3) {
            if (strcmp(argv[1], "-f") == 0)
                FileMode(argv[2]);
            else
                throw SyntaxError("wrong mode");
        } else
            throw SyntaxError("wrong mode");
    } catch (std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}
