OBJECTS = UT_Lib.o SCM_Lib.o CFM_Lib.o BF_Lib.o AM_Lib.o HF_Lib.o testMain.o lex.yy.o parser4.tab.o

prog:${OBJECTS}
	gcc -g3 -o prog ${OBJECTS} -lm
CFM_Lib.o:CFM_Lib.c CFM_Lib.h UT_DM_Defines.h
	gcc -c CFM_Lib.c
SCM_Lib.o:SCM_Lib.c SCM_Lib.h UT_DM_Defines.h
	gcc -c SCM_Lib.c
UT_Lib.o:UT_Lib.c UT_Lib.h UT_DM_Defines.h
	gcc -c UT_Lib.c
testMain.o:testMain.c parser4.h
	gcc -c testMain.c
lex.yy.o:lex.yy.c
	gcc -c lex.yy.c
parser4.tab.o:parser4.tab.c
	gcc -c parser4.tab.c
clean:
	rm -rf CFM_Lib.o SCM_Lib.o UT_Lib.o testMain.o prog
