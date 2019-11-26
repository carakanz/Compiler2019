//
// Created by Zinenko Dmytro on 25.11.2019.
//

#pragma once
#include <IVisitor.h>
#include <fstream>

namespace Visitor {
    class SyntaxTreePrinter : public SyntaxTree::IVisitor {
    public:
        explicit SyntaxTreePrinter(std::ofstream &out) : out_(out) {
        }

        void print_start(const std::string& name) {
            out_ << "digraph " << name << " {" << "\n";
        };

        void print_end() {
            out_ << "}" << std::endl;
        };

        void visit(const SyntaxTree::TypeIntNode &node) override;

        void visit(const SyntaxTree::TypeBooleanNode &node) override;

        void visit(const SyntaxTree::TypeArrayNode &node) override;

        void visit(const SyntaxTree::TypeUserNode &node) override;

        void visit(const SyntaxTree::TypeVoidNode &node) override;

        void visit(const SyntaxTree::TypeStringNode &node) override;

        void visit(const SyntaxTree::IdentifierNode &node) override;

        void visit(const SyntaxTree::ExpressionIdentifierNode &node) override;

        void visit(const SyntaxTree::ExpressionBinaryOperationNode &node) override;

        void visit(const SyntaxTree::ExpressionIndexNode &node) override;

        void visit(const SyntaxTree::ExpressionGetLengthNode &node) override;

        void visit(const SyntaxTree::ExpressionMethodCallNode &node) override;

        void visit(const SyntaxTree::ExpressionStaticMethodCallNode &node) override;

        void visit(const SyntaxTree::ExpressionIntegerLiteralNode &node) override;

        void visit(const SyntaxTree::ExpressionBooleanLiteralNode &node) override;

        void visit(const SyntaxTree::ExpressionThisNode &node) override;

        void visit(const SyntaxTree::ExpressionNewArrayNode &node) override;

        void visit(const SyntaxTree::ExpressionNewNode &node) override;

        void visit(const SyntaxTree::ExpressionNotOperatorNode &node) override;

        void visit(const SyntaxTree::ExpressionRoundBracketsNode &node) override;

        void visit(const SyntaxTree::StatementIfNode &node) override;

        void visit(const SyntaxTree::ListNode<SyntaxTree::IStatementNode, SyntaxTree::IStatementNode> &node) override;

        void visit(const SyntaxTree::StatementEmptyNode &node) override;

        void visit(const SyntaxTree::StatementWhileNode &node) override;

        void visit(const SyntaxTree::StatementPrintlnNode &node) override;

        void visit(const SyntaxTree::StatementAssignNode &node) override;

        void visit(const SyntaxTree::StatementAssignArrayNode &node) override;

        void visit(const SyntaxTree::StatementReturnNode &node) override;

        void visit(const SyntaxTree::DeclarationMethodNode &node) override;

        void visit(const SyntaxTree::DeclarationClassNode &node) override;

        void visit(const SyntaxTree::DeclarationVarNode &node) override;

        void visit(const SyntaxTree::ListNode<SyntaxTree::DeclarationClassNode, SyntaxTree::INodeBase> &node) override;

    private:
        std::ofstream &out_;
    };
}
