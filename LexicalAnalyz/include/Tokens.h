//
// Created by Zinenko Dmytro on 20.10.2019.
//
#pragma once

namespace LexicalAnalyz {

enum Token {
    T_EOF = 0,// По-умолчанию в конце потока scanner
    // возвращает 0.
    // Это можно изменить в #define YY_NULL
            T_SPACE,
    T_CLASS,
    T_THIS,
    T_LEFT_BRACKET,
    T_RIGHT_BRACKET,
    T_LEFT_BRACE,
    T_RIGHT_BRACE,
    T_LEFT_SQUARE_BRACKET,
    T_RIGHT_SQUARE_BRACKET,
    T_PUBLIC_MODIFIER,
    T_PRIVATE_MODIFIER,
    T_STATIC_MODIFIER,
    T_RETURN,
    T_STANDARD_TYPE,
    T_NEW,
    T_WHILE,
    T_IF,
    T_ELSE,
    T_PRINT_LN,
    T_BOOL_VALUE,
    T_INT_VALUE,
    T_REAL_VALUE,
    T_STRING_VALUE,
    T_CHAR_VALUE,
    T_METHOD,
    T_IDENTIFIER,
    T_SEMICOLON,
    T_COMMA,
    T_ASSIGN_OPERATION,
    T_BOOL_OPERATION,
    T_NOT_OPERATION,
    T_ARITHMETIC_OPERATION,
    T_COMPARE_OPERATION,
    T_COMMENT,

    T_UNKNOWN
};

}

