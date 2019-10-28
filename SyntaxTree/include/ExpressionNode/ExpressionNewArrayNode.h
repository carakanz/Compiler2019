//
// Created by Zinenko Dmytro on 27.10.2019.
//
#pragma once

#include "IExpressionNode.h"
#include <IdentifierNode/IdentifierNode.h>
#include <memory>

namespace SyntaxTree {
    class ExpressionNewArrayNode : public virtual IExpressionNode {
    public:
        explicit ExpressionNewArrayNode(std::unique_ptr<IdentifierNode> identifier,
                                        std::unique_ptr<IExpressionNode> size)
                : identifier_(std::move(identifier)), size_(std::move(size)) {
        }

        [[nodiscard]] NodeType get_type() const override {
            return NodeType::EXPRESSION_NEW_ARRAY;
        }

        [[nodiscard]] const IdentifierNode *get_identifier() const {
            return identifier_.get();
        }

        [[nodiscard]] const IExpressionNode *get_size() const {
            return size_.get();
        }

        ~ExpressionNewArrayNode() override = default;

    private:
        std::unique_ptr<IdentifierNode> identifier_;
        std::unique_ptr<IExpressionNode> size_;
    };
}
