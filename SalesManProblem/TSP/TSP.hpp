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
#include <chrono>
#include <iomanip>

#include "GraphCreator.hpp"

class TSP {
protected:
    Graph graph;
    std::string name;
    std::set<size_t> used;
    std::vector<size_t> currentPath;
    size_t currentPathLen;
    std::vector<size_t> minPath;
    size_t minPathLen;
    std::chrono::steady_clock::time_point begin, end;

    void compareCurrentPathWithMinPath();

    TSP(std::string name);
    bool isValid(std::vector<size_t> path);
    virtual void algorithm(Graph graph) = 0;

    size_t getMinPathLen();
    std::vector<size_t> getMinPath();

    void print(std::ostream& out);
    bool isNodeVisited(size_t);

    void setGraph(Graph graph);

public:
     void start(Graph);
};

#endif /* TSP_hpp */
