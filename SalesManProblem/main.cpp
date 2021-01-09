//
//  main.cpp
//  SalesManProblem
//
//  Created by Hristo Todorov on 7.01.21.
//  Copyright © 2021 Hristo Todorov. All rights reserved.
//

#include <iostream>
#include "TSPs.hpp"

int main(int argc, const char * argv[]) {
    Graph graph;
    std::cin >> graph;

    TSP_brute tsp_brute(graph);
    tsp_brute.algorithm();

    TSP_genetic tsp_genetic(graph, 15);
    tsp_genetic.algorithm();

    return 0;
}
