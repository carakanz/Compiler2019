//
// Created by l1onsun on 17.12.19.
//


#include "gtest/gtest.h"
#include <Builder.h>
#include <SymbolTableBuilder.h>
#include <fstream>
#include <iostream>
#include <array>
#include <algorithm>
#include <IRTree/IVisitor.h>
#include "../SyntaxTree/Visitors/include/IRTreeTranslator.h"
#include "../IRTree/Visitors/include/IRTreePrinter.h"


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
const std::string ResultPrefix("../../tests/Samples/Digraph/IRTree/");
//const std::string PathPrefix("Samples/");
//const std::string ResultPrefix("Samples/Digraph/SyntaxTree/");

TEST(IRTree, Test) {
    BisonBuilder::Builder builder;
    for (const auto &path : Paths) {
        std::ifstream sample(PathPrefix + path);
        ASSERT_TRUE(sample.is_open());
        auto analyzer = builder.parse(sample);
        ASSERT_EQ(analyzer, 0);
        std::cout << "Ok: " << PathPrefix + path << "   result: " << analyzer << std::endl;
        sample.close();
        SyntaxTree::Tree tree(std::move(builder.root));
        ASSERT_NO_THROW(
        SymbolTree::SymbolTree symbol_tree = SymbolTree::SymbolTableBuilder::build(tree);
                  SyntaxTreeVisitor::IRTreeTranslator translator(symbol_tree);
                tree.accept(translator);
        );
    }
}

TEST(IRTree, Parse) {
    BisonBuilder::Builder builder;
    for (const auto &path : Paths) {
        std::ifstream sample(PathPrefix + path);
        ASSERT_TRUE(sample.is_open());
        auto analyzer = builder.parse(sample);
        ASSERT_EQ(analyzer, 0);
        std::cout << "Ok: " << PathPrefix + path << "   result: " << analyzer << std::endl;
        sample.close();
        SyntaxTree::Tree tree(std::move(builder.root));
        SymbolTree::SymbolTree symbol_tree = SymbolTree::SymbolTableBuilder::build(tree);
        SyntaxTreeVisitor::IRTreeTranslator translator(symbol_tree);
        tree.accept(translator);

        std::ofstream digraph(ResultPrefix + path + ".dot");
        ASSERT_TRUE(digraph.is_open());
        IRTreeVisitor::IRTreeVisitor printer(digraph);
        printer.print_start(path);
        printer.visit(*translator.goal);
        printer.print_end();
        digraph.close();

    }
}