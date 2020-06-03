//
// Created by l1onsun on 23.12.19.
//

#pragma once

#include <unordered_map>
#include <string>
#include <Wrapper/IWrapper.h>


namespace SyntaxTreeVisitor {

    class IRTreeGoal {
    public:
        std::unordered_map<std::string,
            std::unordered_map<std::string,
                std::unique_ptr<IRTree::IStatementNode> > > wrappers;

        std::unordered_map<std::string,
                std::unordered_map<std::string,
                        std::vector<std::unique_ptr<IRTree::IStatementNode> > > > linear_wrappers;

        void add_class(const std::string& class_name) {
            wrappers[class_name] = std::unordered_map<std::string, std::unique_ptr<IRTree::IStatementNode> >();
        }

        void add_method(const std::string& class_name,
                const std::string& method_name,
                std::unique_ptr<IRTree::IStatementNode>&& wrapper ) {
           wrappers[class_name].emplace(method_name, std::move(wrapper));
        }

        void reset_linear_wrappers() {
            for (auto &class_info : wrappers) {
                linear_wrappers[class_info.first] = std::unordered_map<std::string,
                        std::vector<std::unique_ptr<IRTree::IStatementNode> > >();
            }
        }
    };
}
