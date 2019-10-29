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

    class ExpressionStaticMethodCallNode : public virtual IExpressionNode {
    public:
        ExpressionStaticMethodCallNode(std::unique_ptr<IdentifierNode> class_id,
                                 std::unique_ptr<IdentifierNode> method,
                                 std::unique_ptr<ExpressionMethodCallArgsNode> arguments)
                : class_id_(std::move(class_id)),
                  method_(std::move(method)),
                  arguments_(std::move(arguments->items_)){
        }

        [[nodiscard]] NodeType get_type() const override {
            return NodeType::EXPRESSION_STATIC_METHOD_CALL;
        }

        [[nodiscard]] const IdentifierNode* get_class_id() const {
            return class_id_.get();
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

        ~ExpressionStaticMethodCallNode() override = default;

    private:
        std::unique_ptr<IdentifierNode> class_id_;
        std::unique_ptr<IdentifierNode> method_;
        std::vector<std::unique_ptr<IExpressionNode>> arguments_;
    };
}
