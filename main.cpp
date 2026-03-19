#include <iostream>
#include "board.h"

#include <iostream>
#include "board.h"

int main() {
    Board board;
    board.print();

    while (true) {
        Move whiteMove = board.getBestMove(3, true);
        if (whiteMove.fromRow == -1) {
            std::cout << "White has no valid moves, game over" << std::endl;
            break;
        }
        board.makeMove(whiteMove);
        std::cout << "White moved: " << whiteMove.fromRow << "," << whiteMove.fromCol << " -> " << whiteMove.toRow << "," << whiteMove.toCol << std::endl;
        board.print();

        Move blackMove = board.getBestMove(3, false);
        if (blackMove.fromRow == -1) {
            std::cout << "Black has no valid moves, game over" << std::endl;
            break;
        }
        board.makeMove(blackMove);
        std::cout << "Black moved: " << blackMove.fromRow << "," << blackMove.fromCol << " -> " << blackMove.toRow << "," << blackMove.toCol << std::endl;
        board.print();
    }

    return 0;
}