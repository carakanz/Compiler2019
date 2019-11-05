//
// Created by Zinenko Dmytro on 24.10.2019.
//
#pragma once
#include <iostream>
#include <functional>

#if ! defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

#include "parser.hh"

using Token = yy::parser::token::yytokentype;

namespace BisonBuilder {
    class BisonBuilder : public yyFlexLexer {
    public:
        int parse(std::istream &input);

        int yylex() override;
        int yylex(yy::parser::semantic_type* const value=nullptr);
        Token process(Token token);

        yy::parser::semantic_type* yylval = nullptr;
    };
}
