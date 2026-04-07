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


struct TranspositionEntry {
    //return stored score instead of searching again.
    int score;
    //need to know if stored depth is >= current needed depth because if stored depth is less than current needed depth, stored result can be inaccurate.
    int depth;
    //need store move as minimax returns it.
    Move bestMove;
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
        Move Board::getBestMove(int maxDepth, bool isWhite);

        std::vector<Move> getPawnMoves(int row, int col);
        std::vector<Move> getKnightMoves(int row, int col);
        std::vector<Move> getRookMoves(int row, int col);
        std::vector<Move> getBishopMoves(int row, int col);
        std::vector<Move> getQueenMoves(int row, int col);
        std::vector<Move> getKingMoves(int row, int col);
        std::vector<Move> GenerateAllMoves(int color);

    private:
        //for iterative deepening
        Move previousBestMove;
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


        //standard piece tables (more score if in these spots added/subtracted in evaluate depending on color). currently this is for white.
        //for black, it's flipped vertically.
        int pawnTable[8][8] =  {
            {0,  0,  0,  0,  0,  0,  0,  0},
            {50, 50, 50, 50, 50, 50, 50, 50},
            {10, 10, 20, 30, 30, 20, 10, 10},
            {5,  5, 10, 25, 25, 10,  5,  5},
            {0,  0,  0, 20, 20,  0,  0,  0},
            {5, -5, -10,  0,  0,-10, -5,  5},
            {5, 10, 10,-20,-20, 10, 10,  5},
            {0,  0,  0,  0,  0,  0,  0,  0}
        };
        int knightTable[8][8] = {
            {-50,-40,-30,-30,-30,-30,-40,-50},
            {-40,-20,  0,  0,  0,  0,-20,-40},
            {-30,  0, 10, 15, 15, 10,  0,-30},
            {-30,  5, 15, 20, 20, 15,  5,-30},
            {-30,  0, 15, 20, 20, 15,  0,-30},
            {-30,  5, 10, 15, 15, 10,  5,-30},
            {-40,-20,  0,  5,  5,  0,-20,-40},
            {-50,-40,-30,-30,-30,-30,-40,-50}
        };
        int bishopTable[8][8] = {
            {-20,-10,-10,-10,-10,-10,-10,-20},
            {-10,  0,  0,  0,  0,  0,  0,-10},
            {-10,  0,  5, 10, 10,  5,  0,-10},
            {-10,  5,  5, 10, 10,  5,  5,-10},
            {-10,  0, 10, 10, 10, 10,  0,-10},
            {-10, 10, 10, 10, 10, 10, 10,-10},
            {-10,  5,  0,  0,  0,  0,  5,-10},
            {-20,-10,-10,-10,-10,-10,-10,-20}
        };
        int rookTable[8][8] = {
            {0,  0,  0,  0,  0,  0,  0,  0},
            {5,  10, 10, 10, 10, 10, 10,  5},
            {-5,  0,  0,  0,  0,  0,  0, -5},
            {-5,  0,  0,  0,  0,  0,  0, -5},
            {-5,  0,  0,  0,  0,  0,  0, -5},
            {-5,  0,  0,  0,  0,  0,  0, -5},
            {-5,  0,  0,  0,  0,  0,  0, -5},
            {0,  0,  0,  5,  5,  0,  0,  0}
        };
        int queenTable[8][8] = {
            {-20,-10,-10, -5, -5,-10,-10,-20},
            {-10,  0,  0,  0,  0,  0,  0,-10},
            {-10,  0,  5,  5,  5,  5,  0,-10},
            {-5,  0,  5,  5,  5,  5,  0, -5},
            {0,  0,  5,  5,  5,  5,  0,  -5},
            {-10,  5,  5,  5,  5,  5,  0,-10},
            {-10,  0,  5,  0,  0,  0,  0,-10},
            {-20,-10,-10, -5, -5,-10,-10,-20}
        };
        int kingTable[8][8] = {
            {-30,-40,-40,-50,-50,-40,-40,-30},
            {-30,-40,-40,-50,-50,-40,-40,-30},
            {-30,-40,-40,-50,-50,-40,-40,-30},
            {-30,-40,-40,-50,-50,-40,-40,-30},
            {-20,-30,-30,-40,-40,-30,-30,-20},
            {-10,-20,-20,-20,-20,-20,-20,-10},
            {20,  20,  0,  0,  0,  0, 20, 20},
            {20,  30, 10,  0,  0, 10, 30, 20}
        };

        //endgame where these piece get rewarded more for their playstyle.
        int kingEndgameTable[8][8] = {
            {-50,-40,-30,-20,-20,-30,-40,-50},
            {-30,-20,-10,  0,  0,-10,-20,-30},
            {-30,-10, 20, 30, 30, 20,-10,-30},
            {-30,-10, 30, 40, 40, 30,-10,-30},
            {-30,-10, 30, 40, 40, 30,-10,-30},
            {-30,-10, 20, 30, 30, 20,-10,-30},
            {-30,-30,  0,  0,  0,  0,-30,-30},
            {-50,-30,-30,-30,-30,-30,-30,-50}
        };

        int pawnEndgameTable[8][8] = {
            {0,   0,   0,   0,   0,   0,   0,   0},
            {80,  80,  80,  80,  80,  80,  80,  80},
            {50,  50,  50,  50,  50,  50,  50,  50},
            {30,  30,  30,  30,  30,  30,  30,  30},
            {20,  20,  20,  20,  20,  20,  20,  20},
            {10,  10,  10,  10,  10,  10,  10,  10},
            {5,   5,   5,   5,   5,   5,   5,   5},
            {0,   0,   0,   0,   0,   0,   0,   0}
        };

        int rookEndgameTable[8][8] = {
            {10,  10,  10,  10,  10,  10,  10,  10},
            {20,  20,  20,  20,  20,  20,  20,  20},
            {0,   0,   0,   0,   0,   0,   0,   0},
            {0,   0,   0,   0,   0,   0,   0,   0},
            {0,   0,   0,   0,   0,   0,   0,   0},
            {0,   0,   0,   0,   0,   0,   0,   0},
            {20,  20,  20,  20,  20,  20,  20,  20},
            {0,   0,   0,   5,   5,   0,   0,   0}
        };
        
        //use zobrist hash to look up entry.
        std::unordered_map<uint64_t, TranspositionEntry> transpositionTable;


};

//end the if statement
#endif