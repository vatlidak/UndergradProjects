/*
 * Part: 2.1 Record Management Module
 *
 * Authors: Atlidakis Vaggelis, Aggelogiannopoulos Aris, Kuriazof Xristina
 * AM: 	    1115200500010, 1115200500004, 1115200600267
 * 
 * Date: 1.12.2009
 *
 */

H metaglwtissi egine sto linux01.di.uoa.gr
ParaQetw mazi ta dika sas .o kai .h gia twn
proigoumenwn epipedwn.
Metaglwtissi:

gcc -c RMM_Lib.c;
gcc -c main41.c;
gcc -c main42.c;
gcc -c main43.c;
gcc -o exe1 main41.o RMM_Lib.o BF_Lib.o;
gcc -o exe2 main42.o RMM_Lib.o BF_Lib.o;
gcc -o exe3 main43.o RMM_Lib.o BF_Lib.o;

