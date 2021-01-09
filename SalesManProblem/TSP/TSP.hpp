//
//  TSP.hpp
//  SalesManProblem
//
//  Created by Hristo Todorov on 8.01.21.
//  Copyright © 2021 Hristo Todorov. All rights reserved.
//

#ifndef TSP_hpp
#define TSP_hpp

#include <stdio.h>
#include <stack>
#include <string>
#include "Graph.hpp"

class TSP {
public:
    Graph graph;
    std::string name;

    std::set<size_t> used;

    std::vector<size_t> currentPath;
    size_t currentPathLen;

    std::vector<size_t> minPath;
    size_t minPathLen;

    void compareCurrentPathWithMinPath();

    TSP(Graph graph, std::string name);

    virtual void algorithm() = 0;

    size_t getMinPathLen();
    std::vector<size_t> getMinPath();

    void print(std::ostream& out);
    bool isNodeVisited(size_t);
};

#endif /* TSP_hpp */
