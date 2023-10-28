CC = gcc
CFLAGS = -Wall -g

CLIENT_SRC = client.c Handlers_Cli.h serv_cli_fifo.h
SERVER_SRC = server.c Handlers_Serv.h serv_cli_fifo.h

CLIENT_OBJ = client.o
SERVER_OBJ = server.o

all: client server

client: $(CLIENT_OBJ)
	$(CC) -o $@ $(CLIENT_OBJ)

server: $(SERVER_OBJ)
	$(CC) -o $@ $(SERVER_OBJ)

%.o: %.c
	$(CC) -c $<

client.o: $(CLIENT_SRC)
server.o: $(SERVER_SRC)
