//
// Created by Zinenko Dmytro on 27.10.2019.
//
#pragma once

#include "IExpressionNode.h"
#include <IdentifierNode/IdentifierNode.h>
#include <memory>

namespace SyntaxTree {
    class ExpressionNewArrayNode : public IExpressionNode {
    public:
        [[nodiscard]] NodeType get_type() const override {
            return NodeType::EXPRESSION_NEW_ARRAY;
        }
        std::unique_ptr<ITypeNode> type;
        std::unique_ptr<IExpressionNode> size;
    };
}
