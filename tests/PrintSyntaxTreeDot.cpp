//
// Created by Zinenko Dmytro on 25.11.2019.
//

#include "gtest/gtest.h"
#include <include/Builder.h>
#include <Visitors.h>
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
const std::string ResultPrefix("../../tests/Samples/Digraph/SyntaxTree/");

TEST(SyntaxTree, Digraph) {
    BisonBuilder::Builder builder;
    for (const auto &path : Paths) {
        std::ifstream sample(PathPrefix + path);
        ASSERT_TRUE(sample.is_open());
        auto analyzer = builder.parse(sample);
        ASSERT_EQ(analyzer, 0);
        SyntaxTree::Tree tree(std::move(builder.root));
        std::ofstream digraph(ResultPrefix + path + ".dot");
        ASSERT_TRUE(digraph.is_open());
        SyntaxTreeVisitor::SyntaxTreePrinter printer(digraph);
        SyntaxTreeVisitor::SyntaxTreeDFSVisitor<SyntaxTreeVisitor::SyntaxTreePrinter> DFS_visitor(printer);
        ASSERT_NO_THROW(printer.print_start(path));
        ASSERT_NO_THROW(tree.accept(DFS_visitor));
        ASSERT_NO_THROW(printer.print_end());
        digraph.close();
        std::cout << "Ok: " << PathPrefix + path << "   result: " << analyzer << std::endl;
        sample.close();
    }
}
