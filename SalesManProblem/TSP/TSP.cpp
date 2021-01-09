//
//  TSP.cpp
//  SalesManProblem
//
//  Created by Hristo Todorov on 8.01.21.
//  Copyright © 2021 Hristo Todorov. All rights reserved.
//

#include "TSP.hpp"
TSP::TSP(std::string name): minPathLen(SIZE_MAX), currentPathLen(0), name(name) {}

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
    out << std::left << std::setw(20) << std::setfill(' ') << name;
    out << std::left << std::setw(10) << std::setfill(' ') << std::chrono::duration_cast<std::chrono::milliseconds> (end - begin).count();
    out << std::left << std::setw(5) << std::setfill(' ') << minPathLen;
    std::cout << std::left << std::setw(6) << std::setfill(' ') << (isValid(minPath) ? "T" : "F");
    out << minPath;
    out << "\n";
}

bool TSP::isValid(std::vector<size_t> path) {
    for(size_t i = 0; i < path.size() - 1; i++) {
        if(!graph.hasPathBetween(path[i], path[i + 1])) {
            return false;
        }
    }

    return true;
}


bool TSP::isNodeVisited(size_t a) {
    return used.find(a) != used.end();
}

void TSP::setGraph(Graph graph) {
    this->graph = graph;
    used.clear();
    currentPath.clear();
    minPath.clear();
    currentPathLen = 0;
    minPathLen = SIZE_T_MAX;
}

void TSP::start(Graph graph) {
    setGraph(graph);
    begin = std::chrono::steady_clock::now();
    algorithm(graph);
    end = std::chrono::steady_clock::now();
    print(std::cout);
}
