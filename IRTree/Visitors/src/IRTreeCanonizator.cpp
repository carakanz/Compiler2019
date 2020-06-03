//
// Created by Admin on 02.06.2020.
//

#include <IRTreeCanonizator.h>

namespace IRTreeVisitor{
    void IRTreeCanonizator::updateLastExp(const IRTree::ExpressionNameNode &node) {
        auto& nc_node = const_cast<IRTree::ExpressionNameNode &>(node);
        prevExp = std::make_unique<IRTree::ExpressionNameNode>(std::move(nc_node.label));
    }

    void IRTreeCanonizator::updateLastExp(const IRTree::ExpressionTempNode &node) {
        auto& nc_node = const_cast<IRTree::ExpressionTempNode &>(node);
        prevExp = std::make_unique<IRTree::ExpressionTempNode>(std::move(nc_node.temp));
    }

    void IRTreeCanonizator::updateLastExp(const IRTree::ExpressionConstNode &node) {
        auto& nc_node = const_cast<IRTree::ExpressionConstNode &>(node);
        prevExp = std::make_unique<IRTree::ExpressionConstNode>(nc_node.value);
    }

    void IRTreeCanonizator::updateLastExp(const IRTree::ExpressionLocalNode &node) {
        auto& nc_node = const_cast<IRTree::ExpressionLocalNode &>(node);
        prevExp = std::make_unique<IRTree::ExpressionLocalNode>(nc_node.is_class_var, nc_node.name);
    }

    void IRTreeCanonizator::updateLastStm(const IRTree::StatementJumpNode &node) {
        auto& nc_node = const_cast<IRTree::StatementJumpNode &>(node);
        prevStm = std::make_unique<IRTree::StatementJumpNode>(std::move(nc_node.label));
    }

    void IRTreeCanonizator::updateLastStm(const IRTree::StatementLabelNode &node) {
        auto& nc_node = const_cast<IRTree::StatementLabelNode &>(node);
        prevStm = std::make_unique<IRTree::StatementLabelNode>(std::move(nc_node.label));
    }
}

