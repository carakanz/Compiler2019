//
// Created by Zinenko Dmytro on 27.10.2019.
//
#pragma once

#include "IExpressionNode.h"
#include <IdentifierNode/IdentifierNode.h>
#include <memory>

namespace SyntaxTree {
    class ExpressionIdentifierNode : public IExpressionNode {
    public:
        [[nodiscard]] NodeType get_type() const override {
            return NodeType::EXPRESSION_IDENTIFIER;
        }
        std::unique_ptr<IdentifierNode> identifier;
    };
}
