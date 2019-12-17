//
// Created by carak on 17.12.2019.
//

#include "TypeCheck.h"


namespace Visitor {

    void TypeCheck::visit(const SyntaxTree::TypeIntNode &node) {

    }

    void TypeCheck::visit(const SyntaxTree::TypeBooleanNode &node) {

    }

    void TypeCheck::visit(const SyntaxTree::TypeArrayNode &node) {

    }

    void TypeCheck::visit(const SyntaxTree::TypeUserNode &node) {

    }

    void TypeCheck::visit(const SyntaxTree::TypeVoidNode &node) {

    }

    void TypeCheck::visit(const SyntaxTree::TypeStringNode &node) {

    }

    void TypeCheck::visit(const SyntaxTree::IdentifierNode &node) {

    }

    void TypeCheck::visit(const SyntaxTree::ExpressionIdentifierNode &node) {

    }

    void TypeCheck::visit(const SyntaxTree::ExpressionBinaryOperationNode &node) {

    }

    void TypeCheck::visit(const SyntaxTree::ExpressionIndexNode &node) {

    }

    void TypeCheck::visit(const SyntaxTree::ExpressionGetLengthNode &node) {

    }

    void TypeCheck::visit(const SyntaxTree::ExpressionMethodCallNode &node) {

    }

    void TypeCheck::visit(const SyntaxTree::ExpressionStaticMethodCallNode &node) {

    }

    void TypeCheck::visit(const SyntaxTree::ExpressionIntegerLiteralNode &node) {

    }

    void TypeCheck::visit(const SyntaxTree::ExpressionBooleanLiteralNode &node) {

    }

    void TypeCheck::visit(const SyntaxTree::ExpressionThisNode &node) {

    }

    void TypeCheck::visit(const SyntaxTree::ExpressionNewArrayNode &node) {

    }

    void TypeCheck::visit(const SyntaxTree::ExpressionNewNode &node) {

    }

    void TypeCheck::visit(const SyntaxTree::ExpressionNotOperatorNode &node) {

    }

    void TypeCheck::visit(const SyntaxTree::ExpressionRoundBracketsNode &node) {

    }

    void TypeCheck::visit(const SyntaxTree::StatementIfNode &node) {

    }

    void TypeCheck::visit(const SyntaxTree::ListNode<SyntaxTree::IStatementNode, SyntaxTree::IStatementNode> &node) {
                
    }

    void TypeCheck::visit(const SyntaxTree::StatementEmptyNode & /*node*/) {
    }

    void TypeCheck::visit(const SyntaxTree::StatementWhileNode &node) {
        node.conditional->accept(*this);
        if (!can_assigned(last_return_type_, "boolean")) {
            throw std::runtime_error(
                    "Can not assigned " + last_return_type_ + " to boolean");
        }
        node.then_statement->accept(*this);
    }

    void TypeCheck::visit(const SyntaxTree::StatementPrintlnNode &node) {
        node.expression->accept(*this);
        if (!can_assigned(last_return_type_, "int")) {
            throw std::runtime_error(
                    "Can not assigned " + last_return_type_ + " to int");
        }
    }

    void TypeCheck::visit(const SyntaxTree::StatementAssignNode &node) {
        node.identifier->accept(*this);
        std::string type = last_return_type_;
        node.expression->accept(*this);
        if (!can_assigned(last_return_type_, type)) {
            throw std::runtime_error(
                    "Can not assigned " + last_return_type_ + " to " + type);
        }
    }

    void TypeCheck::visit(const SyntaxTree::StatementAssignArrayNode &node) {
        node.index->accept(*this);
        if (!can_assigned(last_return_type_, "int")) {
            throw std::runtime_error(
                    "Can not assigned " + last_return_type_ + " to int");
        }
        node.identifier->accept(*this);
        std::string type = is_array(last_return_type_);
        if (type.empty()) {
            throw std::runtime_error(node.identifier->name + " is not array");
        }
        node.expression->accept(*this);
        if (!can_assigned(last_return_type_, type)) {
            throw std::runtime_error(
                    "Can not assigned " + last_return_type_ + " to " + type);
        }
    }

    void TypeCheck::visit(const SyntaxTree::StatementReturnNode &node) {
        node.expression->accept(*this);
        if (!can_assigned(last_return_type_, current_method_->return_type->get_name())) {
            throw std::runtime_error(
                    "Can not assigned " + last_return_type_ + " to " + current_method_->return_type->get_name());
        }
        last_return_type_ = current_method_->return_type->get_name();
    }

    void TypeCheck::visit(const SyntaxTree::DeclarationMethodNode &node) {
        current_method_ = &node;
        for (const auto& arg_node: node.arguments) {
            arg_node->accept(*this);
        }
        for (const auto& var_node : node.variables) {
            var_node->accept(*this);
        }
        for (const auto& statement_node: node.statements) {
            statement_node->accept(*this);
        }
        node.return_type->accept(*this);
    }

    void TypeCheck::visit(const SyntaxTree::DeclarationClassNode &node) {
        current_class_ = &node;
        for (const auto& var_node : node.variables) {
            var_node->accept(*this);
        }
        for (const auto& method_node: node.methods) {
            method_node->accept(*this);
        }
    }

    void TypeCheck::visit(const SyntaxTree::DeclarationVarNode &node) {
        node.var_type->accept(*this);
    }

    void TypeCheck::visit(const SyntaxTree::ListNode<SyntaxTree::DeclarationClassNode, SyntaxTree::INodeBase> &node) {
        for (const auto& class_node : node.items) {
            class_node->accept(*this);
        }
    }
}