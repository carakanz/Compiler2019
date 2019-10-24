//
// Created by Zinenko Dmytro on 20.10.2019.
//

#pragma once

#include "LexicalAnalyzer.h"
#include <iostream>
#include <functional>
#if ! defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

class FlexAnalyzerBuilder : public yyFlexLexer {
public:
    LexicalAnalyzer build(std::istream& input);
private:
    int yylex() override; // Генерируется Flex
    void update_pos();
    void space();
    void end_of_line();

    size_t column_ = 0;         // Положение
    size_t line_ = 0;
    LexicalAnalyzer* current_analyzer_ = nullptr;
};
