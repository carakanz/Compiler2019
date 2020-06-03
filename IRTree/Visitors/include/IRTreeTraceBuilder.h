//
// Created by carak on 02.06.2020.
//

#include <IRTree/IRTree.h>

#pragma once
namespace IRTreeVisitor {
    class IRTreeTraceBuilder : IRTree::IVisitor {
    public:
        static IRTree::ProgramInBlock build(IRTree::ProgramInBlock&& program) {
            IRTreeTraceBuilder builder(std::move(program));
            return builder.run();
        }

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
        explicit IRTreeTraceBuilder(IRTree::ProgramInBlock&& program)
                : program_(std::move(program)){};
        IRTree::ProgramInBlock run();
        IRTree::MethodInBlock build_method();

        IRTree::Block* current_block_{};

        IRTree::MethodInBlock * current_method_{};

        std::string label;
        std::string positive_label;
        std::string negative_label;

        IRTree::ProgramInBlock program_;
    };
}