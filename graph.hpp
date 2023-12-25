#pragma once
#include <cstdint>
#include <iostream>
#include <cstring>
#define MAX 1
#define MIN -1

using namespace std;

class Graph
{
public:
    int sizeBoard = 3;
    char Board[3][3]; // Can make Getter.
    Graph();
    Graph(const Graph &G);
    void printBoard() const;
    bool isTerminal() const;
    int value() const;
    char player();
};

