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

const std::array<std::string, 8> Paths = {
        "BinarySearch.java",
        "BinaryTree.java",
        "BubbleSort.java",
        "Factorial.java",
        "LinearSearch.java",
        "LinkedList.java",
        "QuickSort.java",
        "TreeVisitor.java"
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
        Visitor::SyntaxTreePrinter printer(digraph);
        Visitor::SyntaxTreeDFSVisitor<Visitor::SyntaxTreePrinter> DFS_visitor(printer);
        printer.print_start(path);
        tree.accept(DFS_visitor);
        printer.print_end();
        digraph.close();
        std::cout << "Ok: " << PathPrefix + path << "   result: " << analyzer << std::endl;
        sample.close();
    }
}
