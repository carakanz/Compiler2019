//
// Created by Zinenko Dmytro on 27.10.2019.
//
#pragma once

#include <INodeBase.h>
#include <memory>
#include <utility>
#include <vector>

namespace SyntaxTree {
    template <class Original, NodeType type>
    class CloneNode : public Original {
    public:
        using Original::Original;

        [[nodiscard]] NodeType get_type() const override {
            return type;
        }

        ~CloneNode() override = default;
    };
}
