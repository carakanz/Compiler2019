//
// Created by carak on 03.06.2020.
//

#pragma once

#include <vector>
#include <StatementNode/IStatementNode.h>
#include <unordered_map>

namespace IRTree {
    using Block = std::vector<std::unique_ptr<IRTree::IStatementNode>>;
    using MethodInBlock = std::vector<Block>;
    using ClassInBlock = std::unordered_map<std::string, MethodInBlock>;
    using ProgramInBlock = std::unordered_map<std::string, ClassInBlock>;

    using Line = std::unique_ptr<IRTree::IStatementNode>;
    using MethodInLine = std::vector<Line>;
    using ClassInLine = std::unordered_map<std::string, MethodInLine>;
    using ProgramInLine = std::unordered_map<std::string, ClassInLine>;
}