//
// Created by l1onsun on 15.12.19.
//

#include "IRTreeTranslator.h"


IRTree::IRTreeTranslator::IRTreeTranslator(SyntaxTree::Tree &tree,
                                           SymbolTree::SymbolTree symbol_tree) : symbol_tree_(std::move(symbol_tree)) {
    findMain();
    tree.accept(*this);
}

void IRTree::IRTreeTranslator::visit(const SyntaxTree::TypeIntNode &node) {

}

void IRTree::IRTreeTranslator::visit(const SyntaxTree::TypeArrayNode &node) {

}

void IRTree::IRTreeTranslator::visit(const SyntaxTree::TypeBooleanNode &node) {

}

void IRTree::IRTreeTranslator::visit(const SyntaxTree::TypeUserNode &node) {

}

void IRTree::IRTreeTranslator::visit(const SyntaxTree::TypeVoidNode &node) {

}

void IRTree::IRTreeTranslator::visit(const SyntaxTree::TypeStringNode &node) {

}

void IRTree::IRTreeTranslator::visit(const SyntaxTree::IdentifierNode &node) {

}

void IRTree::IRTreeTranslator::visit(const SyntaxTree::ExpressionIdentifierNode &node) {

}

void IRTree::IRTreeTranslator::visit(const SyntaxTree::ExpressionBinaryOperationNode &node) {

}

void IRTree::IRTreeTranslator::visit(const SyntaxTree::ExpressionIndexNode &node) {

}

void IRTree::IRTreeTranslator::visit(const SyntaxTree::ExpressionGetLengthNode &node) {

}

void IRTree::IRTreeTranslator::visit(const SyntaxTree::ExpressionMethodCallNode &node) {

}

void IRTree::IRTreeTranslator::visit(const SyntaxTree::ExpressionStaticMethodCallNode &node) {

}

void IRTree::IRTreeTranslator::visit(const SyntaxTree::ExpressionIntegerLiteralNode &node) {

}

void IRTree::IRTreeTranslator::visit(const SyntaxTree::ExpressionBooleanLiteralNode &node) {

}

void IRTree::IRTreeTranslator::visit(const SyntaxTree::ExpressionThisNode &node) {

}

void IRTree::IRTreeTranslator::visit(const SyntaxTree::ExpressionNewArrayNode &node) {

}

void IRTree::IRTreeTranslator::visit(const SyntaxTree::ExpressionNewNode &node) {

}

void IRTree::IRTreeTranslator::visit(const SyntaxTree::ExpressionNotOperatorNode &node) {

}

void IRTree::IRTreeTranslator::visit(const SyntaxTree::ExpressionRoundBracketsNode &node) {

}

void IRTree::IRTreeTranslator::visit(const SyntaxTree::StatementIfNode &node) {

}

void IRTree::IRTreeTranslator::visit(
        const SyntaxTree::ListNode<SyntaxTree::IStatementNode, SyntaxTree::IStatementNode> &node) {

}

void IRTree::IRTreeTranslator::visit(const SyntaxTree::StatementEmptyNode &node) {

}

void IRTree::IRTreeTranslator::visit(const SyntaxTree::StatementWhileNode &node) {

}

void IRTree::IRTreeTranslator::visit(const SyntaxTree::StatementPrintlnNode &node) {

}

void IRTree::IRTreeTranslator::visit(const SyntaxTree::StatementAssignNode &node) {

}

void IRTree::IRTreeTranslator::visit(const SyntaxTree::StatementAssignArrayNode &node) {

}

void IRTree::IRTreeTranslator::visit(const SyntaxTree::StatementReturnNode &node) {

}

void IRTree::IRTreeTranslator::visit(const SyntaxTree::DeclarationMethodNode &node) {

}

void IRTree::IRTreeTranslator::visit(const SyntaxTree::DeclarationClassNode &node) {
    //auto x = symbol_tree_.classes_info.find(node.identifier->name);
    SymbolTree::ClassInfo* classinfo = getClassFromName(node.identifier->name);
    for (const auto& method : classinfo->method_info) {
        method.second.name;
        //goal->AddMethod(currentWrapper->ToStatement());
    }
}

void IRTree::IRTreeTranslator::visit(const SyntaxTree::DeclarationVarNode &node) {

}

void IRTree::IRTreeTranslator::visit( // GoalNode
        const SyntaxTree::ListNode<SyntaxTree::DeclarationClassNode, SyntaxTree::INodeBase> &node) {

    //handle main class first
    for (const auto& item : node.items) {
        if (item->identifier->name == mainClass->name)
            item->accept(*this);
    }

    //then handle others
    for (const auto& item : node.items) {
        if (item->identifier->name == mainClass->name)
            item->accept(*this);
    }
    //yea it's govnokod
}



