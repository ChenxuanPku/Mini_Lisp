#include"./parser.h"
#include"./error.h"
ValuePtr Parser::parse()
{
    auto token=std::move(tokens.front());//智能指针不能复制
    if(token->getType()==TokenType::NUMERIC_LITERAL)
    {
         auto value = static_cast<NumericLiteralToken&>(*token).getValue();
        return std::make_shared<NumericValue>(value);
    }
    else
     if(token->getType()==TokenType::BOOLEAN_LITERAL)
    {
         auto value = static_cast<BooleanLiteralToken&>(*token).getValue();
        return std::make_shared<BooleanValue>(value);
    }
    else if
    (token->getType()==TokenType::STRING_LITERAL)
    {
         auto value = static_cast<StringLiteralToken&>(*token).getValue();
        return std::make_shared<StringValue>(value);
    }
    else throw SyntaxError("Unimplemented");
}

