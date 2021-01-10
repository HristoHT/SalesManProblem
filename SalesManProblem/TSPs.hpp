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
#include <ctime>
#include <random>
#include <queue>
#include "TSP.hpp"

class TSP_brute: public TSP {
    void getNextNodeFrom(size_t a);
    void algorithm(Graph);
public:
    TSP_brute();
};

class TSP_genetic: public TSP {
public:
    struct Individual;

private:
    size_t populationSize;
    size_t generations;
    std::default_random_engine generator;
    std::normal_distribution<float> distribution;
    size_t random(size_t, size_t);
    std::vector<size_t> mutateGene(std::vector<size_t>);
    std::vector<size_t> createGenom();
    Individual calculateFitness(std::vector<size_t>);
    size_t coolDown(size_t);
    inline float getNormalDist();

    void algorithm(Graph);
public:
    TSP_genetic(size_t, size_t);
};

bool operator < (TSP_genetic::Individual&, TSP_genetic::Individual&);
bool operator > (TSP_genetic::Individual&, TSP_genetic::Individual&);

class TSP_dp: public TSP {
    struct Result {
        bool status;
        size_t result;
    };

    std::map<std::pair<size_t, std::set<size_t>>, size_t> calculations, calculationsPath;
    std::vector<size_t> findPath(size_t, std::set<size_t>);
    void algorithm(Graph);
    Result g(size_t, std::set<size_t>);
public:
    TSP_dp();
};

#endif /* TSPs_hpp */
