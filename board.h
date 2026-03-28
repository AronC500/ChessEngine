//if board.h not defined yet, then define
#ifndef BOARD_H
#define BOARD_H
#include <vector>

//need because we need to generate all possible move and store them in vector and pick the best one.
struct Move {
    int fromRow;
    int fromCol;
    int toRow;
    int toCol;
};

//for minimax
struct MoveScore {
    int score;
    Move move;
};


class Board {
    public:
        Board();
        void print();
        void makeMove(Move m);
        void undoMove(Move m, int capturedPiece, int enPassantCaptureRow, int enPassantCaptureCol);
        int evaluate();
        MoveScore Board::minimax(int depth, bool isWhite, int alpha, int beta);
        bool isSquareAttacked(int row, int col, bool isWhite);
        bool isInCheck(bool isWhite);
        bool isDraw(bool isWhite);
        bool isGameOver(bool isWhite);
        bool hasLegalMoves(bool isWhite);
        int pieceToIndex(int piece);
        int scoreMovesForOrdering(Move move);

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
        int EnPassantRow = -1;
        int EnPassantCol = -1;
        //these one are for passing in UndoMove
        int passRow = -1;
        int passCol = -1;

        //variables for castling
        bool WhiteKingMoved = false;
        bool WhiteKingSideRookMoved = false;
        bool WhiteQueenSideRookMoved = false;
        bool BlackKingMoved = false;
        bool BlackKingSideRookMoved = false;
        bool BlackQueenSideRookMoved = false;

        //12 different pieces(6 black and 6 white) and there is 8 row and 8 columns.
        //we use unsigned(only positive) 64 bit because 32 bit (normal int is too small) and 64 bit makes it less likely for random numbers to be same and therefore to have collision
        //we use unsigned instead of sign to avoid sign complication.
        uint64_t RandomTable[12][8][8];
        uint64_t currentHash = 0;
        std::vector<uint64_t> positionHistory;

};

//end the if statement
#endif