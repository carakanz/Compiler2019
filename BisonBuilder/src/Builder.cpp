//
// Created by Zinenko Dmytro on 24.10.2019.
//

#include "Builder.h"
#include "cassert"

namespace BisonBuilder {

    int Builder::parse(std::istream &input) {
        switch_streams(input, std::cerr);
        old_position = {0, 0};
        new_position = {0, 0};
        BisonParser::Parser parser(*this);
        return parser.parse();
    }

    BisonParser::Parser::symbol_type Builder::process(FlexToken token) {
        //BisonParser::Parser::make_T_BOOL_VALUE(true);
        std::string text(YYText());
        old_position = new_position;
        //std::cout << "Line: " << old_position.line << " column: " << old_position.column << "  " << text << std::endl;
        new_position.column += text.size();
        auto build = [&](auto operation) {
            return BisonParser::Parser::symbol_type (token, Token(old_position, operation));
        };
        switch (token) {
            case FlexToken::T_PRIVACY_MODIFIER:
                return build(text == "private" ?
                             SyntaxTree::DeclarationMethodNode::PRIVATE :
                             SyntaxTree::DeclarationMethodNode::PUBLIC);
            case FlexToken::T_BOOL_VALUE:
                return build(text == "true");
            case FlexToken::T_INT_VALUE:
                return build(std::stoi(text));
            case FlexToken::T_IDENTIFIER:
                return build(text);
            case FlexToken::T_MUL_OPERATION:
                if (text == "*") {
                    return build(BinaryOperationType::MUL);
                }
                else if (text == "/") {
                    return build(BinaryOperationType::DIV);
                }
                else if (text == "%") {
                    return build(BinaryOperationType::MOD);
                } else {
                    assert(false);
                }
            case FlexToken::T_ADD_OPERATION:
                if (text == "+") {
                    return build(BinaryOperationType::ADD);
                }
                else if (text == "-") {
                    return build(BinaryOperationType::SUB);
                } else {
                    assert(false);
                }
            case FlexToken::T_COMPARE_OPERATION:
                if (text == "<") {
                    return build(BinaryOperationType::LESS);
                }
                else if (text == "<=") {
                    return build(BinaryOperationType::LESS_OR_EQUIVALENT);
                }
                else if (text == ">") {
                    return build(BinaryOperationType::MORE);
                }
                else if (text == ">=") {
                    return build(BinaryOperationType::LESS_OR_EQUIVALENT);
                } else {
                    assert(false);
                }
            case FlexToken::T_EQUIVALENT_OPERATION:
                if (text == "==") {
                    return build(BinaryOperationType::EQUIVALENT);
                }
                else if (text == "!=") {
                    return build(BinaryOperationType::NOT_EQUIVALENT);
                } else {
                    assert(false);
                }
            case FlexToken::T_AND_OPERATION:
                return build(BinaryOperationType::AND);
            case FlexToken::T_OR_OPERATION:
                return build(BinaryOperationType::OR);
            default:
                return BisonParser::Parser::symbol_type(token, Token<void>(old_position));
        }
    }
}