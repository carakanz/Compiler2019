//
// Created by Admin on 03.06.2020.
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
#include "../IRTree/Visitors/include/IRTreeCallCanonizator.h"
#include "../IRTree/Visitors/include/IRTreeESeqCanonizator.h"
#include "../IRTree/Visitors/include/IRTreeFinalLinearisator.h"


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
const std::string ResultPrefix("../../tests/Samples/Digraph/IRTreeLinearization/");

TEST(IRTreeLinearization, Test) {
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
        IRTreeVisitor::IRTreeCallCanonizator call_canonizator;
        call_canonizator.visit(*translator.goal);
        IRTreeVisitor::IRTreeESeqCanonizator eseq_canonizator;
        eseq_canonizator.visit(*translator.goal);
        ASSERT_NO_THROW(
                IRTreeVisitor::IRTreeFinalLinearisator linearizator;
                linearizator.visit(*translator.goal);
        );
    }
}

TEST(IRTreeLinearization, Parse) {
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

        IRTreeVisitor::IRTreeCallCanonizator call_canonizator;
        call_canonizator.visit(*translator.goal);
        IRTreeVisitor::IRTreeESeqCanonizator eseq_canonizator;
        eseq_canonizator.visit(*translator.goal);
        IRTreeVisitor::IRTreeFinalLinearisator linearizator;
        linearizator.visit(*translator.goal);

        std::ofstream digraph(ResultPrefix + path + ".dot");
        ASSERT_TRUE(digraph.is_open());
        IRTreeVisitor::IRTreeVisitor printer(digraph);
        printer.print_start(path);
        printer.visit_linear(*translator.goal);
        printer.print_end();
        digraph.close();
    }
}

