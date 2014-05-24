/*
 * FileName: ReadMe.txt
 *
 *
 * Authors: Atlidakis Vaggelis, Aggelogianopoulos Aris, Kuriazof Xristina
 *
 *
 * Date: Jan 2010
 *
 *
 */

gcc -o aminirel testMain.c DM_Lib.c SCM_Lib.c SCM_Lib_DM.c BF_Lib.o HF_Lib.o AM_Lib.o CFM_Lib.c UT_Lib.c parser4.tab.c lex.yy.c ArgsManipulation_Lib.c -lm;
gcc -o dbcreate dbcreate.c BF_Lib.o HF_Lib.o CFM_Lib.c -lm;
gcc -o dbdestroy dbdestroy.c BF_Lib.o HF_Lib.o CFM_Lib.c -lm;


Ta evretiria den scinontai swsta, oi AM sunartuseus exoun provlima!
