//
// Created by l1onsun on 17.12.19.
//

#include <Builder.h>
#include <SymbolTableBuilder.h>
#include <TypeCheck.h>
#include <fstream>
#include <iostream>
#include <array>
#include <algorithm>

//const std::array<std::string, 8> goodPaths = {
//        "BinarySearch.java",
//        "BinaryTree.java",
//        "BubbleSort.java",
//        "Factorial.java",
//        "LinearSearch.java",
//        "LinkedList.java",
//        "QuickSort.java",
//        "TreeVisitor.java",
//};

const std::array<std::string, 1> goodPaths = {
        "TreeVisitor.java",
};

const std::array<std::string, 25> badPaths = {
        "LC_1.java",
        "TC_11a.java",
        "TC_13a.java",
        "TC_13c.java",
        "TC_1a.java",
        "TC_2a.java",
        "TC_3a(2).java",
        "TC_3b.java",
        "TC_4b.java",
        "TC_6a.java",
        "TC_7c.java",
        "TC_9a.java",
        "TC_bonus1.java",
        "TC_1.java",
        "TC_12b.java",
        "TC_13b.java",
        "TC_13d(optional).java",
        "TC_2.java",
        "TC_3a(1).java",
        "TC_3a.java",
        "TC_4a.java",
        "TC_5a.java",
        "TC_7b.java",
        "TC_8a.java",
        "TC_9a_2.java"

};

const std::string goodPathPrefix("../../tests/Samples/");
const std::string badPathPrefix("../../tests/badSamples/");

//void testFiles(std::string Paths, std::string PathPrefix) {
//    BisonBuilder::Builder builder;
//
//    for (const auto &path : Paths) {
//        std::ifstream sample(PathPrefix + path);
//        ASSERT_TRUE(sample.is_open());
//        auto analyzer = builder.parse(sample);
//        ASSERT_EQ(analyzer, 0);
//        std::cout << "Ok: " << PathPrefix + path << "   result: " << analyzer << std::endl;
//        sample.close();
//        SyntaxTree::Tree tree(std::move(builder.root));
//        SymbolTree::SymbolTree symbol_tree;
//        ASSERT_NO_THROW(symbol_tree = SymbolTree::SymbolTableBuilder::build(tree));
//    }
//}

int main() {
    BisonBuilder::Builder builder;

    for (const auto &path : goodPaths) {
        std::ifstream sample(goodPathPrefix + path);
        (sample.is_open());
        auto analyzer = builder.parse(sample);
        std::cout << "Ok: " << goodPathPrefix + path << "   result: " << analyzer << std::endl;
        sample.close();
        SyntaxTree::Tree tree(std::move(builder.root));
        SymbolTree::SymbolTree symbol_tree;
        (symbol_tree = SymbolTree::SymbolTableBuilder::build(tree));
        Visitor::TypeCheck type_checker(symbol_tree);
        (tree.accept(type_checker));
    }
}
//
//TEST(SymbolTable, TypeCheckBad) {
//    BisonBuilder::Builder builder;
//
//    for (const auto &path : badPaths) {
//        std::ifstream sample(badPathPrefix + path);
//        ASSERT_TRUE(sample.is_open());
//        auto analyzer = builder.parse(sample);
//        ASSERT_EQ(analyzer, 0);
//        std::cout << "Ok: " << badPathPrefix + path << "   result: " << analyzer << std::endl;
//        sample.close();
//        SyntaxTree::Tree tree(std::move(builder.root));
//        SymbolTree::SymbolTree symbol_tree;
//        ASSERT_NO_THROW(symbol_tree = SymbolTree::SymbolTableBuilder::build(tree));
//        Visitor::TypeCheck type_checker(symbol_tree);
//        ASSERT_ANY_THROW(tree.accept(type_checker));
//    }
//}