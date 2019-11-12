//
// Created by Zinenko Dmytro on 24.10.2019.
//

#include "Builder.h"
#include "cassert"

namespace BisonBuilder {

    int Builder::parse(std::istream &input) {
        switch_streams(input, std::cerr);
        BisonParser::Parser parser(*this);
        return parser.parse();
    }

    BisonParser::Parser::symbol_type Builder::process(Token token) {
        //yy::parser::make_T_BOOL_VALUE(true);
        std::string text(YYText());
        std::cout << token << " " << text << std::endl;
        auto build = [&](auto operation) {
            return BisonParser::Parser::symbol_type (token, std::move (operation));
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
            case Token::T_COMPARE_OPERATION:
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
                return BisonParser::Parser::symbol_type(token);
        }
    }
}