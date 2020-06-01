//
// Created by carak on 21.05.2020.
//

#include "IRTreeLinearisator.h"

namespace IRTreeVisitor {
    void IRTreeLinearisator::visit(const IRTree::ExpressionBinaryOperationNode &node) {
        node.left->accept(*this);
        node.right->accept(*this);
        lineTrees.back().push_back(&node);
    }

    void IRTreeLinearisator::visit(const IRTree::ExpressionCallNode &node) {
        for (const auto &arg : node.arguments) {
            arg->accept(*this);
        }
        lineTrees.back().push_back(&node);
    }

    void IRTreeLinearisator::visit(const IRTree::ExpressionConstNode &node) {
        lineTrees.back().push_back(&node);
    }

    void IRTreeLinearisator::visit(const IRTree::ExpressionESeqNode &node) {
        assert(false);
        lineTrees.back().push_back(&node);
        node.expression->accept(*this);
        node.statement->accept(*this);
    }

    void IRTreeLinearisator::visit(const IRTree::ExpressionLocalNode &node) {
        lineTrees.back().push_back(&node);
    }

    void IRTreeLinearisator::visit(const IRTree::ExpressionMemoryNode &node) {
        node.expression->accept(*this);
        lineTrees.back().push_back(&node);
    }

    void IRTreeLinearisator::visit(const IRTree::ExpressionNameNode &node) {
        lineTrees.back().push_back(&node);
    }

    void IRTreeLinearisator::visit(const IRTree::ExpressionTempNode &node) {
        lineTrees.back().push_back(&node);
    }

    void IRTreeLinearisator::visit(const IRTree::LabelNode &node) {
        lineTrees.back().push_back(&node);
    }

    void IRTreeLinearisator::visit(const IRTree::StatementCJumpNode &node) {
        node.left_expression->accept(*this);
        node.right_expression->accept(*this);
        lineTrees.back().push_back(&node);
    }

    void IRTreeLinearisator::visit(const IRTree::StatementExpressionNode &node) {
        lineTrees.back().push_back(&node);
        node.expression->accept(*this);
    }

    void IRTreeLinearisator::visit(const IRTree::StatementJumpNode &node) {
        lineTrees.back().push_back(&node);
    }

    void IRTreeLinearisator::visit(const IRTree::StatementLabelNode &node) {
        node.label->accept(*this);
        lineTrees.back().push_back(&node);
    }

    void IRTreeLinearisator::visit(const IRTree::StatementMoveNode &node) {
        node.source->accept(*this);
        node.destination->accept(*this);
        lineTrees.back().push_back(&node);
    }

    void IRTreeLinearisator::visit(const IRTree::StatementSeqNode &node) {
        node.left->accept(*this);
        node.right->accept(*this);
    }

    void IRTreeLinearisator::visit(const IRTree::TempNode &node) {
        lineTrees.back().push_back(&node);
    }

    void IRTreeLinearisator::visit(const SyntaxTreeVisitor::IRTreeGoal &goal) {
        for (const auto &class_info : goal.wrappers) {
            for (const auto &method_info : class_info.second) {
                lineTrees.emplace_back();
                method_info.second->accept(*this);
            }
        }
    }
}