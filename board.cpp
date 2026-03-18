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
                case 0: 
                    std::cout << ". "; 
                    break;
                case 1:  
                    std::cout << "P "; 
                    break;
                case -1: 
                    std::cout << "p "; 
                    break;
                case 2:  
                    std::cout << "N "; 
                    break;
                case -2: 
                    std::cout << "n "; 
                    break;
                case 3:  
                    std::cout << "B "; 
                    break;
                case -3: 
                    std::cout << "b "; 
                    break;
                case 4:  
                    std::cout << "R "; 
                    break;
                case -4: 
                    std::cout << "r "; 
                    break;
                case 5:  
                    std::cout << "Q "; 
                    break;
                case -5: 
                    std::cout << "q "; 
                    break;
                case 6:  
                    std::cout << "K "; 
                    break;
                case -6: 
                    std::cout << "k "; 
                    break;

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

            //starting move for white pawn you can move two up  but first have to make sure square above it is empty.
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
        
    }
    return moves;
}

std::vector<Move> Board::getKnightMoves(int row, int col) {
    std::vector<Move> moves;
    int piece = board[row][col];
    if (abs(piece) !=2 ) {
        return moves;
    }
    //all possible 8 knight jumps from left to right and top to bottom.
    //0x0x
    //x000x
    //00k00
    //x000x
    //0x0x0
    int jumpRow[] = {-2, -2, -1, -1, 1, 1, 2, 2};
    int jumpCol[] = {-1, 1, -2, 2, -2, 2, -1, 1};
    
    //loop through both jumpRow and jumpCol
    for (int i = 0; i < 8; i++) {
        int newRow = row + jumpRow[i];
        int newCol = col + jumpCol[i];

        //check bounds
        if (newRow < 0 || newRow >= 8 || newCol < 0 || newCol >= 8) {
            continue;
        }

        //iempty square or black piece capture
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
    if (abs(piece) != 4 ) {
        return moves;
    }

    int directions[4][2] = {{0,-1},{0,1},{1,0},{-1,0}};

    for (int i = 0; i < 4; i++) {
        int newRow = row + directions[i][0];
        int newCol = col + directions[i][1];
    
        while (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8) {
            if (board[newRow][newCol] == 0) {
                moves.push_back({row, col, newRow, newCol});
            } 
            else if (piece == 4 && board[newRow][newCol] < 0) {
                moves.push_back({row, col, newRow, newCol});
                break;
            } 
            else if (piece == -4 && board[newRow][newCol] > 0) {
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
    if (abs(piece) != 3 ) {
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
            } 
            else if (piece == 3 && board[newRow][newCol] < 0) {
                moves.push_back({row, col, newRow, newCol});
                break;
            } 
            else if (piece == -3 && board[newRow][newCol] > 0) {
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
    if (abs(piece) != 5 ) {
        return moves;
    }
    int directions[8][2] = {{0,-1},{0,1},{1,0},{-1,0},{-1,-1},{1,1},{1,-1},{-1,1}};

    for (int i = 0; i < 8; i++) {
        int newRow = row + directions[i][0];
        int newCol = col + directions[i][1];
    
        while (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8) {
            if (board[newRow][newCol] == 0) {
                moves.push_back({row, col, newRow, newCol});
            } 
            else if (piece == 5 && board[newRow][newCol] < 0) {
                moves.push_back({row, col, newRow, newCol});
                break;
            } 
            else if (piece == -5 && board[newRow][newCol] > 0) {
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
    if (abs(piece) != 6 ) {
        return moves;
    }

    int directions[8][2] = {{0,-1},{0,1},{1,0},{-1,0},{-1,-1},{1,1},{1,-1},{-1,1}};
    for (int i = 0; i < 8; i++) {
        int newRow = row + directions[i][0];
        int newCol = col + directions[i][1];
        if (newCol < 8 && newCol >= 0 && newRow < 8 && newRow >= 0 ) {
            //for white capture or empty
            if (piece == 6 && board[newRow][newCol] <= 0 ) {
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
    for (int i = 0; i < 8;i++) {
        for (int j = 0; j < 8; j++) {
            int piece = board[i][j];
            if (piece == 0) {
                continue;
            } 
            //if white and piece not white, don't generate moves for it.
            if (color == 1 && piece < 0) {
                continue;
            }
            if (color == -1 && piece > 0)  {
                continue;
            }
            std::vector<Move> temporaryMove;
            switch(abs(piece)) {
                case 1:
                    temporaryMove = getPawnMoves(i,j);
                    break;
                case 2:
                    temporaryMove = getKnightMoves(i, j); 
                    break;
                case 3:
                    temporaryMove = getBishopMoves(i, j); 
                    break;
                case 4:
                    temporaryMove = getRookMoves(i, j); 
                    break;
                case 5:
                    temporaryMove = getQueenMoves(i, j); 
                    break;
                case 6:
                    temporaryMove = getKingMoves(i, j); 
                    break;
            }
            for (int k = 0; k < temporaryMove.size();k++) {
                moves.push_back(temporaryMove[k]);
            }


        }
    }
    return moves;
}

//make move to the board. move piece from the from square to the to square and set the from square to 0.
void Board::makeMove(Move m) {
    int piece = board[m.fromRow][m.fromCol];
    board[m.toRow][m.toCol] = piece;
    board[m.fromRow][m.fromCol] = 0;
}

//reverse a move. puts the piece back on the from square and restore captured piece on the to square.
void Board::undoMove(Move m, int capturedPiece) {
    board[m.fromRow][m.fromCol] = board[m.toRow][m.toCol];
    board[m.toRow][m.toCol] = capturedPiece;
}

//return a score base on board. positive mean white is winning and negative mean black is winning. 
int Board::evaluate() {
    int count = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            switch(board[i][j]) {
                case 0:
                    break;
                case 1:
                    count+=100;
                    break;
                case -1:
                    count-=100;
                    break;
                case 2:
                    count+=300;
                    break;
                case -2:
                    count-=300;
                    break;
                case 3:
                    count+=300;
                    break;
                case -3:
                    count-=300;
                    break;
                case 4:
                    count+=500;
                    break;
                case -4:
                    count-=500;
                    break;
                case 5:
                    count+=900;
                    break;
                case -5:
                    count-=900;
                    break;
                case 6:
                    count+=1000000;
                    break;
                case -6:
                    count-=1000000;
                    break;
            }
        }
    }
    return count;

}