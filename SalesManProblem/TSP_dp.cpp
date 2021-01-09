//
//  TSP_dp.cpp
//  SalesManProblem
//
//  Created by Hristo Todorov on 9.01.21.
//  Copyright © 2021 Hristo Todorov. All rights reserved.
//

#include "TSPs.hpp"
TSP_dp::TSP_dp(): TSP("TSP_dp") {}

void TSP_dp::algorithm(Graph graph) {
    currentPath.push_back(0);
    g(0);

}

size_t TSP_dp::g(size_t a) {
    std::set<size_t> connections = clearConnectionsOf(a);

    if(connections.empty() && graph.hasPathBetween(a, 0) && currentPath.size() == graph.size()) {
        currentPath.push_back(0);
        currentPathLen += graph.getPath(a, 0);
        compareCurrentPathWithMinPath();
        currentPath.pop_back();
        currentPathLen -= graph.getPath(a, 0);
        return graph.getPath(a, 0);
    }
    
//    if(calculations.find(std::make_pair(a, connections)) != calculations.end()){
//        return  calculations[std::make_pair(a, connections)];
//    }
    used.insert(a);

    size_t minPath = SIZE_T_MAX;
    for (size_t b : connections) {
            currentPath.push_back(b);
            currentPathLen += graph.getPath(a, b);
            minPath = std::min(minPath, graph.getPath(a, b) + g(b));
            currentPath.pop_back();
            currentPathLen -= graph.getPath(a, b);
    }

//    calculations[std::make_pair(a, connections)] = minPath;
    used.erase(a);

    return minPath;
}

std::set<size_t> TSP_dp::clearConnectionsOf(size_t a) {
    std::set<size_t> connections = graph.connectionsOf(a);

    for (size_t b : used) {
        if(connections.find(b) != connections.end()) {
            connections.erase(b);
        }
    }

    return connections;
}
