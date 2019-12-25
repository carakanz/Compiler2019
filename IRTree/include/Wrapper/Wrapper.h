//
// Created by Zinenko Dmytro on 23.12.2019.
//
#pragma once

#include <memory>
#include "IWrapper.h"
#include "cassert"
#include <CJumpCondition.h>

namespace IRTree {

    template<class NodeType>
    class Wrapper : public IWrapper {
    public:
        explicit Wrapper(std::unique_ptr<NodeType>&& node) : node_(std::move(node)) {
        }

        template <class... Args>
        explicit Wrapper(Args... args) : node_(std::make_unique<NodeType>(std::forward<Args>(args)...)) {
        }

//        template<typename T = std::enable_if_t<std::is_base_of_v<IExpressionNode,NodeType>>>
//        inline std::unique_ptr<IExpressionNode> to_expression_check() {
//            return std::move(node_);
//        }
        static std::unique_ptr<IExpressionNode> to_expression(std::unique_ptr<IExpressionNode>&& node) {
            return std::move(node);
        }

        static std::unique_ptr<IExpressionNode> to_expression(std::unique_ptr<IStatementNode>&& /*node*/) {
            assert(false);
        }

        std::unique_ptr<IExpressionNode> to_expression() override {
            return to_expression(std::move(node_));
        }

        static std::unique_ptr<IStatementNode> to_statement(std::unique_ptr<IExpressionNode>&& /*node*/) {
            assert(false);
        }

        static std::unique_ptr<IStatementNode> to_statement(std::unique_ptr<IStatementNode>&& node) {
            return std::move(node);
        }

        std::unique_ptr<IStatementNode> to_statement() override {
            return to_statement(std::move(node_));
        }

        std::unique_ptr<IStatementNode> to_conditional(std::unique_ptr<LabelNode> && /*true_label*/,
                                                       std::unique_ptr<LabelNode> && /*false_label*/) override {
            assert(false);
        }

    private:
        std::unique_ptr<NodeType> node_;
    };

    template<>
    std::unique_ptr<IStatementNode>
    Wrapper<ExpressionCallNode>::to_conditional(std::unique_ptr<LabelNode> && true_label, std::unique_ptr<LabelNode> && false_label) {
        return std::make_unique<StatementCJumpNode>(CJumpCondition::NOT_EQUIVALENT,
                                                    std::make_unique<ExpressionConstNode>(0),
                                                    std::move(node_),
                                                    std::move(true_label),
                                                    std::move(false_label));
    }

    template<>
    std::unique_ptr<IStatementNode>
    Wrapper<ExpressionLocalNode>::to_conditional(std::unique_ptr<LabelNode> && true_label, std::unique_ptr<LabelNode> && false_label) {
        return std::make_unique<StatementCJumpNode>(CJumpCondition::NOT_EQUIVALENT,
                                                    std::make_unique<ExpressionConstNode>(0),
                                                    std::move(node_),
                                                    std::move(true_label),
                                                    std::move(false_label));
    }
}
