//
// Created by Zinenko Dmytro on 24.10.2019.
//

#include "LexicalAnalyzer.h"
#include <algorithm>

namespace LexicalAnalyz {

    LexicalAnalyzer::ErrorIterator LexicalAnalyzer::begin_error() {
        return {std::find_if(begin(), end(),
                             [](const LexicalAnalyz &item) {
                                 return item.token == Token::T_UNKNOWN;
                             }),
                end()};
    }

    LexicalAnalyzer::ErrorIterator LexicalAnalyzer::end_error() {
        return {end(), end()};
    }

    LexicalAnalyzer::ErrorIterator &LexicalAnalyzer::ErrorIterator::operator++() {
        assert(it_ < end_);
        it_ = std::find_if(++it_, end_,
                           [](const LexicalAnalyz &item) {
                               return item.token == Token::T_UNKNOWN;
                           });
        return (*this);
    }

    LexicalAnalyzer::ErrorIterator LexicalAnalyzer::ErrorIterator::operator++(int) {
        auto temp(*this);
        this->operator++();
        return temp;
    }

}
