/* FileName: ReadMe.txt
 *
 *
 * author: 	Atlidakis Vaggelis 
 * 
 * std05010@di.uoa.gr
 * A.M.:1115200500010
 * 
 */
Gia to part1.3,
Paradidw ta arxeia: BF_Lib.c, BF_Lib.h, BF_Defines.h
kai ta DIKA sas FMM_Lib.o, BMM_Lib.o, HDF_Lib.o kai .h apo ta proigoumena epipeda.
Den Vazw tis main mesa sto fakelo gia na min exei polu megalo megeQos.


Metaglwtisi se linux:

gcc -c main31.c;
gcc -c main32.c;
gcc -c main33.c;
gcc -c BF_Lib.c;
gcc -o exe1 main31.o BF_Lib.o BMM_Lib.o FMM_Lib.o HDF_Lib.o;
gcc -o exe2 main32.o BF_Lib.o BMM_Lib.o FMM_Lib.o HDF_Lib.o;
gcc -o exe3 main33.o BF_Lib.o BMM_Lib.o FMM_Lib.o HDF_Lib.o;

