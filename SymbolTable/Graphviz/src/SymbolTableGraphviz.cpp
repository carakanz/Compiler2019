//
// Created by carak on 15.12.2019.
//

#include "../include/SymbolTableGraphviz.h"

namespace SymbolTree::Graphviz {

    void Graph::print_table(std::string name) {
        print_start(name);
        for (const auto &class_info : tree_.classes_info) {
            print_class(class_info.second);
        }
        print_end();
    }

    void Graph::print_start(std::string name) {
        size_t dot = name.find('.');
        while (dot != std::string::npos) {
            name.erase(name.find('.'));
            dot = name.find('.');
        }
        out_ << "digraph " << name << " {" << "\n";
    }

    void Graph::print_end() {
        out_ << "}" << std::endl;
    }

    void Graph::print_class(const ClassInfo &class_info) {
        out_ << "\"" << &class_info << "\"" << " [label=" << class_info.name << " shape=diamond]\n";
        if (!class_info.base.empty()) {
            out_ << "\"" << &class_info << "\"" << " -> " "\"" << &tree_.classes_info.at(class_info.base) << "\"\n";
        }
        for (const auto &method_info : class_info.method_info) {
            print_method(method_info.second);
            out_ << "\"" << &class_info << "\"" << " -> " "\"" << &method_info.second << "\"\n";
        }
        for (const auto &var_info : class_info.var_info) {
            print_var(var_info.second);
            out_ << "\"" << &class_info << "\"" << " -> " "\"" << &var_info.second << "\"\n";
        }
    }

    void Graph::print_method(const MethodInfo &method_info) {
        out_ << "\"" << &method_info << "\"" << " [label=\"" << method_info.name << "\" shape=box]\n";
        for (const auto &arg_info : method_info.arg_info) {
            print_var(arg_info.second);
            out_ << "\"" << &method_info << "\"" << " -> " "\"" << &arg_info.second << "\"\n";
        }
        for (const auto &var_info : method_info.var_info) {
            print_var(var_info.second);
            out_ << "\"" << &method_info << "\"" << " -> " "\"" << &var_info.second << "\"\n";
        }

    }

    void Graph::print_var(const VarInfo &var_info) {
        out_ << "\"" << &var_info << "\"" << " [label=\"" << var_info.type << " : " << var_info.name << "\"]\n";
    }

}