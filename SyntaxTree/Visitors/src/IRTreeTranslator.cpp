//
// Created by l1onsun on 15.12.19.
//

#include <SymbolTableBuilder.h>
#include "../include/IRTreeTranslator.h"


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
    std::cout << "ExpressionMethodCallNode" << std::endl;
    node.object->accept(*this);

//    const auto objectOperandWrapper = std::move(currentWrapper);
//
//    const auto objectOperandClass = currentObjectClass;
//
//    const auto methodInfo = objectOperandClass->GetMethodByName(methodCallExpression->GetMethodIdentifier()->GetIdentifier());
//    if (!methodInfo->GetReturnType()->IsSimpleType()) {
//        currentObjectClass = getClassByType(methodInfo->GetReturnType());
//    }
//
//    std::vector<std::shared_ptr<const IIrtExpression>> arguments;
//    arguments.push_back(objectOperandWrapper->ToExpression());   // this
//    std::vector<const IExpression*> syntaxTreeArgs;
//    methodCallExpression->GetAllArguments(syntaxTreeArgs);
//    for (const auto arg : syntaxTreeArgs) {
//        arg->AcceptVisitor(this);
//        arguments.push_back(currentWrapper->ToExpression());
//    }
//
//    currentWrapper = makeWrapper<ExpressionWrapper>(
//            makeNode<IrtCallExpression>(
//                    makeNode<IrtNameExpression>(
//                            makeMethodName(objectOperandClass->GetClassName(), methodInfo->GetMethodName())
//                    ),
//                    makeNode<IrtExpressionList>(std::move(arguments))
//            )
//    );
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
    currentObjectClass = getClassFromName(node.type->get_name());
    std::vector<std::shared_ptr<const IRTreeExpression>> arguments;

//    arguments.push_back(
//            makeNode<ExpressionConstNode>(classInfo->GetFieldsCount())
//    );
//    currentWrapper = makeWrapper<ExpressionWrapper>(
//            makeNode<IrtCallExpression>(
//                    makeNode<IrtNameExpression>(makeNode<IrtLabel>(L"malloc")),
//                    makeNode<IrtExpressionList>(std::move(arguments))
//            )
//    );
//    currentObjectClass = classInfo;
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
    std::cout << "SyntaxTree::StatementPrintlnNode" << std::endl;
    node.expression->accept(*this);

//    const auto printOperandWrapper = std::move(currentWrapper);
//    std::vector<std::shared_ptr<const IIrtExpression>> arguments;
//    arguments.push_back(printOperandWrapper->ToExpression());
//
//    currentWrapper = makeWrapper<StatementWrapper>(
//            makeNode<IrtExpressionStatement>(
//                    makeNode<IrtCallExpression>(
//                            makeNode<IrtNameExpression>(makeNode<IrtLabel>(L"print")),
//                            makeNode<IrtExpressionList>(std::move(arguments))
//                    )
//            )
//    );
}

void IRTree::IRTreeTranslator::visit(const SyntaxTree::StatementAssignNode &node) {

}

void IRTree::IRTreeTranslator::visit(const SyntaxTree::StatementAssignArrayNode &node) {

}

void IRTree::IRTreeTranslator::visit(const SyntaxTree::StatementReturnNode &node) {

}

void IRTree::IRTreeTranslator::visit(const SyntaxTree::DeclarationMethodNode &node) {
    for (const auto& statement : node.statements) {
        buildStatement(statement);
    }

    // ... node.variables

}

void IRTree::IRTreeTranslator::visit(const SyntaxTree::DeclarationClassNode &node) {
    std::cout << "DeclarationClassNode: " << node.identifier->name << std::endl;
    for (const auto& method : node.methods)  {
        std::string method_signature = SymbolTree::SymbolTableBuilder::build_method_signature(*method);
        current_method = &current_class->method_info.at(method_signature);
        std::cout << "method name: " << method->identifier->name << std::endl;
        method->accept(*this);
        //goal->AddMethod(currentWrapper->ToStatement());
    }

}

void IRTree::IRTreeTranslator::visit(const SyntaxTree::DeclarationVarNode &node) {

}

void IRTree::IRTreeTranslator::visit( // GoalNode
        const SyntaxTree::ListNode<SyntaxTree::DeclarationClassNode, SyntaxTree::INodeBase> &node) {

    //yea it's govnokod
    //handle main class first
    for (const auto& item : node.items) {
        if (item->identifier->name == mainClass->name) {
            current_class = getClassFromName(item->identifier->name);
            item->accept(*this);
        }
    }

    //then handle others
    for (const auto& item : node.items) {
        if (item->identifier->name != mainClass->name) {
            current_class = getClassFromName(item->identifier->name);
            item->accept(*this);
        }
    }

}

void IRTree::IRTreeTranslator::buildStatement(const std::unique_ptr<SyntaxTree::IStatementNode> &statement) {
    std::cout << "here now" << std::endl;
    statement->accept(*this);
    //...
}



