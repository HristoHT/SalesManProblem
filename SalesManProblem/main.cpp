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
	std::srand((int)time(0));

	GraphCreator small(5, 2);
	GraphCreator mid(10, 4);
	GraphCreator large(12, 6);

	TSP_brute tsp_brute;
	TSP_genetic tsp_genetic_small(1000, 1000), tsp_genetic_large(100000, 10000000);
	TSP_dp tsp_dp;

	std::cout << std::left << std::setw(20) << std::setfill(' ') << "Algorithm";
	std::cout << std::left << std::setw(10) << std::setfill(' ') << "Time[ms]";
	std::cout << std::left << std::setw(5) << std::setfill(' ') << "LEN";
    std::cout << std::left << std::setw(6) << std::setfill(' ') << "VALID";
	std::cout << std::left << std::setw(5) << std::setfill(' ') << "PATH\n";

	tsp_brute.start(small);
    tsp_dp.start(small);
	tsp_genetic_small.start(small);

	tsp_brute.start(mid);
    tsp_dp.start(mid);
	tsp_genetic_small.start(mid);

    tsp_genetic_large.start(large);
    tsp_brute.start(large);
    tsp_dp.start(large);

	return 0;
}
