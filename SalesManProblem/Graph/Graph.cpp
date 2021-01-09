//
//  Graph.cpp
//  SalesManProblem
//
//  Created by Hristo Todorov on 7.01.21.
//  Copyright © 2021 Hristo Todorov. All rights reserved.
//

#include "Graph.hpp"
std::ostream& operator<< (std::ostream& out, std::vector<size_t> vec) {
    for (size_t i : vec) {
        out << i << " ";
    }
    return out;
}


Graph::Graph() {}
Graph::Graph(size_t nodes): nodes(nodes) {}

void Graph::setNodes() {
    for (size_t i = 0; i < nodes; i++) {
        graph.push_back(std::set<size_t>{});
    }
}

void Graph::setNodes(size_t nodes) {
    this->nodes = nodes;
    setNodes();
}

void Graph::_connectNode(size_t a, size_t b, size_t path = 0) {
    if(!hasPathBetween(a, b)) {
        graph[a].insert(b);
        paths.insert(std::pair<std::pair<size_t, size_t>, size_t>(std::pair<size_t, size_t>(a, b), path));
    } else {
        std::map<std::pair<size_t, size_t>, size_t>::iterator currentPathIt = paths.find(std::pair<size_t, size_t>(a, b));
        size_t currentPathLength = (*currentPathIt).second;

        if (currentPathLength > path) {
            (*currentPathIt).second = path;
        }
    }
}

bool Graph::hasPathBetween(size_t a, size_t b) {
    return graph[a].find(b) != graph[a].end();
}

bool Graph::hasUsedPathBetween(size_t a, size_t b) {
    return used.find(std::pair<size_t, size_t>(a, b)) != used.end();
}

size_t Graph::_usePathBetween(size_t a, size_t b) {
    if(!hasUsedPathBetween(a, b)) {
        used.insert(std::pair<size_t, size_t>(a, b));

        return  getPath(a, b);
    }

    return 0;
}

size_t Graph::_unUsePathBetween(size_t a, size_t b) {
    if(hasPathBetween(a, b) && hasUsedPathBetween(a, b)) {
        used.erase(std::pair<size_t, size_t>(a, b));
        
        return  getPath(a, b);
    }

    return 0;
}

size_t Graph::getPath(size_t a, size_t b) {
    std::map<std::pair<size_t, size_t>, size_t>::iterator it = paths.find(std::pair<size_t, size_t>(a, b));

    if(it == paths.end()) {
        return SIZE_T_MAX;
    } else {
        return (*it).second;
    }
}

void Graph::print(std::ostream& out) {
    for(size_t i = 0; i < graph.size(); i++){
        for (size_t node : graph[i]) {
            out << i << "->" << node << "[" << getPath(i, node) << "]\n";
        }
    }
}

void Graph::connectNode(size_t a, size_t b, size_t path) {
    _connectNode(a, b, path);
    _connectNode(b, a, path);
}

size_t Graph::usePathBetween(size_t a, size_t b) {
    _usePathBetween(a, b);
    return _usePathBetween(b, a);
}

size_t Graph::unUsePathBetween(size_t a, size_t b){
    _unUsePathBetween(a, b);
    return _unUsePathBetween(b, a);
}

std::istream& operator>> (std::istream& in, Graph& graph){
    size_t nodes, paths;
    in >> nodes >> paths;
    graph.setNodes(nodes);
    
    for (size_t i = 0; i < paths; i++) {
        size_t a, b, path;
        in >> a >> b >> path;

        graph.connectNode(a, b, path);
    }

    return in;
}

size_t Graph::size() {
    return nodes;
}

std::set<size_t> Graph::connectionsOf(size_t a) {
    return graph[a];
}
