#include "graph.hpp"

void Graph::printBoard() const{
    cout << "  0   1   2" <<endl;
    for(int i=0; i < sizeBoard; i++){
        cout << i << " ";
        for (int j=0; j < sizeBoard; j++){
            cout << Board[i][j];
            if (j < sizeBoard - 1) {
               cout << " | ";
            }
        }
       cout <<endl;
        if (i < sizeBoard - 1) {
           cout << " -----------" <<endl;
        }
        }
       cout <<endl;
}
bool Graph::isTerminal() const {
    for (int i = 0; i < sizeBoard; i++) {
        if ((Board[i][0] == Board[i][1] && Board[i][1] == Board[i][2]) && (Board[i][0] == 'x' || Board[i][0] == 'o') ||
            (Board[0][i] == Board[1][i] && Board[1][i] == Board[2][i]) && (Board[0][i] == 'x' || Board[0][i] == 'o')) {
            return true;
        }
    }
    if ((Board[0][0] == Board[1][1] && Board[1][1] == Board[2][2] && (Board[0][0] == 'x' || Board[0][0] == 'o')) ||
        (Board[0][2] == Board[1][1] && Board[1][1] == Board[2][0] && (Board[0][2] == 'x' || Board[0][2] == 'o'))) {
        return true;
    }
    for (int i = 0; i < sizeBoard; i++) {
        for (int j = 0; j < sizeBoard; j++) {
            if (Board[i][j] != 'x' && Board[i][j] != 'o') {
                return false;
            }
        }
    }
    return true;
}


int Graph::value() const{
    for (int i = 0; i < sizeBoard; i++) {
        if (((Board[i][0] == Board[i][1] && Board[i][1] == Board[i][2]) && Board[i][0] == 'x') || 
            ((Board[0][i] == Board[1][i] && Board[1][i] == Board[2][i]) && Board[0][i] == 'x')) {
            return MAX;
        }
    }
    if ((Board[0][0] == Board[1][1] && Board[1][1] == Board[2][2] && Board[0][0] == 'x') ||
        (Board[0][2] == Board[1][1] && Board[1][1] == Board[2][0] && Board[0][2] == 'x')) {
        return MAX;
    }
    for (int i = 0; i < sizeBoard; i++) {
        if ((Board[i][0] == Board[i][1] && Board[i][1] == Board[i][2]) && Board[i][0] == 'o' || 
            ((Board[0][i] == Board[1][i] && Board[1][i] == Board[2][i]) && Board[0][i] == 'o')) {
            return MIN;
        }
    }
    if ((Board[0][0] == Board[1][1] && Board[1][1] == Board[2][2] && Board[0][0] == 'o') ||
        (Board[0][2] == Board[1][1] && Board[1][1] == Board[2][0] && Board[0][2] == 'o')) {
        return MIN;
    }
    return 0;
}

Graph::Graph()
{
    for (int i = 0; i < sizeBoard; i++)
    {
        for (int j = 0; j < sizeBoard; j++)
        {
            Board[i][j] = ' ';
        }
    }
}

Graph::Graph(const Graph &G) {
    for (size_t i = 0; i < sizeBoard; i++) {
        memcpy(Board[i], G.Board[i], sizeBoard);
    }
}

char Graph::player() {
    int nb_x = 0, nb_o = 0;
    for (int i = 0; i < sizeBoard; i++) {
        for (int j = 0; j < sizeBoard; j++) {
            if (Board[i][j] == 'x') nb_x++;
            else if (Board[i][j] == 'o') nb_o++;
        }
    }
    return (nb_x > nb_o) ? 'o' : 'x';
}
