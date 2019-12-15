//
// Created by carak on 15.12.2019.
//

#pragma once

#include <unordered_map>
#include <string>
#include "ClassInfo.h"

namespace SymbolTree {

    class SymbolTree {
    public:
        std::unordered_map<std::string, ClassInfo> classes_info;
    };

}
