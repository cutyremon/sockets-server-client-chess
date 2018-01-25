#ifndef CHESSBOARD_H_INCLUDED
#define CHESSBOARD_H_INCLUDED
#define EMPTY 0
#define SOLDIER 1
#define UPGSOLDIER 2
#define ADVISOR 3
#define ELEPHANT 4
#define HORSE 5
#define CANNON 6
#define CHARIOT 7
#define GENERAL 8
#define BLACK 50
#define RED 0

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_RESET   "\x1b[0m"

char *makeNewBoard();
char getPieceAt(char *board, int row, int col);
void setPieceAt(char *board,int row,int col, char pieceId);
char isBlack(char pieceId);
char isRed(char pieceId);
void printBoard(char* board);
int calculateBoard(char* board,int color);
char freeBoard(char* board);
void cloneBoard(char *board, char *newBoard);




#endif // CHESSBOARD_H_INCLUDED
