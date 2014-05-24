#
# Makefile for Exercise4
#

all: 		main dict CompDecomp 	exe


main:	main.c
		gcc -c main.c

dict:	dict.c
	     gcc -c dict.c
	          
CompDecomp:	CompDecomp.c
		gcc -c  CompDecomp.c 
			
exe:		main.o dict.o CompDecomp.o bit_io_linux.o
		gcc -g -o  exe main.o dict.o CompDecomp.o bit_io_linux.o -lm
			
clean:		
		rm -rf main.o dict.o CompDecomp.o
		
count:		
		wc *.h *.c	
