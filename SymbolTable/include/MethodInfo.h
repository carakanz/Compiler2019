//
// Created by Zinenko Dmytro on 15.12.2019.
//

#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include "VarInfo.h"

namespace SymbolTree {

    class MethodInfo {
    public:
        std::string name;
        std::vector<std::string> args;
        std::string signature;
        bool is_private;
        bool is_static;
        std::string return_type_name;
        std::unordered_map<std::string, VarInfo> arg_info;
        std::unordered_map<std::string, VarInfo> var_info;
    };

}
