#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#include "BF_Defines.h"
#include "BF_Lib.h"

//#include "HF_Defines.h"
#include "HF_Lib.h"

#include "UT_DM_Defines.h"
#include "CFM_Lib.h"

#define relCat "relCat"
#define attrCat "attrCat"

/*typedef enum {
    FALSE = 0,
    TRUE = 1
}BOOLEAN;
*/

/*
 * This is a function creating and initializing files (catalogs)
 * RELCAT and ATTRCAT, which initially contain information
 * only about theirselves. Uppon successful execution 
 * UTE_OK is returned, otherwise appropriate error code
 * is returned and UT_errno is set.
 */
int CFM_Create(void)
{
	int	i;
	int	rval;
	relDesc rel, attr;
	attrDesc rel_attrDesc[4],attr_attrDesc[7];
	



	if ( (rval=HF_CreateFile(relCat))!=HFE_OK ) 		/* Create files: "ATTRCAT" and  "RELCAT" */
		return UT_errno=rval;
	if ( (rval=HF_CreateFile(attrCat))!=HFE_OK )
		return UT_errno=rval;
	if ( (relCatFd=HF_OpenFile(relCat)) < 0 )		/* Open file RELCAT */
		return UT_errno=rval;									
	if ( (attrCatFd=HF_OpenFile(attrCat)) < 0 )	/* Open file ATTRCAT */
		return UT_errno=rval;

	strcpy(rel.relname,relCat);				/* Create a relDesc record for file "RELCAT" */ 
	rel.relwidth=sizeof(relDesc);
	rel.attrcnt=4;
	rel.indexcnt=0;
	
	strcpy(rel_attrDesc[0].relname,relCat);			/* Create one attrDesc record for each field of rel */
	strcpy(rel_attrDesc[0].attrname,"relname");
	rel_attrDesc[0].offset=0;
	rel_attrDesc[0].attrlength=MAXNAME;
	rel_attrDesc[0].attrtype='c';
	rel_attrDesc[0].indexed=FALSE;	
	rel_attrDesc[0].indexno=0;
	
	strcpy(rel_attrDesc[1].relname,relCat);
	strcpy(rel_attrDesc[1].attrname,"relwidth");
	rel_attrDesc[1].offset=MAXNAME;
	rel_attrDesc[1].attrlength=sizeof(int);
	rel_attrDesc[1].attrtype='i';
	rel_attrDesc[1].indexed=FALSE;	
	rel_attrDesc[1].indexno=0;

	strcpy(rel_attrDesc[2].relname,relCat);
	strcpy(rel_attrDesc[2].attrname,"attrcnt");
	rel_attrDesc[2].offset=MAXNAME+sizeof(int);
	rel_attrDesc[2].attrlength=sizeof(int);
	rel_attrDesc[2].attrtype='i';
	rel_attrDesc[2].indexed=FALSE;	
	rel_attrDesc[2].indexno=0;

	strcpy(rel_attrDesc[3].relname,relCat);
	strcpy(rel_attrDesc[3].attrname,"indexcnt");
	rel_attrDesc[3].offset=MAXNAME+2*sizeof(int);
	rel_attrDesc[3].attrlength=sizeof(int);
	rel_attrDesc[3].attrtype='i';
	rel_attrDesc[3].indexed=FALSE;	
	rel_attrDesc[3].indexno=0;
	
	if ( (rval=CFM_AddRel(rel,rel_attrDesc)) != UTE_OK )	/* Add relDesc and attrDesc to respective files */
		return UT_errno = rval;	
	

	strcpy(attr.relname,attrCat);				/* Create a relDesc record for file "ATTRCAT" */
	attr.relwidth=sizeof(attrDesc);
	attr.attrcnt=7;
	attr.indexcnt=0;
	
	strcpy(attr_attrDesc[0].relname,attrCat);		/* Create one attrDesc record for each field of attr */
	strcpy(attr_attrDesc[0].attrname,"relname");
	attr_attrDesc[0].offset=0;
	attr_attrDesc[0].attrlength=MAXNAME;
	attr_attrDesc[0].attrtype='c';
	attr_attrDesc[0].indexed=FALSE;	
	attr_attrDesc[0].indexno=0;
        
	strcpy(attr_attrDesc[1].relname,attrCat);
	strcpy(attr_attrDesc[1].attrname,"attrname");
	attr_attrDesc[1].offset=MAXNAME;
	attr_attrDesc[1].attrlength=MAXNAME;
	attr_attrDesc[1].attrtype='c';
	attr_attrDesc[1].indexed=FALSE;	
	attr_attrDesc[1].indexno=0;

	strcpy(attr_attrDesc[2].relname,attrCat);
	strcpy(attr_attrDesc[2].attrname,"offset");
	attr_attrDesc[2].offset=2*MAXNAME;
	attr_attrDesc[2].attrlength=sizeof(int);
	attr_attrDesc[2].attrtype='i';
	attr_attrDesc[2].indexed=FALSE;	
	attr_attrDesc[2].indexno=0;
	
	strcpy(attr_attrDesc[3].relname,attrCat);
	strcpy(attr_attrDesc[3].attrname,"attrlength");
	attr_attrDesc[3].offset=2*MAXNAME+sizeof(int);
	attr_attrDesc[3].attrlength=sizeof(int);
	attr_attrDesc[3].attrtype='i';
	attr_attrDesc[3].indexed=FALSE;	
	attr_attrDesc[3].indexno=0;
	
	strcpy(attr_attrDesc[4].relname,attrCat);
	strcpy(attr_attrDesc[4].attrname,"attrtype");
	attr_attrDesc[4].offset=2*MAXNAME+2*sizeof(int);
	attr_attrDesc[4].attrlength=sizeof(char);
	attr_attrDesc[4].attrtype='c';
	attr_attrDesc[4].indexed=FALSE;	
	attr_attrDesc[4].indexno=0;
	
	strcpy(attr_attrDesc[5].relname,attrCat);
	strcpy(attr_attrDesc[5].attrname,"indexed");
	attr_attrDesc[5].offset=2*MAXNAME+2*sizeof(int)+sizeof(char);
	attr_attrDesc[5].attrlength=sizeof(int);
	attr_attrDesc[5].attrtype='i';
	attr_attrDesc[5].indexed=FALSE;	
	attr_attrDesc[5].indexno=0;
	
	strcpy(attr_attrDesc[6].relname,attrCat);
	strcpy(attr_attrDesc[6].attrname,"indexno");
	attr_attrDesc[6].offset=2*MAXNAME+3*sizeof(int)+sizeof(char);
	attr_attrDesc[6].attrlength=sizeof(int);
	attr_attrDesc[6].attrtype='i';
	attr_attrDesc[6].indexed=FALSE;	
	attr_attrDesc[6].indexno=0;

	if ( (rval=CFM_AddRel(attr,attr_attrDesc)) != UTE_OK )	/* Add relDesc and attrDesc to respective files */
		return UT_errno = rval;	
	return UTE_OK;
}


/*
 * This is a function inserting into files (catalogs)
 * RELCAT and ATTRCAT the records of a new relation.
 * Uppon successful execution UTE_OK is returned, 
 * otherwise appropriate error code is returned and 
 * UT_errno is set.
 */
int CFM_AddRel(relDesc rel, attrDesc* attrs )
{
	int 	i;
	int 	rval;

	if ( (rval=HF_InsertRec(relCatFd, (char *)&rel, sizeof(relDesc))) < 0)		/* Insert relDesc into RELCAT */
		return UT_errno=rval;	
	for ( i=0; i<rel.attrcnt; i++ )							/* Insert attrDescs int ATTRCAT */
		if ( (rval=HF_InsertRec(attrCatFd, (char *)&attrs[i], sizeof(attrDesc))) < 0 )
			return UT_errno=rval;
	return UTE_OK;	
}


/*
 * This is a function deleting from files (catalogs)
 * RELCAT and ATTRCAT records related to relation
 * relname. Uppon successful execution UTE_OK is returned, 
 * otherwise appropriate error code is returned and 
 * UT_errno is set.
 */
int CFM_DeleteRel(char* relName)
{
	int 	rval;
	int	recId;
	int 	sd;
	relDesc relRec;
	attrDesc attrRec;
	
	if ( (sd=HF_OpenFileScan(relCatFd,sizeof(relDesc),'c',MAXNAME,0, 1, relName)) < 0 )		/* Start a new scan on records of file RELCAT */
		return UT_errno=sd;									/* search for them that have first field */ 
													/* "1. EQUAL TO" relName */
												
	if ( (rval=HF_FindNextRec(sd, (char*)&relRec)) < 0 )
		return UT_errno=rval;
	else
	{
		recId=rval;
		if ( (rval=HF_DeleteRec(relCatFd,recId,sizeof(relDesc))) != HFE_OK )
			return UT_errno=rval;
	}
	if ( (rval=HF_CloseFileScan(sd)) != HFE_OK )							/* Close open scan */
		return UT_errno=rval;

	if ( (sd=HF_OpenFileScan(attrCatFd,sizeof(attrDesc),'c',MAXNAME,0, 1, relName)) < 0 )		/* Start a new scan on records of file ATTRCAT */
		return UT_errno=sd;									/* search for them that have first field */ 
													/* "1. EQUAL TO" relName */
	while ( (rval=HF_FindNextRec(sd, (char*)&attrRec)) >= 0 )
	{
			recId=rval;
			if ( (rval=HF_DeleteRec(attrCatFd,recId,sizeof(attrDesc))) != HFE_OK )
				return UT_errno=rval;
	}
	if ( (rval=HF_CloseFileScan(sd)) != HFE_OK )							/* Close open scan */
		return UT_errno=rval;
	return UTE_OK;
}


/*
 * This is a function updating the records related to 
 * relation'UTE_NOMEMs relname field attrname, of files (catalogs)
 * RELCAT and ATTRCAT. Uppon successful execution UTE_OK is 
 * returned, otherwise appropriate error code is returned and 
 * UT_errno is set.
 */
int CFM_IndexAttribute(char* relName, char* attrName, int indexNo)
{
	int	i;
	int 	rval;
	int 	recId;
	int	sd;
	int 	fd;
	char	*record;
	relDesc relRec;
	attrDesc attrRec;
	
	if ( (sd=HF_OpenFileScan(relCatFd,sizeof(relDesc),'c',MAXNAME,0, 1, relName)) < 0 )		/* Start a new scan on records of file ATTRCAT */
		return UT_errno=sd;									/* search for them that have first field */ 
													/* "1. EQUAL TO" relName */		
	if ( (rval=HF_FindNextRec(sd, (char*)&relRec)) < 0 )
		return UT_errno=rval;
	else
	{
		recId=rval;
		if ( (rval=HF_DeleteRec(relCatFd,recId,sizeof(relDesc))) != HFE_OK )			/* with attrName */
				return UT_errno=rval;
		relRec.indexcnt++;
		if ( (rval=HF_InsertRec(relCatFd, (char *)&relRec, sizeof(relDesc))) != HFE_OK )
				return UT_errno=rval;
	}
	if ( (rval=HF_CloseFileScan(sd)) != HFE_OK )							/* Close open scan */
		return UT_errno=rval;
	
	
	if ( (sd=HF_OpenFileScan(attrCatFd,sizeof(attrDesc),'c',MAXNAME,0, 1, relName)) < 0 )		/* Start a new scan on records of file ATTRCAT */
		return UT_errno=sd;									/* search for them that have first field */ 
													/* "1. EQUAL TO" relName */
	while ( (rval=HF_FindNextRec(sd, (char*)&attrRec)) >= 0 )
	{
		recId=rval;
		if ( strcmp(attrRec.attrname,attrName) == 0 ){						/* delete only records related to field */
			if ( (rval=HF_DeleteRec(attrCatFd,recId,sizeof(attrDesc))) != HFE_OK )		/* with attrName */
				return UT_errno=rval;
			attrRec.indexed=TRUE;
			attrRec.indexno=indexNo;
			if ( (rval=HF_InsertRec(attrCatFd, (char *)&attrRec, sizeof(attrDesc))) != HFE_OK )
				return UT_errno=rval;
		}
	}
	if ( (rval=HF_CloseFileScan(sd)) != HFE_OK )							/* Close open scan */
		return UT_errno=rval;
	return UTE_OK;
}	


/*
 * This is a function searching into files (catalogs)
 * RELCAT and ATTRCAT, information about relation relname.
 * Uppon successful execution  UTE_OK is returned, rel points 
 * to relation's record and attrs[] points to each record for
 * respective fields of relation. Otherwise appropriate error 
 * code is returned and  UT_errno is set.
 */
int CFM_Lookup(char* relName, relDesc* rel, attrDesc** attrs)
{

	int	i;
	int 	rval;
	int	recId;
	int 	sd;
	char	*temp;
	
	if ( (sd=HF_OpenFileScan(relCatFd,sizeof(relDesc),'c',MAXNAME,0, 1, relName)) < 0 )     	/* Start a new scan on records of file RELCAT */
		return UT_errno=sd;									/* search for them that have first field */ 
													/* "1. EQUAL TO" relName */	
	if ( (rval=HF_FindNextRec(sd, (char*)rel)) < 0 )						/* print every error except for HFE_EOF */
		return UT_errno=rval;
	if ( (rval=HF_CloseFileScan(sd)) != HFE_OK )							/* Close open scan */
		return UT_errno=rval;
	if ( (*attrs=calloc(rel->attrcnt,sizeof(attrDesc))) == NULL )
		return UT_errno=UTE_NOMEM;
	if ( (sd=HF_OpenFileScan(attrCatFd,sizeof(attrDesc),'c',MAXNAME,0, 1, relName)) < 0 )		/* Start a new scan on records of file ATTRCAT */
		return UT_errno=sd;									/* search for them that have first field */ 														/* "1. EQUAL TO" relName */		
	i=0;	
	if ( (temp=calloc(sizeof(attrDesc),sizeof(char))) == NULL)
		return UT_errno=UTE_NOMEM;
	while ( (rval=HF_FindNextRec(sd, temp)) >= 0 )
		memcpy((char*)&(*attrs)[i++],temp,sizeof(attrDesc));	
	free(temp);
	if ( (rval=HF_CloseFileScan(sd)) != HFE_OK )							/* Close open scan */
		return UT_errno=rval;
	return UTE_OK;
}

