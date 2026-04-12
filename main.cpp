#include <iostream>
#include "board.h"

int main() {
    Board board;
    while (true) {
        Move whiteMove = board.getBestMove(5, true); 
        board.makeMove(whiteMove);
        board.print();
        std::cout << std::endl;
        if (board.isGameOver(false)) {
            std::cout << "Game Over. Black Lost." << std::endl;
            break;
        }
        
        Move blackMove = board.getBestMove(1, false); 
        board.makeMove(blackMove);
        board.print();
        std::cout << std::endl;
        if (board.isGameOver(true)) {
            std::cout << "Game Over. White Lost." << std::endl;
            break;
        }
        if (board.isDraw(true) || board.isDraw(false)) {
            std::cout << "Draw." << std::endl;
           
            break;
        }
    }

    return 0;
}