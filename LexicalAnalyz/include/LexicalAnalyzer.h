//
// Created by Zinenko Dmytro on 24.10.2019.
//
#pragma once
#include "Tokens.h"
#include <string>
#include <vector>
#include <iterator>
#include <cassert>
#include <iostream>

struct LexicalAnalyz {
    Token token;
    std::string text;
    size_t column;
    size_t line;
};

class LexicalAnalyzer : public std::vector<LexicalAnalyz> {
public:
    class ErrorIterator
            : public std::iterator<std::forward_iterator_tag, LexicalAnalyz> {
    public:
        ErrorIterator(LexicalAnalyzer::iterator it, LexicalAnalyzer::iterator end)
                : it_(it), end_(end) {}

        LexicalAnalyz &operator*() { return *it_; }

        const LexicalAnalyz &operator*() const {
            return *it_;
        }

        LexicalAnalyz *operator->() { return it_.operator->(); }

        const LexicalAnalyz *operator->() const {
            return it_.operator->();
        }

        bool operator==(const ErrorIterator &it) {
            return it_ == it.it_;
        }

        bool operator!=(const ErrorIterator &it) {
            return it_ != it.it_;
        }

        ErrorIterator& operator++();
        ErrorIterator operator++(int);

    private:
        LexicalAnalyzer::iterator it_;
        LexicalAnalyzer::iterator end_;
    };

    ErrorIterator begin_error();
    ErrorIterator end_error();
};
