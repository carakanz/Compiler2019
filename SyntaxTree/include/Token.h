//
// Created by Zinenko Dmytro on 19.11.2019.
//

#pragma once

#include "Position.h"

namespace SyntaxTree {
    template<class Info = void>
    class Token;

    template<>
    class Token<void> {
    public:
        Token() = default;
        explicit Token(Position position) : position(position) {
        }

        Position position;
    };

    template<class Info>
    class Token : public Token<void> {
    public:
        Token() : Token<void>() {
        }
        Token(Position position, Info info)
                : Token<void>(position), info(info) {
        }

        Info info;
    };
}