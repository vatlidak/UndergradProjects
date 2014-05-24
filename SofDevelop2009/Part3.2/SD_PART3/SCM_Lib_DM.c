/*
 * FileName: SCM_Lib_DM.c
 *
 *
 * Authors: Atlidakis Vaggelis, Aggelogianopoulos Aris, Kuriazof Xristina
 *
 *
 * Date: Jan 2010
 *
 *
 */
 #include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "UT_DM_Defines.h"
#include "SCM_Lib.h"
#include "CFM_Lib.h"

//#include "HF_Defines.h"
#include "HF_Lib.h"



int check_type(char* value, char * ar, char type)
{
	int num;
	float num2;

	if(type == 'c')
	{
		if(strlen(value) > MAXNAME || strlen(value) <= 0)
		{
			printf("ERROR : length of string ");
			return 0;
		}
	}
	return 1;
}

int SCM_insert(int argc, char *argv[])
{
	int i, j, flag = 0, flag2 = 0;
	relDesc rel;
	attrDesc *attrs;

	if( CFM_Lookup(argv[1], &rel, &attrs) != UTE_OK )
	{
		printf("ERROR : There is no file with name: %s\n", argv[1]);
		return (DM_errno = SCM_ERROR);
	}
	if(argc != (rel.attrcnt)*2 + 2)
		return  (DM_errno = SCM_ERROR);

	//elegxos gia to an yparxoun ola ta pedia tou arxeiou sthn entolh insert
	for(i = 0; i < rel.attrcnt; i++)
	{
		for(j = 2; j < argc; j+=2)
		{		
			if((strcmp(argv[j], attrs[i].attrname))==0)
			{
				flag = 1;
				if(check_type(argv[j+1], argv[j], attrs[i].attrtype) != 1)
					flag2 = 1;
				break;
			}
		}
		if(flag!=1)		//shmainei pws den yparxei to sygkekrimeno attr sto arxeio ths bash mas h einai diplotypo
			return (DM_errno = SCM_ERROR);
	}
	if(flag2==1)
		return (DM_errno = SCM_ERROR);
	return DME_OK;
	
}


int SCM_delete(int argc, char* argv[])
{
	int i, flag = 0;
	relDesc rel;
	attrDesc *attrs;

	if(argc==2 || argc==5)
	{
		if( CFM_Lookup(argv[1], &rel, &attrs) != UTE_OK )
		{
			printf("ERROR : There is no file with name: %s\n", argv[1]);
			return (DM_errno = SCM_ERROR);
		}
		if(argc==5)
		{
			//synexizw elegxous gia ta ypoloipa orismata
			for(i = 0; i < rel.attrcnt; i++)
			{
				if(strcmp(attrs[i].attrname, argv[2])==0)
				{
					flag = 1;
					if(check_type(argv[4], argv[2], attrs[i].attrtype) != 1)
						return (DM_errno = SCM_ERROR);
				}
			}
			if (flag==0)
			{
				printf("ERROR : There is not field %s in file with name %s\n", argv[2], argv[1]);
				return (DM_errno = SCM_ERROR);
			}
			//elegxo gia ton telesth, an den einai kanena apo ta epitrepomena 
			if( (argv[3][1] != '=') && (argv[3][1] != '<') && (strcmp(argv[3], "'<='")!=0) && (argv[3][1] != '>') && (strcmp(argv[3], "'>='")!=0)
			&& (strcmp(argv[3], "'!='")!=0))
			{
				printf("ERROR : The operator is not valid");
				return (DM_errno = SCM_ERROR);
			}
			
		}	
	}
	else
	{
		printf("ERROR : You gave wrong number of arguments\n");
		return (DM_errno = SCM_ERROR);
	}
	return DME_OK;
}

int SCM_select(int argc, char* argv[])
{
	relDesc rel;
	attrDesc *attrs;
	int num, i, j, flag = 0;
	int condition_fields, into;

	if(argc % 2 == 0)	//leipei to onoma sxeshs apotelesmatos
		into = 0;
	else
	{
		into = 1;
		//h sxesh pou tha eisaxthoun ta apotelesmta den prepei na yparxei
		if(Scan_relcat(argv[1])==1)
		{
			printf("ERROR : The filename %s exists\n", argv[1]);
			return (DM_errno = SCM_ERROR);
		}
		
	}
	num = atoi(argv[1+into]);		//plhthos gnwrismatwn pou proballontai

	if(argc == 2*num + 1 + into)
		condition_fields = 0;
	else if(argc == 2*num + 1 + into + 4 )
		condition_fields = 1;
	else 
	{
		printf("ERROR : Incomplete the last 4 arguments\n");	
		return (DM_errno = SCM_ERROR);
	}

	//epeidh den exw zeuxh, prepei ola ta onomata sxesewn na einai idia
	for(i = 2 + into; i < num; i+=2)
	{
		for(j = 2 + into; j < num; j+=2)
		{		
			if( (strcmp(argv[i], argv[j])) != 0 )
			{
				printf("ERROR : (You have to refer to one file) The file names must be the same\n");
				return (DM_errno = SCM_ERROR);
			}
		}
	}
	//koitaw an yparxei ayth h sxesh kai gemizw tis domes rel kai attrs
	if( CFM_Lookup(argv[2 + into], &rel, &attrs) != UTE_OK )
	{
		printf("ERROR : There is no file with name: %s\n", argv[2 + into]);
		return (DM_errno = SCM_ERROR);
	}
	//elegxos an ta pedia pou exoun dwthei einai parapanw apo ayta pou yparxoun
	if( num > rel.attrcnt)
	{
		printf("ERROR : The number of given attributes must be less or equal than the number of files' fields\n");
		return (DM_errno = SCM_ERROR);
	}

	for(j = 2 + into; j < num; j+=2)
	{
		//elegxos gia diplotypa attributes
		for(i = 2 + into; i < num; i+=2)
		{
			if( (j!=i) && (strcmp(argv[j], argv[i])==0) )
			{
				printf("ERROR : You have to give only once each attribute\n");
				return (DM_errno = SCM_ERROR);
			}
		}
		for(i = 0; i<rel.attrcnt; i++)
		{		
			if(strcmp(argv[j], attrs[i].attrname)==0)
				flag = 1;
		}
		if(flag==0)
		{
			printf("ERROR : There is no field with name %s in file %s\n", argv[j], argv[2+into]);
			return (DM_errno = SCM_ERROR);
		}
	}
	//elegxos gia thn synthikh epiloghs
	if(condition_fields)
	{
		if(strcmp(argv[argc-4], argv[2+into])!=0)
		{
			printf("ERROR : The file name of condition must be the same with the file name in target_list\n");
			return (DM_errno = SCM_ERROR);
		}
		for(i = 0; i<rel.attrcnt; i++)
		{		
			if(strcmp(argv[argc-3], attrs[i].attrname)==0) {
				flag = 1;
				if(check_type(argv[argc-1], argv[argc-3], attrs[i].attrtype) != 1)
					return (DM_errno = SCM_ERROR);
			}
		}
		if(flag!=1)
		{
			printf("ERROR : There is no field with name %s in file %s\n", argv[j], argv[2 + into]);
			return (DM_errno = SCM_ERROR);
		}
		//elegxo gia ton telesth, an den einai kanena apo ta epitrepomena 
		if( (argv[argc-2][1] != '=') && (argv[argc-2][1] != '<') 
			&& (strcmp(argv[argc-2], "'<='")!=0) && (argv[argc-2][1] != '>')
			&& (strcmp(argv[argc-2], "'>='")!=0) && (strcmp(argv[argc-2], "'!='")!=0) )
		{
			printf("ERROR : The operator is not valid");
			return (DM_errno = SCM_ERROR);
		}
			
	}
	return DME_OK;
}

int SCM_join(int argc, char* argv[])
{
	relDesc rel1, rel2;
	attrDesc *attrs1, *attrs2;

	int num, i, j, flag = 0;
	int k;		//krataw th thesh tou pinaka attrs1 
	int condition_fields, into;

	if(argc % 2 != 0)	//leipei to onoma sxeshs apotelesmatos
		into = 0;
	else
	{
		into = 1;
		//h kainouria sxesh pou tha eisaxthoun ta apotelesmta den prepei na yparxei
		if(Scan_relcat(argv[1])==1)
		{
			printf("ERROR : The filename %s exists\n", argv[1]);
			return (DM_errno = SCM_ERROR);
		}
		
	}
	num = atoi(argv[1+into]);		//plhthos gnwrismatwn pou proballontai
/*~~~~~~~~~~~~~*/
	//elegxos gia th synthikh zeyxhs
		//elegxos gia th prwth sxesh
	if( CFM_Lookup(argv[argc-5], &rel1, &attrs1) != UTE_OK )
	{
		printf("ERROR : There is no file with name: %s\n", argv[argc-5]);
		return (DM_errno = SCM_ERROR);
	}
	for(i = 0; i<rel1.attrcnt; i++)
	{		
		if(strcmp(argv[argc-4], attrs1[i].attrname)==0){
			k = i;
			flag = 1;
			break;
		}
	}
	if (flag!=1) {
		printf("ERROR : There is no field with name %s in file %s\n", argv[argc-4], argv[argc-5]);
		return (DM_errno = SCM_ERROR);
	}
	flag = 0;	//epanafora

		//elegxos gia th deyterh sxesh
	if( CFM_Lookup(argv[argc-2], &rel2, &attrs2) != UTE_OK )
	{
		printf("ERROR : There is no file with name: %s\n", argv[argc-5]);
		return (DM_errno = SCM_ERROR);
	}
	for(i = 0; i<rel2.attrcnt; i++)
	{		
		if(strcmp(argv[argc-1], attrs2[i].attrname)==0){
			//elegxos na einai idia ta types twn pediwn
			if( attrs1[k].attrtype != attrs2[i].attrtype ) {
				printf("ERROR : The types of the fields in condition must be the same\n");
				return (DM_errno = SCM_ERROR);
			}
			flag = 1;
			break;
		}
	}
	if (flag!=1) {
		printf("ERROR : There is no field with name %s in file %s\n", argv[argc-4], argv[argc-5]);
		return (DM_errno = SCM_ERROR);
	}
	flag = 0;	//epanafora

	//elegxo gia ton telesth, an den einai kanena apo ta epitrepomena
	if( (argv[argc-3][1] != '=') && (argv[argc-3][1] != '<') 
	&& (strcmp(argv[argc-3], "'<='")!=0) && (argv[argc-3][1] != '>') 
	&& (strcmp(argv[argc-3], "'>='")!=0)&& (strcmp(argv[argc-3], "'!='")!=0))
	{
		printf("ERROR : The operator is not valid");
		return (DM_errno = SCM_ERROR);
	}
/*~~~~~~~~~~~~~~*/
	for(j = 2 + into; j < num; j+=2)
	{
		//elegxos gia ta onomata sxesewn
		if( (strcmp(argv[j], rel1.relname)!=0) && (strcmp(argv[j], rel2.relname)!=0) )
		{
			printf("ERROR : You have to select file names from the file names in condition\n");
			return (DM_errno = SCM_ERROR);
		}
		//elegxos an to pedio anhkei se mia apo tis sxeseis aytes
		for(i = 0; i<rel1.attrcnt; i++)
		{		
			if( strcmp(argv[j+1], attrs1[i].attrname)==0 )
				flag = 1;
		}
		for(i = 0; i<rel2.attrcnt; i++)
		{		
			if( strcmp(argv[j+1], attrs2[i].attrname)==0 )
				flag = 1;
		}
		if(flag!=1)
		{
			printf("ERROR : There is no field with name %s in file %s\n", argv[j], argv[2+into]);
			return (DM_errno = SCM_ERROR);
		}	
		//elegxos gia diplotypa px: select athletes.id, athletes.id ...
		for(i = 2 + into; i < num; i+=2)
		{
			if( (i!=j) && (strcmp(argv[j], argv[i])==0) && (strcmp(argv[j+1], argv[i+1])==0))
			{
				printf("ERROR : You have to give only once each <file.attribute>\n");
				return (DM_errno = SCM_ERROR);
			}
		}
	}
	return DME_OK;
}
