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
        int minimax(int depth, bool isWhite);
        Move getBestMove(int depth, bool isWhite);
        bool isSquareAttacked(int row, int col, bool isWhite);
        bool isInCheck(bool isWhite);
        bool isDraw(bool isWhite);
        bool isGameOver(bool isWhite);
        bool hasLegalMoves(bool isWhite);


        std::vector<Move> getPawnMoves(int row, int col);
        std::vector<Move> getKnightMoves(int row, int col);
        std::vector<Move> getRookMoves(int row, int col);
        std::vector<Move> getBishopMoves(int row, int col);
        std::vector<Move> getQueenMoves(int row, int col);
        std::vector<Move> getKingMoves(int row, int col);
        std::vector<Move> GenerateAllMoves(int color);

    private:
        int board[8][8];
        //a full move consist of two half move and if there is 50 full move with no pawn moving or
        //and no piece being captured, game is draw.
        int halfMoveCount = 0;

};

//end the if statement
#endif