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
        EXPRESSION_IDENTIFIER,
        EXPRESSION_BINARY_OPERATION,
        EXPRESSION_INDEX,
        EXPRESSION_GET_LENGHT,
        EXPRESSION_METHOD_CALL,
        EXPRESSION_INTEGER_LITERAL,
        EXPRESSION_BOOLEAN_LITERAL,
        EXPRESSION_THIS,
        EXPRESSION_NEW_ARRAY,
        EXPRESSION_NEW,
        EXPRESSION_NOT_OPERATION,
        EXPRESSION_ROUND_BRACKETS,
        STATEMENT_MERGE,
        STATEMENT_IF,
        STATEMENT_WHILE,
        STATEMENT_PRINTLN,
        STATEMENT_ASSIGN,
        STATEMENT_ASSIGN_ARRAY,
        DECLARATION_VAR,
        DECLARATION_METHOD,
        DECLARATION_CLASS,
        GOAL
    };

    class INodeBase {
    public:
        virtual NodeType get_type() const = 0;

        virtual ~INodeBase() = default;
    };
}
