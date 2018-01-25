#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ChessBoard.h"
#include "ChessMove.h"

Move bestArray[5];


MoveList *newMoveList()
{
    
    MoveList *set = (MoveList*)malloc(sizeof(MoveList));
    if(set == NULL) printf("cannot allocate memory");
    set->cap = 50;
    set->size = 0;
    set->moves = (Move**)malloc(sizeof(Move*) * set->cap);
    if(set->moves == NULL) printf("cannot allocate memory\n");
    //printf("new movelist created: %lu,%lu\n",sizeof(set),sizeof(set->moves));
    return set;
}

void *cloneMove(Move* newMove,Move *move)
{
    //Move *newMove = (Move*)malloc(sizeof(Move));
    newMove->pieceId = move->pieceId;
    newMove->startRow = move->startRow;
    newMove->startCol = move->startCol;
    newMove->endRow = move->endRow;
    newMove->endCol = move->endCol;
}
void addMove(MoveList *set, char pieceId, int startRow, int startCol, int endRow,int endCol)
{
    if(set->size >= set->cap)
    {
        set->cap *= 2;
        int i;
        Move** oMoves = set->moves;
        set->moves = (Move**)malloc(sizeof(Move*) * set->cap);
        for(i=0;i<set->size;i++)
            set->moves[i] = oMoves[i];
        free(oMoves);
    }

    Move *move = (Move*)malloc(sizeof(Move));
    move->pieceId = pieceId;
    move->startRow = (char) startRow;
    move->startCol = (char) startCol;
    move->endRow = (char) endRow;
    move->endCol = (char) endCol;
    set->moves[set->size++] = move;
}

MoveList *getAllPossibleMoves(char *board,int color)
{
    int i,j;
    int x,y;
    char piece;
    MoveList *moveList = newMoveList();
    //char* board = makeNewBoard();
    //cloneBoard(board,board);
    for(i=0;i<10;i++)
    {
        for(j=0;j<9;j++)
        {
            //printf("i:%d,j:%d\n",i,j);
            piece = getPieceAt(board,i,j);
            if(color == RED)
            {
                if(isRed(getPieceAt(board,i,j)))
                {
                    switch(piece)
                    {
                    case SOLDIER:
                        x = i;
                        y = j;
                        if(x+1 < 10)
                        {
                            if(getPieceAt(board,x+1,y) == EMPTY || isBlack(getPieceAt(board,x+1,y)))
                            {
                                addMove(moveList,piece,i,j,x+1,y);
                            }
                        }
                        break;

                    case ADVISOR:
                        x = i;
                        y = j;
                        if(x==0&&y==3)
                        {
                            if(getPieceAt(board,1,4) == EMPTY || isBlack(getPieceAt(board,1,4)))
                            {
                                addMove(moveList,piece,0,3,1,4);
                            }
                        }
                        if(x==2&&y==3)
                        {
                            if(getPieceAt(board,1,4) == EMPTY || isBlack(getPieceAt(board,1,4)))
                            {
                                addMove(moveList,piece,2,3,1,4);
                            }
                        }
                        if(x==2&&y==5)
                        {
                            if(getPieceAt(board,1,4) == EMPTY || isBlack(getPieceAt(board,1,4)))
                            {
                                addMove(moveList,piece,2,5,1,4);
                            }
                        }
                        if(x==0&&y==5)
                        {
                            if(getPieceAt(board,1,4) == EMPTY || isBlack(getPieceAt(board,1,4)))
                               {
                                   addMove(moveList,piece,0,5,1,4);
                               }
                        }
                        if(x==1&&y==4)
                        {
                            if(getPieceAt(board,2,3) == EMPTY || isBlack(getPieceAt(board,2,3)))
                            {
                                addMove(moveList,piece,1,4,2,3);
                            }
                            if(getPieceAt(board,0,3) == EMPTY || isBlack(getPieceAt(board,0,3)))
                            {
                                addMove(moveList,piece,1,4,0,3);
                            }
                            if(getPieceAt(board,2,5) == EMPTY || isBlack(getPieceAt(board,2,5)))
                            {
                                addMove(moveList,piece,1,4,2,5);
                            }
                            if(getPieceAt(board,0,5) == EMPTY || isBlack(getPieceAt(board,0,5)))
                            {
                                addMove(moveList,piece,1,4,0,5);
                            }
                        }
                        break;

                    case ELEPHANT:
                        x = i;
                        y = j;
                        if(x==2 && y==0)
                        {
                            if(getPieceAt(board,4,2) == EMPTY || isBlack(getPieceAt(board,4,2)))
                            {
                                addMove(moveList,piece,2,0,4,2);
                            }
                            if(getPieceAt(board,0,2) == EMPTY || isBlack(getPieceAt(board,0,2)))
                            {
                                addMove(moveList,piece,2,0,0,2);
                            }
                        }
                        if(x==4 && y==2)
                        {
                            if(getPieceAt(board,2,0) == EMPTY || isBlack(getPieceAt(board,2,0)))
                            {
                                addMove(moveList,piece,4,2,2,0);
                            }
                            if(getPieceAt(board,2,4) == EMPTY || isBlack(getPieceAt(board,2,4)))
                            {
                                addMove(moveList,piece,4,2,2,4);
                            }
                        }
                        if(x==0 && y==2)
                        {
                            if(getPieceAt(board,2,0) == EMPTY || isBlack(getPieceAt(board,2,0)))
                            {
                                addMove(moveList,piece,0,2,2,0);
                            }
                            if(getPieceAt(board,2,4) == EMPTY || isBlack(getPieceAt(board,2,4)))
                            {
                                addMove(moveList,piece,0,2,2,4);
                            }
                        }
                        if(x==2 && y==8)
                        {
                            if(getPieceAt(board,4,6) == EMPTY || isBlack(getPieceAt(board,4,6)))
                            {
                                addMove(moveList,piece,2,8,4,6);
                            }
                            if(getPieceAt(board,0,6) == EMPTY || isBlack(getPieceAt(board,0,6)))
                            {
                                addMove(moveList,piece,2,8,0,6);
                            }
                        }
                        if(x==4 && y==6)
                        {
                            if(getPieceAt(board,2,4) == EMPTY || isBlack(getPieceAt(board,2,4)))
                            {
                                addMove(moveList,piece,4,6,2,4);
                            }
                            if(getPieceAt(board,2,8) == EMPTY || isBlack(getPieceAt(board,2,8)))
                            {
                                addMove(moveList,piece,4,6,2,8);
                            }
                        }
                        if(x==0 && y==6)
                        {
                            if(getPieceAt(board,2,4) == EMPTY || isBlack(getPieceAt(board,2,4)))
                            {
                                addMove(moveList,piece,0,6,2,4);
                            }
                            if(getPieceAt(board,2,8) == EMPTY || isBlack(getPieceAt(board,2,8)))
                            {
                                addMove(moveList,piece,0,6,2,8);
                            }
                        }
                        if(x==2 && y==4)
                        {
                            if(getPieceAt(board,4,2) == EMPTY || isBlack(getPieceAt(board,4,2)))
                            {
                                addMove(moveList,piece,2,4,4,2);
                            }
                            if(getPieceAt(board,2,2) == EMPTY || isBlack(getPieceAt(board,2,2)))
                            {
                                addMove(moveList,piece,2,4,2,2);
                            }
                            if(getPieceAt(board,4,6) == EMPTY || isBlack(getPieceAt(board,4,6)))
                            {
                                addMove(moveList,piece,2,4,4,6);
                            }
                            if(getPieceAt(board,2,6) == EMPTY || isBlack(getPieceAt(board,2,6)))
                            {
                                addMove(moveList,piece,2,4,2,6);
                            }
                        }
                        break;

                    case UPGSOLDIER:
                        x = i;
                        y = j;
                        if(x+1<10 && (getPieceAt(board,x+1,y) == EMPTY || isBlack(getPieceAt(board,x+1,y))))
                        {
                            addMove(moveList,piece,i,j,x+1,y);
                        }
                        if(y+1<9 && (getPieceAt(board,x,y+1) == EMPTY || isBlack(getPieceAt(board,x,y+1))))
                        {
                            addMove(moveList,piece,i,j,x,y+1);
                        }
                        if(y-1>=0 && (getPieceAt(board,x,y-1) == EMPTY || isBlack(getPieceAt(board,x,y-1))))
                        {
                            addMove(moveList,piece,i,j,x,y-1);
                        }
                        break;

                    case GENERAL:
                        x = i;
                        y = j;
                        if(x+1<2 && (getPieceAt(board,x+1,y) == EMPTY || isBlack(getPieceAt(board,x+1,y))))
                        {
                            addMove(moveList,piece,i,j,x+1,y);
                        }
                        if(x-1>=0 && (getPieceAt(board,x-1,y) == EMPTY || isBlack(getPieceAt(board,x-1,y))))
                        {
                            addMove(moveList,piece,i,j,x-1,y);
                        }
                        if(y+1<6 && (getPieceAt(board,x,y+1) == EMPTY || isBlack(getPieceAt(board,x,y+1))))
                        {
                            addMove(moveList,piece,i,j,x,y+1);
                        }
                        if(y-1>=3 && (getPieceAt(board,x,y-1) == EMPTY || isBlack(getPieceAt(board,x,y-1))))
                        {
                            addMove(moveList,piece,i,j,x,y-1);
                        }
                        break;

                    case HORSE:
                        x = i;
                        y = j;
                        if(x+2<10 && y+1<9 && getPieceAt(board,x+1,y) == EMPTY && (getPieceAt(board,x+2,y+1) == EMPTY || isBlack(getPieceAt(board,x+2,y+1))))
                        {
                            addMove(moveList,piece,i,j,x+2,y+1);
                        }
                        if(x-1>=0 && y+2<9 && getPieceAt(board,x,y+1) == EMPTY && (getPieceAt(board,x-1,y+2) == EMPTY || isBlack(getPieceAt(board,x-1,y+2))))
                        {
                            addMove(moveList,piece,i,j,x-1,y+2);
                        }
                        if(x-2>=0 && y-1>=0 && getPieceAt(board,x-1,y) == EMPTY && (getPieceAt(board,x-2,y-1) == EMPTY || isBlack(getPieceAt(board,x-2,y-1))))
                        {
                            addMove(moveList,piece,i,j,x-2,y-1);
                        }
                        if(x+1<10 && y-2>=0 && getPieceAt(board,x,y-1) == EMPTY && (getPieceAt(board,x+1,y-2) == EMPTY || isBlack(getPieceAt(board,x+1,y-2))))
                        {
                            addMove(moveList,piece,i,j,x+1,y-2);
                        }
                        if(x+2<10 && y-1>=0 && getPieceAt(board,x+1,y) == EMPTY && (getPieceAt(board,x+2,y-1) == EMPTY || isBlack(getPieceAt(board,x+2,y-1))))
                        {
                            addMove(moveList,piece,i,j,x+2,y-1);
                        }
                        if(x+1<10 && y+2<9 && getPieceAt(board,x,y+1) == EMPTY && (getPieceAt(board,x+1,y+2) == EMPTY || isBlack(getPieceAt(board,x+1,y+2))))
                        {
                            addMove(moveList,piece,i,j,x+1,y+2);
                        }
                        if(x-2>=0 && y+1<9 && getPieceAt(board,x-1,y) == EMPTY && (getPieceAt(board,x-2,y+1) == EMPTY || isBlack(getPieceAt(board,x-2,y+1))))
                        {
                            addMove(moveList,piece,i,j,x-2,y+1);
                        }
                        if(x-1>=0 && y-2>=0 && getPieceAt(board,x,y-1) == EMPTY && (getPieceAt(board,x-1,y-2) == EMPTY || isBlack(getPieceAt(board,x-1,y-2))))
                        {
                            addMove(moveList,piece,i,j,x-1,y-2);
                        }
                        break;

                    case CHARIOT:
                        x = i;
                        y = j;
                        while(x+1<10 && !isRed(getPieceAt(board,x+1,y)))
                        {
                            x++;
                            if(isBlack(getPieceAt(board,x,y)))
                            {
                                addMove(moveList,piece,i,j,x,y);
                                break;
                            }
                            else addMove(moveList,piece,i,j,x,y);
                        }
                        x = i;
                        while(x-1>=0 && !isRed(getPieceAt(board,x-1,y)))
                        {
                            x--;
                            if(isBlack(getPieceAt(board,x,y)))
                            {
                                addMove(moveList,piece,i,j,x,y);
                                break;
                            }
                            else addMove(moveList,piece,i,j,x,y);
                        }
                        x = i;
                        while(y+1<9 && !isRed(getPieceAt(board,x,y+1)))
                        {
                            y++;
                            if(isBlack(getPieceAt(board,x,y)))
                            {
                                addMove(moveList,piece,i,j,x,y);
                                break;
                            }
                            else addMove(moveList,piece,i,j,x,y);
                        }
                        y = j;
                        while(y-1>=0 && !isRed(getPieceAt(board,x,y-1)))
                        {
                            y--;
                            if(isBlack(getPieceAt(board,x,y)))
                            {
                                addMove(moveList,piece,i,j,x,y);
                                break;
                            }
                            else addMove(moveList,piece,i,j,x,y);
                        }
                        y = j;
                        break;

                    case CANNON:
                        x = i;
                        y = j;
                        int cover = 0;
                        while(x+1<10)
                        {
                            while(cover==0)
                            {
                                if(getPieceAt(board,x+1,y) != EMPTY)
                                {
                                    cover = 1;
                                    x++;
                                    break;
                                }
                                else
                                {
                                    addMove(moveList,piece,i,j,x+1,y);
                                    x++;
                                }
                                if(x==9) break;
                            }
                            if(cover==1)
                            {
                                if(x!= 9 && isBlack(getPieceAt(board,x+1,y)))
                                {
                                    addMove(moveList,piece,i,j,x+1,y);
                                    break;
                                }
                                else if(getPieceAt(board,x+1,y) == EMPTY) x++;
                                else if(isRed(getPieceAt(board,x+1,y))) break;
                            }
                        }
                        cover = 0;
                        x = i;
                        while(x-1>=0)
                        {
                            while(cover==0)
                            {
                                if(getPieceAt(board,x-1,y) != EMPTY)
                                {
                                    cover = 1;
                                    x--;
                                    break;
                                }
                                else
                                {
                                    addMove(moveList,piece,i,j,x-1,y);
                                    x--;
                                }
                                if(x==0) break;
                            }
                            if(cover==1)
                            {
                                if(x!= 0 && isBlack(getPieceAt(board,x-1,y)))
                                {
                                    addMove(moveList,piece,i,j,x-1,y);
                                    break;
                                }
                                else if(getPieceAt(board,x-1,y) == EMPTY) x--;
                                else if(isRed(getPieceAt(board,x-1,y))) break;
                            }
                        }
                        cover = 0;
                        x = i;
                        while(y+1<9)
                        {
                            while(cover==0)
                            {
                                if(getPieceAt(board,x,y+1) != EMPTY)
                                {
                                    cover = 1;
                                    y++;
                                    break;
                                }
                                else
                                {
                                    addMove(moveList,piece,i,j,x,y+1);
                                    y++;
                                }
                                if(y==8) break;
                            }
                            if(cover==1)
                            {
                                if(y != 8 && isBlack(getPieceAt(board,x,y+1)))
                                {
                                    addMove(moveList,piece,i,j,x,y+1);
                                    break;
                                }
                                else if(getPieceAt(board,x,y+1) == EMPTY) y++;
                                else if(isRed(getPieceAt(board,x,y+1))) break;
                            }
                        }
                        cover = 0;
                        y = j;
                        while(y-1>=0)
                        {
                            while(cover==0)
                            {
                                if(getPieceAt(board,x,y-1) != EMPTY)
                                {
                                    cover = 1;
                                    y--;
                                    break;
                                }
                                else
                                {
                                    addMove(moveList,piece,i,j,x,y-1);
                                    y--;
                                }
                                if(y==0) break;
                            }
                            if(cover==1)
                            {
                                if(y!=0 && isBlack(getPieceAt(board,x,y-1)))
                                {
                                    addMove(moveList,piece,i,j,x,y-1);
                                    break;
                                }
                                else if(getPieceAt(board,x,y-1) == EMPTY) y--;
                                else if(isRed(getPieceAt(board,x,y-1))) break;
                            }
                        }
                        cover = 0;
                        y = j;
                        break;
                    }
                }
            }

            else if(color == BLACK)
            {
                if(isBlack(getPieceAt(board,i,j)))
                {
                    switch(piece)
                    {
                    case SOLDIER + BLACK:
                        x = i;
                        y = j;
                        if(x-1>=0)
                        {
                            if(getPieceAt(board,x-1,y) == EMPTY || isRed(getPieceAt(board,x-1,y)))
                            {
                                addMove(moveList,piece,i,j,x-1,y);
                            }
                        }
                        break;

                    case ADVISOR + BLACK:
                        x = i;
                        y = j;
                        if(x==9&&y==3)
                        {
                            if(getPieceAt(board,8,4) == EMPTY || isRed(getPieceAt(board,8,4)))
                            {
                                addMove(moveList,piece,9,3,8,4);
                            }
                        }
                        if(x==7&&y==3)
                        {
                            if(getPieceAt(board,8,4) == EMPTY || isRed(getPieceAt(board,8,4)))
                            {
                                addMove(moveList,piece,7,3,8,4);
                            }
                        }
                        if(x==9&&y==5)
                        {
                            if(getPieceAt(board,8,4) == EMPTY || isRed(getPieceAt(board,8,4)))
                            {
                                addMove(moveList,piece,9,5,8,4);
                            }
                        }
                        if(x==7&&y==5)
                        {
                            if(getPieceAt(board,8,4) == EMPTY || isRed(getPieceAt(board,8,4)))
                               {
                                   addMove(moveList,piece,7,5,8,4);
                               }
                        }
                        if(x==8&&y==4)
                        {
                            if(getPieceAt(board,9,3) == EMPTY || isRed(getPieceAt(board,9,3)))
                            {
                                addMove(moveList,piece,8,4,9,3);
                            }
                            if(getPieceAt(board,7,3) == EMPTY || isRed(getPieceAt(board,7,3)))
                            {
                                addMove(moveList,piece,8,4,7,3);
                            }
                            if(getPieceAt(board,9,5) == EMPTY || isRed(getPieceAt(board,9,5)))
                            {
                                addMove(moveList,piece,8,4,9,5);
                            }
                            if(getPieceAt(board,7,5) == EMPTY || isRed(getPieceAt(board,7,5)))
                            {
                                addMove(moveList,piece,8,4,7,5);
                            }
                        }
                        break;

                    case ELEPHANT + BLACK:
                        x = i;
                        y = j;
                        if(x==9 && y==2)
                        {
                            if(getPieceAt(board,7,0) == EMPTY || isRed(getPieceAt(board,7,0)))
                            {
                                addMove(moveList,piece,9,2,7,0);
                            }
                            if(getPieceAt(board,7,4) == EMPTY || isRed(getPieceAt(board,7,4)))
                            {
                                addMove(moveList,piece,9,2,7,4);
                            }
                        }
                        if(x==7 && y==0)
                        {
                            if(getPieceAt(board,9,2) == EMPTY || isRed(getPieceAt(board,9,2)))
                            {
                                addMove(moveList,piece,7,0,9,2);
                            }
                            if(getPieceAt(board,5,2) == EMPTY || isRed(getPieceAt(board,5,2)))
                            {
                                addMove(moveList,piece,7,0,5,2);
                            }
                        }
                        if(x==5 && y==2)
                        {
                            if(getPieceAt(board,7,0) == EMPTY || isRed(getPieceAt(board,7,0)))
                            {
                                addMove(moveList,piece,5,2,7,0);
                            }
                            if(getPieceAt(board,7,4) == EMPTY || isRed(getPieceAt(board,7,4)))
                            {
                                addMove(moveList,piece,5,2,7,4);
                            }
                        }
                        if(x==9 && y==6)
                        {
                            if(getPieceAt(board,7,4) == EMPTY || isRed(getPieceAt(board,7,4)))
                            {
                                addMove(moveList,piece,9,6,7,4);
                            }
                            if(getPieceAt(board,7,8) == EMPTY || isRed(getPieceAt(board,7,8)))
                            {
                                addMove(moveList,piece,9,6,7,8);
                            }
                        }
                        if(x==7 && y==8)
                        {
                            if(getPieceAt(board,9,6) == EMPTY || isRed(getPieceAt(board,9,6)))
                            {
                                addMove(moveList,piece,7,8,9,6);
                            }
                            if(getPieceAt(board,5,6) == EMPTY || isRed(getPieceAt(board,5,6)))
                            {
                                addMove(moveList,piece,7,8,5,6);
                            }
                        }
                        if(x==5 && y==6)
                        {
                            if(getPieceAt(board,7,4) == EMPTY || isRed(getPieceAt(board,7,4)))
                            {
                                addMove(moveList,piece,5,6,7,4);
                            }
                            if(getPieceAt(board,7,8) == EMPTY || isRed(getPieceAt(board,7,8)))
                            {
                                addMove(moveList,piece,5,6,7,8);
                            }
                        }
                        if(x==7 && y==4)
                        {
                            if(getPieceAt(board,9,2) == EMPTY || isRed(getPieceAt(board,9,2)))
                            {
                                addMove(moveList,piece,7,4,9,2);
                            }
                            if(getPieceAt(board,5,2) == EMPTY || isRed(getPieceAt(board,5,2)))
                            {
                                addMove(moveList,piece,7,4,5,2);
                            }
                            if(getPieceAt(board,9,6) == EMPTY || isRed(getPieceAt(board,9,6)))
                            {
                                addMove(moveList,piece,7,4,9,6);
                            }
                            if(getPieceAt(board,5,6) == EMPTY || isRed(getPieceAt(board,5,6)))
                            {
                                addMove(moveList,piece,7,4,5,6);
                            }
                        }
                        break;

                    case UPGSOLDIER + BLACK:
                        x = i;
                        y = j;
                        if(x-1>0 && (getPieceAt(board,x-1,y) == EMPTY || isRed(getPieceAt(board,x-1,y))))
                        {
                            addMove(moveList,piece,i,j,x-1,y);
                        }
                        if(y+1<9 && (getPieceAt(board,x,y+1) == EMPTY || isRed(getPieceAt(board,x,y+1))))
                        {
                            addMove(moveList,piece,i,j,x,y+1);
                        }
                        if(y-1>=0 && (getPieceAt(board,x,y-1) == EMPTY || isRed(getPieceAt(board,x,y-1))))
                        {
                            addMove(moveList,piece,i,j,x,y-1);
                        }
                        break;

                    case GENERAL + BLACK:
                        x = i;
                        y = j;
                        if(x+1<10 && (getPieceAt(board,x+1,y) == EMPTY || isRed(getPieceAt(board,x+1,y))))
                        {
                            addMove(moveList,piece,i,j,x+1,y);
                        }
                        if(x-1>=7 && (getPieceAt(board,x-1,y) == EMPTY || isRed(getPieceAt(board,x-1,y))))
                        {
                            addMove(moveList,piece,i,j,x-1,y);
                        }
                        if(y+1<6 && (getPieceAt(board,x,y+1) == EMPTY || isRed(getPieceAt(board,x,y+1))))
                        {
                            addMove(moveList,piece,i,j,x,y+1);
                        }
                        if(y-1>=3 && (getPieceAt(board,x,y-1) == EMPTY || isRed(getPieceAt(board,x,y-1))))
                        {
                            addMove(moveList,piece,i,j,x,y-1);
                        }
                        break;

                    case HORSE + BLACK:
                        x = i;
                        y = j;
                        if(x+2<10 && y+1<9 && getPieceAt(board,x+1,y) == EMPTY && (getPieceAt(board,x+2,y+1) == EMPTY || isRed(getPieceAt(board,x+2,y+1))))
                        {
                            addMove(moveList,piece,i,j,x+2,y+1);
                        }
                        if(x-1>=0 && y+2<9 && getPieceAt(board,x,y+1) == EMPTY && (getPieceAt(board,x-1,y+2) == EMPTY || isRed(getPieceAt(board,x-1,y+2))))
                        {
                            addMove(moveList,piece,i,j,x-1,y+2);
                        }
                        if(x-2>=0 && y-1>=0 && getPieceAt(board,x-1,y) == EMPTY && (getPieceAt(board,x-2,y-1) == EMPTY || isRed(getPieceAt(board,x-2,y-1))))
                        {
                            addMove(moveList,piece,i,j,x-2,y-1);
                        }
                        if(x+1<10 && y-2>=0 && getPieceAt(board,x,y-1) == EMPTY && (getPieceAt(board,x+1,y-2) == EMPTY || isRed(getPieceAt(board,x+1,y-2))))
                        {
                            addMove(moveList,piece,i,j,x+1,y-2);
                        }
                        if(x+2<10 && y-1>=0 && getPieceAt(board,x+1,y) == EMPTY && (getPieceAt(board,x+2,y-1) == EMPTY || isRed(getPieceAt(board,x+2,y-1))))
                        {
                            addMove(moveList,piece,i,j,x+2,y-1);
                        }
                        if(x+1<10 && y+2<9 && getPieceAt(board,x,y+1) == EMPTY && (getPieceAt(board,x+1,y+2) == EMPTY || isRed(getPieceAt(board,x+1,y+2))))
                        {
                            addMove(moveList,piece,i,j,x+1,y+2);
                        }
                        if(x-2>=0 && y+1<9 && getPieceAt(board,x-1,y) == EMPTY && (getPieceAt(board,x-2,y+1) == EMPTY || isRed(getPieceAt(board,x-2,y+1))))
                        {
                            addMove(moveList,piece,i,j,x-2,y+1);
                        }
                        if(x-1>=0 && y-2>=0 && getPieceAt(board,x,y-1) == EMPTY && (getPieceAt(board,x-1,y-2) == EMPTY || isRed(getPieceAt(board,x-1,y-2))))
                        {
                            addMove(moveList,piece,i,j,x-1,y-2);
                        }
                        break;

                    case CHARIOT + BLACK:
                        x = i;
                        y = j;
                        while(x+1<10 && !isBlack(getPieceAt(board,x+1,y)))
                        {
                            x++;
                            if(isRed(getPieceAt(board,x,y)))
                            {
                                addMove(moveList,piece,i,j,x,y);
                                break;
                            }
                            else addMove(moveList,piece,i,j,x,y);
                        }
                        x = i;
                        while(x-1>=0 && !isBlack(getPieceAt(board,x-1,y)))
                        {
                            x--;
                            if(isRed(getPieceAt(board,x,y)))
                            {
                                addMove(moveList,piece,i,j,x,y);
                                break;
                            }
                            else addMove(moveList,piece,i,j,x,y);
                        }
                        x = i;
                        while(y+1<9 && !isBlack(getPieceAt(board,x,y+1)))
                        {
                            y++;
                            if(isRed(getPieceAt(board,x,y)))
                            {
                                addMove(moveList,piece,i,j,x,y);
                                break;
                            }
                            else addMove(moveList,piece,i,j,x,y);
                        }
                        y = j;
                        while(y-1>=0 && !isBlack(getPieceAt(board,x,y-1)))
                        {
                            y--;
                            if(isRed(getPieceAt(board,x,y)))
                            {
                                addMove(moveList,piece,i,j,x,y);
                                break;
                            }
                            else addMove(moveList,piece,i,j,x,y);
                        }
                        y = j;
                        break;

                    case CANNON + BLACK:
                        x = i;
                        y = j;
                        int cover = 0;
                        while(x+1<10)
                        {
                            while(cover==0)
                            {
                                if(getPieceAt(board,x+1,y) != EMPTY)
                                {
                                    cover = 1;
                                    x++;
                                    break;
                                }
                                else
                                {
                                    addMove(moveList,piece,i,j,x+1,y);
                                    x++;
                                }
                                if(x==9) break;
                            }
                            if(cover==1)
                            {
                                if(x!=9 && isRed(getPieceAt(board,x+1,y)))
                                {
                                    addMove(moveList,piece,i,j,x+1,y);
                                    break;
                                }
                                else if(getPieceAt(board,x+1,y) == EMPTY) x++;
                                else if(isBlack(getPieceAt(board,x+1,y))) break;
                            }
                        }
                        cover = 0;
                        x = i;
                        while(x-1>=0)
                        {
                            while(cover==0)
                            {
                                if(getPieceAt(board,x-1,y) != EMPTY)
                                {
                                    cover = 1;
                                    x--;
                                    break;
                                }
                                else
                                {
                                    addMove(moveList,piece,i,j,x-1,y);
                                    x--;
                                }
                                if(x==0) break;
                            }
                            if(cover==1)
                            {
                                if(x!=0 && isRed(getPieceAt(board,x-1,y)))
                                {
                                    addMove(moveList,piece,i,j,x-1,y);
                                    break;
                                }
                                else if(getPieceAt(board,x-1,y) == EMPTY) x--;
                                else if(isBlack(getPieceAt(board,x-1,y))) break;
                            }
                        }
                        cover = 0;
                        x = i;
                        while(y+1<9)
                        {
                            while(cover==0)
                            {
                                if(getPieceAt(board,x,y+1) != EMPTY)
                                {
                                    cover = 1;
                                    y++;
                                    break;
                                }
                                else
                                {
                                    addMove(moveList,piece,i,j,x,y+1);
                                    y++;
                                }
                                if(y==8) break;
                            }
                            if(cover==1)
                            {
                                if(y!=8 && isRed(getPieceAt(board,x,y+1)))
                                {
                                    addMove(moveList,piece,i,j,x,y+1);
                                    break;
                                }
                                else if(getPieceAt(board,x,y+1) == EMPTY) y++;
                                else if(isBlack(getPieceAt(board,x,y+1))) break;
                            }
                        }
                        cover = 0;
                        y = j;
                        while(y-1>=0)
                        {
                            while(cover==0)
                            {
                                if(getPieceAt(board,x,y-1) != EMPTY)
                                {
                                    cover = 1;
                                    y--;
                                    break;
                                }
                                else
                                {
                                    addMove(moveList,piece,i,j,x,y-1);
                                    y--;
                                }
                                if(y==0) break;
                            }
                            if(cover==1)
                            {
                                if(y!=0 && isRed(getPieceAt(board,x,y-1)))
                                {
                                    addMove(moveList,piece,i,j,x,y-1);
                                    break;
                                }
                                else if(getPieceAt(board,x,y-1) == EMPTY) y--;
                                else if(isBlack(getPieceAt(board,x,y-1))) break;
                            }
                        }
                        cover = 0;
                        y = j;
                        break;

                    }
                }
            }
        }
    }
    //printf("move list successfully created\n");
    return moveList;
}

char *moveToString(Move* move)
{
    char *str = (char*)malloc(5);
    sprintf(str,"%d%d%d%d\0",move->startRow,move->startCol,move->endRow,move->endCol);
    return str;
}

void printMoveList(MoveList *moveList)
{
    int i;
    Move *move;
    char *buff;
    int a,b,c,d;
    for(i=0;i<moveList->size;i++)
    {
        move = moveList->moves[i];
        //a=move->startRow;
        //b=move->startCol;
        //c=move->endRow;
        //d=move->endCol;
        //printf("%d%d%d%d; ",a,b,c,d);
        buff = moveToString(move);
        printf("%s;", buff);
        free(buff);
    }
    printf("\n");
}

void freeMoveList(MoveList *moveList)
{
    int i;
    for(i=0;i<moveList->size;i++)
    {
        free(moveList->moves[i]);
    }
    free(moveList->moves);
    //moveList = NULL;
    //moveList->moves = NULL;
    free(moveList);
}

Move* stringToMove(char *board,char *str)
{
    Move *move = (Move*)malloc(sizeof(Move));
    //printf("here1\n");
    move->startRow = str[0]-48;
    move->startCol = str[1]-48;
    move->endRow = str[2]-48;
    move->endCol = str[3]-48;
    //printf("here2\n");
    move->pieceId = getPieceAt(board,move->startRow,move->startCol);
    return move;
}


int validMove(MoveList *moveList, Move *move)
{
    int i;
    Move *tmpMove;
    for(i=0;i<moveList->size;i++)
    {
        tmpMove = moveList->moves[i];
        if(move->pieceId == tmpMove->pieceId)
        {
            if(move->startRow == tmpMove->startRow)
            {
                if(move->startCol == tmpMove->startCol)
                {
                    if(move->endRow == tmpMove->endRow)
                    {
                        if(move->endCol == tmpMove->endCol)
                        {
                            return 1;
                        }
                    }
                }
            }
        }
    }
    return 0;
}

int doMove(char *board, Move *move)
{
    int result = -1;//0 - not ended, 0 - RED won, 50 - BLACK won
    char pieceId = move->pieceId;
    char oldPiece;
    if(pieceId == SOLDIER && move->endRow == 5)
    {
        setPieceAt(board, move->startRow,move->startCol, EMPTY);
        setPieceAt(board, move->endRow,move->endCol, UPGSOLDIER);
    }
    else if(pieceId == (SOLDIER + BLACK) && move->endRow == 4)
    {
        setPieceAt(board, move->startRow,move->startCol, EMPTY);
        setPieceAt(board, move->endRow,move->endCol, UPGSOLDIER + BLACK);
    }
    else
    {
        oldPiece = getPieceAt(board,move->endRow,move->endCol);
        setPieceAt(board, move->startRow,move->startCol, EMPTY);
        setPieceAt(board, move->endRow, move->endCol,move->pieceId);
    }
    if(isRed(pieceId) && (oldPiece == (GENERAL + BLACK)))
    {
        result = RED;
    }
    if(isBlack(pieceId) && (oldPiece == GENERAL))
    {
        result = BLACK;
    }
    return result;
}

int undoMove(char *board,Move *move,char oldPiece)
{
    char pieceId = move->pieceId;
    if(pieceId == SOLDIER && move->endRow == 5)
    {
        setPieceAt(board, move->startRow,move->startCol, SOLDIER);
        setPieceAt(board, move->endRow,move->endCol, oldPiece);
    }
    else if(pieceId == (SOLDIER + BLACK) && move->endRow == 4)
    {
        setPieceAt(board, move->startRow,move->startCol, SOLDIER + BLACK);
        setPieceAt(board, move->endRow,move->endCol, oldPiece);
    }
    else
    {
        setPieceAt(board, move->startRow,move->startCol, pieceId);
        setPieceAt(board, move->endRow, move->endCol,oldPiece);
    }
}

Move *getBestMove(char *board,int color)
{
    MoveList *list = getAllPossibleMoves(board,color);
    char *tmpBoard = makeNewBoard();
    Move *curMove;
    Move *resultMove;
    int score;
    int max = -20000;
    int i;
    for(i=0;i<list->size;i++)
    {
        cloneBoard(board,tmpBoard);
        curMove = list->moves[i];
        doMove(tmpBoard,curMove);
        score = calculateBoard(tmpBoard,color);
        if(score >= max)
        {
            max = score;
            resultMove = curMove;
        }
    }
    free(list);
    return resultMove;
    freeBoard(tmpBoard);
}

Move* bestMove(char *board,int depth,int alpha,int beta,int comColor,int maxColor)
{
    int oppColor;
    if(maxColor == RED) oppColor = BLACK;
    else if(maxColor == BLACK) oppColor = RED;
    Move *curMove;
    Move *tmpMove;
    Move *resultMove = (Move*)malloc(sizeof(Move));
    int i,j;
    int v;
    int max,min;
    int bestScore;
    int score;
    MoveList *moveList;
    char *tmpBoard = makeNewBoard();
    
    //printf("Chay best move: %d!!\n",depth);
    //printBoard(board);
    if(depth == 0)
    {
        //printf("depth = 0\n");
        bestScore = -20000;
        moveList = getAllPossibleMoves(board,maxColor);
        for(i=0;i<moveList->size;i++)
        {
            cloneBoard(board,tmpBoard);
            //printBoard(tmpBoard);
            curMove = moveList->moves[i];
            //printf("Curmove: %s\n",moveToString(curMove));
            doMove(tmpBoard,curMove);
            //printBoard(tmpBoard);
            score = calculateBoard(tmpBoard,maxColor);
            if(score >= bestScore)
            {
                bestScore = score;
                cloneMove(resultMove,curMove);
            }
        }
        
        //free(curMove);
        //freeBoard(tmpBoard);
        freeMoveList(moveList);
        freeBoard(tmpBoard);
        //printf("Result: %s of depth %d\n",moveToString(resultMove),depth);
        //printf("Best Score: %d\n", bestScore);
        return resultMove;
    }
    
    if(maxColor != comColor)
    {
        //printf("depth !=0\n");
        bestScore = 20000;
        moveList = getAllPossibleMoves(board,maxColor);
        
        for(i=0;i<moveList->size;i++)
        {
            cloneBoard(board,tmpBoard);
            curMove = moveList->moves[i];
            doMove(tmpBoard,curMove);
            tmpMove = bestMove(tmpBoard,depth-1,alpha,beta,comColor,oppColor);
            doMove(tmpBoard,tmpMove);
            score = calculateBoard(tmpBoard,comColor);
            free(tmpMove);
            if(score < bestScore)
            {
                bestScore = score;
                cloneMove(resultMove,curMove);
            }
            if(bestScore <= beta)
            {
                beta = bestScore;
            }
            if(beta <= alpha)  
            {
                //printf("beta <= alpha\n");
                break;
            }
        }
    }
    
    if(maxColor == comColor)
    {
        //printf("depth !=0\n");
        bestScore = -20000;
        moveList = getAllPossibleMoves(board,maxColor);
        
        for(i=0;i<moveList->size;i++)
        {
            cloneBoard(board,tmpBoard);
            curMove = moveList->moves[i];
            //printf("curmove: %s\n",moveToString(curMove));
            doMove(tmpBoard,curMove);
            tmpMove = bestMove(tmpBoard,depth -1,alpha,beta,comColor,oppColor);
            doMove(tmpBoard,tmpMove);
            score = calculateBoard(tmpBoard,comColor);
            free(tmpMove);
            if(score >= bestScore)
            {
                bestScore = score;
                cloneMove(resultMove,curMove);
            }
            if(bestScore >= alpha)
            {
                alpha = bestScore;
            }
            if(beta <= alpha)   
            {
                //printf("beta <= alpha\n");
                break;
            }
        }
    }
    
    //free(curMove);
    //free(tmpMove);
    freeMoveList(moveList);
    freeBoard(tmpBoard);
    //printf("Result: %s of depth %d\n",moveToString(resultMove),depth);
    //printf("Best Score: %d\n", bestScore);
    return resultMove;
    
}


