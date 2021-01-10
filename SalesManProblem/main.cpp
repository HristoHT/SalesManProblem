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
    
	GraphCreator small(5);
	GraphCreator mid(10);
	GraphCreator large(15);
    GraphCreator complex(15, 8);

	TSP_brute tsp_brute;
	TSP_genetic tsp_genetic(10000, 100);
	TSP_dp tsp_dp;

	std::cout << std::left << std::setw(20) << std::setfill(' ') << "Algorithm";
	std::cout << std::left << std::setw(10) << std::setfill(' ') << "Time[ms]";
	std::cout << std::left << std::setw(5) << std::setfill(' ') << "LEN";
    std::cout << std::left << std::setw(6) << std::setfill(' ') << "VALID";
	std::cout << std::left << std::setw(5) << std::setfill(' ') << "PATH\n";

	tsp_brute.start(small);
    tsp_dp.start(small);
	tsp_genetic.start(small);

	tsp_brute.start(mid);
    tsp_dp.start(mid);
	tsp_genetic.start(mid);

    tsp_dp.start(large);
    tsp_genetic.start(large);

    tsp_dp.start(complex);
    tsp_genetic.start(complex);

	return 0;
}
