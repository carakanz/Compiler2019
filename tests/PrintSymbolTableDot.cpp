//
// Created by Zinenko Dmytro on 15.12.2019.
//

#include "gtest/gtest.h"
#include <Builder.h>
#include <SymbolTableBuilder.h>
#include <SymbolTableGraphviz.h>
#include <fstream>
#include <iostream>
#include <array>
#include <algorithm>

const std::array<std::string, 9> Paths = {
        "BinarySearch.java",
        "BinaryTree.java",
        "BubbleSort.java",
        "Factorial.java",
        "LinearSearch.java",
        "LinkedList.java",
        "QuickSort.java",
        "TreeVisitor.java",
        "Test"
};

const std::string PathPrefix("../../tests/Samples/");
const std::string ResultPrefix("../../tests/Samples/Digraph/SymbolTable/");

TEST(SymbolTable, PrintTable) {
    BisonBuilder::Builder builder;
    for (const auto &path : Paths) {
        std::ifstream sample(PathPrefix + path);
        ASSERT_TRUE(sample.is_open());
        auto analyzer = builder.parse(sample);
        ASSERT_EQ(analyzer, 0);
        std::cout << "Ok: " << PathPrefix + path << "   result: " << analyzer << std::endl;
        sample.close();
        SyntaxTree::Tree tree(std::move(builder.root));
        SymbolTree::SymbolTree symbol_tree = SymbolTree::SymbolTree();
        ASSERT_NO_THROW(symbol_tree = SymbolTree::SymbolTableBuilder::build(tree));
        std::ofstream digraph(ResultPrefix + path + ".dot");
        ASSERT_TRUE(digraph.is_open());
        SymbolTree::Graphviz::Graph printer(symbol_tree, digraph);
        ASSERT_NO_THROW(printer.print_table(path));
        digraph.close();
    }
}
