//
//  TSP_genetic.cpp
//  SalesManProblem
//
//  Created by Hristo Todorov on 8.01.21.
//  Copyright © 2021 Hristo Todorov. All rights reserved.
//

#include "TSPs.hpp"
TSP_genetic::TSP_genetic(size_t populationSize, size_t generations) : TSP("Genetic Algorithm"), populationSize(populationSize), generations(generations), distribution(std::normal_distribution<float>(.5 ,1.)) {
}

struct TSP_genetic::Individual {
	std::vector<size_t> genom;
    size_t len;
	size_t fitness;
};

void TSP_genetic::algorithm(Graph graph) {
	size_t generation = 1;
	std::vector<struct TSP_genetic::Individual> population;
    size_t count1 = 0, count2 = 0, count3 = 0, count4 = 0;
    struct TSP_genetic::Individual fitestIndividual{{}, SIZE_T_MAX, 0};

	for(size_t i = 0; i < populationSize; i++) {
		population.push_back(calculateFitness(createGenom()));

        if(fitestIndividual < population[i]) {
            fitestIndividual = population[i];
        }
	}

	size_t temperature = 10000;

	while (temperature > 1000 && generation <= generations) {
//		std::cout << "curent generation is " << generation << std::endl;
		std::sort(population.begin(), population.end(), operator<);
		std::vector<struct TSP_genetic::Individual> newPopulation;

        if(population.size() < populationSize) {
            while(population.size() != populationSize) {
                population.push_back(population[random(0, population.size())]);
            }
        }

		for (TSP_genetic::Individual individual : population) {
            std::vector<size_t> newGenom = mutateGene(individual.genom);
            struct TSP_genetic::Individual newIndividual = calculateFitness(newGenom);

            count1++;
            float probabilityToAccept = getNormalDist();
            if(newIndividual < individual || probabilityToAccept > 0.8) {
                newPopulation.push_back(newIndividual);
            }

        }

		temperature = coolDown(temperature);
		population = newPopulation;
		generation++;

        for (TSP_genetic::Individual individual: population) {
           if(individual > fitestIndividual) {
               fitestIndividual = individual;
           }
        }
	}
//    std::cout<<count1<<", "<<count2<<", "<<count3<<", "<<count4<<std::endl;

	minPath = fitestIndividual.genom;
	minPathLen = fitestIndividual.len;
}

size_t TSP_genetic::random(size_t from, size_t to) {
	size_t min = std::min(from, to);
	size_t max = std::max(from, to);
	return min + (std::rand() % (max - min));
}

std::vector<size_t> TSP_genetic::mutateGene(std::vector<size_t> pathToMutate) {
    size_t index1;
    size_t index2;

    do {
        index1 = random(1, graph.size() - 1);
        index2 = random(1, graph.size() - 1);
    } while (index1 == index2);

    pathToMutate[index1] = pathToMutate[index1] + pathToMutate[index2];
    pathToMutate[index2] = pathToMutate[index1] - pathToMutate[index2];
    pathToMutate[index1] = pathToMutate[index1] - pathToMutate[index2];

	return pathToMutate;
}

TSP_genetic::Individual TSP_genetic::calculateFitness(std::vector<size_t> genom) {
	size_t path = 0;

	for(size_t i = 0; i < genom.size() - 1; i++) {
		path += graph.getPath(genom[i], genom[i + 1]);
	}

    size_t fitness = path + (isValid(genom) ? SIZE_T_MAX : 0);
    return TSP_genetic::Individual{genom, path, fitness};
}

size_t TSP_genetic::coolDown(size_t t) {
	return (90 * t) / 100;
}

bool operator < (TSP_genetic::Individual& a, TSP_genetic::Individual& b) {
	return a.fitness < b.fitness;
}

bool operator > (TSP_genetic::Individual& a, TSP_genetic::Individual& b) {
	return !(a < b);
}

std::vector<size_t> TSP_genetic::createGenom() {
    std::vector<size_t> genom;
    used.clear();
    genom.push_back(0);
    used.insert(0);
    do {
        size_t gen = random(1, graph.size());
        if(!isNodeVisited(gen)) {
            used.insert(gen);
            genom.push_back(gen);
        }
    } while (genom.size() != graph.size());
    genom.push_back(0);

    return genom;
}

float TSP_genetic::getNormalDist() {
    float val = -1;
    do { val = distribution(generator); }
    while(val < 0.0f || val > 1.0f);

    return val;
}
