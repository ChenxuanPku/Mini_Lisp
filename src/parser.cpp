#include"./parser.h"
ValuePtr Parser::parse()
{
    auto token=tokens.front();
    if(token->getType()==TokenType::NUMERIC_LITERAL)
    {
         auto value = static_cast<NumericLiteralToken&>(*token).getValue();
        return std::make_shared<NumericValue>(value);
    }
    else
     if(token->getType()==TokenType::NUMERIC_LITERAL)
    {
         auto value = static_cast<NumericLiteralToken&>(*token).getValue();
        return std::make_shared<NumericValue>(value);
    }
}