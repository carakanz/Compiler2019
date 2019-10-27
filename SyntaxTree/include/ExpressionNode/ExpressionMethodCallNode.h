//
// Created by Zinenko Dmytro on 27.10.2019.
//
#pragma once

#include "IExpressionNode.h"
#include <IdentifierNode/IdentifierNode.h>
#include <memory>
#include <vector>

namespace SyntaxTree {
    class ExpressionMethodCallNode : public virtual IExpressionNode {
    public:
        ExpressionMethodCallNode(IExpressionNode* object,
                                 IdentifierNode* method,
                                 std::vector<IExpressionNode*> arguments)
                : object_(object),
                  method_(method),
                  arguments_(arguments.begin(), arguments.end()){
        }

        NodeType get_type() const override {
            return NodeType::EXPRESSION_METHOD_CALL;
        }

        const IExpressionNode* get_object() const {
            return object_.get();
        }

        const IdentifierNode* get_method() const {
            return method_.get();
        }

        // get begin iterator
        auto get_first_arguments() const {
            return arguments_.cbegin();
        }

        // get end iterator
        auto get_last_arguments() const {
            return arguments_.cend();
        }

        ~ExpressionMethodCallNode() override = default;

    private:
        std::unique_ptr<IExpressionNode> object_;
        std::unique_ptr<IdentifierNode> method_;
        std::vector<std::unique_ptr<IExpressionNode>> arguments_;
    };
}
