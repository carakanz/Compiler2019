//
// Created by Zinenko Dmytro on 24.10.2019.
//
#pragma once
#include <iostream>
#include <functional>

#if ! defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

#include <parser.hh>

using FlexToken = BisonParser::Parser::token::yytokentype;

namespace BisonBuilder {
    class Builder : public yyFlexLexer {
    public:
        int parse(std::istream &input);
        template <class Tree>
        Tree get_tree() {
            return Tree(std::move(root));
        }

        BisonParser::Parser::symbol_type get_next_token();
        BisonParser::Parser::symbol_type process(FlexToken token);

        ~Builder() override = default;

        std::unique_ptr<GoalNode> root;

        Position old_position = {};
        Position new_position = {};
    };
}
