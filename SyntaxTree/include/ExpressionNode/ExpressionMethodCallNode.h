//
// Created by Zinenko Dmytro on 27.10.2019.
//
#pragma once

#include "IExpressionNode.h"
#include <IdentifierNode/IdentifierNode.h>
#include <memory>
#include <vector>

namespace SyntaxTree {
    using ExpressionMethodCallArgsNode = ListNode<IExpressionNode,
            IExpressionNode,
            NodeType::EXPRESSION_METHOD_CALL_ARGS>;

    class ExpressionMethodCallNode : public virtual IExpressionNode {
    public:
        ExpressionMethodCallNode(std::unique_ptr<IExpressionNode> object,
                                 std::unique_ptr<IdentifierNode> method,
                                 std::unique_ptr<ExpressionMethodCallArgsNode> arguments)
                : object_(std::move(object)),
                  method_(std::move(method)),
                  arguments_(std::move(arguments->items_)){
        }

        [[nodiscard]] NodeType get_type() const override {
            return NodeType::EXPRESSION_METHOD_CALL;
        }

        [[nodiscard]] const IExpressionNode* get_object() const {
            return object_.get();
        }

        [[nodiscard]] const IdentifierNode* get_method() const {
            return method_.get();
        }

        // get begin iterator
        [[nodiscard]] auto get_first_argument() const {
            return arguments_.cbegin();
        }

        // get end iterator
        [[nodiscard]] auto get_last_argument() const {
            return arguments_.cend();
        }

        ~ExpressionMethodCallNode() override = default;

    private:
        std::unique_ptr<IExpressionNode> object_;
        std::unique_ptr<IdentifierNode> method_;
        std::vector<std::unique_ptr<IExpressionNode>> arguments_;
    };
}
