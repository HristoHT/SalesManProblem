//
//  TSP.hpp
//  SalesManProblem
//
//  Created by Hristo Todorov on 7.01.21.
//  Copyright © 2021 Hristo Todorov. All rights reserved.
//

#ifndef TSPs_hpp
#define TSPs_hpp

#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <math.h>

#include "TSP.hpp"

class TSP_brute: public TSP {
    void getNextNodeFrom(size_t a);
public:
    TSP_brute(Graph);
    void algorithm();
};

class TSP_genetic: public TSP {
    size_t populationSize;

    size_t random(size_t, size_t);
    bool isValidGenom(std::vector<size_t>);
    std::vector<size_t> mutateGene(std::vector<size_t>);
    std::vector<size_t> createGenom();
    size_t calculateFitness(std::vector<size_t>);
    size_t coolDown(size_t);
public:
    struct Individual;

    TSP_genetic(Graph, size_t);
    void algorithm();
};

bool operator < (TSP_genetic::Individual&, TSP_genetic::Individual&);
bool operator > (TSP_genetic::Individual&, TSP_genetic::Individual&);


#endif /* TSPs_hpp */
