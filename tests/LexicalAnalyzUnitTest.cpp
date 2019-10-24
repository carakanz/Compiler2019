//
// Created by Zinenko Dmytro on 20.10.2019.
//
#include "gtest/gtest.h"
#include "../LexicalAnalyz/include/FlexAnalyzerBuilder.h"
#include <fstream>
#include <iostream>
#include <array>
#include <algorithm>
#include <unordered_set>

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

TEST(LexicalAnalyz, FindUnknownToken) {
    FlexAnalyzerBuilder builder;
    for (const auto &path : Paths) {
        std::ifstream sample(PathPrefix + path);
        ASSERT_TRUE(sample.is_open());
        auto analyzer = builder.build(sample);
        for (const auto &item : analyzer) {
            ASSERT_NE(item.token, Token::T_UNKNOWN) <<
                                                    item.text << " " <<
                                                    item.line << " " <<
                                                    item.column << std::endl;
        }
        std::cout << "Ok: " << PathPrefix + path << std::endl;
        sample.close();
    }
}

TEST(LexicalAnalyz, FindUnknownIterator) {
    FlexAnalyzerBuilder builder;
    std::ifstream sample(PathPrefix + "BadFactorial.java");
    ASSERT_TRUE(sample.is_open());
    auto analyzer = builder.build(sample);
    std::vector<LexicalAnalyz> errors(analyzer.begin_error(), analyzer.end_error());
    ASSERT_TRUE(std::distance(analyzer.begin_error(), analyzer.end_error()) > 10);
    ASSERT_EQ(analyzer.begin_error()->line, 7);
    std::cout << "Ok: " << PathPrefix + "BadFactorial.java" << std::endl;
    sample.close();
}
