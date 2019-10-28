//
// Created by Zinenko Dmytro on 27.10.2019.
//
#pragma once

#include "IStatementNode.h"
#include <memory>
#include <vector>

namespace SyntaxTree {
    class StatementMergeNode : public virtual IStatementNode {
    public:
        explicit StatementMergeNode(std::vector<std::unique_ptr<IStatementNode>> parts)
                : parts_(std::move(parts)) {
        }

        [[nodiscard]] NodeType get_type() const override {
            return NodeType::STATEMENT_MERGE;
        }

        // get begin iterator
        [[nodiscard]] auto get_first_part() const {
            return parts_.cbegin();
        }

        // get end iterator
        [[nodiscard]] auto get_last_part() const {
            return parts_.cend();
        }

        ~StatementMergeNode() override = default;

    private:
        std::vector<std::unique_ptr<IStatementNode>> parts_;
    };
}
