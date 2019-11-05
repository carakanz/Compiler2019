//
// Created by Zinenko Dmytro on 27.10.2019.
//
#pragma once

#include "IExpressionNode.h"
#include <IdentifierNode/IdentifierNode.h>
#include <memory>
#include <vector>

namespace SyntaxTree {
    class ExpressionMethodCallNode : public IExpressionNode {
    public:
        [[nodiscard]] NodeType get_type() const override {
            return NodeType::EXPRESSION_METHOD_CALL;
        }
        std::unique_ptr<IExpressionNode> object;
        std::unique_ptr<IdentifierNode> method;
        std::vector<std::unique_ptr<IExpressionNode>> arguments;
    };
}
