//
// Created by carak on 21.12.2019.
//

#include "SymbolTree.h"
#include <cassert>

namespace SymbolTree {

    SymbolTree::AssignedType SymbolTree::can_assigned(std::string src, std::string dst) const {
        assert(!src.empty());
        assert(!dst.empty());
        if (src == "void" || dst == "void") {
            return AssignedType::NotAssigned;
        }
        if (src == dst) {
            return AssignedType::Equal;
        } else if (src == "int" && dst == "boolean") {
            return AssignedType::Extension;
        } else if (src == "boolean" && dst == "int") {
            return AssignedType::Contraction;
        }
        std::string src_base = is_array(src);
        std::string dst_base = is_array(dst);
        while (!src_base.empty() && !dst_base.empty()) {
            src = std::move(src_base);
            dst = std::move(dst_base);
            src_base = is_array(src);
            dst_base = is_array(dst);
        }
        if (src_base.empty() != dst_base.empty()) {
            return AssignedType::NotAssigned;
        }
        if (src == "int" || src == "bool" || src == "void" || src == "String" ||
            dst == "int" || dst == "bool" || dst == "void" || dst == "String") {
            return AssignedType::NotAssigned;
        }
        auto src_info = classes_info.at(src);
        while (src != dst && !src_info.base.empty()) {
            src = src_info.base;
            src_info = classes_info.at(src);
        }
        if (src == dst) {
            return AssignedType::Inheritance;
        } else {
            return AssignedType::NotAssigned;
        }
    }

    std::string SymbolTree::is_array(const std::string &type_name) {
        return (type_name.size() > 2 &&
                type_name[type_name.size() - 1] == ']' &&
                type_name[type_name.size() - 2] == '[') ?
               type_name.substr(0,type_name.size() - 2) :
               "";
    }
}