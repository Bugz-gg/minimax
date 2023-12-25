#pragma once
#include "graph.hpp"
#include <vector>

class Actions : public Graph
{
public:
    int count;
    int final;
    std::vector<Graph> Acts;

    Actions();
    ~Actions();

    void add(Graph &G, char c, int i, int j);
    std::vector<Graph> listActions(Graph &G, char c);
};

