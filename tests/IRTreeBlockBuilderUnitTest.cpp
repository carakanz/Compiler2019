//
// Created by carak on 03.06.2020.
//

#include "gtest/gtest.h"
#include <array>
#include <include/Builder.h>
#include <fstream>
#include <SymbolTree.h>
#include <SymbolTableBuilder.h>
#include <IRTreeTranslator.h>
#include <IRTreeCallCanonizator.h>
#include <IRTreeESeqCanonizator.h>
#include <IRTreeFinalLinearisator.h>
#include <IRVisitors.h>
#include <IRTreeBlockPrinter.h>

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
const std::string ResultPrefix("../../tests/Samples/Digraph/IRTreeBlockBuilder/");

TEST(IRTreeBlockBuilder, Test) {
    BisonBuilder::Builder builder;
    for (const auto &path : Paths) {
        ASSERT_NO_THROW(
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
                IRTree::ProgramInBlock program_in_block = IRTreeVisitor::IRTreeBlockBuilder::build(
                        std::move(translator.goal->linear_wrappers));
        );
    }
}

TEST(IRTreeBlockBuilder, Parse) {
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
        IRTree::ProgramInBlock program_in_block = IRTreeVisitor::IRTreeBlockBuilder::build(
                std::move(translator.goal->linear_wrappers));

        std::ofstream digraph(ResultPrefix + path + ".dot");
        ASSERT_TRUE(digraph.is_open());
        IRTreeVisitor::IRTreeBlockPrinter printer(digraph);
        printer.print_start(path);
        printer.visit(program_in_block);
        printer.print_end();
        digraph.close();
    }
}