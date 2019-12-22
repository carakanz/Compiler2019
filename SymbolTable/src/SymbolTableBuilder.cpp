//
// Created by carak on 15.12.2019.
//

#include <stdexcept>
#include "SymbolTableBuilder.h"

namespace SymbolTree {

    SymbolTree SymbolTableBuilder::build(const SyntaxTree::Tree& syntax_tree) {
        SymbolTree symbol_tree = SymbolTree();
        const SyntaxTree::GoalNode &goal_node = syntax_tree.get_root();
        size_t layer = 256*256;
        while (symbol_tree.classes_info.size() != goal_node.items.size()) {
            for (const auto &class_node : goal_node.items) {
                if (class_node->base_class_identifier) {
                    const auto base_node = symbol_tree.classes_info.find(class_node->base_class_identifier->name);
                    if (base_node != symbol_tree.classes_info.end()) {
                        auto result = symbol_tree.classes_info.emplace(class_node->identifier->name,
                                                                       build_class(*class_node, &base_node->second));
                        if (!result.second) {
                            throw std::runtime_error("Duplicated class " + class_node->identifier->name);
                        }
                    } else {
                        continue;
                    }
                } else {
                    auto result = symbol_tree.classes_info.emplace(class_node->identifier->name, build_class(*class_node, nullptr));
                    if (!result.second) {
                        throw std::runtime_error("Duplicated class " + class_node->identifier->name);
                    }
                }
            }
            if (layer-- == 0) {
                throw std::runtime_error("Cyclic dependence");
            }
        }
        return symbol_tree;
    }

    std::string SymbolTableBuilder::build_method_signature(const SyntaxTree::DeclarationMethodNode &method_node) {
        std::string method_signature = method_node.return_type->get_name() + " " +
                                       method_node.identifier->name + "(";
        for (auto const& argument : method_node.arguments) {
            method_signature += argument->var_type->get_name() + ", ";
        }
        method_signature += ")";
        return method_signature;
    }

    ClassInfo SymbolTableBuilder::build_class(const SyntaxTree::DeclarationClassNode &class_node,
                                             const ClassInfo *base_class_node) {
        ClassInfo class_info;
        if (base_class_node) {
            class_info = *base_class_node;
            class_info.base = base_class_node->name;
        } else {
            class_info = ClassInfo();
        }
        class_info.name = class_node.identifier->name;
        for (const auto &method_node : class_node.methods) {
            class_info.method_info[build_method_signature(*method_node)] = build_method(*method_node);
        }
        for (const auto &var_node : class_node.variables) {
            auto result = class_info.var_info.emplace(var_node->identifier->name, build_var(*var_node));
            if (!result.second) {
                throw std::runtime_error("Duplicated var " + class_info.name + "::" + var_node->identifier->name);
            }
        }
        return class_info;
    }

    MethodInfo SymbolTableBuilder::build_method(const SyntaxTree::DeclarationMethodNode &method_node) {
        MethodInfo method_info;
        method_info.name = method_node.identifier->name;
        method_info.signature = build_method_signature(method_node);
        method_info.return_type_name = method_node.return_type->get_name();
        method_info.is_private = method_node.privacy_modifier == SyntaxTree::DeclarationMethodNode::PRIVATE;
        method_info.is_static = method_node.is_static;
        for (const auto &arg_node : method_node.arguments) {
            method_info.args.push_back(arg_node->var_type->get_name());
            auto result = method_info.arg_info.emplace(arg_node->identifier->name, build_var(*arg_node));
            if (!result.second) {
                throw std::runtime_error("Duplicated arg " + method_info.name + "::" + arg_node->identifier->name);
            }
        }
        for (const auto &var_node : method_node.variables) {
            auto result = method_info.var_info.emplace(var_node->identifier->name, build_var(*var_node));
            if (!result.second) {
                throw std::runtime_error("Duplicated var " + method_info.name + "::" + var_node->identifier->name);
            }
        }
        return method_info;
    }

    VarInfo SymbolTableBuilder::build_var(const SyntaxTree::DeclarationVarNode &var_node) {
        VarInfo var_info;
        var_info.name = var_node.identifier->name;
        var_info.type = var_node.var_type->get_name();
        return var_info;
    }
}
