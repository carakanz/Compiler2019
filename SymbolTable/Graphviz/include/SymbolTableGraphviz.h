//
// Created by carak on 15.12.2019.
//

#pragma once

#include <fstream>
#include <SymbolTree.h>

namespace SymbolTree::Graphviz {

    class Graph {
    public:
        explicit Graph(const SymbolTree& tree, std::ofstream &out) : tree_(tree), out_(out) {
        }

        void print_table(std::string name);
        void print_start(std::string name);
        void print_class(const ClassInfo& class_info);
        void print_method(const MethodInfo& method_info);
        void print_var(const VarInfo& var_info);

        void print_end();

    private:
        const SymbolTree& tree_;
        std::ofstream &out_;
    };
}
