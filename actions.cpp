#include "actions.hpp"


void Actions::add(Graph &G, char c, int i, int j)
{
    G.Board[i][j] = c;
}

std::vector<Graph> Actions::listActions(Graph &G, char c)
{
    for (size_t i = 0; i < G.sizeBoard; i++)
    {
        for (size_t j = 0; j < G.sizeBoard; j++)
        {
            if (G.Board[i][j] == ' ')
            {
                Graph newGraph = G;
                add(newGraph, c, i, j);
                Acts.push_back(newGraph);
            }
        }
    }
    final = static_cast<int>(Acts.size());
    count = 0;
    return Acts;
}

Actions::Actions() : count(0), final(0) {}

Actions::~Actions() {}
