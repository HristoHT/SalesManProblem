//
//  GraphCreator.hpp
//  SalesManProblem
//
//  Created by Hristo Todorov on 9.01.21.
//  Copyright © 2021 Hristo Todorov. All rights reserved.
//

#ifndef GraphCreator_hpp
#define GraphCreator_hpp

#include <stdio.h>
#include "Graph.hpp"

class GraphCreator: public Graph {
    size_t connections;
    std::vector<std::set<size_t>> nodesWithConnection;
    std::set<size_t> usedInCurrentLvl;

    size_t random(size_t, size_t);
    void connectAllOnLevel(size_t);
    void connectEverything();
    size_t findNextUnconnectedTo(size_t, std::set<size_t>);

    void usePathBetween(size_t a, size_t b);
    bool isUsedInCurrentLvl(size_t);
public:
    GraphCreator(size_t);
    GraphCreator(size_t, size_t);
};

#endif /* GraphCreator_hpp */
