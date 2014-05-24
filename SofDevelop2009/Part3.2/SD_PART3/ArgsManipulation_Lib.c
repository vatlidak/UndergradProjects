/*
 * FileName: ArgsManipulation_Lib.c
 *
 *
 * Authors: Atlidakis Vaggelis, Aggelogianopoulos Aris, Kuriazof Xristina
 *
 *
 * Date: Jan 2010
 *
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ArgsManipulation_Lib.h" 

#include "UT_DM_Defines.h"

int Create_MakeArgs(char** argv,char ***myargv,int attrcnt,relDesc relRec, attrDesc* attrs,int mode)
{
	int i;
	int j;
	int myargc;
	
	myargc=2*attrcnt+2;							/* make args for UT_create */
	if ( (*myargv=calloc(myargc+1,sizeof(char*))) == NULL)
			return  DM_errno=DME_NOMEM;		
	if ( (**myargv=calloc(strlen("create")+1,sizeof(char))) == NULL)
			return  DM_errno=DME_NOMEM; 
	strcpy(**myargv,"create");
	(*myargv)++;
	if  ( mode == 0 )							/* name of relation to create is given */
	{
		if ( (**myargv=calloc(strlen(argv[1])+1,sizeof(char))) == NULL)
			return  DM_errno=DME_NOMEM; 
		strcpy(**myargv,argv[1]);
	}
	else if ( mode == -1 )							/* name of relation create is not given */
	{
		if ( (**myargv=calloc(strlen("TempRelation")+1,sizeof(char))) == NULL)
			return  DM_errno=DME_NOMEM; 
		strcpy(**myargv,"TempRelation");
		
	}
	(*myargv)++;
	for (i=0; i<attrcnt;i++)
	{	
		for ( j=0; j<relRec.attrcnt; j++)
			if ( strcmp(argv[4+2*i+mode],attrs[j].attrname) == 0 )
				break;
		if ( (**myargv=calloc(strlen(argv[4+2*i+mode])+1,sizeof(char))) == NULL)
				return  DM_errno=DME_NOMEM; 
		strcpy(**myargv,argv[4+2*i+mode]);				/* copy name */
		(*myargv)++;	
		if ( (**myargv=calloc(sizeof(char)+10,sizeof(char))) == NULL)
			return  DM_errno=DME_NOMEM; 
		if ( attrs[j].attrtype == 'c' )				/* copy type */
			sprintf(**myargv,"'%c%d'",'c',attrs[j].attrlength);
		else if ( attrs[j].attrtype == 'i' )
			strcpy(**myargv,"'i'");
		else 
			strcpy(**myargv,"'f'");
		(*myargv)++;
	}
	**myargv=NULL;
	(*myargv)-=myargc;
	return DM_errno=DME_OK;							/* make args completed */
}

int Insert_MakeArgs(char* record,char** argv,char ***myargv,int attrcnt,relDesc relRec, attrDesc* attrs,int mode)
{

	int i;
	int j;
	int myargc;

	myargc=2*attrcnt+2;
	if ( (*myargv=calloc(myargc+1,sizeof(char*))) == NULL)
		return  DM_errno=DME_NOMEM;
	if ( (**myargv=calloc(strlen("insert")+1,sizeof(char))) == NULL)
		return  DM_errno=DME_NOMEM; 
	strcpy(**myargv,"insert");
	(*myargv)++;
	if ( mode == 0 )								/* name of relation to insert results is given */
	{
  		if ( (**myargv=calloc(strlen(argv[1])+1,sizeof(char))) == NULL)
			return  DM_errno=DME_NOMEM; 
		strcpy(**myargv,argv[1]);
	}
	else										/* name of relation to insert results is not given */
	{
		if ( (**myargv=calloc(strlen("TempRelation")+1,sizeof(char))) == NULL)
			return  DM_errno=DME_NOMEM; 
		strcpy(**myargv,"TempRelation");
	}
	(*myargv)++;
	for (i=0; i<attrcnt;i++)
	{	
		for ( j=0; j<relRec.attrcnt; j++)
			if ( strcmp(argv[4+2*i+mode],attrs[j].attrname) == 0 )
				break;
		if ( (**myargv=calloc(strlen(argv[4+2*i+mode])+1,sizeof(char))) == NULL)
			return  DM_errno=DME_NOMEM; 
		strcpy(**myargv,argv[4+2*i+mode]);			/* copy name */
		(*myargv)++;	
		if ( (**myargv=calloc(attrs[j].attrlength,sizeof(char))) == NULL)
			return  DM_errno=DME_NOMEM; 
		if ( attrs[j].attrtype == 'i' )
		{
			sprintf(**myargv,"%d",*(int*)(record+attrs[j].offset));
		}
		else if ( attrs[j].attrtype == 'f' )
		{
			sprintf(**myargv,"%.2f",*(float*)(record+attrs[j].offset));
		}
		else
		{
			sprintf(**myargv,"%s",record+attrs[j].offset);
 		}
		(*myargv)++;
	}
	**myargv=NULL;
	(*myargv)-=myargc;	
	return DM_errno=DME_OK;							/* make args completed */
}

int Destroy_MakeArgs(char ***myargv,char* relname,int myargc)
{
	if ( (*myargv=calloc(3,sizeof(char*))) == NULL)
		return  DM_errno=DME_NOMEM;
	if ( (**myargv=calloc(strlen("destroy")+1,sizeof(char))) == NULL)
		return  DM_errno=DME_NOMEM; 
	strcpy(**myargv,"destroy");
	(*myargv)++;
	if ( (**myargv=calloc(strlen(relname)+1,sizeof(char))) == NULL)
		return  DM_errno=DME_NOMEM; 
	strcpy(**myargv,relname);
	(*myargv)++;
 	**myargv=NULL;
	(*myargv)-=myargc;
	return DM_errno=DME_OK;							/* make args completed */
}
	
void free_args(char** myargv,int myargc)
{
	int i;
	
	for ( i=0; i<myargc+1; i++)
		free(myargv[i]);
	free(myargv);
}
