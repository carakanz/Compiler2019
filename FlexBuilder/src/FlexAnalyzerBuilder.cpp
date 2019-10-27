//
// Created by Zinenko Dmytro on 20.10.2019.
//

#include "../include/FlexAnalyzerBuilder.h"
#include <cassert>

namespace FlexBuilder {

    LexicalAnalyz::LexicalAnalyzer FlexAnalyzerBuilder::build(std::istream &input) {
        switch_streams(input, std::cerr);
        LexicalAnalyz::LexicalAnalyzer analyzer;
        current_analyzer_ = &analyzer;
        column_ = 0;
        line_ = 0;
        auto next = [&]() {
            auto token = static_cast<LexicalAnalyz::Token>(yylex());
            analyzer.push_back({token, YYText(), column_, line_});
            update_pos();
            return token;
        };
        while (next() != LexicalAnalyz::Token::T_EOF);
        return analyzer;
    }

    void FlexAnalyzerBuilder::update_pos() {
        column_ += std::string(YYText()).size();
    }

    void FlexAnalyzerBuilder::space() {
        column_++;
    }

    void FlexAnalyzerBuilder::end_of_line() {
        line_++;
        column_ = 0;
    }

}
