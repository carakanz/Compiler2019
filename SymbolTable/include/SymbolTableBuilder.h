//
// Created by Zinenko Dmytro on 15.12.2019.
//
#include <memory>
#include <Tree.h>
#include "SymbolTree.h"

namespace SymbolTree {

    class SymbolTableBuilder {
    public:
        static SymbolTree build(const SyntaxTree::Tree &syntax_tree);

        static ClassInfo
        build_class(const SyntaxTree::DeclarationClassNode &class_node, const ClassInfo *base_class_node);

        static MethodInfo build_method(const SyntaxTree::DeclarationMethodNode &method_node);

        static VarInfo build_var(const SyntaxTree::DeclarationVarNode &var_node);
    };

}
