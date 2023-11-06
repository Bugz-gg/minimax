#include <iostream>
#include <limits>
#define VALUE 3
#define MAX 1
#define MIN -1

struct Action {
    char a[VALUE][VALUE];
    struct Action * next_action;
};

struct gameboard{
    char board[VALUE][VALUE];
};

void printBoard(char s[VALUE][VALUE]) {
    for (int i = 0; i < VALUE; ++i) {
        for (int j = 0; j < VALUE; ++j) {
            std::cout << s[i][j];
            if (j < VALUE - 1) {
                std::cout << " | ";
            }
        }
        std::cout << std::endl;
        if (i < VALUE - 1) {
            std::cout << "---------" << std::endl;
        }
    }
    std::cout << std::endl;
}


bool terminal(char s[VALUE][VALUE]){
    for (int i = 0; i < VALUE; i++) {
        if ((s[i][0] == s[i][1] && s[i][1] == s[i][2]) && (s[i][0] == 'x' || s[i][0] == 'o') || 
            (s[0][i] == s[1][i] && s[1][i] == s[2][i]) && (s[0][i] == 'x' || s[0][i] == 'o')) {
            return true;
        }
    }
    if ((s[0][0] == s[1][1] && s[1][1] == s[2][2] && (s[0][0] == 'x' || s[0][0] == 'o')) ||
        (s[0][2] == s[1][1] && s[1][1] == s[2][0] && (s[0][2] == 'x' || s[0][2] == 'o'))) {
        return true;
    }
    for (int i = 0; i < VALUE; i++) {
        for (int j = 0; j < VALUE; j++) {
            if (s[i][j] != 'x' && s[i][j] != 'o'){
                return false;
            }
        }
    }
    return true;
}

int value(char s[VALUE][VALUE]){
    for (int i = 0; i < VALUE; i++) {
        if (((s[i][0] == s[i][1] && s[i][1] == s[i][2]) && s[i][0] == 'x') || 
            ((s[0][i] == s[1][i] && s[1][i] == s[2][i]) && s[0][i] == 'x')) {
            return MAX;
        }
    }
    if ((s[0][0] == s[1][1] && s[1][1] == s[2][2] && s[0][0] == 'x') ||
        (s[0][2] == s[1][1] && s[1][1] == s[2][0] && s[0][2] == 'x')) {
        return MAX;
    }
    for (int i = 0; i < VALUE; i++) {
        if ((s[i][0] == s[i][1] && s[i][1] == s[i][2]) && s[i][0] == 'o' || 
            ((s[0][i] == s[1][i] && s[1][i] == s[2][i]) && s[0][i] == 'o')) {
            return MIN;
        }
    }
    if ((s[0][0] == s[1][1] && s[1][1] == s[2][2] && s[0][0] == 'o') ||
        (s[0][2] == s[1][1] && s[1][1] == s[2][0] && s[0][2] == 'o')) {
        return MIN;
    }
    return 0;
}


char player(char s[VALUE][VALUE]){
    int p1 = 0, p2 = 0;
    for (int i = 0; i < VALUE; i++) {
        for (int j = 0; j < VALUE; j++) {
            if (s[i][j] == 'o'){
                p1++;
            }
            else if (s[i][j] == 'x'){
                p2++;
            }
        }
    }
    return (p1 <= p2)? 'o': 'x';
}

struct Action* createNewAction(char s[VALUE][VALUE]) {
    struct Action* newAction = new Action;
    std::copy(&s[0][0], &s[0][0] + VALUE * VALUE, &newAction->a[0][0]);
    newAction->next_action = nullptr;
    return newAction;
}

struct Action* action(char s[VALUE][VALUE]) {
    char p = player(s);
    struct Action* list_action = nullptr;
    struct Action *current = nullptr;
    if (p == 'o') {
        for (int i = 0; i < VALUE; i++) {
            for (int j = 0; j < VALUE; j++) {
                if (s[i][j] != 'x' && s[i][j] != 'o') {
                    char s_copy[VALUE][VALUE] = {
                        {' ', ' ', ' '},
                        {' ', ' ', ' '},
                        {' ', ' ', ' '}
                    };
                    s_copy[i][j] = 'o';
                    struct Action* newAction = createNewAction(s_copy);
                    if (list_action == nullptr) {
                        list_action = newAction;
                        current = list_action;
                    } else {
                        current->next_action = newAction;
                        current = current->next_action;
                    }
                }
            }
        }
    }
    else {
        for (int i = 0; i < VALUE; i++) {
            for (int j = 0; j < VALUE; j++) {
                if (s[i][j] != 'x' && s[i][j] != 'o') {
                    char s_copy[VALUE][VALUE] = {
                        {' ', ' ', ' '},
                        {' ', ' ', ' '},
                        {' ', ' ', ' '}
                    };  
                    s_copy[i][j] = 'x';
                    struct Action* newAction = createNewAction(s_copy);
                    if (list_action == nullptr) {
                        list_action = newAction;
                        current = list_action;
                    } else {
                        current->next_action = newAction;
                        current = current->next_action;
                    }

                }
            }
        }
    }
    return list_action;
}
struct gameboard result(char s[VALUE][VALUE], char a[VALUE][VALUE]){
    struct gameboard b;
    std::copy(&s[0][0], &s[0][0] + VALUE * VALUE, &b.board[0][0]);
    for (int i = 0; i < VALUE; i++) {
            for (int j = 0; j < VALUE; j++){
                if (a[i][j] == 'x' || a[i][j] == 'o'){
                    b.board[i][j] = a[i][j];
                }
            }
    }
    return b;
}

int max(int a, int b){
    return (a > b)? a: b;
}

int min(int a, int b){
    return (a > b)? b: a;
}

int minimax(char s[VALUE][VALUE]) {
    if (terminal(s)) {
        return value(s);
    }
    if (player(s) == 'x') {
        int value = -std::numeric_limits<int>::max();
        struct Action* list_action = action(s);
        do {
            value = max(value, minimax(result(s, list_action->a).board));
            struct Action* temp = list_action;
            list_action = list_action->next_action;
            delete temp;
        } while (list_action != nullptr);
        return value;
    } else {
        int value = std::numeric_limits<int>::max();
        struct Action* list_action = action(s);
        do {
            value = min(value, minimax(result(s, list_action->a).board));
            struct Action* temp = list_action;
            list_action = list_action->next_action;
            delete temp;
        } while (list_action != nullptr);
        return value;
    }
}


int main() {
    char initialBoard[VALUE][VALUE] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}
    };

    int result = minimax(initialBoard);
    std::cout << "Le résultat de l'algorithme Minimax est : " << result << std::endl;
    

    return 0;
}