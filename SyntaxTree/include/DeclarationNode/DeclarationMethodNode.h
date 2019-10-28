//
// Created by Zinenko Dmytro on 27.10.2019.
//
#pragma once

#include <INodeBase.h>
#include <IdentifierNode/IdentifierNode.h>
#include <TypeNode/ITypeNode.h>
#include <DeclarationNode/DeclarationVarNode.h>
#include <StatementNode/IStatementNode.h>
#include <ExpressionNode/IExpressionNode.h>
#include <memory>
#include <utility>
#include <vector>

namespace SyntaxTree {
    class DeclarationMethodNode : public virtual INodeBase {
    public:
        DeclarationMethodNode(bool is_public,
                              bool is_static,
                              std::unique_ptr<ITypeNode> return_type,
                              std::unique_ptr<IdentifierNode> identifier,
                              std::vector<std::pair<std::unique_ptr<ITypeNode>,
                                      std::unique_ptr<IdentifierNode>>> arguments,
                              std::vector<IStatementNode> statements,
                              std::vector<DeclarationVarNode> variables,
                              std::unique_ptr<IExpressionNode> return_expression)
                : is_public_(is_public),
                  is_static_(is_static),
                  return_type_(std::move(return_type)),
                  identifier_(std::move(identifier)),
                  arguments_(std::move(arguments)),
                  variables_(std::move(variables)),
                  statements_(std::move(statements)),
                  return_expression_(std::move(return_expression)) {
        }

        [[nodiscard]] NodeType get_type() const override {
            return NodeType::DECLARATION_METHOD;
        }

        [[nodiscard]] auto is_public() const {
            return is_public_;
        }

        [[nodiscard]] auto is_static() const {
            return is_static_;
        }

        [[nodiscard]] auto return_type() const {
            return return_type_.get();
        }

        [[nodiscard]] auto get_identifier() const {
            return identifier_.get();
        }

        [[nodiscard]] auto get_first_argument() const {
            return arguments_.cbegin();
        }

        [[nodiscard]] auto get_last_argument() const {
            return arguments_.cend();
        }

        [[nodiscard]] auto get_first_variable() const {
            return variables_.cbegin();
        }

        [[nodiscard]] auto get_last_variable() const {
            return variables_.cend();
        }

        [[nodiscard]] auto get_first_statement() const {
            return statements_.cbegin();
        }

        [[nodiscard]] auto get_last_statement() const {
            return statements_.cend();
        }

        [[nodiscard]] auto get_return_expression() const {
            return return_expression_.get();
        }

        ~DeclarationMethodNode() override = default;

    private:
        bool is_public_;
        bool is_static_;
        std::unique_ptr<ITypeNode> return_type_;
        std::unique_ptr<IdentifierNode> identifier_;
        std::vector<std::pair<std::unique_ptr<ITypeNode>,
                std::unique_ptr<IdentifierNode>>> arguments_;
        std::vector<DeclarationVarNode> variables_;
        std::vector<IStatementNode> statements_;
        std::unique_ptr<IExpressionNode> return_expression_;
    };
}
