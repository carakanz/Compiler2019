//
// Created by carak on 21.05.2020.
//

#include "IRTreeLinearisator.h"

namespace IRTreeVisitor {
    void IRTreeLinearisator::visit(const IRTree::ExpressionBinaryOperationNode &node) {
        lineTrees.back().push_back(&node);
        node.left->accept(*this);
        node.right->accept(*this);
    }

    void IRTreeLinearisator::visit(const IRTree::ExpressionCallNode &node) {
        lineTrees.back().push_back(&node);
        node.method->accept(*this);
        for (const auto &arg : node.arguments) {
            arg->accept(*this);
        }
    }

    void IRTreeLinearisator::visit(const IRTree::ExpressionConstNode &node) {
        lineTrees.back().push_back(&node);
    }

    void IRTreeLinearisator::visit(const IRTree::ExpressionESeqNode &node) {
        lineTrees.back().push_back(&node);
        node.expression->accept(*this);
        node.statement->accept(*this);
    }

    void IRTreeLinearisator::visit(const IRTree::ExpressionLocalNode &node) {
        lineTrees.back().push_back(&node);
    }

    void IRTreeLinearisator::visit(const IRTree::ExpressionMemoryNode &node) {
        lineTrees.back().push_back(&node);
        node.expression->accept(*this);
    }

    void IRTreeLinearisator::visit(const IRTree::ExpressionNameNode &node) {
        lineTrees.back().push_back(&node);
        node.label->accept(*this);
    }

    void IRTreeLinearisator::visit(const IRTree::ExpressionTempNode &node) {
        lineTrees.back().push_back(&node);
        node.temp->accept(*this);
    }

    void IRTreeLinearisator::visit(const IRTree::LabelNode &node) {
        lineTrees.back().push_back(&node);
    }

    void IRTreeLinearisator::visit(const IRTree::StatementCJumpNode &node) {
        lineTrees.back().push_back(&node);
        node.left_expression->accept(*this);
        node.right_expression->accept(*this);
        node.negative_label->accept(*this);
        node.positive_label->accept(*this);
    }

    void IRTreeLinearisator::visit(const IRTree::StatementExpressionNode &node) {
        lineTrees.back().push_back(&node);
        node.expression->accept(*this);
    }

    void IRTreeLinearisator::visit(const IRTree::StatementJumpNode &node) {
        lineTrees.back().push_back(&node);
        node.label->accept(*this);
    }

    void IRTreeLinearisator::visit(const IRTree::StatementLabelNode &node) {
        lineTrees.back().push_back(&node);
        node.label->accept(*this);
    }

    void IRTreeLinearisator::visit(const IRTree::StatementMoveNode &node) {
        lineTrees.back().push_back(&node);
        node.source->accept(*this);
        node.destination->accept(*this);
    }

    void IRTreeLinearisator::visit(const IRTree::StatementSeqNode &node) {
        lineTrees.back().push_back(&node);
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