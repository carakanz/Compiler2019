//
// Created by carak on 21.05.2020.
//

#pragma once

#include "../include/IRTree/IVisitor.h"
#include "../include/IRTree/Nodes.h"
#include "IRTree/IRTreeGoal.h"

namespace IRTreeVisitor {
    class IRTreeLinearisator : IRTree::IVisitor {
    public:
        explicit IRTreeLinearisator() {}

        void visit(const IRTree::ExpressionBinaryOperationNode &node) override;

        void visit(const IRTree::ExpressionCallNode &node) override;

        void visit(const IRTree::ExpressionConstNode &node) override;

        void visit(const IRTree::ExpressionESeqNode &node) override;

        void visit(const IRTree::ExpressionLocalNode &node) override;

        void visit(const IRTree::ExpressionMemoryNode &node) override;

        void visit(const IRTree::ExpressionNameNode &node) override;

        void visit(const IRTree::ExpressionTempNode &node) override;

        void visit(const IRTree::LabelNode &node) override;

        void visit(const IRTree::StatementCJumpNode &node) override;

        void visit(const IRTree::StatementExpressionNode &node) override;

        void visit(const IRTree::StatementJumpNode &node) override;

        void visit(const IRTree::StatementLabelNode &node) override;

        void visit(const IRTree::StatementMoveNode &node) override;

        void visit(const IRTree::StatementSeqNode &node) override;

        void visit(const IRTree::TempNode &node) override;

        void visit(const IRTree::IRTreeGoal &goal);

        [[nodiscard]] std::vector<std::vector<const IRTree::INodeBase*>> GetLineTrees() const {
            return lineTrees;
        };
    private:
        std::vector<std::vector<const IRTree::INodeBase*>> lineTrees;
    };
}
