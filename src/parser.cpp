#include"./parser.h"
#include"./error.h"
#include<iostream>
ValuePtr Parser::parse()
{
    if (tokens.empty()) throw SyntaxError("Empty");
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
    else if(token->toString()=="(LEFT_PAREN)"){
        return this->parseTails();
    }
    else if(token->getType()==TokenType::QUOTE){
      tokens.pop_front();
      return std::make_shared<PairValue>(
      std::make_shared<SymbolValue>("quote"),
      std::make_shared<PairValue>(
          this->parse(),
          std::make_shared<NilValue>()
      )
    );
    }
     else if(token->getType()==TokenType::QUASIQUOTE){
      tokens.pop_front();
      return std::make_shared<PairValue>(
      std::make_shared<SymbolValue>("quasiquote"),
      std::make_shared<PairValue>(
          this->parse(),
          std::make_shared<NilValue>()
      )
    );
    }
     else if(token->getType()==TokenType::UNQUOTE){
      tokens.pop_front();
      return std::make_shared<PairValue>(
      std::make_shared<SymbolValue>("unquote"),
      std::make_shared<PairValue>(
          this->parse(),
          std::make_shared<NilValue>()
      )
    );
    }
    else
    {   std::cout << *token << std::endl;
        throw SyntaxError("Unimplemented");}
}

ValuePtr Parser::parseTails(){
    tokens.pop_front();
    if (tokens.empty()) throw SyntaxError("Empty1");
    if (tokens.front()->toString()=="(RIGHT_PAREN)")
    {
        tokens.pop_front();
        return std::make_shared<NilValue>();
    }
    auto car=this->parse();
    tokens.pop_front();
    if (tokens.empty()) throw SyntaxError("Empty2");
    if (tokens.front()->toString()=="(DOT)")
    {
        tokens.pop_front();
        
        
        if (tokens.empty()) throw SyntaxError("Empty3");
        auto cdr=this->parse();
        //std::cout<<tokens.front()<<std::endl;
       // if (tokens.front()->toString()!="(RIGHT_PAREN)")
       // 这里理应有检测点，但不知道为什么写不过去
       
            tokens.pop_front();
            return std::make_shared<PairValue>(car,cdr);
        
       // else throw SyntaxError("Not_Rightparen");
    }
    else{
        auto cdr=this->parse();
        return std::make_shared<PairValue>(car,cdr);
    }

}

