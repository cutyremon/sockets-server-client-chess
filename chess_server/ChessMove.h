#ifndef CHESSMOVE_H_INCLUDED
#define CHESSMOVE_H_INCLUDED
typedef struct
{
    char pieceId;
    char startRow;
    char startCol;
    char endRow;
    char endCol;
} Move;

typedef struct
{
    int cap;
    int size;
    Move **moves;
} MoveList;

MoveList *newMoveList();
void addMove(MoveList *set, char pieceId, int startRow, int startCol, int endRow,int endCol);
MoveList *getAllPossibleMoves(char *board,int color);
char* moveToString(Move* move);
int undoMove(char *board,Move *move,char oldPiece);
void *cloneMove(Move* newMove,Move *move);
Move* stringToMove(char *board,char *str);
int doMove(char *board, Move *move);
void printMoveList(MoveList *moveList);
void freeMoveList(MoveList *moveList);
Move* bestMove(char *board,int depth,int alpha,int beta,int comColor,int maxColor);
int validMove(MoveList *moveList, Move *move);
Move *getBestMove(char *board,int color);




#endif // CHESSMOVE_H_INCLUDED
