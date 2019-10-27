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
        EXPRESSION_ROUND_BRACKETS
    };

    class INodeBase {
    public:
        virtual NodeType get_type() const = 0;

        virtual ~INodeBase() = default;
    };
}
