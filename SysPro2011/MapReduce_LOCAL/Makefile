#
# In order to execute this "Makefile" just type "make"


OBJS 	= records.o buffers.o pipeLevel.o MapReduce.o sort.o mapreduce_index.o
SOURCE	= records.c buffers.c pipeLevel.c MapReduce.c
HEADER  = records.h buffers.h pipeLevel.h mapreduce.h
OUT  	= myexe
CC	= gcc
FLAGS   = -g -c 
# -g option enables debugging mode 
# -c flag generates object code for separate files

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT)

# create/compile the individual files >>separately<< 
MapReduce.o: MapReduce.c
	$(CC) $(FLAGS) MapReduce.c

buffers.o: buffers.c
	$(CC) $(FLAGS) buffers.c

pipeLevel.o: pipeLevel.c
	$(CC) $(FLAGS) pipeLevel.c

records.o: records.c
	$(CC) $(FLAGS) records.c


# do a bit of accounting
count:
	wc $(SOURCE) $(HEADER)
