//
// Created by Admin on 03.06.2020.
//

#ifndef COMPILER2019_IRTREEFINALLINEARISATOR_H
#define COMPILER2019_IRTREEFINALLINEARISATOR_H

#include <IRTree/IVisitor.h>
#include <IRTree/Nodes.h>
#include <IRTree/IRTreeGoal.h>

namespace IRTreeVisitor {
    class IRTreeFinalLinearisator : IRTree::IVisitor {

    public:
        explicit IRTreeFinalLinearisator() = default;

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

        void updateLastExp(const IRTree::ExpressionConstNode &node);
        void updateLastExp(const IRTree::ExpressionTempNode &node);
        void updateLastExp(const IRTree::ExpressionNameNode & node);
        void updateLastExp(const IRTree::ExpressionLocalNode &node);

        void updateLastExp( std::unique_ptr<IRTree::IExpressionNode> newLastExp ){
            prevExp = std::move( newLastExp );
        }


        void updateLastStm(const IRTree::StatementJumpNode& node);
        void updateLastStm(const IRTree::StatementLabelNode &node);

        void updateLastStm(std::unique_ptr<IRTree::IStatementNode> newLastStm) {
            prevStm = std::move(newLastStm );
        }

        std::unique_ptr<IRTree::IExpressionNode> prevExp;
        std::unique_ptr<IRTree::IStatementNode> prevStm;

        void saveCreatedStm( std::unique_ptr<IRTree::IStatementNode> result );

        std::vector<std::unique_ptr<IRTree::IStatementNode>> stackOfSeqChildren;
        std::vector<int> stackDepthCounter;

    };
}

#endif //COMPILER2019_IRTREEFINALLINEARISATOR_H
