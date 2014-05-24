#AtliD vaggelis

MAIN1OBJ	= main1.o
MAIN2OBJ	= main2.o
MAIN3OBJ	= main3.o
HDF_LIBOBJ	= HDF_Lib.o
FMM_LIBOBJ	= FMM_Lib.o
HEADER1		= BF_Defines.h
HEADER2		= HDF_Lib.h
HEADER3		= FMM_Lib.h
SOURCE		= main1.c main2.c main3.c HDF_Lib.c FMM_Lib.c
MYEXE1		= myexe1
MYEXE2		= myexe2
MYEXE3		= myexe3
CC		= gcc
FLAGS		= -g -c
# -g option enables debugging mode
# -c flag generates object code for separate files


all:	$(MAIN1OBJ) $(MAIN2OBJ) $(MAIN3OBJ) $(HDF_LIBOBJ) $(FMM_LIBOBJ)
	$(CC) -g $(MAIN1OBJ) $(HDF_LIBOBJ) $(FMM_LIBOBJ) -o $(MYEXE1) 
	$(CC) -g $(MAIN2OBJ) $(HDF_LIBOBJ) $(FMM_LIBOBJ) -o $(MYEXE2) 
	$(CC) -g $(MAIN3OBJ) $(HDF_LIBOBJ) $(FMM_LIBOBJ) -o $(MYEXE3) 

# create/compile the individual files >>separately<<
main1.o: main1.c
	$(CC) $(FLAGS) main1.c

main2.o: main2.c
	$(CC) $(FLAGS) main2.c
	
main3.o: main3.c
	$(CC) $(FLAGS) main3.c

HDF_Lib.o: HDF_Lib.c
	$(CC) $(FLAGS) HDF_Lib.c
	
FMM_Lib.o: FMM_Lib.c
	$(CC) $(FLAGS) FMM_Lib.c


# clean house
clean:
	rm -f *.o $(MYEXE1) $(MYEXE2) $(MYEXE3) 

# do a bit of accounting
count:
	wc $(SOURCE) $(HEADER1) $(HEADER2) $(HEADER3) 
