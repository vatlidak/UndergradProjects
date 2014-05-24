/*A.M.: 1115 2005 00010 */
/*ATLIDAKIS VAGGELIS	*/
/*std05010@di.uoa.gr	*/

H metaglwtisi kai ektelesi egine sto linux05.di.uoa.gr.


Gia metaglwtissi: 

gcc -c main21.c;
gcc -c main22.c;
gcc -c My_Lib.c;
gcc -c BMM_Lib.c;
gcc -o myexe21 main21.o BMM_Lib.o HDF_Lib.o FMM_Lib.o My_Lib.o;
gcc -o myexe22 main22.o BMM_Lib.o HDF_Lib.o FMM_Lib.o My_Lib.o;

