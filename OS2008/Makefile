#
# In order to execute this "Makefile" just type "make"
#	V. Atlidakis (std05010@di.uoa.gr)
#
OBJS 		= mybaya.o Baya_Lib.o supportfunct.o 
COMPRESSOBJ 	= compress.o
SOURCE		= mybaya.c Baya_Lib.c supportfunct.c compress.c
HEADER  	= Baya_Lib.h supportfunct.h
OUT  		= mybaya
COMPRESSOUT 	= compress
CC		= gcc
FLAGS   	= -g -c 
# -g option enables debugging mode 
# -c flag generates object code for separate files

all: $(OBJS) $(COMPRESSOBJ)
	$(CC) -g $(OBJS) -o $(OUT) 
	$(CC) -g $(COMPRESSOBJ) -o $(COMPRESSOUT)


# create/compile the individual files >>separately<< 
mybaya.o: mybaya.c
	$(CC) $(FLAGS) mybaya.c

Baya_Lib.o: Baya_Lib.c
	$(CC) $(FLAGS) Baya_Lib.c

supportfunct.o: supportfunct.c
	$(CC) $(FLAGS) supportfunct.c

compress.o: compress.c
	$(CC) $(FLAGS) compress.c
# clean house
clean:
	rm -f *.o $(OBJS) $(OUT) $(COMPRESSOBJ) $(COMPRESSOUT)

# do a bit of accounting
count:
	wc $(SOURCE) $(HEADER)
