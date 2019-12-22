//
// Created by l1onsun on 21.12.19.
//

#include "IRTreeNode.h"



namespace IRTree {

    class IRTreeGoal;
    class IRTreeStatement;


    class IRTreeVisitor {
    public:
        virtual ~IRTreeVisitor() = default;
        virtual void VisitNode(const IRTreeGoal* goal) = 0;
        virtual void VisitNode(const IRTreeStatement* goal) = 0;
    };
}