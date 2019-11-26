//
// Created by Zinenko Dmytro on 27.10.2019.
//

#pragma once

#include "TypeNode/TypeIntNode.h"
#include "TypeNode/TypeBooleanNode.h"
#include "TypeNode/TypeArrayNode.h"
#include "TypeNode/TypeUserNode.h"
#include "TypeNode/TypeVoidNode.h"
#include "TypeNode/TypeStringNode.h"
#include "IdentifierNode/IdentifierNode.h"
#include "ExpressionNode/ExpressionIdentifierNode.h"
#include "ExpressionNode/ExpressionBinaryOperationNode.h"
#include "ExpressionNode/ExpressionIndexNode.h"
#include "ExpressionNode/ExpressionGetLengthNode.h"
#include "ExpressionNode/ExpressionMethodCallNode.h"
#include "ExpressionNode/ExpressionStaticMethodCallNode.h"
#include "ExpressionNode/ExpressionIntegerLiteralNode.h"
#include "ExpressionNode/ExpressionBooleanLiteralNode.h"
#include "ExpressionNode/ExpressionThisNode.h"
#include "ExpressionNode/ExpressionNewArrayNode.h"
#include "ExpressionNode/ExpressionNewNode.h"
#include "ExpressionNode/ExpressionNotOperatorNode.h"
#include "ExpressionNode/ExpressionRoundBracketsNode.h"
#include "StatementNode/StatementIfNode.h"
#include "StatementNode/StatementWhileNode.h"
#include "StatementNode/StatementPrintlnNode.h"
#include "StatementNode/StatementAssignNode.h"
#include "StatementNode/StatementAssignArrayNode.h"
#include "StatementNode/StatementReturnNode.h"
#include "DeclarationNode/DeclarationMethodNode.h"
#include "DeclarationNode/DeclarationClassNode.h"
#include "DeclarationNode/DeclarationVarNode.h"
#include "Goal/GoalNode.h"

#include <cstddef>
#include <functional>
#include <IVisitor.h>

namespace SyntaxTree {
    class Tree {
    public:
        explicit Tree(std::unique_ptr<GoalNode> root)
                : root_(std::move(root)) {
        }

        [[nodiscard]] const GoalNode &get_root() const {
            return *root_;
        }

        void accept(IVisitor& visitor) const {
            root_->accept(visitor);
        }

    protected:
        std::unique_ptr<GoalNode> root_;
    };
}
