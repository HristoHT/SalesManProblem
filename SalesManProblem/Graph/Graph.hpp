//
//  Graph.hpp
//  SalesManProblem
//
//  Created by Hristo Todorov on 7.01.21.
//  Copyright © 2021 Hristo Todorov. All rights reserved.
//

#ifndef Graph_hpp
#define Graph_hpp

#include <stdio.h>
#include <vector>
#include <iostream>
#include <set>
#include <map>

std::ostream& operator<< (std::ostream&, std::vector<size_t>);

class Graph {
    size_t nodes;
    std::vector<std::set<size_t>> graph;
    std::set<std::pair<size_t, size_t>> used;
    std::map<std::pair<size_t, size_t>, size_t> paths;

    void setNodes();
    void _connectNode(size_t a, size_t b, size_t path);
   size_t _usePathBetween(size_t a, size_t b);
   size_t _unUsePathBetween(size_t a, size_t b);
public:
    Graph();
    Graph(size_t nodes);
    void setNodes(size_t nodes);

    void connectNode(size_t a, size_t b, size_t path);

    bool hasPathBetween(size_t a, size_t b);
    bool hasUsedPathBetween(size_t a, size_t b);
    
    size_t usePathBetween(size_t a, size_t b);
    size_t unUsePathBetween(size_t a, size_t b);
    size_t getPath(size_t a, size_t b);

    std::set<size_t> connectionsOf(size_t a);

    void print(std::ostream& out);

    size_t size();
};

std::istream& operator>> (std::istream& in, Graph& graph);

#endif /* Graph_hpp */
