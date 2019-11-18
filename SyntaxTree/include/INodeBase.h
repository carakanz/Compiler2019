//
// Created by Zinenko Dmytro on 27.10.2019.
//
#pragma once

#include "string"
#include <iostream>

namespace SyntaxTree {
    enum NodeType {
        TYPE_INT,
        TYPE_BOOLEAN,
        TYPE_VOID,
        TYPE_STRING,
        TYPE_USER,
        TYPE_ARRAY,
        IDENTIFIER_NODE,
        EXPRESSION_STATIC_METHOD_CALL,
        EXPRESSION_IDENTIFIER,
        EXPRESSION_BINARY_OPERATION,
        EXPRESSION_INDEX,
        EXPRESSION_GET_LENGTH,
        EXPRESSION_METHOD_CALL,
        EXPRESSION_INTEGER_LITERAL,
        EXPRESSION_BOOLEAN_LITERAL,
        EXPRESSION_THIS,
        EXPRESSION_NEW_ARRAY,
        EXPRESSION_NEW,
        EXPRESSION_NOT_OPERATION,
        EXPRESSION_ROUND_BRACKETS,
        STATEMENT_LIST,
        STATEMENT_EMPTY,
        STATEMENT_IF,
        STATEMENT_WHILE,
        STATEMENT_PRINTLN,
        STATEMENT_ASSIGN,
        STATEMENT_ASSIGN_ARRAY,
        STATEMENT_RETURN,
        PAIR_TYPE_IDENTIFIER,
        DECLARATION_VAR,
        DECLARATION_METHOD,
        DECLARATION_CLASS,
        GOAL
    };

    class INodeBase {
    public:
        struct Position {
            size_t line;
            size_t column;
        };
        [[nodiscard]] virtual NodeType get_type() const = 0;
        Position position{};
        virtual ~INodeBase() = default;
    };
}
