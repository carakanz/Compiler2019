cmake_minimum_required (VERSION 3.8)

project(IRTree VERSION 1.0 LANGUAGES CXX)

add_library(${PROJECT_NAME} STATIC
        ../Defines/BinaryOperationType.h
        include/IRTree/Nodes.h
        include/IRTree/INodeBase.h
        include/IRTree/IVisitor.h
        include/StatementNode/IStatementNode.h
        src/IRTree/Nodes.cpp
        include/StatementNode/StatementExpressionNode.h
        include/ExpressionNode/IExpressionNode.h
        include/StatementNode/StatementJumpNode.h
        include/LabelNode/LabelNode.h
        include/TempNode/TempNode.h
        include/StatementNode/StatementCJumpNode.h
        include/StatementNode/StatementLabelNode.h
        include/StatementNode/StatementMoveNode.h
        include/StatementNode/StatementSeqNode.h
        include/ExpressionNode/ExpressionBinaryOperationNode.h
        include/ExpressionNode/ExpressionConstNode.h
        include/ExpressionNode/ExpressionNameNode.h
        include/ExpressionNode/ExpressionTempNode.h
        include/ExpressionNode/ExpressionESeqNode.h
        include/ExpressionNode/ExpressionMemoryNode.h
        include/ExpressionNode/ExpressionCallNode.h ../Defines/CJumpCondition.h)

set(COMMON_INCLUDES ${PROJECT_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${COMMON_INCLUDES} ../Defines)
target_link_libraries(${PROJECT_NAME})

set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION})

set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER
        include/IRTree/Nodes.h
        )