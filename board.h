//if board.h not defined yet, then define
#ifndef BOARD_H
#define BOARD_H
#include <vector>

//need because we need to generate all possible move and store them in vector and pick the best one.
struct Move {
    int fromRow, fromCol;
    int toRow, toCol;
};

class Board {
    public:
        Board();
        void print();
        void makeMove(Move m);
        void undoMove(Move m, int capturedPiece);
        int evaluate();

        std::vector<Move> getPawnMoves(int row, int col);
        std::vector<Move> getKnightMoves(int row, int col);
        std::vector<Move> getRookMoves(int row, int col);
        std::vector<Move> getBishopMoves(int row, int col);
        std::vector<Move> getQueenMoves(int row, int col);
        std::vector<Move> getKingMoves(int row, int col);
        std::vector<Move> GenerateAllMoves(int color);

    private:
        int board[8][8];

};

//end the if statement
#endif