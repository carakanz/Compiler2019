//
// Created by Zinenko Dmytro on 25.11.2019.
//

#pragma once

#include <IVisitor.h>
#include "Nodes.h"

namespace SyntaxTreeVisitor {
    template<class WorkerVisitor>
    class SyntaxTreeDFSVisitor : public SyntaxTree::IVisitor {
    public:
        explicit SyntaxTreeDFSVisitor(WorkerVisitor &worker_visitor)
                : worker_visitor_(worker_visitor) {
        }

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
        WorkerVisitor &worker_visitor_;
    };

    template<class WorkerVisitor>
    void SyntaxTreeDFSVisitor<WorkerVisitor>::visit(const SyntaxTree::TypeIntNode &node) {
        node.accept(worker_visitor_);
    }

    template<class WorkerVisitor>
    void SyntaxTreeDFSVisitor<WorkerVisitor>::visit(const SyntaxTree::TypeBooleanNode &node) {
        node.accept(worker_visitor_);
    }

    template<class WorkerVisitor>
    void SyntaxTreeDFSVisitor<WorkerVisitor>::visit(const SyntaxTree::TypeArrayNode &node) {
        node.type->accept(*this);
        node.accept(worker_visitor_);
    }

    template<class WorkerVisitor>
    void SyntaxTreeDFSVisitor<WorkerVisitor>::visit(const SyntaxTree::TypeUserNode &node) {
        node.identifier->accept(*this);
        node.accept(worker_visitor_);
    }

    template<class WorkerVisitor>
    void SyntaxTreeDFSVisitor<WorkerVisitor>::visit(const SyntaxTree::TypeVoidNode &node) {
        node.accept(worker_visitor_);
    }

    template<class WorkerVisitor>
    void SyntaxTreeDFSVisitor<WorkerVisitor>::visit(const SyntaxTree::TypeStringNode &node) {
        node.accept(worker_visitor_);
    }

    template<class WorkerVisitor>
    void SyntaxTreeDFSVisitor<WorkerVisitor>::visit(const SyntaxTree::IdentifierNode &node) {
        node.accept(worker_visitor_);
    }

    template<class WorkerVisitor>
    void SyntaxTreeDFSVisitor<WorkerVisitor>::visit(const SyntaxTree::ExpressionIdentifierNode &node) {
        node.identifier->accept(*this);
        node.accept(worker_visitor_);
    }

    template<class WorkerVisitor>
    void SyntaxTreeDFSVisitor<WorkerVisitor>::visit(const SyntaxTree::ExpressionBinaryOperationNode &node) {
        node.left->accept(*this);
        node.right->accept(*this);
        node.accept(worker_visitor_);
    }

    template<class WorkerVisitor>
    void SyntaxTreeDFSVisitor<WorkerVisitor>::visit(const SyntaxTree::ExpressionIndexNode &node) {
        node.array->accept(*this);
        node.index->accept(*this);
        node.accept(worker_visitor_);
    }

    template<class WorkerVisitor>
    void SyntaxTreeDFSVisitor<WorkerVisitor>::visit(const SyntaxTree::ExpressionGetLengthNode &node) {
        node.array->accept(*this);
        node.accept(worker_visitor_);
    }

    template<class WorkerVisitor>
    void SyntaxTreeDFSVisitor<WorkerVisitor>::visit(const SyntaxTree::ExpressionMethodCallNode &node) {
        node.object->accept(*this);
        node.method->accept(*this);
        for (auto& argument : node.arguments) {
            argument->accept(*this);
        }
        node.accept(worker_visitor_);
    }

    template<class WorkerVisitor>
    void SyntaxTreeDFSVisitor<WorkerVisitor>::visit(const SyntaxTree::ExpressionStaticMethodCallNode &node) {
        node.class_id->accept(*this);
        node.method->accept(*this);
        for (auto& argument : node.arguments) {
            argument->accept(*this);
        }
        node.accept(worker_visitor_);
    }

    template<class WorkerVisitor>
    void SyntaxTreeDFSVisitor<WorkerVisitor>::visit(const SyntaxTree::ExpressionIntegerLiteralNode &node) {
        node.accept(worker_visitor_);
    }

    template<class WorkerVisitor>
    void SyntaxTreeDFSVisitor<WorkerVisitor>::visit(const SyntaxTree::ExpressionBooleanLiteralNode &node) {
        node.accept(worker_visitor_);
    }

    template<class WorkerVisitor>
    void SyntaxTreeDFSVisitor<WorkerVisitor>::visit(const SyntaxTree::ExpressionThisNode &node) {
        node.accept(worker_visitor_);
    }

    template<class WorkerVisitor>
    void SyntaxTreeDFSVisitor<WorkerVisitor>::visit(const SyntaxTree::ExpressionNewArrayNode &node) {
        node.type->accept(*this);
        node.size->accept(*this);
        node.accept(worker_visitor_);
    }

    template<class WorkerVisitor>
    void SyntaxTreeDFSVisitor<WorkerVisitor>::visit(const SyntaxTree::ExpressionNewNode &node) {
        node.type->accept(*this);
        node.accept(worker_visitor_);
    }

    template<class WorkerVisitor>
    void SyntaxTreeDFSVisitor<WorkerVisitor>::visit(const SyntaxTree::ExpressionNotOperatorNode &node) {
        node.expression->accept(*this);
        node.accept(worker_visitor_);
    }

    template<class WorkerVisitor>
    void SyntaxTreeDFSVisitor<WorkerVisitor>::visit(const SyntaxTree::ExpressionRoundBracketsNode &node) {
        node.expression->accept(*this);
        node.accept(worker_visitor_);
    }

    template<class WorkerVisitor>
    void SyntaxTreeDFSVisitor<WorkerVisitor>::visit(const SyntaxTree::StatementIfNode &node) {
        node.conditional->accept(*this);
        node.then_statement->accept(*this);
        node.else_statement->accept(*this);
        node.accept(worker_visitor_);
    }

    template<class WorkerVisitor>
    void SyntaxTreeDFSVisitor<WorkerVisitor>::visit(
            const SyntaxTree::ListNode<SyntaxTree::IStatementNode, SyntaxTree::IStatementNode> &node) {
        for (auto& argument : node.items) {
            argument->accept(*this);
        }
        node.accept(worker_visitor_);
    }

    template<class WorkerVisitor>
    void SyntaxTreeDFSVisitor<WorkerVisitor>::visit(const SyntaxTree::StatementEmptyNode &node) {
        node.accept(worker_visitor_);
    }

    template<class WorkerVisitor>
    void SyntaxTreeDFSVisitor<WorkerVisitor>::visit(const SyntaxTree::StatementWhileNode &node) {
        node.conditional->accept(*this);
        node.then_statement->accept(*this);
        node.accept(worker_visitor_);
    }

    template<class WorkerVisitor>
    void SyntaxTreeDFSVisitor<WorkerVisitor>::visit(const SyntaxTree::StatementPrintlnNode &node) {
        node.expression->accept(*this);
        node.accept(worker_visitor_);
    }

    template<class WorkerVisitor>
    void SyntaxTreeDFSVisitor<WorkerVisitor>::visit(const SyntaxTree::StatementAssignNode &node) {
        node.identifier->accept(*this);
        node.expression->accept(*this);
        node.accept(worker_visitor_);
    }

    template<class WorkerVisitor>
    void SyntaxTreeDFSVisitor<WorkerVisitor>::visit(const SyntaxTree::StatementAssignArrayNode &node) {
        node.identifier->accept(*this);
        node.index->accept(*this);
        node.expression->accept(*this);
        node.accept(worker_visitor_);
    }

    template<class WorkerVisitor>
    void SyntaxTreeDFSVisitor<WorkerVisitor>::visit(const SyntaxTree::StatementReturnNode &node) {
        node.expression->accept(*this);
        node.accept(worker_visitor_);
    }

    template<class WorkerVisitor>
    void SyntaxTreeDFSVisitor<WorkerVisitor>::visit(const SyntaxTree::DeclarationMethodNode &node) {
        node.return_type->accept(*this);
        node.identifier->accept(*this);
        for (auto& argument : node.arguments) {
            argument->accept(*this);
        }
        for (auto& argument : node.variables) {
            argument->accept(*this);
        }
        for (auto& argument : node.statements) {
            argument->accept(*this);
        }
        node.accept(worker_visitor_);
    }

    template<class WorkerVisitor>
    void SyntaxTreeDFSVisitor<WorkerVisitor>::visit(const SyntaxTree::DeclarationClassNode &node) {
        node.identifier->accept(*this);
        if (node.base_class_identifier) {
            node.base_class_identifier->accept(*this);
        }
        for (auto& argument : node.variables) {
            argument->accept(*this);
        }
        for (auto& argument : node.methods) {
            argument->accept(*this);
        }
        node.accept(worker_visitor_);
    }

    template<class WorkerVisitor>
    void SyntaxTreeDFSVisitor<WorkerVisitor>::visit(const SyntaxTree::DeclarationVarNode &node) {
        node.var_type->accept(*this);
        node.identifier->accept(*this);
        node.accept(worker_visitor_);
    }

    template<class WorkerVisitor>
    void SyntaxTreeDFSVisitor<WorkerVisitor>::visit(
            const SyntaxTree::ListNode<SyntaxTree::DeclarationClassNode, SyntaxTree::INodeBase> &node) {
        for (auto& argument : node.items) {
            argument->accept(*this);
        }
        node.accept(worker_visitor_);
    }
}

