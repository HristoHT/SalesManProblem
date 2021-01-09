//
//  TSP.cpp
//  SalesManProblem
//
//  Created by Hristo Todorov on 8.01.21.
//  Copyright © 2021 Hristo Todorov. All rights reserved.
//

#include "TSP.hpp"
TSP::TSP(Graph graph, std::string name): graph(graph), minPathLen(SIZE_MAX), currentPathLen(0), name(name) {}

size_t TSP::getMinPathLen() {
    return minPathLen;
}

std::vector<size_t> TSP::getMinPath() {
    return minPath;
}

void TSP::compareCurrentPathWithMinPath() {
    if(currentPathLen < minPathLen) {
        minPathLen = currentPathLen;
        minPath = currentPath;
    }
}

void TSP::print(std::ostream& out) {
    out << name  << " | ";
    out << minPath;
    out << " | LENGTH=" << minPathLen << "\n";
}

bool TSP::isNodeVisited(size_t a) {
    return used.find(a) != used.end();
}
