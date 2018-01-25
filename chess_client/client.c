#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>

#include <string.h>
#include "ChessMove.h"
#include "ChessBoard.h"

void clean_stdin(void)
{
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}

void recvFiles(int client_sock)
{
    ssize_t len;
    char buffer[BUFSIZ];
    int file_size;
    int remain_data = 0;
    int turn = 0;
    FILE *received_file = fopen("mychesslog1.txt","w");

    recv(client_sock, buffer, BUFSIZ, 0);
    file_size = atoi(buffer);
    fprintf(stdout, "\nFile size : %d\n", file_size);
    if(received_file == NULL) exit(EXIT_FAILURE);

            remain_data = file_size;

        while (remain_data > 0)
        {
        	len = recv(client_sock, buffer, BUFSIZ, 0);
        	if(len <= 0) break;
        	//printf("turn: %d\n", turn);
                if(fwrite(buffer, sizeof(char), len, received_file) != len)
                {
                    printf("cant write to file\n");
                }
                remain_data -= len;
                //printf("buffer: %s\n", buffer);
                fprintf(stdout, "Receive %d bytes and we hope : %d bytes\n", len, remain_data);
                turn++;
        }
        
        printf("alrdy received log file\n");
        fclose(received_file);
}

int main(){
    char addr[50];
    int server_port;
	int client_sock;
    char buff[1024];
    struct sockaddr_in server_addr;
    int bytes_sent,bytes_received;
    char tmp[1024];
    char * buffer;
    int step;
    int color,comColor;
    char *board = makeNewBoard();
    MoveList *moveList;
    Move *move;
    int turn = RED;
    int result = -1;

    
    //printf("Input server's IP address: ");
    //scanf("%s",addr);
    //printf("\nInput port number: ");
    //scanf("%d",&server_port);
	client_sock=socket(AF_INET,SOCK_STREAM,0);
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(5500);
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");



	if(connect(client_sock,(struct sockaddr*)&server_addr,sizeof(struct sockaddr))!=0){
		printf("\nError!Can not connect to sever!Client exit imediately! ");
		return 0;
	}

	bytes_received = recv(client_sock,buff,1024,0);
	if(bytes_received == -1){
		printf("\nError!Cannot receive data from sever!\n");
		close(client_sock);
		exit(0);
	}
	    if(bytes_received == 0){
		    printf("\nServer has been shut down!\n");
		    close(client_sock);
		    exit(0);
	    }
	buff[bytes_received] = '\0';
	puts(buff);
	scanf("%s", tmp);
	if(strcmp(tmp,"1") == 0)
	{
	    color = RED;
	    comColor = BLACK;
	}
	else if(strcmp(tmp,"2") == 0)
	{
	    color = BLACK;
	    comColor = RED;
	}
	bytes_sent = send(client_sock, tmp, sizeof(tmp), 0);
    if(bytes_sent == -1) {
        printf("\nError! Cannot send data to sever!\n");
        close(client_sock);
        return 1;
    }
	bytes_received = recv(client_sock,buff,1024,0);
	if(bytes_received == -1){
		printf("\nError!Cannot receive data from sever!\n");
		close(client_sock);
		exit(0);
	}
	if(bytes_received == 0){
		    printf("\nServer has been shut down!\n");
		    close(client_sock);
		    exit(0);
	}
	buff[bytes_received] = '\0';
	puts(buff);
	scanf("%s", tmp);
	bytes_sent = send(client_sock, tmp, sizeof(tmp), 0);
    if(bytes_sent == -1) {
        printf("\nError! Cannot send data to sever!\n");
        close(client_sock);
        return 1;
    }
    printf("sent computer level\n");
	while(result == -1)
	{
		//system("clear");
	    int play = 0;
	    //printf("here\n");
	    //printf("turn: %d, color: %d\n",turn,color);
	    printf("vao day\n");
	    
	    
	    //printMoveList(moveList);
	    if(turn == color && play == 0)
	    {
	    //printf("vao day\n");
	    moveList = getAllPossibleMoves(board,color);
	    if(color == RED) printBoard(board);
	    else if(color == BLACK) printReverseBoard(board);
        bytes_received = recv(client_sock,buff,1024,0);
	    if(bytes_received == -1){
		    printf("\nError!Cannot receive data from sever!\n");
		    close(client_sock);
		    exit(0);
	    }
	    if(bytes_received == 0){
		    printf("\nServer has been shut down!\n");
		    close(client_sock);
		    exit(-1);
	    }
	    buff[bytes_received] = '\0';
	    printf("%s\n",buff);
	    clean_stdin();
	    scanf("%s",tmp);
	    if(strcmp(tmp,"quit") == 0 )
	    	{
	    		bytes_sent = send(client_sock, tmp, sizeof(tmp), 0);
        		if(bytes_sent == -1) {
            		printf("\nError! Cannot send data to sever!\n");
            		close(client_sock);
            		return 1;
        		}
	        	close(client_sock);
	        	return 0;
	        }
	    move = stringToMove(board,tmp);
	    //printf("chay vao day\n");
	    while(validMove(moveList,move) == 0)
	    {
	        printf("invalid move!! Input a valid move: ");
	        clean_stdin();
	        scanf("%s",tmp);
	        if(strcmp(tmp,"quit") == 0 ) 
	        {
	        	bytes_sent = send(client_sock, tmp, sizeof(tmp), 0);
        		if(bytes_sent == -1) {
            		printf("\nError! Cannot send data to sever!\n");
            		close(client_sock);
            		return 1;
        		}
	        	close(client_sock);
	        	return 0;
	        }
	        move = stringToMove(board,tmp);
	    }
	    //printf("chay vao day\n");
	    
	    bytes_sent = send(client_sock, tmp, sizeof(tmp), 0);
        if(bytes_sent == -1) {
            printf("\nError! Cannot send data to sever!\n");
            close(client_sock);
            return 1;
        }
        
        
        result = doMove(board,move);
	    turn = comColor;
	    play = 1;
	    free(move);
	    freeMoveList(moveList);
	    }
	    
	    else if(turn == comColor && play == 0)
	    {
	        printf("comp play\n");
	        bytes_received = recv(client_sock,buff,1024,0);
	        if(bytes_received == -1){
		        printf("\nError!Cannot receive data from sever!\n");
		        close(client_sock);
		        exit(0);
	        }
	        if(bytes_received == 0){
		        printf("\nServer has been shut down!\n");
		        close(client_sock);
		        exit(-1);
	        }

	        buff[bytes_received] = '\0';
	        strcpy(tmp,buff);
	        printf("alrd received: %s\n",tmp);
	        move = stringToMove(board,tmp);
	        result = doMove(board,move);
	    	if(color == RED) printBoard(board);
	    	else if(color == BLACK) printReverseBoard(board);
	        free(move);
	        turn = color;
	        play = 1;
	    }
	}
		    bytes_received = recv(client_sock,buff,1024,0);
	        if(bytes_received == -1){
		        printf("\nError!Cannot receive data from sever!\n");
		        close(client_sock);
		        exit(0);
	        }
	        if(bytes_received == 0){
		        printf("\nServer has been shut down!\n");
		        close(client_sock);
		        exit(-1);
	        }

	        buff[bytes_received] = '\0';
	        puts(buff);
	        
	        recvFiles(client_sock);
	        //fclose(f);
	        
	        //(client_sock);
	    
	close(client_sock);
	return 0;
}
