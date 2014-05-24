#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "UT_DM_Defines.h"
#include "SCM_Lib.h"
#include "CFM_Lib.h"

#include "HF_Lib.h"


int SCM_create(int argc, char* argv[])
{
	int i, j, l;

	if(Scan_relcat(argv[1])==1){
		printf("ERROR : The filename %s exists\n", argv[1]);
		return (UT_errno = SCM_ERROR);
	}
//	for(i = 0; i<argc; i++)
//	{
//		printf("->%s\n", argv[i]);
//	}
	//elegxos gia to an exei dwsei 2 gnwrismata me idio onoma 
	for(i = 2; i<argc; i = i+2)
	{
		for(j = 4; j<argc; j = j+2)
		{
			if( (i!=j) && (strcmp(argv[i], argv[j])==0))
				return (UT_errno = SCM_ERROR);
	
		}
		//elefxos gia na dwthei c, i, f kai mono
		if(argv[i+1][1]!='c' && argv[i+1][1]!='i' && argv[i+1][1]!='f'){
			printf("ERROR : You have to give for type : 'c', 'i' or 'f'\n");
			return (UT_errno = SCM_ERROR);
		}
		//elegxos gia na einai ths morfhs "cnumber"
		if(argv[i+1][1] == 'c')
		{
			l = atoi(&argv[i+1][2]);
			if(l <= 0 || l > 256) {
				printf("ERROR : length of string\n");
				return (UT_errno = SCM_ERROR);
			}
		}
	}
	if(argv[argc] != NULL)
		return (UT_errno = SCM_ERROR);
	return UTE_OK;
}


int SCM_buildIndex(int argc, char* argv[])
{	
	//elegxos gia argv[1]
	if(Scan_relcat(argv[1]) != 1)
	{
		printf("ERROR : File %s does not exist\n", argv[1]);
		return (UT_errno = SCM_ERROR);
	}
	//elegxos gia argv[2]
	
	if( Scan_attrcat(argv[2]) != 1)
	{
		printf("ERROR : Attribute %s does not exist\n", argv[2]);
		return (UT_errno = SCM_ERROR);
	}
	if(argv[argc] != NULL)
		return (UT_errno = SCM_ERROR);
//	printf("ggggggg\n");
	return UTE_OK;
}


int SCM_destroy(int argc, char* argv[])
{
	attrDesc* attrs;
	relDesc rel;

	if(argc != 2)
		return (UT_errno = SCM_ERROR);	
	if(CFM_Lookup(argv[1], &rel, &attrs) != UTE_OK)
		return (UT_errno = SCM_ERROR);
	if(argv[argc] != NULL)
		return (UT_errno = SCM_ERROR);
	return UTE_OK;
}

int SCM_print(char* relName)
{
	//elegxos gia to an yparxei to relName
	if(Scan_relcat(relName)!=1)
		return (UT_errno = SCM_ERROR);
	return UTE_OK;
}


int Scan_relcat(char *ar)
{
	int recid;
	relDesc record;
	int fd, sd;

	if( (sd = HF_OpenFileScan(relCatFd, sizeof(relDesc), 'c',  MAXNAME,  0, 1, ar)) < 0)
		return (UT_errno = HF_errno);
	if((recid = HF_FindNextRec(sd, (char*)&record)) >=0 )
	{
		if(HF_CloseFileScan(sd) < 0)
			return (UT_errno = HF_errno);
		return 1;
	}
	else 
	{
		if(HF_CloseFileScan(sd) < 0)
			return (UT_errno = HF_errno);
		printf("Scan_relCat: %d\n", recid);	
		return (UT_errno = HF_errno);
	}
}

int Scan_attrcat(char *ar)
{
	int recid;
	attrDesc record;
	int sd;
	printf("name = %s\n",ar);
	if( (sd = HF_OpenFileScan(attrCatFd, sizeof(attrDesc), 'c', MAXNAME, MAXNAME, 1, ar)) < 0 )
		return (UT_errno = HF_errno);
	if((recid = HF_FindNextRec(sd, (char*)&record)) >= 0)
	{
		if(HF_CloseFileScan(sd) < 0)
			return (UT_errno = HF_errno);
		printf("prin to return\n");
		return 1;
	}
	else  
	{
		if(HF_CloseFileScan(sd) < 0)
			return (UT_errno = HF_errno);
		printf("---  %d\n", recid);	
		return (UT_errno = HF_errno);
	}
}
