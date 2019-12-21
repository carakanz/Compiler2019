//
// Created by l1onsun on 17.12.19.
//


#include "gtest/gtest.h"
#include <include/Builder.h>
#include <Visitors.h>
#include <fstream>
#include <iostream>
#include <array>
#include <algorithm>
#include <IRTreeTranslator.h>

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

TEST(IRTree, Test) {
    IRTree::IRTreeTranslator();
}