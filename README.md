# sockets-server-client-chess
#tcp socket.
#da tien trinh
#AI : minimax 
#setup chess_server/
-gcc -o chess_server server.c ChessBoard.c ChessMove.c
#setup chess_client/
-gcc -o chess_client client.c ChessBoard.c ChessMove.c
#run server
./chess_server
./chess_client
