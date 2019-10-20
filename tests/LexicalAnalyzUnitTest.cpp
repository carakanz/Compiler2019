//
// Created by Zinenko Dmytro on 20.10.2019.
//

#include "gtest/gtest.h"
#include "../LexicalAnalyz/include/LexicalAnalyz.h"
#include <fstream>
#include <iostream>
#include <array>

void PrintToken(Token token, const std::string& metadata, int column, int line) {
    std::cout << token << " " <<
              metadata << " " <<
              column << " " <<
              line << std::endl;
}

void FindUnknownToken(Token token, const std::string& metadata, int column, int line) {
    ASSERT_NE(token, Token::T_UNKNOWN) <<
                                       metadata << " " <<
                                       line << " " <<
                                       column << std::endl;
}

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

const std::string PathPrefix = "../tests/Samples/";

TEST(LexicalAnalyz, FindUnknownToken) {
    for (const auto& path : Paths) {
        std::ifstream sample(PathPrefix + path);
        ASSERT_TRUE(sample.is_open());
        LexicalAnalyz scanner(FindUnknownToken);
        scanner.parseStream(sample);
        std::cout << "Ok: " << PathPrefix + path << std::endl;
        sample.close();
    }
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}