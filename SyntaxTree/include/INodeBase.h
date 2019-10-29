//
// Created by Zinenko Dmytro on 27.10.2019.
//
#pragma once

namespace SyntaxTree {
    enum NodeType {
        TYPE_INT,
        TYPE_BOOLEAN,
        TYPE_USER,
        TYPE_ARRAY,
        IDENTIFIER_NODE,
        EXPRESSION_METHOD_CALL_ARGS,
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
        STATEMENT_IF,
        STATEMENT_WHILE,
        STATEMENT_PRINTLN,
        STATEMENT_ASSIGN,
        STATEMENT_ASSIGN_ARRAY,
        PAIR_TYPE_IDENTIFIER,
        DECLARATION_METHOD_ARG_LIST,
        DECLARATION_VAR,
        DECLARATION_VAR_LIST,
        DECLARATION_METHOD,
        DECLARATION_METHOD_LIST,
        DECLARATION_CLASS,
        DECLARATION_CLASS_LIST,
        GOAL
    };

    class INodeBase {
    public:
        virtual NodeType get_type() const = 0;

        virtual ~INodeBase() = default;
    };
}
