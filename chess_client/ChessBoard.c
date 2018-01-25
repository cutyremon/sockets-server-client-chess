#include <stdio.h>
#include <stdlib.h>
#include "ChessBoard.h"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_RESET   "\x1b[0m"

char *makeNewBoard()
{
    int i,idx;
    char *board = (char*) malloc(90);

    //epmty placement
    for(i=0;i<90;i++)
    {
        board[i] = EMPTY;
    }

    //red piece placement
    board[0] = CHARIOT;
    board[1] = HORSE;
    board[2] = ELEPHANT;
    board[3] = ADVISOR;
    board[4] = GENERAL;
    board[5] = ADVISOR;
    board[6] = ELEPHANT;
    board[7] = HORSE;
    board[8] = CHARIOT;
    board[19] = CANNON;
    board[25] = CANNON;
    board[27] = SOLDIER;
    board[29] = SOLDIER;
    board[31] = SOLDIER;
    board[33] = SOLDIER;
    board[35] = SOLDIER;

    //board[10] = SOLDIER;

    //black piece placement
    board[81] = CHARIOT + BLACK;
    board[82] = HORSE + BLACK;
    board[83] = ELEPHANT + BLACK;
    board[84] = ADVISOR + BLACK;
    board[85] = GENERAL + BLACK;
    board[86] = ADVISOR + BLACK;
    board[87] = ELEPHANT + BLACK;
    board[88] = HORSE + BLACK;
    board[89] = CHARIOT + BLACK;
    board[64] = CANNON + BLACK;
    board[70] = CANNON + BLACK;
    board[54] = SOLDIER + BLACK;
    board[56] = SOLDIER + BLACK;
    board[58] = SOLDIER + BLACK;
    board[60] = SOLDIER + BLACK;
    board[62] = SOLDIER + BLACK;
    //board[58] = CANNON;
    //board[72] = SOLDIER + BLACK;
    //board[65] = HORSE + BLACK;

    return board;
}

char getPieceAt(char *board, int row, int col)
{
    char result;
    if(row >= 0 && col >= 0 && row < 10 && col < 9)
    {
        result = board[row*9 + col];
        return board[row * 9 + col];
    }
    else return -1;
}

void setPieceAt(char *board,int row,int col, char pieceId)
{
    board[row*9 + col] = pieceId;
}

char isBlack(char pieceId)
{
    return (pieceId > BLACK);
}

char isRed(char pieceId)
{
    return !(pieceId == EMPTY || pieceId > BLACK);
}

void printBoard(char* board)
{
    char black = 'b';
    char red = 'r';
    char pieceId;
    int i,j;
    for(i=9;i>=0;i--)
    {
        printf("%d  ",i);
        for(j=0;j<9;j++)
        {
            pieceId = getPieceAt(board,i,j);
            if(pieceId == EMPTY)
            {
                printf(".");
            }
            else if(pieceId > BLACK)
            {
                pieceId = (char)(pieceId - BLACK);
                switch(pieceId)
                {
                case SOLDIER:
                    printf(ANSI_COLOR_MAGENTA "S" ANSI_COLOR_RESET);
                    break;
                case UPGSOLDIER:
                    printf(ANSI_COLOR_MAGENTA "S" ANSI_COLOR_RESET);
                    break;
                case ADVISOR:
                    printf(ANSI_COLOR_MAGENTA "A" ANSI_COLOR_RESET);
                    break;
                case ELEPHANT:
                    printf(ANSI_COLOR_MAGENTA "E" ANSI_COLOR_RESET);
                    break;
                case HORSE:
                    printf(ANSI_COLOR_MAGENTA "H" ANSI_COLOR_RESET);
                    break;
                case CANNON:
                    printf(ANSI_COLOR_MAGENTA "C" ANSI_COLOR_RESET);
                    break;
                case CHARIOT:
                    printf(ANSI_COLOR_MAGENTA "R" ANSI_COLOR_RESET);
                    break;
                case GENERAL:
                    printf(ANSI_COLOR_MAGENTA "G" ANSI_COLOR_RESET);
                    break;
                }
            }
            else
            {
                switch(pieceId)
                {
                case SOLDIER:
                    printf(ANSI_COLOR_RED  "S" ANSI_COLOR_RESET);
                    break;
                case UPGSOLDIER:
                    printf(ANSI_COLOR_RED  "S" ANSI_COLOR_RESET);
                    break;
                case ADVISOR:
                    printf(ANSI_COLOR_RED  "A" ANSI_COLOR_RESET);
                    break;
                case ELEPHANT:
                    printf(ANSI_COLOR_RED  "E" ANSI_COLOR_RESET);
                    break;
                case HORSE:
                    printf(ANSI_COLOR_RED  "H" ANSI_COLOR_RESET);
                    break;
                case CANNON:
                    printf(ANSI_COLOR_RED  "C" ANSI_COLOR_RESET);
                    break;
                case CHARIOT:
                    printf(ANSI_COLOR_RED  "R" ANSI_COLOR_RESET);
                    break;
                case GENERAL:
                    printf(ANSI_COLOR_RED  "G" ANSI_COLOR_RESET);
                    break;
            }
        }

        if(j < 8)
        {
            printf("--");
        }
        }
        printf("\n");
    }

    printf("   |  |  |  |  |  |  |  |  |\n");
    printf("   0  1  2  3  4  5  6  7  8\n");
}
void printReverseBoard(char *board)
{
    char black = 'b';
    char red = 'r';
    char pieceId;
    int i,j;
    for(i=0;i<10;i++)
    {
        printf("%d  ",i);
        for(j=0;j<9;j++)
        {
            pieceId = getPieceAt(board,i,j);
            if(pieceId == EMPTY)
            {
                printf(".");
            }
            else if(pieceId > BLACK)
            {
                pieceId = (char)(pieceId - BLACK);
                switch(pieceId)
                {
                case SOLDIER:
                    printf(ANSI_COLOR_MAGENTA "S" ANSI_COLOR_RESET);
                    break;
                case UPGSOLDIER:
                    printf(ANSI_COLOR_MAGENTA "S" ANSI_COLOR_RESET);
                    break;
                case ADVISOR:
                    printf(ANSI_COLOR_MAGENTA "A" ANSI_COLOR_RESET);
                    break;
                case ELEPHANT:
                    printf(ANSI_COLOR_MAGENTA "E" ANSI_COLOR_RESET);
                    break;
                case HORSE:
                    printf(ANSI_COLOR_MAGENTA "H" ANSI_COLOR_RESET);
                    break;
                case CANNON:
                    printf(ANSI_COLOR_MAGENTA "C" ANSI_COLOR_RESET);
                    break;
                case CHARIOT:
                    printf(ANSI_COLOR_MAGENTA "R" ANSI_COLOR_RESET);
                    break;
                case GENERAL:
                    printf(ANSI_COLOR_MAGENTA "G" ANSI_COLOR_RESET);
                    break;
                }
            }
            else
            {
                switch(pieceId)
                {
                case SOLDIER:
                    printf(ANSI_COLOR_RED  "S" ANSI_COLOR_RESET);
                    break;
                case UPGSOLDIER:
                    printf(ANSI_COLOR_RED  "S" ANSI_COLOR_RESET);
                    break;
                case ADVISOR:
                    printf(ANSI_COLOR_RED  "A" ANSI_COLOR_RESET);
                    break;
                case ELEPHANT:
                    printf(ANSI_COLOR_RED  "E" ANSI_COLOR_RESET);
                    break;
                case HORSE:
                    printf(ANSI_COLOR_RED  "H" ANSI_COLOR_RESET);
                    break;
                case CANNON:
                    printf(ANSI_COLOR_RED  "C" ANSI_COLOR_RESET);
                    break;
                case CHARIOT:
                    printf(ANSI_COLOR_RED  "R" ANSI_COLOR_RESET);
                    break;
                case GENERAL:
                    printf(ANSI_COLOR_RED  "G" ANSI_COLOR_RESET);
                    break;
            }
        }

        if(j < 8)
        {
            printf("--");
        }
        }
        printf("\n");
    }

    printf("   |  |  |  |  |  |  |  |  |\n");
    printf("   0  1  2  3  4  5  6  7  8\n");
}
char freeBoard(char* board)
{
    free(board);
}

int calculateBoard(char *board,int color)
{
    int i,j;
    char piece;
    int score = 0;
    if(color == RED)
    {
        for(i=0;i<10;i++)
        {
            for(j=0;j<9;j++)
            {
                piece = getPieceAt(board,i,j);
                switch(piece)
                {
                case SOLDIER:
                    score = score + 10;
                    break;
                case UPGSOLDIER:
                    score = score + 20;
                    break;
                case ADVISOR:
                    score = score + 20;
                    break;
                case ELEPHANT:
                    score = score + 20;
                    break;
                case HORSE:
                    score = score + 40;
                    break;
                case CANNON:
                    score = score + 45;
                    break;
                case CHARIOT:
                    score = score + 90;
                    break;
                case GENERAL:
                    score = score + 5000;
                    break;
                case SOLDIER + BLACK:
                    score = score - 10;
                    break;
                case UPGSOLDIER + BLACK:
                    score = score - 20;
                    break;
                case ADVISOR + BLACK:
                    score = score - 20;
                    break;
                case ELEPHANT + BLACK:
                    score = score - 20;
                    break;
                case HORSE + BLACK:
                    score = score - 40;
                    break;
                case CANNON + BLACK:
                    score = score - 45;
                    break;
                case CHARIOT + BLACK:
                    score = score - 90;
                    break;
                case GENERAL + BLACK:
                    score = score - 5000;
                    break;
                }
            }
        }
    }

    if(color == BLACK)
    {
        for(i=0;i<10;i++)
        {
            for(j=0;j<9;j++)
            {
                piece = getPieceAt(board,i,j);
                switch(piece)
                {
                case SOLDIER:
                    score = score - 10;
                    break;
                case UPGSOLDIER:
                    score = score - 20;
                    break;
                case ADVISOR:
                    score = score - 20;
                    break;
                case ELEPHANT:
                    score = score - 20;
                    break;
                case HORSE:
                    score = score - 40;
                    break;
                case CANNON:
                    score = score - 45;
                    break;
                case CHARIOT:
                    score = score - 90;
                    break;
                case GENERAL:
                    score = score - 5000;
                    break;
                case SOLDIER + BLACK:
                    score = score + 10;
                    break;
                case UPGSOLDIER + BLACK:
                    score = score + 20;
                    break;
                case ADVISOR + BLACK:
                    score = score + 20;
                    break;
                case ELEPHANT + BLACK:
                    score = score + 20;
                    break;
                case HORSE + BLACK:
                    score = score + 40;
                    break;
                case CANNON + BLACK:
                    score = score + 45;
                    break;
                case CHARIOT + BLACK:
                    score = score + 90;
                    break;
                case GENERAL + BLACK:
                    score = score + 5000;
                    break;
                }
            }
        }
    }
    return score;
}

void cloneBoard(char *board, char *newBoard)
{
    int i;
    for(i=0;i<90;i++)
        newBoard[i] = board[i];
}

