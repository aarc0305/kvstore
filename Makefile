CC = gcc

a.out: eventloop.o el_kqueue.o server.o network.o
	$(CC) eventloop.o el_kqueue.o server.o network.o

eventloop.o: eventloop.c
	$(CC) -c eventloop.c

el_kqueue.o: el_kqueue.c
	$(CC) -c el_kqueue.c

server.o: server.c
	$(CC) -c server.c

network.o: network.c
	$(CC) -c network.c

clean:
	rm -rf *.o