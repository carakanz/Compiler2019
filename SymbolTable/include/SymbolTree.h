//
// Created by Zinenko Dmytro on 15.12.2019.
//

#pragma once

#include <unordered_map>
#include <string>
#include <limits>
#include "ClassInfo.h"

namespace SymbolTree {

    class SymbolTree {
    public:
        std::unordered_map<std::string, ClassInfo> classes_info;

        enum AssignedType {
            Equal = 0x0,
            Extension = 0x1,
            Contraction = 0x2,
            Inheritance = 0x4,
            NotAssigned = std::numeric_limits<int>::max()
        };

        AssignedType can_assigned(std::string src, std::string dst) const;
        static std::string is_array(const std::string& type_name);
    };

}
