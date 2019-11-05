# CMakeList.txt: проект CMake для LexicalAnalyz; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

project(SyntaxTree VERSION 1.0 LANGUAGES CXX)

add_library(${PROJECT_NAME} STATIC
        src/TreeNodes.cpp
        include/INodeBase.h
        include/TemplateNode/CloneNode.h
        include/TemplateNode/ListNode.h
        include/TypeNode/ITypeNode.h
        include/TypeNode/TypeVoidNode.h
        include/TypeNode/TypeIntNode.h
        include/TypeNode/TypeBooleanNode.h
        include/TypeNode/TypeArrayNode.h
        include/TypeNode/TypeUserNode.h
        include/IdentifierNode/IdentifierNode.h
        include/ExpressionNode/ExpressionIdentifierNode.h
        include/ExpressionNode/IExpressionNode.h
        include/ExpressionNode/ExpressionBinaryOperationNode.h
        include/ExpressionNode/ExpressionIndexNode.h
        include/ExpressionNode/ExpressionGetLengthNode.h
        include/ExpressionNode/ExpressionMethodCallNode.h
        include/ExpressionNode/ExpressionStaticMethodCallNode.h
        include/ExpressionNode/ExpressionIntegerLiteralNode.h
        include/ExpressionNode/ExpressionThisNode.h
        include/ExpressionNode/ExpressionNewNode.h
        include/ExpressionNode/ExpressionNewArrayNode.h
        include/ExpressionNode/ExpressionBooleanLiteralNode.h
        include/ExpressionNode/ExpressionNotOperatorNode.h
        include/ExpressionNode/ExpressionRoundBracketsNode.h
        include/StatementNode/IStatementNode.h
        include/StatementNode/StatementIfNode.h
        include/StatementNode/StatementWhileNode.h
        include/StatementNode/StatementPrintlnNode.h
        include/StatementNode/StatementAssignNode.h
        include/StatementNode/StatementAssignArrayNode.h
        include/StatementNode/StatementReturnNode.h
        include/DeclarationNode/DeclarationMethodNode.h
        include/DeclarationNode/DeclarationClassNode.h
        include/DeclarationNode/PairTypeIdentifierNode.h
        include/Goal/GoalNode.h include/TypeNode/TypeStringNode.h)

set(COMMON_INCLUDES ${PROJECT_SOURCE_DIR}/include)
include_directories(${COMMON_INCLUDES})

set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION})

set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER
        include/TreeNodes.h
        )
