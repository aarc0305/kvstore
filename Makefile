CC = gcc

kvserver: command_handler.o compiler.o datastructure.o eventloop.o el_select.o server.o network.o
	$(CC) -o kvserver command_handler.o compiler.o datastructure.o eventloop.o el_select.o server.o network.o

command_handler.o: command_handler.c
	$(CC) -c command_handler.c

compiler.o: compiler.c
	$(CC) -c compiler.c

datastructure.o: datastructure.c
	$(CC) -c datastructure.c

eventloop.o: eventloop.c
	$(CC) -c eventloop.c

el_select.o: el_select.c
	$(CC) -c el_select.c

server.o: server.c
	$(CC) -c server.c

network.o: network.c
	$(CC) -c network.c

clean:
	rm -rf *.o