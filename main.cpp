#include "actions.hpp"
#include <limits>

inline int max2(int a, int b)
{
    return (a > b) ? a : b;
}

inline int min2(int a, int b)
{
    return (a > b) ? b : a;
}

int minimax(Graph &b)
{
    if (b.isTerminal())
    {
        return b.value();
    }
    if (b.player() == 'x')
    {
        int value = -std::numeric_limits<int>::max();
        Actions possibleActions;
        std::vector<Graph> acts = possibleActions.listActions(b, 'x');
        for (size_t k = 0; k < acts.size(); k++)
        {
            value = max2(value, minimax(acts[k]));
        }
        return value;
    }
    else
    {
        int value = std::numeric_limits<int>::max();
        Actions possibleActions;
        std::vector<Graph> acts = possibleActions.listActions(b, 'o');
        for (size_t k = 0; k < acts.size(); k++)
        {
            value = min2(value, minimax(acts[k]));
        }
        return value;
    }
}

int main()
{
    Graph b;
    int gameMode;

    std::cout << "Select Game Mode:" << std::endl;
    std::cout << "1. Man vs Bot" << std::endl;
    std::cout << "2. Man vs Man" << std::endl;
    std::cout << "Enter the mode number (1 or 2): ";
    std::cin >> gameMode;
    b.printBoard();

    int startingPlayer;
    std::cout << "Choose Starting Player:" << std::endl;
    std::cout << "1. Player 'x'" << std::endl;
    std::cout << "2. Player 'o'" << std::endl;
    std::cout << "Enter the starting player number (1 or 2): ";
    std::cin >> startingPlayer;

    if (startingPlayer != 1 && startingPlayer != 2)
    {
        std::cout << "Invalid starting player selection. Exiting..." << std::endl;
        return 1;
    }
    while (!b.isTerminal())
    {
        if (gameMode)
        {
            if (startingPlayer == 1)
            {
                int row, col;
                std::cout << "Enter your move (row and column, space-separated): ";
                std::cin >> row >> col;

                if (b.Board[row][col] != ' ')
                {
                    std::cout << "Invalid move. Try again." << std::endl;
                    continue;
                }

                b.Board[row][col] = 'x';
                b.printBoard();

                if (b.isTerminal())
                    break;

                std::cout << "Bot is making a move..." << std::endl;

                int bestValue = std::numeric_limits<int>::max();
                int bestMoveIndex = -1;

                Actions possibleActions;
                std::vector<Graph> acts = possibleActions.listActions(b, 'o');

                for (size_t k = 0; k < acts.size(); k++)
                {
                    int moveValue = minimax(acts[k]);
                    if (moveValue < bestValue)
                    {
                        bestValue = moveValue;
                        bestMoveIndex = k;
                    }
                }

                if (bestMoveIndex != -1)
                {
                    b = acts[bestMoveIndex];
                    b.printBoard();
                }
            }
            else
            {
                if (b.player() == 'x')
                {
                    std::cout << "Bot 'x' is making a move..." << std::endl;

                    int bestValue = -std::numeric_limits<int>::max();
                    int bestMoveIndex = -1;

                    Actions possibleActions;
                    std::vector<Graph> acts = possibleActions.listActions(b, 'x');

                    for (size_t k = 0; k < acts.size(); k++)
                    {
                        int moveValue = minimax(acts[k]);
                        if (moveValue > bestValue)
                        {
                            bestValue = moveValue;
                            bestMoveIndex = k;
                        }
                    }

                    if (bestMoveIndex != -1)
                    {
                        b = acts[bestMoveIndex];
                        b.printBoard();
                    }

                    if (b.isTerminal())
                        break;
                }

                int row, col;
                std::cout << "Your move ('o'), enter the row and column (space-separated): ";
                std::cin >> row >> col;

                if (b.Board[row][col] != ' ')
                {
                    std::cout << "Invalid move. Try again." << std::endl;
                    continue;
                }

                b.Board[row][col] = 'o';
                b.printBoard();
            }
        }
        else if (gameMode == 2)
        {
            int row, col;
            std::cout << "Player 'x', enter your move (row and column, space-separated): ";
            std::cin >> row >> col;

            if (b.Board[row][col] != ' ')
            {
                std::cout << "Invalid move. Try again." << std::endl;
                continue;
            }

            b.Board[row][col] = 'x';
            b.printBoard();
        }
    }
    switch (b.value())
    {
    case 0:
        printf("The result is a draw\n");
        break;
    case MAX:
        printf("x won\n");
        break;
    case MIN:
        printf("o won\n");
        break;
    default:
        break;
    }
    return 0;
}
