//
// Created by Zinenko Dmytro on 25.11.2019.
//

#pragma once
#include <SyntaxTreeDFSVisitor.h>
#include <SyntaxTreePrinter.h>
#include <fstream>

namespace Visitor {
    void foo() {
        std::ofstream bla;
        SyntaxTreePrinter blo(bla);
        SyntaxTreeDFSVisitor<SyntaxTreePrinter> test(blo);
    }
}