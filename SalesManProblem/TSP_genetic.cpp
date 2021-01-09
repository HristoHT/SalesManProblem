//
//  TSP_genetic.cpp
//  SalesManProblem
//
//  Created by Hristo Todorov on 8.01.21.
//  Copyright © 2021 Hristo Todorov. All rights reserved.
//

#include "TSPs.hpp"
TSP_genetic::TSP_genetic(Graph graph, size_t populationSize) : TSP(graph, "Genetic Algorithm"), populationSize(populationSize) {
}

struct TSP_genetic::Individual {
	std::vector<size_t> genom;
	size_t fitness;
};

void TSP_genetic::algorithm() {
	size_t generation = 1;
	size_t numberOfGeneIterations = 15;
	std::vector<struct TSP_genetic::Individual> population;

	for(size_t i = 0; i < populationSize; i++) {
        std::vector<size_t> newGenom = createGenom();
		population.push_back(TSP_genetic::Individual{newGenom, calculateFitness(newGenom)});
		used.clear();
	}

	size_t temperature = 10000;
    struct TSP_genetic::Individual fitestIndividual{{}, SIZE_T_MAX};
    bool isFromValidGenom = false;

	while (temperature > 1000 && generation <= numberOfGeneIterations) {
//		std::cout << "curent generation is " << generation << std::endl;
		std::sort(population.begin(), population.end(), operator<);
		std::vector<struct TSP_genetic::Individual> newPopulation;

		for (TSP_genetic::Individual individual : population) {
			while (true) {
				std::vector<size_t> newGenom = mutateGene(individual.genom);
				struct TSP_genetic::Individual newIndividual {newGenom, calculateFitness(newGenom)};


                if(newIndividual < individual || isValidGenom(newIndividual.genom)) {
					newPopulation.push_back(newIndividual);
					break;
				} else {
					float probabilityToAccept = pow(2.7, -1 * ((float)(newIndividual.fitness
					                                                   - individual.fitness)
					                                           / temperature));
					if (probabilityToAccept > 0.5) {
						newPopulation.push_back(newIndividual);
						break;
					}
				}

			}
		}
		temperature = coolDown(temperature);
		population = newPopulation;
		generation++;

        for (TSP_genetic::Individual individual: population) {
           if(isValidGenom(individual.genom)) {
               if(isFromValidGenom) {
                   if(individual < fitestIndividual) {
                       fitestIndividual = individual;
                   }
               } else {
                   fitestIndividual = individual;
                   isFromValidGenom = true;
               }
           } else if(!isFromValidGenom){
               if(individual < fitestIndividual) {
                   fitestIndividual = individual;
               }
           }
        }
	}

	minPath = fitestIndividual.genom;
	minPathLen = fitestIndividual.fitness;
	print(std::cout);
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

size_t TSP_genetic::calculateFitness(std::vector<size_t> genom) {
	size_t path = 0;

	for(size_t i = 0; i < genom.size() - 1; i++) {
		path += graph.getPath(genom[i], genom[i + 1]);
	}

	return path;
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

bool TSP_genetic::isValidGenom(std::vector<size_t> genome) {
    for(size_t i = 0; i < genome.size() - 1; i++) {
        if(!graph.hasPathBetween(genome[i], genome[i + 1])) {
            return false;
        }
    }

    return true;
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