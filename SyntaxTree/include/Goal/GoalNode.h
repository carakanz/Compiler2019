//
// Created by Zinenko Dmytro on 27.10.2019.
//
#pragma once

#include <INodeBase.h>
#include <DeclarationNode/DeclarationClassNode.h>
#include <memory>
#include <utility>
#include <vector>

namespace SyntaxTree {
    using GoalNode = ListNode<DeclarationClassNode,
            INodeBase>;
}
