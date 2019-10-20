//
// Created by Zinenko Dmytro on 20.10.2019.
//

#include "LexicalAnalyz.h"
#include <cassert>

void LexicalAnalyz::parseStream(std::istream &input) {
    assert(token_processor_ != nullptr);
    switch_streams(input, std::cerr);
    while (yylex() != Token::T_EOF) {
    }
}

Token LexicalAnalyz::Process(Token token) {
    assert(token_processor_ != nullptr);
    token_processor_(token, YYText(), column_, line_);
    UpdatePos();
    return token;
}


void LexicalAnalyz::UpdatePos() {
    std::string text(YYText());
    column_ += text.size();
}

void LexicalAnalyz::Space() {
    UpdatePos();
}

void LexicalAnalyz::EndOfLine() {
    line_ ++;
    column_ = 0;
}
