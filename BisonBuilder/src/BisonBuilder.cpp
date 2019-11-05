//
// Created by Zinenko Dmytro on 24.10.2019.
//

#include "../include/BisonBuilder.h"
#include "cassert"

namespace BisonBuilder {
    int BisonBuilder::parse(std::istream &input) {
        switch_streams(input, std::cerr);
        yy::parser parser(*this);
        return parser.parse();
    }

    Token BisonBuilder::process(Token token) {
        std::string text(YYText());
        auto build = [&](auto operation) {
            yylval->build(operation);
            return token;
        };
        switch (token) {
            case Token::T_PRIVACY_MODIFIER:
                return build(text == "private" ?
                             SyntaxTree::DeclarationMethodNode::PUBLIC :
                             SyntaxTree::DeclarationMethodNode::PRIVATE);
            case Token::T_BOOL_VALUE:
                return build(text == "true");
            case Token::T_INT_VALUE:
                return build(std::stoi(text));
            case Token::T_IDENTIFIER:
                return build(text);
            case Token::T_MUL_OPERATION:
                if (text == "*") {
                    return build(ExpressionBinaryOperationNode::BinaryOperationType::MUL);
                }
                else if (text == "/") {
                    return build(ExpressionBinaryOperationNode::BinaryOperationType::DIV);
                }
                else if (text == "%") {
                    return build(ExpressionBinaryOperationNode::BinaryOperationType::MOD);
                } else {
                    assert(false);
                }
            case Token::T_ADD_OPERATION:
                if (text == "+") {
                    return build(ExpressionBinaryOperationNode::BinaryOperationType::ADD);
                }
                else if (text == "-") {
                    return build(ExpressionBinaryOperationNode::BinaryOperationType::SUB);
                } else {
                    assert(false);
                }
            case Token::T_CMP_OPERATION:
                if (text == "<") {
                    return build(ExpressionBinaryOperationNode::BinaryOperationType::LESS);
                }
                else if (text == "<=") {
                    return build(ExpressionBinaryOperationNode::BinaryOperationType::LESS_OR_EQUIVALENT);
                }
                else if (text == ">") {
                    return build(ExpressionBinaryOperationNode::BinaryOperationType::MORE);
                }
                else if (text == ">=") {
                    return build(ExpressionBinaryOperationNode::BinaryOperationType::LESS_OR_EQUIVALENT);
                } else {
                    assert(false);
                }
            case Token::T_EQUIVALENT_OPERATION:
                if (text == "==") {
                    return build(ExpressionBinaryOperationNode::BinaryOperationType::EQUIVALENT);
                }
                else if (text == "!=") {
                    return build(ExpressionBinaryOperationNode::BinaryOperationType::NOT_EQUIVALENT);
                } else {
                    assert(false);
                }
            case Token::T_AND_OPERATION:
                return build(ExpressionBinaryOperationNode::BinaryOperationType::AND);
            case Token::T_OR_OPERATION:
                return build(ExpressionBinaryOperationNode::BinaryOperationType::OR);
            default:
                return token;
        }
    }
}