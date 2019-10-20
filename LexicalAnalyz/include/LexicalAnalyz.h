//
// Created by Zinenko Dmytro on 20.10.2019.
//

#pragma once

#include "Tokens.h"
#include <iostream>
#include <functional>
#if ! defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

class LexicalAnalyz : public yyFlexLexer {
public:
    using TokenProcessor =
            std::function<void(Token token, const std::string& metadata, int column, int line)>;
    LexicalAnalyz(TokenProcessor token_processor)
        : token_processor_(token_processor) {}
    void parseStream(std::istream& input);
    virtual int yylex(); // Генерируется Flex
    Token Process(Token token);
    void UpdatePos();
    void Space();
    void EndOfLine();

    int column_ = 0;         // Положение
    int line_ = 0;
    TokenProcessor token_processor_;
private:
};
