#include "./parser.h"

#include <iostream>

#include "./error.h"
ValuePtr Parser::parse() {
    if (tokens.empty()) throw SyntaxError("The token is imcomplement.");
    auto token = std::move(tokens.front());
    if (token->getType() == TokenType::IDENTIFIER) {
        auto value = static_cast<IdentifierToken&>(*token).getName();
        tokens.pop_front();
        return std::make_shared<SymbolValue>(std::move(value));
    }
    if (token->getType() == TokenType::NUMERIC_LITERAL) {
        auto value = static_cast<NumericLiteralToken&>(*token).getValue();
        tokens.pop_front();
        return std::make_shared<NumericValue>(std::move(value));
    }

    if (token->getType() == TokenType::BOOLEAN_LITERAL) {
        auto value = static_cast<BooleanLiteralToken&>(*token).getValue();
        tokens.pop_front();
        return std::make_shared<BooleanValue>(std::move(value));
    }
    if (token->getType() == TokenType::STRING_LITERAL) {
        auto value = static_cast<StringLiteralToken&>(*token).getValue();
        tokens.pop_front();
        return std::make_shared<StringValue>(std::move(value));
    } else if (token->toString() == "(LEFT_PAREN)") {
        tokens.pop_front();
        return this->parseTails();
    } else if (token->getType() == TokenType::QUOTE) {
        tokens.pop_front();
        return std::make_shared<PairValue>(
            std::make_shared<SymbolValue>("quote"),
            std::make_shared<PairValue>(this->parse(),
                                        std::make_shared<NilValue>()));
    } else if (token->getType() == TokenType::QUASIQUOTE) {
        tokens.pop_front();
        return std::make_shared<PairValue>(
            std::make_shared<SymbolValue>("quasiquote"),
            std::make_shared<PairValue>(this->parse(),
                                        std::make_shared<NilValue>()));
    } else if (token->getType() == TokenType::UNQUOTE) {
        tokens.pop_front();
        return std::make_shared<PairValue>(
            std::make_shared<SymbolValue>("unquote"),
            std::make_shared<PairValue>(this->parse(),
                                        std::make_shared<NilValue>()));
    } else {
        throw SyntaxError("UnDefined token");
    }
}

ValuePtr Parser::parseTails() {
    if (tokens.empty()) throw SyntaxError("The token is imcomplement.");
    if (tokens.front()->toString() == "(RIGHT_PAREN)") {
        tokens.pop_front();
        return std::make_shared<NilValue>();
    }
    auto car = this->parse();

    if (tokens.empty()) throw SyntaxError("The token is imcomplement.");
    if (tokens.front()->toString() == "(DOT)") {
        tokens.pop_front();
        if (tokens.empty()) throw SyntaxError("The token is imcomplement.");
        auto cdr = this->parse();
        return std::make_shared<PairValue>(std::move(car), std::move(cdr));
    } else {
        auto cdr = this->parseTails();
        return std::make_shared<PairValue>(std::move(car), std::move(cdr));
    }
}
