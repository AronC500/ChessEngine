#include "board.h"
#include <iostream>

Board::Board() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            board[i][j] = 0;
        }
    }
    //white pieces
    board[7][0] = 4;
    board[7][1] = 2;
    board[7][2] = 3;
    board[7][3] = 5;
    board[7][4] = 6;
    board[7][5] = 3;
    board[7][6] = 2;
    board[7][7] = 4;

    //white pawns
    for (int i = 0; i < 8; i++) {
        board[6][i] = 1;
    }

    //black pieces. negative because it's easier to test if its black or white by seeing if its > or < 0.
    //also easy to get the piece type regardless of color if you use abs.
    board[0][0] = -4;
    board[0][1] = -2;
    board[0][2] = -3;
    board[0][3] = -5;
    board[0][4] = -6;
    board[0][5] = -3;
    board[0][6] = -2;
    board[0][7] = -4;

    //black pawns
    for (int i = 0; i < 8; i++) {
        board[1][i] = -1;
    }
}

void Board::print() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            switch(board[i][j]) {
                case 0:  std::cout << ". "; break;
                case 1:  std::cout << "P "; break;
                case -1: std::cout << "p "; break;
                case 2:  std::cout << "N "; break;
                case -2: std::cout << "n "; break;
                case 3:  std::cout << "B "; break;
                case -3: std::cout << "b "; break;
                case 4:  std::cout << "R "; break;
                case -4: std::cout << "r "; break;
                case 5:  std::cout << "Q "; break;
                case -5: std::cout << "q "; break;
                case 6:  std::cout << "K "; break;
                case -6: std::cout << "k "; break;
            }
        }
        std::cout << std::endl;
    }
}

std::vector<Move> Board::getPawnMoves(int row, int col) {
    std::vector<Move> moves;
    int piece = board[row][col];

    //if is an white pawn.
    if (piece == 1) {
        //bound check so its not above board and make sure square above it is empty.
        if (row - 1 >= 0 && board[row-1][col] == 0) {
            moves.push_back({row,col,row-1,col});
            //starting move for white pawn you can move two up but first have to make sure square above it is empty.
            if (row == 6 && board[row-2][col] == 0) {
                moves.push_back({row,col,row-2,col});
            }
        }
        //capture diagonally
        if (row-1 >= 0 && col-1 >= 0 && board[row-1][col-1] < 0) {
            moves.push_back({row,col,row-1,col-1});
        }
        if (row-1 >= 0 && col+1 < 8 && board[row-1][col+1] < 0) {
            moves.push_back({row,col,row-1,col+1});
        }
        //El Passant
        if (row == 3 && EnPassantRow == 2 && abs(col - EnPassantCol) == 1) {
            moves.push_back({row, col, EnPassantRow, EnPassantCol});
        }
    }

    //if is an black pawn
    if (piece == -1) {
        //bound check so its not below board and make sure square above it is empty.
        if (row + 1 < 8 && board[row+1][col] == 0) {
            moves.push_back({row, col, row+1, col});
            //starting move for black pawn you can move two down but first have to make sure square above it is empty.
            if (row == 1 && board[row+2][col] == 0) {
                moves.push_back({row, col, row+2, col});
            }
        }
        // capture diagonally
        if (row+1 < 8 && col-1 >= 0 && board[row+1][col-1] > 0) {
            moves.push_back({row, col, row+1, col-1});
        }
        if (row+1 < 8 && col+1 < 8 && board[row+1][col+1] > 0) {
            moves.push_back({row, col, row+1, col+1});
        }
        //El Passant
        if (row == 4 && EnPassantRow == 5 && abs(col - EnPassantCol) == 1) {
            moves.push_back({row, col, EnPassantRow, EnPassantCol});
        }
    }
    return moves;
}

std::vector<Move> Board::getKnightMoves(int row, int col) {
    std::vector<Move> moves;
    int piece = board[row][col];
    if (abs(piece) != 2) {
        return moves;
    }
    //all possible 8 knight jumps from left to right and top to bottom.
    int jumpRow[] = {-2, -2, -1, -1, 1, 1, 2, 2};
    int jumpCol[] = {-1, 1, -2, 2, -2, 2, -1, 1};

    for (int i = 0; i < 8; i++) {
        int newRow = row + jumpRow[i];
        int newCol = col + jumpCol[i];
        if (newRow < 0 || newRow >= 8 || newCol < 0 || newCol >= 8) {
            continue;
        }
        //empty square or black piece capture
        if (piece == 2 && board[newRow][newCol] <= 0) {
            moves.push_back({row,col,newRow,newCol});
        }
        //empty square or white piece capture.
        if (piece == -2 && board[newRow][newCol] >= 0) {
            moves.push_back({row,col,newRow,newCol});
        }
    }
    return moves;
}

std::vector<Move> Board::getRookMoves(int row, int col) {
    std::vector<Move> moves;
    int piece = board[row][col];
    //if not rook, then leave.
    if (abs(piece) != 4) {
        return moves;
    }
    int directions[4][2] = {{0,-1},{0,1},{1,0},{-1,0}};
    for (int i = 0; i < 4; i++) {
        int newRow = row + directions[i][0];
        int newCol = col + directions[i][1];
        while (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8) {
            if (board[newRow][newCol] == 0) {
                moves.push_back({row, col, newRow, newCol});
            } else if (piece == 4 && board[newRow][newCol] < 0) {
                moves.push_back({row, col, newRow, newCol});
                break;
            } else if (piece == -4 && board[newRow][newCol] > 0) {
                moves.push_back({row, col, newRow, newCol});
                break;
            } else {
                break;
            }
            newRow += directions[i][0];
            newCol += directions[i][1];
        }
    }
    return moves;
}

std::vector<Move> Board::getBishopMoves(int row, int col) {
    std::vector<Move> moves;
    int piece = board[row][col];
    //if not bishop, then leave.
    if (abs(piece) != 3) {
        return moves;
    }
    //for bishop, its diagonal
    int directions[4][2] = {{-1,-1},{1,1},{1,-1},{-1,1}};
    for (int i = 0; i < 4; i++) {
        int newRow = row + directions[i][0];
        int newCol = col + directions[i][1];
        while (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8) {
            if (board[newRow][newCol] == 0) {
                moves.push_back({row, col, newRow, newCol});
            } else if (piece == 3 && board[newRow][newCol] < 0) {
                moves.push_back({row, col, newRow, newCol});
                break;
            } else if (piece == -3 && board[newRow][newCol] > 0) {
                moves.push_back({row, col, newRow, newCol});
                break;
            } else {
                break;
            }
            newRow += directions[i][0];
            newCol += directions[i][1];
        }
    }
    return moves;
}

std::vector<Move> Board::getQueenMoves(int row, int col) {
    std::vector<Move> moves;
    int piece = board[row][col];
    //if not queen, then leave.
    if (abs(piece) != 5) {
        return moves;
    }
    int directions[8][2] = {{0,-1},{0,1},{1,0},{-1,0},{-1,-1},{1,1},{1,-1},{-1,1}};
    for (int i = 0; i < 8; i++) {
        int newRow = row + directions[i][0];
        int newCol = col + directions[i][1];
        while (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8) {
            if (board[newRow][newCol] == 0) {
                moves.push_back({row, col, newRow, newCol});
            } else if (piece == 5 && board[newRow][newCol] < 0) {
                moves.push_back({row, col, newRow, newCol});
                break;
            } else if (piece == -5 && board[newRow][newCol] > 0) {
                moves.push_back({row, col, newRow, newCol});
                break;
            } else {
                break;
            }
            newRow += directions[i][0];
            newCol += directions[i][1];
        }
    }
    return moves;
}

std::vector<Move> Board::getKingMoves(int row, int col) {
    std::vector<Move> moves;
    int piece = board[row][col];
    //if not king, then leave.
    if (abs(piece) != 6) {
        return moves;
    }
    int directions[8][2] = {{0,-1},{0,1},{1,0},{-1,0},{-1,-1},{1,1},{1,-1},{-1,1}};
    for (int i = 0; i < 8; i++) {
        int newRow = row + directions[i][0];
        int newCol = col + directions[i][1];
        if (newCol < 8 && newCol >= 0 && newRow < 8 && newRow >= 0) {
            //for white capture or empty
            if (piece == 6 && board[newRow][newCol] <= 0) {
                moves.push_back({row,col,newRow,newCol});
            }
            //for black capture or empty
            else if (piece == -6 && board[newRow][newCol] >= 0) {
                moves.push_back({row,col,newRow,newCol});
            }
        }
    }
    return moves;
}

std::vector<Move> Board::GenerateAllMoves(int color) {
    std::vector<Move> moves;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            int piece = board[i][j];
            if (piece == 0) {
                continue;
            }
            //if white and piece not white, don't generate moves for it.
            if (color == 1 && piece < 0) {
                continue;
            }
            if (color == -1 && piece > 0) {
                continue;
            }
            std::vector<Move> temporaryMove;
            switch(abs(piece)) {
                case 1: temporaryMove = getPawnMoves(i,j);   break;
                case 2: temporaryMove = getKnightMoves(i,j); break;
                case 3: temporaryMove = getBishopMoves(i,j); break;
                case 4: temporaryMove = getRookMoves(i,j);   break;
                case 5: temporaryMove = getQueenMoves(i,j);  break;
                case 6: temporaryMove = getKingMoves(i,j);   break;
            }
            for (int k = 0; k < temporaryMove.size(); k++) {
                moves.push_back(temporaryMove[k]);
            }
        }
    }
    return moves;
}

//make move to the board. move piece from the from square to the to square and set the from square to 0.
void Board::makeMove(Move m) {
    int piece = board[m.fromRow][m.fromCol];
    //capture en passant piece
    if (EnPassantRow != -1 && EnPassantCol != -1 && abs(piece) == 1 && (m.toRow == EnPassantRow && m.toCol == EnPassantCol)) {
        board[m.fromRow][EnPassantCol] = 0;
    }
    EnPassantRow = -1;
    EnPassantCol = -1;
    //a full move consist of two half move and if there is 50 full move with no pawn moving or
    //and no piece being captured, game is draw.
    if (abs(piece) == 1 || board[m.toRow][m.toCol] != 0) {
        halfMoveCount = 0;
    } else {
        halfMoveCount++;
    }
    //en passant: when opponent pawn first move two forward and is right next to your pawn,
    //you can go diagonally and still capture the pawn under it but the move right after it.
    if (abs(piece) == 1) {
        if (m.fromRow == 1 && m.toRow == 3) {
            EnPassantRow = 2;
            EnPassantCol = m.fromCol;
        }
        if (m.fromRow == 6 && m.toRow == 4) {
            EnPassantRow = 5;
            EnPassantCol = m.fromCol;
        }
    }
    board[m.toRow][m.toCol] = piece;
    board[m.fromRow][m.fromCol] = 0;
    //pawn promotion for white
    if (piece == 1 && m.toRow == 0) {
        board[m.toRow][m.toCol] = 5;
    }
    //for black
    if (piece == -1 && m.toRow == 7) {
        board[m.toRow][m.toCol] = -5;
    }
}

//reverse a move. puts the piece back on the from square and restore captured piece on the to square.
void Board::undoMove(Move m, int capturedPiece, int enPassantCaptureRow, int enPassantCaptureCol) {
    board[m.fromRow][m.fromCol] = board[m.toRow][m.toCol];
    if (enPassantCaptureCol != -1 && enPassantCaptureRow != -1 && abs(board[m.toRow][m.toCol]) == 1) {
        board[enPassantCaptureRow][enPassantCaptureCol] = capturedPiece;
    } else {
        board[m.toRow][m.toCol] = capturedPiece;
    }
}

//return a score base on board. positive mean white is winning and negative mean black is winning.
int Board::evaluate() {
    int count = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            switch(board[i][j]) {
                case 0:   break;
                case 1:   count += 100;     break;
                case -1:  count -= 100;     break;
                case 2:   count += 300;     break;
                case -2:  count -= 300;     break;
                case 3:   count += 300;     break;
                case -3:  count -= 300;     break;
                case 4:   count += 500;     break;
                case -4:  count -= 500;     break;
                case 5:   count += 900;     break;
                case -5:  count -= 900;     break;
                case 6:   count += 1000000; break;
                case -6:  count -= 1000000; break;
            }
        }
    }
    return count;
}

//find best possible score of whole board after looking ahead certain number of moves. when it is white's turn,
//it tries to make the highest score and when it's black turn, it tries every possible black move to find the lowest score.
//depth param is how many moves ahead the engine looks.
int Board::minimax(int depth, bool isWhite) {
    //means we looked as far as we wanted to and we evaluate the board.
    if (depth == 0) {
        return evaluate();
    }

    if (isWhite) {
        int bestScore = -9999999;
        std::vector<Move> moves = GenerateAllMoves(1);
        for (int i = 0; i < moves.size(); i++) {
            passRow = -1;
            passCol = -1;
            //we have to check whether enpass or not before makemove so we can pass to undo move to check because in make move we change it to -1 after so it would be too late for undomove function
            if (EnPassantRow != -1 && EnPassantCol != -1 && abs(board[moves[i].fromRow][moves[i].fromCol]) == 1 && (moves[i].toRow == EnPassantRow && moves[i].toCol == EnPassantCol)) {
                passRow = moves[i].fromRow;
                passCol = EnPassantCol;
            }
            //save halfMoveCount and en passant state before making move so we can restore after undo
            int savedHalfMove = halfMoveCount;
            int savedEPRow = EnPassantRow;
            int savedEPCol = EnPassantCol;

            int capturedPiece = board[moves[i].toRow][moves[i].toCol];
            makeMove(moves[i]);
            //filter move that make king in check.
            if (isInCheck(true)) {
                undoMove(moves[i], capturedPiece, passRow, passCol);
                halfMoveCount = savedHalfMove;
                EnPassantRow = savedEPRow;
                EnPassantCol = savedEPCol;
                continue;
            }
            int score = minimax(depth - 1, false);
            undoMove(moves[i], capturedPiece, passRow, passCol);
            //restore saved state after undo
            halfMoveCount = savedHalfMove;
            EnPassantRow = savedEPRow;
            EnPassantCol = savedEPCol;

            if (score > bestScore) {
                bestScore = score;
            }
        }
        return bestScore;
    } else {
        int bestScore = 9999999;
        std::vector<Move> moves = GenerateAllMoves(-1);
        for (int i = 0; i < moves.size(); i++) {
            passRow = -1;
            passCol = -1;
            //we have to check whether enpass or not before makemove so we can pass to undo move to check because in make move we change it to -1 after so it would be too late for undomove function
            if (EnPassantRow != -1 && EnPassantCol != -1 && abs(board[moves[i].fromRow][moves[i].fromCol]) == 1 && (moves[i].toRow == EnPassantRow && moves[i].toCol == EnPassantCol)) {
                passRow = moves[i].fromRow;
                passCol = EnPassantCol;
            }
            int savedHalfMove = halfMoveCount;
            int savedEPRow = EnPassantRow;
            int savedEPCol = EnPassantCol;

            int capturedPiece = board[moves[i].toRow][moves[i].toCol];
            makeMove(moves[i]);
            if (isInCheck(false)) {
                undoMove(moves[i], capturedPiece, passRow, passCol);
                halfMoveCount = savedHalfMove;
                EnPassantRow = savedEPRow;
                EnPassantCol = savedEPCol;
                continue;
            }
            int score = minimax(depth - 1, true);
            undoMove(moves[i], capturedPiece, passRow, passCol);
            halfMoveCount = savedHalfMove;
            EnPassantRow = savedEPRow;
            EnPassantCol = savedEPCol;

            if (score < bestScore) {
                bestScore = score;
            }
        }
        return bestScore;
    }
}

//similar to minimax but instead of returning a score it returns the actual best move to play.
Move Board::getBestMove(int depth, bool isWhite) {
    if (isWhite) {
        std::vector<Move> moves = GenerateAllMoves(1);
        if (isGameOver(isWhite) || isDraw(isWhite) || moves.size() == 0) {
            return {-1,-1,-1,-1};
        }
        int bestScore = -9999999;
        Move bestMove = moves[0];
        for (int i = 0; i < moves.size(); i++) {
            passRow = -1;
            passCol = -1;
            //we have to check whether enpass or not before makemove so we can pass to undo move to check because in make move we change it to -1 after so it would be too late for undomove function
            if (EnPassantRow != -1 && EnPassantCol != -1 && abs(board[moves[i].fromRow][moves[i].fromCol]) == 1 && (moves[i].toRow == EnPassantRow && moves[i].toCol == EnPassantCol)) {
                passRow = moves[i].fromRow;
                passCol = EnPassantCol;
            }
            int savedHalfMove = halfMoveCount;
            int savedEPRow = EnPassantRow;
            int savedEPCol = EnPassantCol;

            int capturedPiece = board[moves[i].toRow][moves[i].toCol];
            makeMove(moves[i]);
            if (isInCheck(true)) {
                undoMove(moves[i], capturedPiece, passRow, passCol);
                halfMoveCount = savedHalfMove;
                EnPassantRow = savedEPRow;
                EnPassantCol = savedEPCol;
                continue;
            }
            int score = minimax(depth, false);
            undoMove(moves[i], capturedPiece, passRow, passCol);
            halfMoveCount = savedHalfMove;
            EnPassantRow = savedEPRow;
            EnPassantCol = savedEPCol;

            if (score > bestScore) {
                bestScore = score;
                bestMove = moves[i];
            }
        }
        return bestMove;
    } else {
        std::vector<Move> moves = GenerateAllMoves(-1);
        if (isGameOver(isWhite) || isDraw(isWhite) || moves.size() == 0) {
            return {-1,-1,-1,-1};
        }
        int bestScore = 9999999;
        Move bestMove = moves[0];
        for (int i = 0; i < moves.size(); i++) {
            passRow = -1;
            passCol = -1;
            //we have to check whether enpass or not before makemove so we can pass to undo move to check because in make move we change it to -1 after so it would be too late for undomove function
            if (EnPassantRow != -1 && EnPassantCol != -1 && abs(board[moves[i].fromRow][moves[i].fromCol]) == 1 && (moves[i].toRow == EnPassantRow && moves[i].toCol == EnPassantCol)) {
                passRow = moves[i].fromRow;
                passCol = EnPassantCol;
            }
            int savedHalfMove = halfMoveCount;
            int savedEPRow = EnPassantRow;
            int savedEPCol = EnPassantCol;

            int capturedPiece = board[moves[i].toRow][moves[i].toCol];
            makeMove(moves[i]);
            if (isInCheck(false)) {
                undoMove(moves[i], capturedPiece, passRow, passCol);
                halfMoveCount = savedHalfMove;
                EnPassantRow = savedEPRow;
                EnPassantCol = savedEPCol;
                continue;
            }
            int score = minimax(depth, true);
            undoMove(moves[i], capturedPiece, passRow, passCol);
            halfMoveCount = savedHalfMove;
            EnPassantRow = savedEPRow;
            EnPassantCol = savedEPCol;

            if (score < bestScore) {
                bestScore = score;
                bestMove = moves[i];
            }
        }
        return bestMove;
    }
}

//check if square is being attacked by color.
bool Board::isSquareAttacked(int row, int col, bool isWhite) {
    int color;
    if (isWhite) {
        color = 1;
    } else {
        color = -1;
    }
    int straight[4][2] = {{0,-1},{0,1},{1,0},{-1,0}};
    int diagonal[4][2] = {{-1,-1},{1,1},{1,-1},{-1,1}};
    int knightMoves[8][2] = {{-2,-1},{-2,1},{-1,-2},{-1,2},{1,-2},{1,2},{2,-1},{2,1}};
    int kingMoves[8][2] = {{0,-1},{0,1},{1,0},{-1,0},{-1,-1},{1,1},{1,-1},{-1,1}};

    //For checking if current position is in danger of an rook/queen (straight)
    for (int i = 0; i < 4; i++) {
        int r = row + straight[i][0];
        int c = col + straight[i][1];
        while (r >= 0 && r < 8 && c >= 0 && c < 8) {
            if (board[r][c] != 0) {
                if (board[r][c] == 4 * color || board[r][c] == 5 * color) {
                    return true;
                }
                //would mean something else is blocking the enemy rook/queen so not being attacked.
                break;
            }
            r += straight[i][0];
            c += straight[i][1];
        }
    }
    //For bishop/queen (diagonals)
    for (int i = 0; i < 4; i++) {
        int r = row + diagonal[i][0];
        int c = col + diagonal[i][1];
        while (r >= 0 && r < 8 && c >= 0 && c < 8) {
            if (board[r][c] != 0) {
                if (board[r][c] == 3 * color || board[r][c] == 5 * color) {
                    return true;
                }
                break;
            }
            r += diagonal[i][0];
            c += diagonal[i][1];
        }
    }
    //knights
    for (int i = 0; i < 8; i++) {
        int r = row + knightMoves[i][0];
        int c = col + knightMoves[i][1];
        if (r >= 0 && r < 8 && c >= 0 && c < 8) {
            if (board[r][c] == 2 * color) {
                return true;
            }
        }
    }
    //pawns
    int pawnDir;
    if (isWhite) {
        pawnDir = -1;
    } else {
        pawnDir = 1;
    }
    if (row + pawnDir >= 0 && row + pawnDir < 8 && col - 1 >= 0 && board[row+pawnDir][col-1] == 1 * color) {
        return true;
    }
    if (row + pawnDir >= 0 && row + pawnDir < 8 && col + 1 < 8 && board[row+pawnDir][col+1] == 1 * color) {
        return true;
    }
    // king
    for (int i = 0; i < 8; i++) {
        int r = row + kingMoves[i][0];
        int c = col + kingMoves[i][1];
        if (r >= 0 && r < 8 && c >= 0 && c < 8) {
            if (board[r][c] == 6 * color) {
                return true;
            }
        }
    }
    return false;
}

//check if king is in check.
bool Board::isInCheck(bool isWhite) {
    int kingPiece;
    if (isWhite) {
        kingPiece = 6;
    } else {
        kingPiece = -6;
    }
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (board[i][j] == kingPiece) {
                //see if square is attacked by opposite color.
                return isSquareAttacked(i, j, !isWhite);
            }
        }
    }
    return false;
}

//Stalemate = not in check + no legal moves
//Fifty move rule = 100 half moves with no pawn move or capture
bool Board::isDraw(bool isWhite) {
    return halfMoveCount == 100 || (!isInCheck(isWhite) && !hasLegalMoves(isWhite));
}

//Checkmate = in check + no legal moves.
bool Board::isGameOver(bool isWhite) {
    return isInCheck(isWhite) && !hasLegalMoves(isWhite);
}

//check if have legal move by going through all possible moves and seeing if one move can make it so you are not in check.
bool Board::hasLegalMoves(bool isWhite) {
    int color;
    if (isWhite) {
        color = 1;
    } else {
        color = -1;
    }
    std::vector<Move> AllMoves = GenerateAllMoves(color);
    for (int i = 0; i < AllMoves.size(); i++) {
        passRow = -1;
        passCol = -1;
        //we have to check whether enpass or not before makemove so we can pass to undo move to check because in make move we change it to -1 after so it would be too late for undomove function
        if (EnPassantRow != -1 && EnPassantCol != -1 && abs(board[AllMoves[i].fromRow][AllMoves[i].fromCol]) == 1 && (AllMoves[i].toRow == EnPassantRow && AllMoves[i].toCol == EnPassantCol)) {
            passRow = AllMoves[i].fromRow;
            passCol = EnPassantCol;
        }
        int savedHalfMove = halfMoveCount;
        int savedEPRow = EnPassantRow;
        int savedEPCol = EnPassantCol;

        int capturedPiece = board[AllMoves[i].toRow][AllMoves[i].toCol];
        makeMove(AllMoves[i]);
        if (!isInCheck(isWhite)) {
            undoMove(AllMoves[i], capturedPiece, passRow, passCol);
            halfMoveCount = savedHalfMove;
            EnPassantRow = savedEPRow;
            EnPassantCol = savedEPCol;
            return true;
        }
        undoMove(AllMoves[i], capturedPiece, passRow, passCol);
        halfMoveCount = savedHalfMove;
        EnPassantRow = savedEPRow;
        EnPassantCol = savedEPCol;
    }
    return false;
}