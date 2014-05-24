#
# In order to execute this "Makefile" just type "make"


OBJS 	= records.o buffers.o MapReduce_threaded.o sort.o mapreduce_index.o
SOURCE	= records.c buffers.c MapReduce_threaded.c
HEADER  = records.h buffers.h mapreduce.h
OUT  	= myexe
CC	= gcc
FLAGS   = -g -c 
# -g option enables debugging mode 
# -c flag generates object code for separate files

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) -pthread

# create/compile the individual files >>separately<< 
MapReduce_threaded.o: MapReduce_threaded.c
	$(CC) $(FLAGS) MapReduce_threaded.c

buffers.o: buffers.c
	$(CC) $(FLAGS) buffers.c

records.o: records.c
	$(CC) $(FLAGS) records.c


# do a bit of accounting
count:
	wc $(SOURCE) $(HEADER)
