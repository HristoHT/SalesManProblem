//
//  TSP_brute.cpp
//  SalesManProblem
//
//  Created by Hristo Todorov on 7.01.21.
//  Copyright © 2021 Hristo Todorov. All rights reserved.
//

#include <stdio.h>
#include "TSPs.hpp"
TSP_brute::TSP_brute(Graph graph): TSP(graph, "Brute Force") {}

void TSP_brute::algorithm() {
    currentPath.push_back(0);

    getNextNodeFrom(0);

    print(std::cout);
}

void TSP_brute::getNextNodeFrom(size_t a) {
    if(currentPath.size() == graph.size()) {
        if(graph.hasPathBetween(a, 0)) {
            currentPathLen += graph.getPath(a, 0);
            currentPath.push_back(0);
            compareCurrentPathWithMinPath();
            currentPath.pop_back();
            currentPathLen -= graph.getPath(a, 0);
        } else {
            return;
        }
    }

    used.insert(a);

    for (size_t node : graph.connectionsOf(a)) {
        if(!isNodeVisited(node)) {
            currentPath.push_back(node);
            currentPathLen += graph.getPath(a, node);
            getNextNodeFrom(node);
            currentPath.pop_back();
            currentPathLen -= graph.getPath(a, node);
        }
    }

    used.erase(a);
}
