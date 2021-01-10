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
    calculations.clear();
    calculationsPath.clear();
    TSP_dp::Result r = g(0, {0});
    minPathLen = r.result;
    minPath = findPath(0, {0});
}

struct TSP_dp::Result TSP_dp::g(size_t node, std::set<size_t> passed) {
    std::pair<size_t, std::set<size_t>> keyPair{node, passed};

    if(passed.size() == graph.size()) {
        if(graph.hasPathBetween(node, 0)) {
            return TSP_dp::Result{true, graph.getPath(node, 0)};
        } else {
            return {false};
        }
    }

    if(calculations.find(keyPair) != calculations.end()) {
        return TSP_dp::Result{true, calculations[keyPair]};
    }

    size_t minPathForCurrentNode = 10000000;
    bool isVisitedAny = false;
    for (size_t nextNode : graph.connectionsOf(node)) {
        if(passed.find(nextNode) == passed.end()) {
            isVisitedAny = true;
            passed.insert(nextNode);
            currentPath.push_back(nextNode);
            TSP_dp::Result gResult = g(nextNode, passed);
            size_t result = graph.getPath(node, nextNode) + (gResult.status ? gResult.result : 10000000);
            if(minPathForCurrentNode > result) {
                minPathForCurrentNode = result;
                calculationsPath[keyPair] = nextNode;
                calculations[keyPair] = minPathForCurrentNode;
            }
            currentPath.pop_back();
            passed.erase(nextNode);
        }
    }

    if(!isVisitedAny) {
        return {false};
    }

    return {true, minPathForCurrentNode};
}

std::vector<size_t> TSP_dp::findPath(size_t a, std::set<size_t> set) {
    std::vector<size_t> vec;
    while (set.size() != graph.size()) {
        size_t nextNode = calculationsPath[std::make_pair(a, set)];
        vec.push_back(a);
        set.insert(nextNode);
        a = nextNode;
    }
    vec.push_back(a);
    vec.push_back(0);
    return vec;
}
