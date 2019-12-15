//
// Created by Zinenko Dmytro on 25.11.2019.
//

#include <Nodes.h>
#include "SyntaxTreePrinter.h"

namespace Visitor {
    void SyntaxTreePrinter::visit(const SyntaxTree::TypeIntNode &node) {
        out_ << "\"" << &node << "\"" << " [label=\"TypeInt\" shape=box]\n";
    }

    void SyntaxTreePrinter::visit(const SyntaxTree::TypeBooleanNode &node) {
        out_ << "\"" << &node << "\"" << " [label=\"TypeBoolean\" shape=box]\n";
    }

    void SyntaxTreePrinter::visit(const SyntaxTree::TypeArrayNode &node) {
        out_ << "\"" << &node << "\"" << " [label=\"TypeArray\" shape=box]\n";
        out_ << "\"" << &node << "\"" << " -> " << "\"" << node.type.get() << "\"" << "\n";
    }

    void SyntaxTreePrinter::visit(const SyntaxTree::TypeUserNode &node) {
        out_ << "\"" << &node << "\"" << " [label=\"TypeUser\" shape=box]\n";
        out_ << "\"" << &node << "\"" << " -> " << "\"" << node.identifier.get() << "\"" << "\n";
    }

    void SyntaxTreePrinter::visit(const SyntaxTree::TypeVoidNode &node) {
        out_ << "\"" << &node << "\"" << " [label=\"TypeVoid\" shape=box]\n";
    }


    void SyntaxTreePrinter::visit(const SyntaxTree::TypeStringNode &node) {
        out_ << "\"" << &node << "\"" << " [label=\"TypeString\" shape=box]\n";
    }


    void SyntaxTreePrinter::visit(const SyntaxTree::IdentifierNode &node) {
        out_ << "\"" << &node << "\"" << " [label=\"Identifier: " << node.name << "\" shape=box]\n";
    }


    void SyntaxTreePrinter::visit(const SyntaxTree::ExpressionIdentifierNode &node) {
        out_ << "\"" << &node << "\"" << " [label=\"ExpressionIdentifier\" shape=circle]\n";
        out_ << "\"" << &node << "\"" << "  -> " << "\"" << node.identifier.get() << "\"" << "\n";
    }


    void SyntaxTreePrinter::visit(const SyntaxTree::ExpressionBinaryOperationNode &node) {
        out_ << "\"" << &node << "\"" << " [label=\"ExpressionBinaryOperation\noperation_type: " << node.operation_type
             << "\" shape=circle]\n";
        out_ << "\"" << &node << "\"" << " -> " << "\"" << node.left.get() << "\"" << "\n";
        out_ << "\"" << &node << "\"" << " -> " << "\"" << node.right.get() << "\"" << "\n";
    }


    void SyntaxTreePrinter::visit(const SyntaxTree::ExpressionIndexNode &node) {
        out_ << "\"" << &node << "\"" << " [label=\"ExpressionIndex\" shape=circle]\n";
        out_ << "\"" << &node << "\"" << " -> " << "\"" << node.array.get() << "\"" << "\n";
        out_ << "\"" << &node << "\"" << " -> " << "\"" << node.index.get() << "\"" << "\n";
    }

    void SyntaxTreePrinter::visit(const SyntaxTree::ExpressionGetLengthNode &node) {
        out_ << "\"" << &node << "\"" << " [label=\"ExpressionGetLength\" shape=circle]\n";
        out_ << &node << " -> " << "\"" << node.array.get() << "\"" << "\n";
    }

    void SyntaxTreePrinter::visit(const SyntaxTree::ExpressionMethodCallNode &node) {
        out_ << "\"" << &node << "\"" << " [label=\"ExpressionMethodCall\" shape=circle]\n";
        out_ << "\"" << &node << "\"" << " -> " << "\"" << node.object.get() << "\"" << "\n";
        out_ << "\"" << &node << "\"" << " -> " << "\"" << node.method.get() << "\"" << "\n";
        for (auto &argument : node.arguments) {
            out_ << "\"" << &node << "\"" << " -> " << "\"" << argument.get() << "\"" << "\n";
        }
    }

    void SyntaxTreePrinter::visit(const SyntaxTree::ExpressionStaticMethodCallNode &node) {
        out_ << &node << " [label=\"ExpressionStaticMethodCall\" shape=circle]\n";
        out_ << &node << " -> " << "\"" << node.class_id.get() << "\"" << "\n";
        out_ << &node << " -> " << "\"" << node.method.get() << "\"" << "\n";
        for (auto &argument : node.arguments) {
            out_ << &node << " -> " << "\"" << argument.get() << "\"" << "\n";
        }

    }

    void SyntaxTreePrinter::visit(const SyntaxTree::ExpressionIntegerLiteralNode &node) {
        out_ << "\"" << &node << "\"" << " [label=\"ExpressionIntegerLiteral: " << node.value << "\" shape=circle]\n";
    }

    void SyntaxTreePrinter::visit(const SyntaxTree::ExpressionBooleanLiteralNode &node) {
        out_ << "\"" << &node << "\"" << " [label=\"ExpressionBooleanLiteral: " << node.value << "\" shape=circle]\n";
    }

    void SyntaxTreePrinter::visit(const SyntaxTree::ExpressionThisNode &node) {
        out_ << "\"" << &node << "\"" << " [label=\"ExpressionThis\" shape=circle]\n";
    }

    void SyntaxTreePrinter::visit(const SyntaxTree::ExpressionNewArrayNode &node) {
        out_ << "\"" << &node << "\"" << " [label=\"ExpressionNewArray\" shape=circle]\n";
        out_ << "\"" << &node << "\"" << " -> " << "\"" << node.type.get() << "\"" << "\n";
        out_ << "\"" << &node << "\"" << " -> " << "\"" << node.size.get() << "\"" << "\n";
    }

    void SyntaxTreePrinter::visit(const SyntaxTree::ExpressionNewNode &node) {
        out_ << "\"" << &node << "\"" << " [label=\"ExpressionNew\" shape=circle]\n";
        out_ << "\"" << &node << "\"" << " -> " << "\"" << node.type.get() << "\"" << "\n";
    }

    void SyntaxTreePrinter::visit(const SyntaxTree::ExpressionNotOperatorNode &node) {
        out_ << "\"" << &node << "\"" << " [label=\"ExpressionNotOperator\" shape=circle]\n";
        out_ << "\"" << &node << "\"" << " -> " << "\"" << node.expression.get() << "\"" << "\n";
    }

    void SyntaxTreePrinter::visit(const SyntaxTree::ExpressionRoundBracketsNode &node) {
        out_ << "\"" << &node << "\"" << " [label=\"ExpressionRoundBrackets\" shape=circle]\n";
        out_ << "\"" << &node << "\"" << " -> " << "\"" << node.expression.get() << "\"" << "\n";
    }

    void SyntaxTreePrinter::visit(const SyntaxTree::StatementIfNode &node) {
        out_ << "\"" << &node << "\"" << " [label=\"StatementIf\"]\n";
        out_ << "\"" << &node << "\"" << " -> " << "\"" << node.conditional.get() << "\"" << "\n";
        out_ << "\"" << &node << "\"" << " -> " << "\"" << node.then_statement.get() << "\"" << "\n";
        out_ << "\"" << &node << "\"" << " -> " << "\"" << node.else_statement.get() << "\"" << "\n";
    }

    void SyntaxTreePrinter::visit(
            const SyntaxTree::ListNode<SyntaxTree::IStatementNode, SyntaxTree::IStatementNode> &node) {
        out_ << "\"" << &node << "\"" << " [label=\"StatementList\"]\n";
        for (auto &argument : node.items) {
            out_ << "\"" << &node << "\"" << " -> " << "\"" << argument.get() << "\"" << "\n";
        }
    }

    void SyntaxTreePrinter::visit(const SyntaxTree::StatementEmptyNode &node) {
        out_ << "\"" << &node << "\"" << " [label=\"StatementEmpty\"]\n";
    }

    void SyntaxTreePrinter::visit(const SyntaxTree::StatementWhileNode &node) {
        out_ << "\"" << &node << "\"" << " [label=\"StatementWhile\"]\n";
        out_ << "\"" << &node << "\"" << " -> " << "\"" << node.conditional.get() << "\"" << "\n";
        out_ << "\"" << &node << "\"" << " -> " << "\"" << node.then_statement.get() << "\"" << "\n";
    }

    void SyntaxTreePrinter::visit(const SyntaxTree::StatementPrintlnNode &node) {
        out_ << "\"" << &node << "\"" << " [label=\"StatementPrintln\"]\n";
        out_ << "\"" << &node << "\"" << " -> " << "\"" << node.expression.get() << "\"" << "\n";
    }

    void SyntaxTreePrinter::visit(const SyntaxTree::StatementAssignNode &node) {
        out_ << "\"" << &node << "\"" << " [label=\"StatementAssign\"]\n";
        out_ << "\"" << &node << "\"" << " -> " << "\"" << node.identifier.get() << "\"" << "\n";
        out_ << "\"" << &node << "\"" << " -> " << "\"" << node.expression.get() << "\"" << "\n";
    }

    void SyntaxTreePrinter::visit(const SyntaxTree::StatementAssignArrayNode &node) {
        out_ << "\"" << &node << "\"" << " [label=\"StatementAssignArray\"]\n";
        out_ << "\"" << &node << "\"" << " -> " << "\"" << node.identifier.get()  << "\"" << "\n";
        out_ << "\"" << &node << "\"" << " -> " << "\"" << node.index.get() << "\"" << "\n";
        out_ << "\"" << &node << "\"" << " -> " << "\"" << node.expression.get() << "\"" << "\n";
    }

    void SyntaxTreePrinter::visit(const SyntaxTree::StatementReturnNode &node) {
        out_ << "\"" << &node << "\"" << " [label=\"StatementReturn\"]\n";
        out_ << "\"" << &node << "\"" << " -> " << "\"" << node.expression.get() << "\"" << "\n";
    }

    void SyntaxTreePrinter::visit(const SyntaxTree::DeclarationMethodNode &node) {
        node.return_type->accept(*this);
        node.identifier->accept(*this);
        out_ << "\"" << &node << "\"" << " [label=\"DeclarationMethod\nPrivacyModifier: " << node.privacy_modifier
             << "\nis_static: "
             << node.is_static << "\" shape=diamond]\n";
        out_ << "\"" << &node << "\"" << " -> " << "\"" << node.return_type.get() << "\"" << "\n";
        out_ << "\"" << &node << "\"" << " -> " << "\"" << node.identifier.get() << "\"" << "\n";
        for (auto &argument : node.arguments) {
            out_ << "\"" << &node << "\"" << " -> " << "\"" << argument.get() << "\"" << "\n";
        }
        for (auto &argument : node.variables) {
            out_ << "\"" << &node << "\"" << " -> " << "\"" << argument.get() << "\"" << "\n";
        }
        for (auto &argument : node.statements) {
            out_ << "\"" << &node << "\"" << " -> " << "\"" << argument.get() << "\"" << "\n";
        }
    }

    void SyntaxTreePrinter::visit(const SyntaxTree::DeclarationClassNode &node) {
        out_ << "\"" << &node << "\"" << " [label=\"DeclarationClass\" shape=diamond]\n";
        out_ << "\"" << &node << "\"" << " -> " << "\"" << node.identifier.get() << "\"" << "\n";
        if (node.base_class_identifier) {
            out_ << "\"" << &node << "\"" << " -> " << "\"" << node.base_class_identifier.get() << "\"" << "\n";
        }
        for (auto &argument : node.variables) {
            out_ << "\"" << &node << "\"" << " -> " << "\"" << argument.get() << "\"" << "\n";
        }
        for (auto &argument : node.methods) {
            out_ << "\"" << &node << "\"" << " -> " << "\"" << argument.get() << "\"" << "\n";
        }
    }

    void SyntaxTreePrinter::visit(const SyntaxTree::DeclarationVarNode &node) {
        out_ << "\"" << &node << "\"" << " [label=\"DeclarationVar\" shape=diamond]\n";
        out_ << "\"" << &node << "\"" << " -> " << "\"" << node.var_type.get() << "\"" << "\n";
        out_ << "\"" << &node << "\"" << " -> " << "\"" << node.identifier.get() << "\"" << "\n";
    }

    void SyntaxTreePrinter::visit(
            const SyntaxTree::ListNode<SyntaxTree::DeclarationClassNode, SyntaxTree::INodeBase> &node) {
        out_ << "\"" << &node << "\"" << " [label=\"Goal\" shape=diamond]\n";
        for (auto &argument : node.items) {
            out_ << "\"" << &node << "\"" << " -> " << "\"" << argument.get() << "\"" << "\n";
        }
    }
}