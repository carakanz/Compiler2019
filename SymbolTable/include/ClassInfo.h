//
// Created by Zinenko Dmytro on 15.12.2019.
//

#pragma once

#include <unordered_map>
#include <string>
#include <vector>
#include "MethodInfo.h"
#include "VarInfo.h"

namespace SymbolTree {

    class ClassInfo {
    public:
        std::string name;
        std::string base;
        std::unordered_map<std::string, MethodInfo> method_info;
        std::unordered_map<std::string, VarInfo> var_info;
    };

}
