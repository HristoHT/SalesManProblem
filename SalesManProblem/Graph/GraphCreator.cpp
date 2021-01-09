//
//  GraphCreator.cpp
//  SalesManProblem
//
//  Created by Hristo Todorov on 9.01.21.
//  Copyright © 2021 Hristo Todorov. All rights reserved.
//

#include "GraphCreator.hpp"
GraphCreator::GraphCreator(size_t nodes, size_t connections) {
    this->nodes = nodes < 3 ? 3 : nodes;
    this->connections = connections * 2 > this->nodes ? this->nodes - 1 : connections * 2;

    setNodes();

    for(size_t i = 0; i <= this->connections; i++) {
        nodesWithConnection.push_back(std::set<size_t>{});
    }

    for(size_t i = 0; i < this->nodes; i++){
        nodesWithConnection[0].insert(i);
    }

    connectAllOnLevel(0);
}

size_t GraphCreator::random(size_t from, size_t to) {
    size_t min = std::min(from, to);
    size_t max = std::max(from, to);
    return min + (std::rand() % (max - min));
}

void GraphCreator::connectAllOnLevel(size_t lvl) {
    usedInCurrentLvl.clear();
    if(lvl == this->connections) {
        return;
    }

    std::vector<size_t> toErase;
    std::vector<size_t> toEraseFromNextLvl;
    while (!nodesWithConnection[lvl].empty()) {
        size_t firstNode = *nodesWithConnection[lvl].begin();
        if(!isUsedInCurrentLvl(firstNode) && nodesWithConnection[lvl].size() > 1) {
            size_t secondNode = findNextUnconnectedTo(firstNode, nodesWithConnection[lvl]);
//            std::cout << firstNode << "->" << secondNode << std::endl;

            connectNode(firstNode, secondNode, random(1, 10));
            usePathBetween(firstNode, secondNode);

            nodesWithConnection[lvl].erase(secondNode);
            nodesWithConnection[lvl + 1].insert(secondNode);
        } else if (nodesWithConnection[lvl].size() == 1) {
            size_t secondNode = findNextUnconnectedTo(firstNode, nodesWithConnection[lvl + 1]);
//            std::cout << firstNode << "->" << secondNode << std::endl;

            connectNode(firstNode, secondNode, random(1, 10));
            usePathBetween(firstNode, secondNode);

            nodesWithConnection[lvl + 1].erase(secondNode);
            nodesWithConnection[lvl + 2].insert(secondNode);
        }

        nodesWithConnection[lvl].erase(firstNode);
        nodesWithConnection[lvl + 1].insert(firstNode);
    }

    connectAllOnLevel(lvl + 1);
}

size_t GraphCreator::findNextUnconnectedTo(size_t node, std::set<size_t> posibilitiesForConnection) {
    for (size_t otherNode : posibilitiesForConnection) {
        if (!hasUsedPathBetween(node, otherNode) && node != otherNode) {
            return otherNode;
        }
    }

    for (size_t otherNode : posibilitiesForConnection) {
           if (node != otherNode) {
               return otherNode;
           }
    }
    
    return *posibilitiesForConnection.begin();
}

bool GraphCreator::isUsedInCurrentLvl(size_t a) {
    return usedInCurrentLvl.find(a) != usedInCurrentLvl.end();
}

void GraphCreator::usePathBetween(size_t a, size_t b) {
    usedInCurrentLvl.insert(a);
    usedInCurrentLvl.insert(b);
    _usePathBetween(a, b);
    _usePathBetween(b, a);
}
