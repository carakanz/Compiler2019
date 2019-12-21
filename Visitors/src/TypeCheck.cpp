//
// Created by carak on 17.12.2019.
//

#include "TypeCheck.h"
#include <SymbolTableBuilder.h>


namespace Visitor {

    void TypeCheck::visit(const SyntaxTree::TypeIntNode &node) {
        last_return_type_ = node.get_name();
    }

    void TypeCheck::visit(const SyntaxTree::TypeBooleanNode &node) {
        last_return_type_ = node.get_name();
    }

    void TypeCheck::visit(const SyntaxTree::TypeArrayNode &node) {
        node.type->accept(*this);
        last_return_type_ = node.get_name();
    }

    void TypeCheck::visit(const SyntaxTree::TypeUserNode &node) {
        if (symbol_tree_.classes_info.find(node.get_name()) == symbol_tree_.classes_info.cend()) {
            throw std::runtime_error("Can not find type" + node.get_name());
        }
        last_return_type_ = node.get_name();
    }

    void TypeCheck::visit(const SyntaxTree::TypeVoidNode &node) {
        last_return_type_ = node.get_name();
    }

    void TypeCheck::visit(const SyntaxTree::TypeStringNode &node) {
        last_return_type_ = node.get_name();
    }

    void TypeCheck::visit(const SyntaxTree::IdentifierNode &node) {
        const auto &current_class_info = symbol_tree_.classes_info.at(current_class_->identifier->name);
        const auto &current_method_info = current_class_info.method_info.at(
                SymbolTree::SymbolTableBuilder::build_method_signature(*current_method_));

        const auto &var_info = current_method_info.var_info.find(node.name);
        const auto &arg_info = current_method_info.arg_info.find(node.name);
        if (var_info != current_method_info.var_info.cend() &&
            arg_info != current_method_info.arg_info.cend()) {
            throw std::runtime_error(
                    "Type check error " + std::to_string(node.position.line) + ":" +
                    std::to_string(node.position.column));
        }
        if (var_info != current_method_info.var_info.cend()) {
            last_return_type_ = var_info->second.type;
            return;
        }
        if (arg_info != current_method_info.arg_info.cend()) {
            last_return_type_ = arg_info->second.type;
            return;
        }
        const auto &class_var_info = current_class_info.var_info.find(node.name);
        if (class_var_info != current_class_info.var_info.cend()) {
            last_return_type_ = class_var_info->second.type;
        } else {
            throw std::runtime_error("Can not find id" + node.name);
        }
    }

    void TypeCheck::visit(const SyntaxTree::ExpressionIdentifierNode &node) {
        node.identifier->accept(*this);
    }

    void TypeCheck::visit(const SyntaxTree::ExpressionBinaryOperationNode &node) {
        node.left->accept(*this);
        std::string left = last_return_type_;
        node.right->accept(*this);
        std::string right = last_return_type_;
        last_return_type_ = "boolean";
        if (left == "boolean") {
        } else if (left == "int") {
            last_return_type_ = "int";
        } else {
            throw std::runtime_error(
                    "Type check error " + std::to_string(node.position.line) + ":" +
                    std::to_string(node.position.column));
        }

        if (right == "boolean") {
        } else if (right == "int") {
            last_return_type_ = "int";
        } else {
            throw std::runtime_error(
                    "Type check error " + std::to_string(node.position.line) + ":" +
                    std::to_string(node.position.column));
        }
    }

    void TypeCheck::visit(const SyntaxTree::ExpressionIndexNode &node) {
        node.index->accept(*this);
        if (SymbolTree::SymbolTree::NotAssigned == symbol_tree_.can_assigned(last_return_type_, "int")) {
            throw std::runtime_error(
                    "Type check error " + std::to_string(node.position.line) + ":" +
                    std::to_string(node.position.column));
        }
        node.array->accept(*this);
        last_return_type_ = SymbolTree::SymbolTree::is_array(last_return_type_);
        if (last_return_type_.empty()) {
            throw std::runtime_error(
                    "Type check error " + std::to_string(node.position.line) + ":" +
                    std::to_string(node.position.column));
        }
    }

    void TypeCheck::visit(const SyntaxTree::ExpressionGetLengthNode &node) {
        node.array->accept(*this);
        if (SymbolTree::SymbolTree::is_array(last_return_type_).empty()) {
            throw std::runtime_error(
                    "Type check error " + std::to_string(node.position.line) + ":" +
                    std::to_string(node.position.column));
        }
        last_return_type_ = "int";
    }

    void TypeCheck::visit(const SyntaxTree::ExpressionMethodCallNode &node) {
        node.object->accept(*this);
        std::string class_name = last_return_type_;
        std::string method_name = node.method->name;
        const auto& class_info = symbol_tree_.classes_info.at(class_name);
        size_t count = 0;
        bool is_private = false;
        SymbolTree::SymbolTree::AssignedType assigned_type = SymbolTree::SymbolTree::NotAssigned;
        for (const auto& method : class_info.method_info) {
            if (method.second.name != method_name) {
                continue;
            }
            if (method.second.args.size() != node.arguments.size()) {
                continue;
            }
            auto max_assigned = SymbolTree::SymbolTree::Equal;
            for (size_t i = 0; i < method.second.args.size(); ++i) {
                node.arguments[i]->accept(*this);
                auto assigned_arg_type = symbol_tree_.can_assigned(last_return_type_, method.second.args[i]);
                if (assigned_arg_type > max_assigned) {
                    max_assigned = assigned_arg_type;
                }
            }
            if (assigned_type == max_assigned) {
                ++count;
            }
            if (assigned_type > max_assigned) {
                assigned_type = max_assigned;
                is_private = method.second.is_private;
                count = 1;
                last_return_type_ = method.second.return_type_name;
            }
        }
        if (assigned_type == SymbolTree::SymbolTree::NotAssigned) {
            throw std::runtime_error(
                    "Can not find method " + class_name + "::" + method_name);
        } else if (count > 1) {
            throw std::runtime_error(
                    "Multiple definition " + class_name + "::" + method_name);
        } else if (class_name != current_class_->identifier->name && is_private) {
            throw std::runtime_error(
                    "Call private method " + class_name + "::" + method_name);
        }
    }

    void TypeCheck::visit(const SyntaxTree::ExpressionStaticMethodCallNode &node) {
        node.class_id->accept(*this);
        std::string class_name = last_return_type_;
        std::string method_name = node.method->name;
        const auto& class_info = symbol_tree_.classes_info.at(class_name);
        size_t count = 0;
        SymbolTree::SymbolTree::AssignedType assigned_type = SymbolTree::SymbolTree::NotAssigned;
        for (const auto& method : class_info.method_info) {
            if (!method.second.is_static) {
                continue;
            }
            if (method.second.name != method_name) {
                continue;
            }
            if (method.second.args.size() != node.arguments.size()) {
                continue;
            }
            auto max_assigned = SymbolTree::SymbolTree::Equal;
            for (size_t i = 0; i < method.second.args.size(); ++i) {
                node.arguments[i]->accept(*this);
                auto assigned_arg_type = symbol_tree_.can_assigned(last_return_type_, method.second.args[i]);
                if (assigned_arg_type > max_assigned) {
                    max_assigned = assigned_arg_type;
                }
            }
            if (assigned_type == max_assigned) {
                ++count;
            }
            if (assigned_type > max_assigned) {
                assigned_type = max_assigned;
                count = 1;
                last_return_type_ = method.second.return_type_name;
            }
        }
        if (assigned_type == SymbolTree::SymbolTree::NotAssigned) {
            throw std::runtime_error(
                    "Can not find method " + class_name + "::" + method_name);
        } else if (count > 1) {
            throw std::runtime_error(
                    "Multiple definition " + class_name + "::" + method_name);
        }
    }

    void TypeCheck::visit(const SyntaxTree::ExpressionIntegerLiteralNode &node) {
        last_return_type_ = "int";
    }

    void TypeCheck::visit(const SyntaxTree::ExpressionBooleanLiteralNode &node) {
        last_return_type_ = "boolean";
    }

    void TypeCheck::visit(const SyntaxTree::ExpressionThisNode &node) {
        last_return_type_ = current_class_->identifier->name;
    }

    void TypeCheck::visit(const SyntaxTree::ExpressionNewArrayNode &node) {
        node.size->accept(*this);
        if (SymbolTree::SymbolTree::NotAssigned == symbol_tree_.can_assigned(last_return_type_, "int")) {
            throw std::runtime_error(
                    "Can not assigned " + last_return_type_ + " to int");
        }
        last_return_type_ = node.type->get_name() + "[]";
    }

    void TypeCheck::visit(const SyntaxTree::ExpressionNewNode &node) {
        last_return_type_ = node.type->get_name();
    }

    void TypeCheck::visit(const SyntaxTree::ExpressionNotOperatorNode &node) {
        node.expression->accept(*this);
    }

    void TypeCheck::visit(const SyntaxTree::ExpressionRoundBracketsNode &node) {
        node.expression->accept(*this);
    }

    void TypeCheck::visit(const SyntaxTree::StatementIfNode &node) {
        node.conditional->accept(*this);
        if (SymbolTree::SymbolTree::NotAssigned == symbol_tree_.can_assigned(last_return_type_, "boolean")) {
            throw std::runtime_error(
                    "Can not assigned " + last_return_type_ + " to boolean");
        }
        node.then_statement->accept(*this);
        node.else_statement->accept(*this);
    }

    void TypeCheck::visit(const SyntaxTree::ListNode<SyntaxTree::IStatementNode, SyntaxTree::IStatementNode> &node) {
        for (const auto& statement : node.items) {
            statement->accept(*this);
        }
    }

    void TypeCheck::visit(const SyntaxTree::StatementEmptyNode & /*node*/) {
    }

    void TypeCheck::visit(const SyntaxTree::StatementWhileNode &node) {
        node.conditional->accept(*this);
        if (SymbolTree::SymbolTree::NotAssigned == symbol_tree_.can_assigned(last_return_type_, "boolean")) {
            throw std::runtime_error(
                    "Can not assigned " + last_return_type_ + " to boolean");
        }
        node.then_statement->accept(*this);
    }

    void TypeCheck::visit(const SyntaxTree::StatementPrintlnNode &node) {
        node.expression->accept(*this);
        if (SymbolTree::SymbolTree::NotAssigned == symbol_tree_.can_assigned(last_return_type_, "int")) {
            throw std::runtime_error(
                    "Can not assigned " + last_return_type_ + " to int");
        }
    }

    void TypeCheck::visit(const SyntaxTree::StatementAssignNode &node) {
        node.identifier->accept(*this);
        std::string type = last_return_type_;
        node.expression->accept(*this);
        if (SymbolTree::SymbolTree::NotAssigned == symbol_tree_.can_assigned(last_return_type_, type)) {
            throw std::runtime_error(
                    "Can not assigned " + last_return_type_ + " to " + type);
        }
    }

    void TypeCheck::visit(const SyntaxTree::StatementAssignArrayNode &node) {
        node.index->accept(*this);
        if (SymbolTree::SymbolTree::NotAssigned == symbol_tree_.can_assigned(last_return_type_, "int")) {
            throw std::runtime_error(
                    "Can not assigned " + last_return_type_ + " to int");
        }
        node.identifier->accept(*this);
        std::string type = SymbolTree::SymbolTree::is_array(last_return_type_);
        if (type.empty()) {
            throw std::runtime_error(node.identifier->name + " is not array");
        }
        node.expression->accept(*this);
        if (SymbolTree::SymbolTree::NotAssigned == symbol_tree_.can_assigned(last_return_type_, type)) {
            throw std::runtime_error(
                    "Can not assigned " + last_return_type_ + " to " + type);
        }
    }

    void TypeCheck::visit(const SyntaxTree::StatementReturnNode &node) {
        node.expression->accept(*this);
        if (SymbolTree::SymbolTree::NotAssigned == symbol_tree_.can_assigned(last_return_type_, current_method_->return_type->get_name())) {
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