/*
 * FileName: DM_Lib.c
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

#include "BF_Lib.h"

#include "HF_Lib.h"

#include "SCM_Lib.h"
#include "AM_Lib.h"

#include "CFM_Lib.h"
#include "UT_Lib.h"
#include "DM_Lib.h"

#include "ArgsManipulation_Lib.h" 

#include "UT_DM_Defines.h"



int operator(char* op)
{
	if ( strcmp(op,"=") == 0 )
		return 1;
	else if ( strcmp(op,"<") == 0 )
		return 2;
	else if ( strcmp(op,">") == 0 )
		return 3;
	else if ( strcmp(op,"<=") == 0 )
		return 4;
	else if ( strcmp(op,">=") == 0 )
		return 5;
	else 
		return 6;
}

/*
 * This is a function inserting a record to relname's file,
 * If a record's field is indexed appropriate record is also
 * inserted into Index.If an error occours error code is returned
 * and errno is set, else DME_OK is returned.
 */
int DM_insert(int argc, char* argv[])
{
	int i,j;
	int rval;
	int tempi;
	int fd;
	int ind_d;
	int recId;
	float tempf;
	char* rec;
	char* temp;
	relDesc rel;
    	attrDesc *attrs = NULL;

//    	if( (rval=SCM_insert(argc,argv))!=UTE_OK)      		/* Semantic Check */
//     		return DM_errno=rval;

	if( (rval=CFM_Lookup(argv[1], &rel, &attrs))!=UTE_OK)	/* lookup enables us access the relDesc and attrDesc info of the relation argv[1] */
       		return DM_errno=rval;

	if ( (rec=calloc(rel.relwidth,sizeof(char))) == NULL)
		return  DM_errno=DME_NOMEM;

	for ( i=2; i<=argc-2; i=i+2 )				/* Create record */
	{
		for (j=0;j<rel.attrcnt;j++)
			if ( strcmp(attrs[j].attrname,argv[i]) == 0 )
				break;
		if ( attrs[j].attrtype=='i' )
		{
			tempi=atoi(argv[i+1]);
			rec+=attrs[j].offset;
			memcpy((void*)rec,(void*)&tempi,sizeof(int));
			rec-=attrs[j].offset;
		}
		else if ( attrs[j].attrtype=='f' )
		{	
			tempf=(float)atof(argv[i+1]);
			rec+=attrs[j].offset;
			memcpy((void*)rec,(void*)&tempf,sizeof(float));
			rec-=attrs[j].offset;
		}
		else
		{
			rec+=attrs[j].offset;
			memcpy((void*)rec,(void*)argv[i+1],attrs[j].attrlength);
			rec-=attrs[j].offset;
		}
		
	}
	if ( (fd=HF_OpenFile(argv[1])) < 0 ) 			/* Open relation's file to insert record */
       	{
		HF_PrintError("HF_OpenFile:");
  		return DM_errno=fd;
	}
	if ( (rval=HF_InsertRec(fd, rec,rel.relwidth)) < 0)	/* Insert record */
	{
		HF_PrintError("HF_InsertRec:");
		return DM_errno=rval;
	}
	recId=rval;
	if ( (rval=HF_CloseFile(fd)) != HFE_OK ) 		/* Close relation's file */
       	{
       		HF_PrintError("HF_CloseFile:");
       		return DM_errno=rval;
	}
 	for (j=0;j<rel.attrcnt;j++)				
 	{
		if ( attrs[j].indexed == TRUE )			/* If field is indexed insert info into index also */
		{	
			if ( (ind_d=AM_OpenIndex (attrs[j].relname,attrs[j].indexno)) < 0 ) /* open Index */	
				return DM_errno=fd;
			for ( i=0; i<=argc-2; i=i+2 )
				if ( strcmp( attrs[j].attrname,argv[i]) == 0 )
					break;
			if ( attrs[j].attrtype == 'i' )
			{
				if ( (temp=calloc(sizeof(int),sizeof(char))) == NULL)
					return  DM_errno=DME_NOMEM;
				tempi=atoi(argv[i+1]);
				memcpy(temp,&tempi,sizeof(int));
				if ( (rval=AM_InsertEntry(ind_d,attrs[j].attrtype,attrs[j].attrlength,temp,recId)) != AME_OK )
	       			{
	       				AM_PrintError("AM_InsertEntry:");
	       				return DM_errno=rval; 
	       			}
				free(temp);
			}
			else if ( attrs[j].attrtype == 'f' )
			{
				if ( (temp=calloc(sizeof(float),sizeof(char))) == NULL)
					return  DM_errno=DME_NOMEM;
				tempf=(float)atof(argv[i+1]);
				memcpy(temp,&tempf,sizeof(float));
				if ( (rval=AM_InsertEntry(ind_d,attrs[j].attrtype,attrs[j].attrlength,temp,recId)) != AME_OK )
	       			{
	       				AM_PrintError("AM_InsertEntry:");
	       				return DM_errno=rval;
	       			} 
				free(temp);
			}
			else
			{
				if ( (temp=calloc(attrs[j].attrlength,sizeof(char))) == NULL)
					return  DM_errno=DME_NOMEM;
				memcpy(temp,argv[i+1],attrs[j].attrlength);
				if ( (rval=AM_InsertEntry(ind_d,attrs[j].attrtype,attrs[j].attrlength,argv[i+1],recId)) != AME_OK )
	       			{
	       				AM_PrintError("AM_InsertEntry:");
	       				return DM_errno=rval;
	       			} 
	       			free(temp);
      			}
			if ( (rval=AM_CloseIndex(ind_d)) != AME_OK )			/* Close index */	
			{	
				AM_PrintError("AM_CloseIndex:");
				return UT_errno=rval;
			}
		}
	}
	free(rec);
	free(attrs);
	return DM_errno=DME_OK;
}



/*
 * This is a function deleting a record from relname's file,
 * If a record's field is indexed appropriate record is also
 * deleted from respective Index.Note that if no condition is
 * given all records are deleted witout the use of an indec,
 * however if a condition is given and respective field is 
 * indexed, index is used.If an error occours error code is 
 * returned and errno is set, else DME_OK is returned.
 */
int DM_delete(int argc, char* argv[])
{
	int i,j;
	int fd;
	int sd;
	int ind_d;
	int rval;
	int recId;
	int tempi;
	float tempf;
	char* temp;
	char* record;
	relDesc relRec;
    	attrDesc *attrs = NULL;

//	if( (rval=SCM_delete(argc,argv))!=UTE_OK)
//       		return DM_errno=rval;
	if ( (fd=HF_OpenFile(argv[1])) < 0 ) 				/* Open relations' file */	
       	{	
       		HF_PrintError("HF_OpenFile:");
       		return DM_errno=fd;
	}
       	if( (rval=CFM_Lookup(argv[1], &relRec, &attrs))!=UTE_OK)	/* retrieve record's information */
  		return DM_errno=rval;	
  	record = (char *) malloc((relRec.relwidth)*sizeof(char));
	if(record==NULL)
		return DM_errno=UTE_NOMEM;	
	if ( argc == 2 ) 						/* Condition is not given, delete all records */
	{
		if ( (sd=HF_OpenFileScan(fd,relRec.relwidth,' ',-1,-1,-1,(char *) NULL)) < 0 ) /* Open File Scan, index is useless */	  
		{
			HF_PrintError("HF_OpenFileScan:");
			return UT_errno=sd;	
		}
		while ( (recId=HF_FindNextRec(sd, record)) >= 0 )
			if ( (rval=HF_DeleteRec(fd,recId,relRec.relwidth)) != HFE_OK )
			{
				HF_PrintError("HF_DeleteRec:");
				return DM_errno=rval;	
			}
		if ( (rval=HF_CloseFileScan(sd)) != HFE_OK )					/* Close open scan */
		{
			HF_PrintError("HF_CloseFileScan:");
			return DM_errno=rval;
		}
	}
	else								/* Condition is given */
	{
		for (j=0;j<relRec.attrcnt;j++)				
			if ( strcmp(attrs[j].attrname,argv[argc-3]) == 0 )
				break;	
		if ( attrs[j].indexed == TRUE )				/* If field is index we should use it */
		{
			if ( (ind_d=AM_OpenIndex (attrs[j].relname,attrs[j].indexno)) < 0 ) 	
			{	
				AM_PrintError("AM_OpenIndex:");
				return DM_errno=ind_d;
			}
			if ( attrs[j].attrtype == 'i' )			/* Open index Scan depending on fields type */
			{
				if ( (temp=calloc(sizeof(int),sizeof(char))) == NULL)
					return  DM_errno=DME_NOMEM;
				tempi=atoi(argv[argc-1]);
				memcpy(temp,&tempi,sizeof(int));
				if ( (sd=AM_OpenIndexScan(ind_d, attrs[j].attrtype, attrs[j].attrlength, operator(argv[argc-2]), temp)) < 0 )
				{
					AM_PrintError("AM_OpenIndexScan:");
					return DM_errno=sd;
				}
				free(temp);
			}
			else if ( attrs[j].attrtype == 'f' )
			{
				if ( (temp=calloc(sizeof(float),sizeof(char))) == NULL)
					return  DM_errno=DME_NOMEM;
				tempf=(float)atof(argv[argc-1]);
				memcpy(temp,&tempf,sizeof(float));
				if ( (sd=AM_OpenIndexScan(ind_d, attrs[j].attrtype, attrs[j].attrlength, operator(argv[argc-2]), temp)) < 0 )
				{
					AM_PrintError("AM_OpenIndexScan:");
					return DM_errno=sd;
				}
				free(temp);
			}
			else
			{	if ( (temp=calloc(attrs[j].attrlength,sizeof(char))) == NULL)
					return  DM_errno=DME_NOMEM;
				memcpy(temp,argv[argc-1],attrs[j].attrlength);
	   		     	if ( (sd=AM_OpenIndexScan(ind_d,attrs[j].attrtype,attrs[j].attrlength,operator(argv[argc-2]),temp))< 0 )
				{
					AM_PrintError("AM_OpenIndexScan:");
					return DM_errno=sd;
				}
				free(temp);
			}
			while ( (recId=AM_FindNextEntry(sd)) >= 0 )		/* Use index to find recId */
			{
				if ( (rval=HF_DeleteRec(fd,recId,relRec.relwidth)) != HFE_OK )	/* delete particular record  from file*/
				{	
					AM_PrintError("HF_DeleteRec:");
					return DM_errno=rval;	
				}
				if ( (rval=AM_DeleteEntry(ind_d, attrs[j].attrtype,attrs[j].attrlength,NULL,recId)) != AME_OK ) /* from index */
				{
					AM_PrintError("AM_DeleteEntry:");
					return DM_errno=rval;
				}
			}
			if ( (rval=AM_CloseIndex(ind_d)) != AME_OK )		/* Close open Index */
			{
				AM_PrintError("AM_CloseIndex");
				return DM_errno=rval;		
			}
			if ( (rval=AM_CloseIndexScan(sd)) != AME_OK )		/* Close open Index scan */
			{
				AM_PrintError("AM_CloseIndexScan");
				return DM_errno=rval;	
			}
		}
		else						/* If field in not indexed , open File Scan */
		{
			if ( attrs[j].attrtype == 'i' )
			{
				if ( (temp=calloc(sizeof(int),sizeof(char))) == NULL)
					return  DM_errno=DME_NOMEM;
				tempi=atoi(argv[argc-1]);
				memcpy(temp,&tempi,sizeof(int));
				if ( (sd=HF_OpenFileScan(fd,relRec.relwidth,attrs[j].attrtype,attrs[j].attrlength
			    	,attrs[j].offset,operator(argv[argc-2]),temp)) < 0 )	  
				{
					HF_PrintError("HF_OpenFileScan:");
					return DM_errno=sd;
				}
				free(temp); 
			}
			else if ( attrs[j].attrtype == 'f' )
			{
				if ( (temp=calloc(sizeof(float),sizeof(char))) == NULL)
					return  DM_errno=DME_NOMEM;
				tempf=(float)atof(argv[argc-1]);
				memcpy(temp,&tempf,sizeof(float));
				if ( (sd=HF_OpenFileScan(fd,relRec.relwidth,attrs[j].attrtype,attrs[j].attrlength
			    	,attrs[j].offset,operator(argv[argc-2]),temp)) < 0 )	 
				{
					HF_PrintError("HF_OpenFileScan:");
					return DM_errno=sd;
				}
			    	free(temp); 
			}
			else
			{
				if ( (temp=calloc(attrs[j].attrlength,sizeof(char))) == NULL)
					return  DM_errno=DME_NOMEM;
				memcpy(temp,argv[argc-1],attrs[j].attrlength);
				if ( (sd=HF_OpenFileScan(fd,relRec.relwidth,attrs[j].attrtype,attrs[j].attrlength
			    	,attrs[j].offset,operator(argv[argc-2]),temp)) < 0 )
			    	{
			    		HF_PrintError("HF_OpenFileScan:");
			    		return DM_errno=sd;	  
			    	}
				free(temp);
			}	
    			while( (recId=HF_FindNextRec(sd, record)) >= 0)	
    				if ( (rval=HF_DeleteRec(fd,recId,relRec.relwidth)) != HFE_OK )
				{
				if( (rval=SCM_join(argc,argv))!=UTE_OK)
       		return DM_errno=rval;
		HF_PrintError("HF_DeleteRec:");
					return DM_errno=rval;
				}
			if ( (rval=HF_CloseFileScan(sd)) != HFE_OK )		/* Close open scan */
			{
				HF_PrintError("HF_CloseFileScan:");
				return DM_errno=rval;
			}
		}	
	}
	if ( (rval=HF_CloseFile(fd)) != HFE_OK )				/* Close file relName */
	{
		HF_PrintError("HF_CloseFile:");
		return DM_errno=rval;
	}
	free(record);
	free(attrs);
	return DM_errno=DME_OK;
}



/*
 * This is a function to implement selection of records
 * of a relation. If no condition is given all records are 
 * retrieved without the use of and index, but if a 
 * condition is given only records fulfilling condition 
 * should be chosen. If field is indexed index should be used.
 * Retrieved records can be either being print into stdout, or
 * being inserted into a new relation. While we are retrieving 
 * recors, we also call DM_Insert in order to insert them into
 * a temp relation containing only the needed fields.If an error
 * occours error code is returned and errno is set, otherwise 
 * DME_OK  is returned.
 */
int DM_select(int argc, char* argv[])
{
	int i;
	int j;
	int rval;
	int attrcnt;
	int fd;
	int sd;
	int ind_d;
	int mode;
	int recId;
	int myargc;
	int tempi;
	float tempf;
	char* temp;
	char* record;
	char** myargv;
	relDesc relRec;
    	attrDesc *attrs = NULL;
	

//	if( (rval=SCM_select(argc,argv))!=UTE_OK)
//       		return DM_errno=rval;
	if ( (argc+1)%2 == 0 )/* insert results into relation with name: argv[1] */
	{
		if ( (fd=HF_OpenFile(argv[3])) < 0 ) 					/* open relation's file */
       		{
       			HF_PrintError("HF_OpenFile:");
       			return DM_errno=fd;
		}
		if( (rval=CFM_Lookup(argv[3], &relRec, &attrs))!=UTE_OK)		/* retrieve information about records' format */
       			return DM_errno=rval;
       		attrcnt=atoi(argv[2]);
       		myargc=2*attrcnt+2;
		if ( (rval=Create_MakeArgs(argv,&myargv,attrcnt,relRec, attrs,mode=0)) != DME_OK )	/* make arguments for Create*/
			return DM_errno=rval;
		if ( (rval=UT_create(myargc, myargv)) != UTE_OK )			/* Create relation with name:argv[1] */
			return DM_errno=rval;
		free_args(myargv, myargc);
		record = (char *) malloc((relRec.relwidth)*sizeof(char));
		if(record==NULL)
			return DM_errno=UTE_NOMEM;
		if ( 2*attrcnt+4 == argc+1)/* where condition doesn't exist. Retrieve all records. */
 		{
 			if ( (sd=HF_OpenFileScan(fd,relRec.relwidth,' ',-1,-1,-1,(char *) NULL)) < 0 )	  
			{
				HF_PrintError("HF_OpenFileScan:");
				return UT_errno=sd;
			}
    			while(HF_FindNextRec(sd, record) >= 0)      	
  			{
				if ( (rval=Insert_MakeArgs(record,argv,&myargv,attrcnt,relRec,attrs,mode=0)) != DME_OK ) /* Inserrt meake args */
					DM_errno=rval;
				if (  (rval=DM_insert(myargc, myargv)) != DME_OK)	/* Insert recorn into relation */
					return DM_errno=rval;
				free_args(myargv, myargc);
			}//while
       			if ( (rval=HF_CloseFileScan(sd)) != HFE_OK )			/* Close open scan */
			{
				HF_PrintError("HF_CloseFileScan:");
				return DM_errno=rval;
			}
		} 
		else/* where consition exists */
		{
			for (j=0;j<relRec.attrcnt;j++)					/* find field's position */
				if ( strcmp(attrs[j].attrname,argv[argc-3]) == 0 )
					break;	
			if ( attrs[j].indexed == TRUE )/* if field is indexed, use index */
			{
				if ( (ind_d=AM_OpenIndex (attrs[j].relname,attrs[j].indexno)) < 0 ) /* Open Index */	
				{	
					AM_PrintError("AM_OpenIndex:");
					return DM_errno=ind_d;
				}
				if ( attrs[j].attrtype == 'i' )				/* Open index Scan, depending on the field's format */
				{
					if ( (temp=calloc(sizeof(int),sizeof(char))) == NULL)
						return  DM_errno=DME_NOMEM;
					tempi=atoi(argv[argc-1]);
					memcpy(temp,&tempi,sizeof(int));
					if ( (sd=AM_OpenIndexScan(ind_d, attrs[j].attrtype, attrs[j].attrlength, operator(argv[argc-2]), temp)) < 0 )
					{
						AM_PrintError("AM_OpenIndexScan");
						return DM_errno=sd;
					}
					free(temp);
				}
				else if ( attrs[j].attrtype == 'f' )
				{
					if ( (temp=calloc(sizeof(float),sizeof(char))) == NULL)
						return  DM_errno=DME_NOMEM;
					tempf=(float)atof(argv[argc-1]);
					memcpy(temp,&tempf,sizeof(float));
					if ( (sd=AM_OpenIndexScan(ind_d, attrs[j].attrtype, attrs[j].attrlength, operator(argv[argc-2]), temp)) < 0 )
					{
						AM_PrintError("AM_OpenIndexScan:");
						return DM_errno=sd;
					}
					free(temp);
				}
				else
				{	if ( (temp=calloc(attrs[j].attrlength,sizeof(char))) == NULL)
						return  DM_errno=DME_NOMEM;
					memcpy(temp,argv[argc-1],attrs[j].attrlength);
	   			     	if ( (sd=AM_OpenIndexScan(ind_d,attrs[j].attrtype,attrs[j].attrlength,operator(argv[argc-2]),temp))< 0 )
					{
						AM_PrintError("AM_OpenIndexScan:");
						return DM_errno=sd;
					}
					free(temp);
				}
				while ( (recId=AM_FindNextEntry(sd)) >= 0 )		/* retrieve RecId from Index */
				{
					if ( (rval=HF_GetThisRec(fd,recId,record, relRec.relwidth)) != HFE_OK )	/* retrieve record from file */
					{
						AM_PrintError("HF_GetThisRec:");
						return DM_errno=rval;
					}
					if ( (rval=Insert_MakeArgs(record,argv,&myargv,attrcnt,relRec,attrs,mode=0)) != DME_OK )
						return DM_errno=rval;
    				 	if (  (rval=DM_insert(myargc, myargv)) != DME_OK)/* Insert record into relation */
						return DM_errno=rval;
					free_args(myargv, myargc);
				}
 				if ( (rval=AM_CloseIndex(ind_d)) != AME_OK )		/* Close open scan */
				{
					AM_PrintError("AM_CloseIndex:");
					return DM_errno=rval;		
				}
				if ( (rval=AM_CloseIndexScan(sd)) != AME_OK )		/* Close open scan */
				{
					AM_PrintError("AM_CloseIndexScan:");
					return DM_errno=rval;	
				}
			}
			else /* If field is not index, treat the same as above witout IndexScan but FileScan */
			{
				if ( attrs[j].attrtype == 'i' )
				{
					if ( (temp=calloc(sizeof(int),sizeof(char))) == NULL)
						return  DM_errno=DME_NOMEM;
					tempi=atoi(argv[argc-1]);
					memcpy(temp,&tempi,sizeof(int));
					if ( (sd=HF_OpenFileScan(fd,relRec.relwidth,attrs[j].attrtype,attrs[j].attrlength
				    	,attrs[j].offset,operator(argv[argc-2]),temp)) < 0 )	  
					{
						HF_PrintError("HF_OpenFileScan:");
						return DM_errno=sd;
					}
					free(temp); 
				}
				else if ( attrs[j].attrtype == 'f' )
				{
					if ( (temp=calloc(sizeof(float),sizeof(char))) == NULL)
						return  DM_errno=DME_NOMEM;
					tempf=(float)atof(argv[argc-1]);
					memcpy(temp,&tempf,sizeof(float));
					if ( (sd=HF_OpenFileScan(fd,relRec.relwidth,attrs[j].attrtype,attrs[j].attrlength
				    	,attrs[j].offset,operator(argv[argc-2]),temp)) < 0 )	 
					{
						HF_PrintError("HF_OpenFileScan:");
						return DM_errno=sd;
					}
				    	free(temp); 
				}
				else
				{
					if ( (temp=calloc(attrs[j].attrlength,sizeof(char))) == NULL)
						return  DM_errno=DME_NOMEM;
					memcpy(temp,argv[argc-1],attrs[j].attrlength);
					if ( (sd=HF_OpenFileScan(fd,relRec.relwidth,attrs[j].attrtype,attrs[j].attrlength
				    	,attrs[j].offset,operator(argv[argc-2]),temp)) < 0 )
				    	{
				    		HF_PrintError("HF_OpenFileScan:");
				    		return DM_errno=sd;
				    	}	  
					free(temp);
				}	
    				while( (rval=HF_FindNextRec(sd, record)) >= 0)
    				{
     					if ( (rval=Insert_MakeArgs(record,argv,&myargv,attrcnt,relRec,attrs,mode=0)) != DME_OK )
     						return DM_errno=rval;
    				 	if (  (rval=DM_insert(myargc, myargv)) != DME_OK)
						return DM_errno=rval;
					free_args(myargv, myargc);
				}     	
       				if ( (rval=HF_CloseFileScan(sd)) != HFE_OK )		/* Close open scan */
				{
					HF_PrintError("HF_CloseFileScan:");
					return DM_errno=rval;	
				}
			}
		}
	}
	else/* IF results should be print into stdout we should use the same way as above, */
	    /* but we insert results into a temp relation, which will be destroyed afterwards. */
	{	
		if ( (fd=HF_OpenFile(argv[2])) < 0 ) 	
       		{

			HF_PrintError("HF_OpenFile:");
 			return DM_errno=fd;
		}
		if( (rval=CFM_Lookup(argv[2], &relRec, &attrs)) != UTE_OK)
       			return DM_errno=rval;
       		attrcnt=atoi(argv[1]);
        	myargc=2*attrcnt+2;
       		if ( (rval=Create_MakeArgs(argv,&myargv,attrcnt,relRec, attrs,mode=-1)) != DME_OK )	 
			return DM_errno=rval;
		if ( (rval=UT_create(myargc, myargv)) != UTE_OK )
			return DM_errno=rval;
		free_args(myargv, myargc);
		record = (char *) malloc((relRec.relwidth)*sizeof(char));
		if(record==NULL)
			return UT_errno=DME_NOMEM;

		if ( 2*attrcnt+3 == argc+1) /* where condition doesn't exist. Retrieve all records. */						
 		{
 			if ( (sd=HF_OpenFileScan(fd,relRec.relwidth,' ',-1,-1,-1,(char *) NULL)) < 0 )	  
			{
				HF_PrintError("HF_OpenFileScan:");
				return UT_errno=sd;			
    			}
    			while( HF_FindNextRec(sd, record) >= 0)
    			{
    				 if ( (rval=Insert_MakeArgs(record,argv,&myargv,attrcnt,relRec,attrs,mode=-1)) != DME_OK )
    				 	return DM_errno=rval;
    				 if (  (rval=DM_insert(myargc, myargv)) != DME_OK)
					return DM_errno=rval;
				 free_args(myargv, myargc);
			}
			
       			if ( (rval=HF_CloseFileScan(sd)) != HFE_OK )			
			{
				HF_PrintError("HF_CloseFileScan:");
				return DM_errno=rval;
			}
			if ( (rval=UT_print("TempRelation")) != UTE_OK )
				return DM_errno=rval;
			myargc=2;
			if ( (rval=Destroy_MakeArgs(&myargv,"TempRelation",myargc)) != DME_OK )
				return DM_errno=rval;
			if ( (rval=UT_destroy(myargc,myargv)) != UTE_OK )
				return DM_errno=rval;
			free_args(myargv, myargc);
		}
		else /* where condition exists.*/									
		{
			for (j=0;j<relRec.attrcnt;j++)
				if ( strcmp(attrs[j].attrname,argv[argc-3]) == 0 )
					break;	
			if ( attrs[j].indexed == TRUE )
			{
				if ( (ind_d=AM_OpenIndex (attrs[j].relname,attrs[j].indexno)) < 0 ) 	
				{
					AM_PrintError("AM_OpenIndex:");
					return DM_errno=ind_d;
				}
				if ( attrs[j].attrtype == 'i' )
				{
					if ( (temp=calloc(sizeof(int),sizeof(char))) == NULL)
						return  DM_errno=DME_NOMEM;
					tempi=atoi(argv[argc-1]);
					memcpy(temp,&tempi,sizeof(int));
					if ( (sd=AM_OpenIndexScan(ind_d, attrs[j].attrtype, attrs[j].attrlength, operator(argv[argc-2]), temp)) < 0 )
					{
						AM_PrintError("AM_OpenIndexScan:");
						return DM_errno=sd;
					}
					free(temp);
				}
				else if ( attrs[j].attrtype == 'f' )
				{
					if ( (temp=calloc(sizeof(float),sizeof(char))) == NULL)
						return  DM_errno=DME_NOMEM;
					tempf=(float)atof(argv[argc-1]);
					memcpy(temp,&tempf,sizeof(float));
					if ( (sd=AM_OpenIndexScan(ind_d, attrs[j].attrtype, attrs[j].attrlength, operator(argv[argc-2]), temp)) < 0 )
					{
						AM_PrintError("AM_OpenIndexScan:");
						return DM_errno=sd;
					}
					free(temp);
				}
				else
				{
					if ( (temp=calloc(attrs[j].attrlength,sizeof(char))) == NULL)
						return  DM_errno=DME_NOMEM;
					memcpy(temp,argv[argc-1],attrs[j].attrlength);
	   			     	if ( (sd=AM_OpenIndexScan(ind_d,attrs[j].attrtype,attrs[j].attrlength,operator(argv[argc-2]),temp))< 0 )
					{
						AM_PrintError("AM_OpenIndexScan:");
						return DM_errno=sd;
					}
					free(temp);
				}
				while ( (recId=AM_FindNextEntry(sd)) >= 0 )
				{
					if ( (rval=HF_GetThisRec(fd,recId,record, relRec.relwidth)) != HFE_OK )
					{
						AM_PrintError("HF_GetThisRec:");
						return DM_errno=rval;
					}
					if ( (rval=Insert_MakeArgs(record,argv,&myargv,attrcnt,relRec,attrs,mode=-1)) != DME_OK )
						return DM_errno=rval;
    				 	if (  (rval=DM_insert(myargc, myargv)) != DME_OK)
						return DM_errno=rval;
					free_args(myargv, myargc);
				}
 				if ( (rval=UT_print("TempRelation")) != UTE_OK )
					return DM_errno=rval;
				myargc=2;
				if ( (rval=Destroy_MakeArgs(&myargv,"TempRelation",myargc)) != DME_OK )
					return DM_errno=rval;
				if ( (rval=UT_destroy(myargc,myargv)) != UTE_OK )
					return DM_errno=rval;
				free_args(myargv, myargc);
				if ( (rval=AM_CloseIndexScan(sd)) != AME_OK )		
				{
					AM_PrintError("AM_CloseIndexScan:");
					return DM_errno=rval;
				}
				if ( (rval=AM_CloseIndex(ind_d)) != AME_OK )		
				{
					AM_PrintError("AM_CloseIndex:");
					return DM_errno=rval;
				}		
			}
			else 
			{
				if ( attrs[j].attrtype == 'i' )
				{
					if ( (temp=calloc(sizeof(int),sizeof(char))) == NULL)
						return  DM_errno=DME_NOMEM;
					tempi=atoi(argv[argc-1]);
					memcpy(temp,&tempi,sizeof(int));
					if ( (sd=HF_OpenFileScan(fd,relRec.relwidth,attrs[j].attrtype,attrs[j].attrlength
				    	     ,attrs[j].offset,operator(argv[argc-2]),temp)) < 0 )	  
					{
						HF_PrintError("HF_OpenFileScan:");
						return DM_errno=sd;
					}
					free(temp); 
				}
				else if ( attrs[j].attrtype == 'f' )
				{
					if ( (temp=calloc(sizeof(float),sizeof(char))) == NULL)
						return  DM_errno=DME_NOMEM;
					tempf=(float)atof(argv[argc-1]);
					memcpy(temp,&tempf,sizeof(float));
					if ( (sd=HF_OpenFileScan(fd,relRec.relwidth,attrs[j].attrtype,attrs[j].attrlength
				    	,attrs[j].offset,operator(argv[argc-2]),temp)) < 0 )	 
					{
						HF_PrintError("HF_OpenFileScan:");
						return DM_errno=sd;
				    	}
				    	free(temp); 
				}
				else
				{
					if ( (temp=calloc(attrs[j].attrlength,sizeof(char))) == NULL)
						return  DM_errno=DME_NOMEM;
					memcpy(temp,argv[argc-1],attrs[j].attrlength);
					if ( (sd=HF_OpenFileScan(fd,relRec.relwidth,attrs[j].attrtype,attrs[j].attrlength
				    	,attrs[j].offset,operator(argv[argc-2]),temp)) < 0 )
				    	{
				    		HF_PrintError("HF_OpenFileScan:");
				    		return DM_errno=sd;	  
				    	}
				    	free(temp);
				}	
    				while( (rval=HF_FindNextRec(sd, record)) >= 0)
    				{
     					if ( (rval=Insert_MakeArgs(record,argv,&myargv,attrcnt,relRec,attrs,mode=-1)) != DME_OK )
     						return DM_errno=rval;
    				 	if (  (rval=DM_insert(myargc, myargv)) != DME_OK)
						return DM_errno=rval;
					free_args(myargv, myargc);
				}     	
 				if ( (rval=UT_print("TempRelation")) != UTE_OK )
					return DM_errno=rval;
				myargc=2;
				Destroy_MakeArgs(&myargv,"TempRelation",myargc);
				if ( (rval=UT_destroy(myargc,myargv)) != UTE_OK )
					return DM_errno=rval;
				free_args(myargv, myargc);
       				if ( (rval=HF_CloseFileScan(sd)) != HFE_OK )		
				{
					HF_PrintError("HF_CloseFileScan:");
					return DM_errno=rval;	
				}
			}
		}/* second else */
	}/* Outer else */
	if ( (rval=HF_CloseFile(fd)) != HFE_OK )	/* Close file */				
	{
		HF_PrintError("HF_CloseFile:");
		return DM_errno=rval;
	}
	free(record);
	free(attrs);
	return DM_errno=DME_OK;
}


int DM_join(int argc, char* argv[]){

	int             noofelements;
	int		op;
	int		length;	
	int		i,j;
	int		k=0,l,p;
	int             fd1,fd2;
	int		rval;
	int		index;
	int		recId;
	int             sd1,sd2;
	int		help,help1,help2;
	int		scan,fd;
	float           flo,flo1,flo2;
	int 		dargc;
	char 		**dargv;
	int		myargc;
	char		**myargv;
	char            relation1[MAXNAME],relation2[MAXNAME],name[MAXNAME];
	char            *record,*record1,*record2;
	char		*string,*string1,*string2;
	char		*matrix;
	char            *temp = NULL;
	relDesc         relRec1,relRec2,relRec;
	attrDesc        *attrs1 = NULL,*attrs2=NULL,attrs,*requestedAttr=NULL;

//	if( (rval=SCM_join(argc,argv))!=UTE_OK)
//       		return DM_errno=rval;
     	
	op=operator(argv[argc-3]);		/* operator for Scan */
	strcpy(relation1, argv[argc-5]);        /* name of first relation */
	strcpy(relation2, argv[argc-2]);        /* name of second relation */

	if(isdigit(*argv[1])==0)		/* if argv[1] is not a digit results should be kept into a new relation*/
	{
 		strcpy(name, argv[1]);
 		noofelements=atoi(argv[2]);
 		p=3;
	}
	else{                           	/* else results should be kept into a temp relation till they print into screen */
 		strcpy(name,"temp_rel");
 		noofelements=atoi(argv[1]);
 		p=2;
	}

	if( (fd1=HF_OpenFile(relation1)) < 0 )	/* Opening relation1 */
	{	
		HF_PrintError("HF_OpenFile:");
		return (DM_errno=fd1);
	}
	if( (fd2=HF_OpenFile(relation2)) < 0 )	/* Opening relation2 */
	{
		HF_PrintError("HF_OpenFile:");
		return (DM_errno=fd2);
	}

	if( (rval=CFM_Lookup(relation1, &relRec1, &attrs1)) != UTE_OK )          /* retrive records' format */
       		return DM_errno=rval;


	if( (rval=CFM_Lookup(relation2, &relRec2, &attrs2)) != UTE_OK )          
       		return DM_errno=rval;
		
								//euresi megethous eggrafis,arxeiou apotelesmaton
	requestedAttr = malloc(noofelements * sizeof(attrDesc));       //autos einai o pinakas me ta orismata pou mas zitithikan na ektiposoume
	if(requestedAttr==NULL)
	{
		fprintf(stderr,"malloc failed\n"); 
		return DM_errno=UTE_NOMEM;
	}
	int flag;
	for(i=0,k=0,length=0;i<noofelements;i++)
	{                    					//psaxnoume gia ola ta stoixeia pou mas zitithikan na ektipothoun   		for(l=0;l<relRec1.attrcnt;l++)                //arxika psaxnoume stous pinakes tis protis sxesis
		{
     			if(strcmp(attrs1[l].relname,argv[p])==0 && strcmp(attrs1[l].attrname,argv[p+1]) == 0 )
     			{//to p orizete ston elegxo gia to an iparxei to proeretiko orisma i oxi
          			length=length+attrs1[l].attrlength;                            
          			memcpy(&requestedAttr[k++], &attrs1[l], sizeof(attrDesc)); 
         			//bazoume ston pinaka requestedAttr ta stoixeia gia ta attributes pou theloume na ektiposoume
          			break;
          		}
          	}
          	for(j=0;j<relRec2.attrcnt;j++)
		{
     			if(strcmp(attrs2[j].relname,argv[p])==0 && strcmp(attrs2[j].attrname,argv[p+1]) == 0 )
     			{
          			length=length+attrs2[j].attrlength;
          			memcpy(&requestedAttr[k++], &attrs2[j], sizeof( attrDesc));
          			break;
          		}
  		}
  		p=p+2;            //to p auxanete kathe fora kata dio                    

	}
	myargc = 3 + 2*noofelements;                //myargc gia ti UT_Create
	myargv = malloc(myargc * sizeof(char*));                //myargv gia ti UT_Create
	if(myargv==NULL)
	{
		fprintf(stderr,"malloc failed\n"); 
		return DM_errno=UTE_NOMEM;
	}
	myargv[0] = "create";                 
	if( (myargv[1] = malloc(MAXNAME * sizeof(char))) == NULL )
	{
		fprintf(stderr,"malloc failed\n"); 
		return DM_errno=UTE_NOMEM;
	}
	memcpy(myargv[1], name, MAXNAME);          
	//to myargv[1] tha einai eite to proeretiko orisma eite tha exei onoma temp_rel (i metavliti name orizete parapano)
	for( i=2; i<myargc-1; i+=2)
	{                 //gia ola ta attributes pou tha exei i nea mas sxesi
		if( (myargv[i] = malloc(MAXNAME)) == NULL )           //kanoume malloc to name prota
		{
			fprintf(stderr,"malloc failed\n"); 
			return DM_errno=UTE_NOMEM;
		}
		if( (myargv[i+1] = malloc(7*sizeof(char))) == NULL )        //malloc gia ton tipo (7 epeidi to maximum einai "cXXX\0"
		{
			fprintf(stderr,"malloc failed\n"); 
			return DM_errno=UTE_NOMEM;
		}		
	}
	myargv[myargc-1] = NULL;             //to teleuteo einai to NULL

	for( i=0, j=2; i < noofelements; i++, j+=2 )
	{             //to myargv arxizei apo to 2,kanoume copy oti xreiazete
     		memcpy(myargv[j], requestedAttr[i].attrname, MAXNAME);
     		if( requestedAttr[i].attrtype == 'c' )
			sprintf( myargv[j+1], "\'c%d\'", requestedAttr[i].attrlength );
  	 	else
			sprintf( myargv[j+1], "\'%c\'", requestedAttr[i].attrtype );
	}
	myargc--;
	if( (rval=UT_create(myargc, myargv)) != UTE_OK)              //kaloume ti UT_create
   		return DM_errno=rval;
	for( i=1; i < myargc-1; i++ )            //free
		free(myargv[i]);
	free(myargv);

	if( (fd=HF_OpenFile(name)) < 0 )		/* Opening file with name argv[1] or temp_rel */
	{
		HF_PrintError("HF_OpenFile");
		return (DM_errno=fd);
	}
	record = (char *) malloc(length*sizeof(char));
	//i metavliti record tha exei argotera mesa ola ta attributes pou prepei na ektiposoume gia auto ginete malloc me mikos length
	if(record==NULL)
	{	
		fprintf(stderr,"malloc failed\n"); 
		return DM_errno=UTE_NOMEM;
	}
          

	for(i=0;i<relRec1.attrcnt;i++)//vriskoume ta sigekrimena attributes apo ti mia kai tin alli sxesi pou tha xrisimopoiisoume gia tis sigriseis mas
  		if(strcmp(attrs1[i].attrname,argv[argc-4])==0)
	        	break;
	for(j=0;j<relRec2.attrcnt;j++)
		if(strcmp(attrs2[j].attrname,argv[argc-1])==0)
          		break;
	if( attrs1[j].indexed == FALSE && attrs2[i].indexed == FALSE )
	{          //an den exei kanena euretirio tote xrisimopoioume aples HF sinartiseis
		if ( (sd1=HF_OpenFileScan(fd1,relRec1.relwidth,' ',-1,-1,-1,(char *) NULL)) < 0 )
  		{/* Start a new scan on records of file relName.This scan will return all the records of file relName*/
			HF_PrintError("HF_HF_OpenFileScan:");
			return DM_errno=sd1;                                     //kaloume me NULL gia na paroume oli tin eggrafi
		}
  		record1 = (char *) malloc((relRec1.relwidth)*sizeof(char));                    //i record1 tha exei tis eggrafes tis protis sxesis
  		if(record1==NULL)
  		{
  			fprintf(stderr,"malloc failed\n"); 
  			return UT_errno=UTE_NOMEM;
  		}
    
	  	record2 = (char *) malloc((relRec2.relwidth)*sizeof(char));
  		if(record2==NULL)
  		{
  			fprintf(stderr,"malloc failed\n"); 
  			return UT_errno=UTE_NOMEM;
  		}
  

  		while(HF_FindNextRec(sd1, record1) >= 0)
  		{
     
 	    		record1=record1+attrs1[i].offset;             
	     		//pigenoume ekei pou prepei na kanoume ti sigrisi,sto sigekrimeno attribute diladi
  	   
    	 		if ( (sd2=HF_OpenFileScan(fd2,relRec2.relwidth,attrs1[i].attrtype,attrs2[j].attrlength,attrs2[j].offset,op,record1))<0)	  
			{
				HF_PrintError("HF_OpenFileScan:");
				return UT_errno=sd2;              
			}         
     			//anoigoume ena scannarisma dinontas op kai record1,ekei omos pou tha eprepe na einai gia na iparxei elegxos
     
     			record1=record1-attrs1[i].offset;               //epistrofi tou deikti stin arxi
     			while(HF_FindNextRec(sd2, record2) >= 0)
     			{
        	        	for(k=0;k<noofelements;k++)
				{
             				if( strcmp(requestedAttr[k].relname,relation1)==0 )
              				{            
              					//an to sigekrimeno attribute einai tis relation1 tote prepei na to paroume apo to record1
				 		record1 = record1 + requestedAttr[k].offset;              //to pame ekei pou prepei
				 		memcpy(record, record1, requestedAttr[k].attrlength);          //to adigrafoume sto record
                 				record1 = record1 - requestedAttr[k].offset;                 //to girizoume piso
                 				record=record+requestedAttr[k].attrlength;         //auxanoume to deikti kata to mikos pou grapsame
              				}
		      			else
		      			{
		         			record2 = record2 + requestedAttr[k].offset;
                 				memcpy(record, record2, requestedAttr[k].attrlength);
                 				record2 = record2 - requestedAttr[k].offset;
                 				record=record+requestedAttr[k].attrlength;
              				}
              			}
        			record-=length;
       				if((rval=HF_InsertRec(fd,record,length))<0)                     //vazoume tin eggrafi sto arxeio name
          			{
          				HF_PrintError("HF_InsertRec:");
          				return DM_errno=rval;
     				}
     			}//while
  			if ( (rval=HF_CloseFileScan(sd2)) != HFE_OK )							/* Close open scan */
			{
				HF_PrintError("HF_CloseFileScan:");
				return UT_errno=rval;    
			}
		}//while
 		if ( (rval=HF_CloseFileScan(sd1)) != HFE_OK )							/* Close open scan */
		{
			HF_PrintError("HF_CloseFileScan:");
			return DM_errno=rval;
		}
 		if ( (rval=HF_CloseFile(fd)  !=  HFE_OK ))							/* Close file relName */
		{
			HF_PrintError("HF_CloseFile:");
			return DM_errno=rval;
		}
 		if(isdigit(*argv[1])!=0)
 		{
		
	 		if((rval=UT_print(name))!=UTE_OK)                //tiponoume oles tis eggrafes tou arxeiou name me ti UT_Print
	    			return DM_errno=rval;
	                //an den iparxei to proeretiko arxeio tote katastrefoume to prosorino pou ftiaxame		dargc = 3;
 			dargc=3;
 			dargv = malloc(dargc * sizeof(char*));
   	 		if(dargv==NULL)
    			{
    				fprintf(stderr,"malloc failed\n"); 
    				return DM_errno=UTE_NOMEM;
    			}
			for(i=0;i<3;i++)
    				if  ( (dargv[i]=malloc(MAXNAME*sizeof(char))) == NULL )
    				{
    					fprintf(stderr,"malloc failed\n"); 
		    			return DM_errno=UTE_NOMEM;
   				}   			
			strcpy(dargv[0] , "destroy");
			strcpy(dargv[1],name);
			dargv[2] = NULL;
			if((rval = UT_destroy(dargc-1, dargv))!= UTE_OK )
		   		return DM_errno=rval;
		   	for( i=0; i < dargc; i++ )            //free	
				free(dargv[i]);
	    		free(dargv);		}
  		free(record1);
 		free(record2);
 		if ( (rval=HF_CloseFile(fd1) != HFE_OK ))							/* Close file relName */
		{
			HF_PrintError("HF_CloseFile:");
			return DM_errno=rval;
		}
		if ( (rval=HF_CloseFile(fd2) != HFE_OK ))							/* Close file relName */
		{
			HF_PrintError("HF_CloseFile:");
			return DM_errno=rval;
		}
		return DME_OK;
	}//if both not indexed

	if(attrs2[j].indexed == FALSE)
	{       
		//an ena apo ta dio einai TRUE tote mas endiaferei mono an to deutero einai FALSE kai to proto TRUE.Tote prepei na kanoume swap 
		//ta stoixeia oste na mpei .apo mesa to stoixeio me to euretirio
		//swaps first the relRec
  		strcpy(relRec.relname,relRec1.relname);
  		strcpy(relRec1.relname,relRec2.relname);
  		strcpy(relRec2.relname,relRec.relname);
  		relRec.relwidth=relRec1.relwidth;
  		relRec1.relwidth=relRec2.relwidth;
  		relRec2.relwidth=relRec.relwidth;              
  		relRec.attrcnt=relRec1.attrcnt;
  		relRec1.attrcnt=relRec2.attrcnt;
  		relRec2.attrcnt=relRec.attrcnt;           
  		relRec.indexcnt=relRec1.indexcnt;
  		relRec1.indexcnt=relRec2.indexcnt;
  		relRec2.indexcnt=relRec.indexcnt;
  		//now the attrRecs
  		strcpy(attrs.relname,attrs1[i].relname);
  		strcpy(attrs1[i].relname,attrs2[j].relname);
  		strcpy(attrs2[j].relname,attrs.relname);                  
  		strcpy(attrs.attrname,attrs1[i].attrname);
  		strcpy(attrs1[i].attrname,attrs2[j].attrname);
  		strcpy(attrs2[j].attrname,attrs.attrname);       
  		attrs.offset=attrs1[i].offset;
  		attrs1[i].offset=attrs2[j].offset;
  		attrs2[j].offset=attrs.offset;
  		attrs.attrlength=attrs1[i].attrlength;
  		attrs1[i].attrlength=attrs2[j].attrlength;
  		attrs2[j].attrlength=attrs.attrlength;
  		attrs.attrtype=attrs1[i].attrtype;
  		attrs1[i].attrtype=attrs2[j].attrtype;
  		attrs2[j].attrtype=attrs.attrtype;
  		attrs.indexed=attrs1[i].indexed;
  		attrs1[i].indexed=attrs2[j].indexed;
  		attrs2[j].indexed=attrs.indexed;
  		attrs.indexno=attrs1[i].indexno;
  		attrs1[i].indexno=attrs2[j].indexno;
  		attrs2[j].indexno=attrs.indexno;
	}

  	if ( (sd1=HF_OpenFileScan(fd1,relRec1.relwidth,' ',-1,-1,-1,(char *) NULL)) < 0 )	  
  	{/* Start a new scan on records of file relName.This scan will return all the records of file relName*/
		HF_PrintError("HF_OpenFileScan:");
		return DM_errno=sd1;
	}

  	index=AM_OpenIndex (attrs2[j].relname,attrs2[j].indexno);                 //anoigma tou euretiriou

 	record1 = (char *) malloc((relRec1.relwidth)*sizeof(char));
  	if(record1==NULL)
  	{
  		fprintf(stderr,"malloc failed\n"); 
  		return DM_errno=UTE_NOMEM;
  	}
    
  	record2 = (char *) malloc((relRec2.relwidth)*sizeof(char));
  	if(record2==NULL)
  	{
  		fprintf(stderr,"malloc failed\n"); 
  		return DM_errno=UTE_NOMEM;
  	}
  
  	while(HF_FindNextRec(sd1, record1) >= 0)
  	{             
     
     		record1=record1+attrs1[i].offset;
     
     		if ( (scan=AM_OpenIndexScan(index,attrs2[j].attrtype,attrs2[j].attrlength,op,record1)) < 0 )  //lathos edo to record1
      		{
      			AM_PrintError("AM_OpenIndexScan:");
      			return DM_errno=sd2;                     //anoigma sarosis me to euretirio
    		}
     		record1=record1-attrs1[i].offset;
     
     		while((recId=AM_FindNextEntry(scan))>= 0)
     		{                   //vres tin epomeni pou ikanopoiei ta kritiria
        
        		if((rval=HF_GetThisRec(fd2,recId,record2,relRec2.relwidth)) != HFE_OK )
          		{
          			HF_PrintError("HF_GetThisRec:");
          			return DM_errno=rval;                           //pare tin eggrafi pou epestrepse i AM_FindNextEntry
        		}
        		for(k=0;k<noofelements;k++)                                 //same as in previous case
              			if( strcmp(requestedAttr[k].relname,relation1)==0 )
              			{
					record1 = record1 + requestedAttr[k].offset;
				 	memcpy(record, record1, requestedAttr[k].attrlength);
                 			record1 = record1 - requestedAttr[k].offset;
                 			record=record+requestedAttr[k].attrlength;
              			}
		      		else
		      		{
		         		record2 = record2 + requestedAttr[k].offset;
                 			memcpy(record, record2, requestedAttr[k].attrlength);
                 			record2 = record2 - requestedAttr[k].offset;
                 			record=record+requestedAttr[k].attrlength;
              			}
        
       			if((rval=HF_InsertRec(fd,record,length))<0)
          		{
          			HF_PrintError("HF_InsertRec:");
          			return DM_errno=rval;
          		}
     		}//while
  		if ( (rval=AM_CloseIndexScan(scan)) != AME_OK )							/* Close open scan */
		{	
			AM_PrintError("AM_CloseIndexScan:");
			return DM_errno=rval;    
		}
 	}//while
 
 	if((rval=UT_print(name))!=UTE_OK)
    		return DM_errno=rval;
 
 	if(isdigit(*argv[1])!=0)
 	{                          //an den iparxei to proeretiko arxeio tote katastrefoume to prosorino pou ftiaxame
    		dargc = 3;
    		dargv = malloc(dargc * sizeof(char*));
    		if(dargv==NULL)
    		{
    			fprintf(stderr,"malloc failed\n"); 
    			return DM_errno=UTE_NOMEM;
    		}
    		dargv[0] = "destroy";
		strcpy(dargv[1],name);
		dargv[2] = NULL;
		if((rval = UT_destroy(dargc, dargv))!= UTE_OK )
	   		return DM_errno=rval;
    		for( i=1; i < dargc-1; i++ )            //free
			free(dargv[i]);
    	free(dargv);
	}
 
 	free(record1);
 	free(record2);
 	if ( (rval=HF_CloseFileScan(sd1)) != HFE_OK )							/* Close open scan */
	{
		HF_PrintError("HF_CloseFileScan:");
		return DM_errno=rval;
	}
 	if ( (rval=AM_CloseIndex (index)) != AME_OK )
     	{
     		AM_PrintError("AM_CloseIndex:");
     	  	return DM_errno=rval;
     	}
	if ( (rval=HF_CloseFile(fd) != HFE_OK ))							/* Close file relName */
	{
		HF_PrintError("HF_CloseFile:");
		return DM_errno=rval;       
	}
 	if ( (rval=HF_CloseFile(fd1) != HFE_OK ))							/* Close file relName */
	{
		HF_PrintError("HF_CloseFile:");
		return DM_errno=rval;
	}
 	if ( (rval=HF_CloseFile(fd2)) != HFE_OK )							/* Close file relName */
	{
		HF_PrintError("HF_CloseFile:");
		return DM_errno=rval;
	}
 	return DME_OK;
}//if at least one is indexed
