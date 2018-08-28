CC = gcc

a.out: datastructure.o eventloop.o el_kqueue.o server.o network.o
	$(CC) datastructure.o eventloop.o el_kqueue.o server.o network.o

datastructure.o: datastructure.c
	$(CC) -c datastructure.c

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