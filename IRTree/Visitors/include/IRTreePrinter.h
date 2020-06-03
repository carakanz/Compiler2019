//
// Created by l1onsun on 23.12.19.
//
#pragma once

#include <fstream>
#include "../include/IRTree/IVisitor.h"
#include "../include/IRTree/Nodes.h"
#include "IRTree/IRTreeGoal.h"

namespace IRTreeVisitor {
    class IRTreeVisitor : IRTree::IVisitor {
    public:
        explicit IRTreeVisitor(std::ofstream &out) : out_(out) {}

        void print_start(std::string name) {
            size_t dot = name.find('.');
            while (dot != std::string::npos) {
                name.erase(name.find('.'));
                dot = name.find('.');
            }
            out_ << "digraph " << name << " {" << "\n";
        };

        void print_end() {
            out_ << "}" << std::endl;
        };

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

    private:
        std::ofstream &out_;
    };
}
