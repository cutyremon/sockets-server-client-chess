#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/sendfile.h>
#include "ChessMove.h"
#include "ChessBoard.h"

#define PORT 5500
#define BACKLOG 20

void clean_stdin(void)
{
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}

void sig_chld(int signo){
	pid_t pid;
	int stat;
	while((pid=waitpid(-1,&stat,WNOHANG))>0)
		printf("[ForkingServer] Child %d terminated\n",pid);
}

void ToUpperString(char input[])
{
    int i;
    for(i=0; i<strlen(input); i++) {
        input[i] = toupper(input[i]);
    }
}

void sendFiles(int conn_sock,char *fileName)
{
    socklen_t       sock_len;
    ssize_t len;
    int fd;
    int sent_bytes = 0;
    char file_size[256];
    struct stat file_stat;
    off_t offset;
    int remain_data;
    int turn = 0;

    fd = open(fileName,O_RDONLY);
    if(fd == -1)
    {
        exit(EXIT_FAILURE);
    }

    if(fstat(fd,&file_stat) < 0)
    {
        exit(EXIT_FAILURE);
    }

    sprintf(file_size, "%d", file_stat.st_size);

    len = send(conn_sock, file_size, sizeof(file_size),0);
    if(len < 0)
    {
        exit(EXIT_FAILURE);
    }

    //fprintf(stdout, "Server sent %d bytes for the size\n", len);

    offset = 0;
    remain_data = file_stat.st_size;

    while (remain_data > 0)
        {
			sent_bytes = sendfile(conn_sock, fd, &offset, BUFSIZ);
        	//printf("turn: %d\n", turn);
            //fprintf(stdout, "1. Server sent %d bytes from file's data, offset is now : %d and remaining data = %d\n", sent_bytes, offset, remain_data);
            remain_data -= sent_bytes;
            turn++;
            fprintf(stdout, " Server sent %d bytes from file's data, offset is now : %d and remaining data = %d\n", sent_bytes, offset, remain_data);
        }
        printf("Finished sending log files\n");
        close(fd);
}

int main(){

	int listen_sock, conn_sock; /* file descriptors */
	char recv_data[1024];
	int bytes_sent, bytes_received;
	struct sockaddr_in server; /* server's address information */
	struct sockaddr_in client; /* client's address information */
	pid_t pid;
	int sin_size;
	int file_size = 0;
    char *buffer;
    char buff[1024];
    int result = -1;
    int count = 0;

	if ((listen_sock=socket(AF_INET, SOCK_STREAM, 0)) == -1 ){  /* calls socket() */
		printf("socket() error\n");
		exit(-1);
	}
	bzero(&server, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(PORT);   /* Remember htons() from "Conversions" section? =) */
	server.sin_addr.s_addr = htonl(INADDR_ANY);  /* INADDR_ANY puts your IP address automatically */

	if(bind(listen_sock,(struct sockaddr*)&server,sizeof(server))==-1){ /* calls bind() */
		printf("bind() error\n");
		exit(-1);
	}

	if(listen(listen_sock,BACKLOG) == -1){  /* calls listen() */
		printf("listen() error\n");
		exit(-1);
	}

	while(1){

		sin_size=sizeof(struct sockaddr_in);
		if ((conn_sock = accept(listen_sock,(struct sockaddr *)&client,&sin_size))==-1){ /* calls accept() */
			printf("accept() error\n");
			exit(-1);
		}
		else count++;

		if((pid=fork())==0){
			int step = 0;
			char fileName[15];
			int humanColor,comColor;
			int turn = RED;
			int depth;
			char* board = makeNewBoard();
			//MoveList *moveList;
			Move *move;
			
			close(listen_sock);
			//printf("count: %d\n",count);
			sprintf(fileName,"chesslog%d.txt",count);
			//printf("%s\n",fileName);
			printf("You got a connection from %s\n",inet_ntoa(client.sin_addr) ); /* prints client's IP */
			bytes_sent = send(conn_sock,"Welcome to my chinese chess server.\nInput 1 to choose RED. press 2 to choose BLACK:\n",85,0); /* send to the client welcome message */
			if (bytes_sent < 0){
				printf("\nError!Can not sent data to client!");
				close(conn_sock);
				exit(-1);
			}
			bytes_received = recv(conn_sock,recv_data,1024,0);
			if(bytes_received == -1){
				printf("\nError!Cannot receive data from client!\n");
				close(conn_sock);
				exit(-1);
			}
			buff[bytes_received] = '\0';
			strcpy(buff,recv_data);
			FILE *f = fopen(fileName,"w");
			fprintf(f,"%s\n",inet_ntoa(client.sin_addr));

			if(strcmp(buff,"1") == 0) 
			{
				humanColor = RED;
				comColor = BLACK;
				printf("Human choose RED\n");
				fprintf(f,"%s\n","HUMAN IS RED - COMPUTER IS BLACK");
			}
			else
			{
				humanColor = BLACK;
				comColor = RED;
				printf("Human choose BLACK\n");
				fprintf(f,"%s\n","HUMAN IS BLACK - COMPUTER IS RED");
			}
			
			bytes_sent = send(conn_sock,"Choose computer level(0-3)\0",27,0); /* send to the client welcome message */
			if (bytes_sent < 0){
				printf("\nError!Can not sent data to client!");
				close(conn_sock);
				exit(-1);
			}
			//printf("vao day\n");
			bytes_received = recv(conn_sock,recv_data,1024,0);
			if(bytes_received == -1){
				printf("\nError!Cannot receive data from client!\n");
				close(conn_sock);
				exit(-1);
			}	
			//printf("received computer level\n");
			buff[bytes_received] = '\0';
			strcpy(buff,recv_data);
			depth = atoi(buff);
			printf("received computer level\n");
			fprintf(f,"COMPUTER LEVEL IS: %d\n",depth);
		while(result == -1)
		{
			int play = 0;
			//printBoard(board);
			if(turn == humanColor && play == 0)
			{
			//printf("here\n");
			bytes_sent = send(conn_sock,"Input your next move\n",21,0); /* send to the client welcome message */
			if (bytes_sent < 0){
				printf("\nError!Can not sent data to client!");
				close(conn_sock);
				exit(-1);
			}
			//printf("alrdy sent\n");
			bytes_received = recv(conn_sock,recv_data,1024,0);
			if(bytes_received == -1){
				printf("\nError!Cannot receive data from client!\n");
				close(conn_sock);
				exit(-1);
			}
			buff[bytes_received] = '\0';
			//printf("alrdy recv\n");
			strcpy(buff,recv_data);
			//printf("%d\n",strcmp(buff,"quit"));
			if(strcmp(buff,"quit") == 0) 
			{
				freeBoard(board);
				close(conn_sock);
				exit(0);
				break;
			}
			else 
			//printf("Human's move is: %s\n",buff);
			move = stringToMove(board,buff);
			result = doMove(board,move);
			fprintf(f,"%s\n",buff);
			//printf("result: %d\n",result);
			free(move);
			//free(moveList);
			play = 1;
			turn = comColor;
			
			}
			
			else if(turn == comColor && play == 0)
			{
				printf("comp play\n");
				//printBoard(board);
				//printf("movelist ready\n");
				move = bestMove(board,depth,-20000,20000,comColor,comColor);
				buffer = moveToString(move);
				//printf("got move\n");
				strcpy(buff,buffer);
				free(buffer);
				bytes_sent = send(conn_sock,buff,sizeof(buff),0); /* send to the client welcome message */
				if (bytes_sent < 0){
					printf("\nError!Can not sent data to client!");
					close(conn_sock);
					exit(-1);
				}
				//printf("alrd sent: %s\n",buff);
				result = doMove(board,move);
				fprintf(f,"%s\n",buff);
				//printf("result: %d\n",result);
				free(move);
				turn = humanColor;
				play = 1;
			}

		}
		if(result == humanColor)
		{
			printf("Human's won!!\n");
			fprintf(f,"Human's won\n");
			bytes_sent = send(conn_sock,"You've won\n",11,0); /* send to the client welcome message */
			if (bytes_sent < 0){
				printf("\nError!Can not sent data to client!");
				close(conn_sock);
				exit(-1);
			}
		}
		else if(result == comColor)
		{
			printf("Server's won!!\n");
			fprintf(f,"Server's won\n");
			bytes_sent = send(conn_sock,"You've lost\n",12,0); /* send to the client welcome message */
			if (bytes_sent < 0){
				printf("\nError!Can not sent data to client!");
				close(conn_sock);
				exit(-1);
			}
		}
		
		
		fclose(f);
		freeBoard(board);
		sendFiles(conn_sock,fileName);
		
        close(conn_sock);
		exit(0);
		}

		signal(SIGCHLD,sig_chld);

		//close(conn_sock);
	}
	close(listen_sock);
	return 1;
}
