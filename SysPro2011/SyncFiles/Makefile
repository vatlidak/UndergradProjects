PARSEROBJ	= parser.o
MD5_LIBOBJ	= MD5_Lib.o
SERVEROBJ	= server.o 
CLIENTOBJ	= client.o
LISTOBJ		= list.o
SOCKETLEVELOBJ	= socketlevel.o
SOURCE		= parser.c server.c clientent.c list.c socketlevel.c
SERVER		= server
CLIENT		= client
CC		= gcc
FLAGS		= -c
# -g option enables debugging mode
# -c flag generates object code for separate files
# -lm for <math.h>

all:	$(PARSEROBJ) $(SERVEROBJ) $(LISTOBJ) $(CLIENTOBJ) $(SOCKETLEVELOBJ)
	$(CC) $(SERVEROBJ) $(PARSEROBJ) $(LISTOBJ) $(MD5_LIBOBJ) $(SOCKETLEVELOBJ) -o $(SERVER) -pthread
	$(CC) $(CLIENTOBJ) $(PARSEROBJ) $(LISTOBJ) $(MD5_LIBOBJ) $(SOCKETLEVELOBJ) -o $(CLIENT) -pthread

# create/compile the individual files >>separately<<
server.o: server.c
	$(CC) $(FLAGS) server.c

client.o: client.c
	$(CC) $(FLAGS) client.c

parser.o: parser.c
	$(CC) $(FLAGS) parser.c

list.o: list.c
	$(CC) $(FLAGS) list.c

socketlevel.o: socketlevel.c
	$(CC) $(FLAGS) socketlevel.c

# clean house
clean:
	rm -f *.o $(SERVER) $(CLIENT)

# do a bit of accounting
count:
	wc $(SOURCE)
