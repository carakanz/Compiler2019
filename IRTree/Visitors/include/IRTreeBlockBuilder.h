//
// Created by carak on 02.06.2020.
//

#pragma once

#include "../include/IRTree/IRTree.h"
#include "IRTree/IRTreeGoal.h"

namespace IRTreeVisitor {
    class IRTreeBlockBuilder : IRTree::IVisitor {
    public:
        enum class NodeType
        {
            LABEL, JUMP, OTHER
        };

        static IRTree::ProgramInBlock build(IRTree::ProgramInLine&& tree);

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
    private:
        NodeType current_ = NodeType::LABEL;
        NodeType previous_ = NodeType::LABEL;
        IRTree::Block current_block_;
        const IRTree::LabelNode *label_{};
        explicit IRTreeBlockBuilder(IRTree::ProgramInLine &&tree)
                : tree_(std::move(tree)) {}
        IRTree::ProgramInLine tree_;
        IRTree::ProgramInBlock run();
    };
}

