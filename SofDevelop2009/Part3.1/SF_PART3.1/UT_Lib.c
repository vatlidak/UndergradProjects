#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#include "BF_Defines.h"
#include "BF_Lib.h"

//#include "HF_Defines.h"
#include "HF_Lib.h"

#include "UT_DM_Defines.h"
#include "CFM_Lib.h"
#include "SCM_Lib.h"
#include "UT_Lib.h"
#include "AM_Lib.h"


/*
 * This function creates a new relation named argv[1] 
 * with attributes argv[2],argv[4],argv[6],
 * of type argv[3],argv[5],argv[7],... respectively
 */
int UT_create(int argc, char* argv[])
{
	int 	k;
	int 	i=0,j=0;
	int 	relwidth=0;
	int 	fd;
	int 	rval;
	relDesc rel;
    	attrDesc rel_attrDesc[((argc-2)/2)];
    
    	if( (rval=SCM_create(argc,argv))!=UTE_OK)      	/* Semantic Check */
     		return UT_errno=rval;
   	if ( (rval=HF_CreateFile(argv[1]))!=HFE_OK ) 	/* Create file: argv[1] */
       		return UT_errno=rval;
                                          		/* fill the rel struct */
	strcpy(rel.relname,argv[1]);         		/* start with name */
    	i=2;
    	while(argv[i]!=NULL)
    	{                				/* find the relwidth delimeter when NULL is found */
      		if( argv[i+1][1]=='i')
         		relwidth=relwidth+sizeof(int);
      		else if(  argv[i+1][1]=='f' )
         		relwidth=relwidth+sizeof(float);
      		else
         		relwidth=relwidth+atoi(argv[i+1]+2);
      		i=i+2;
    	}
        rel.relwidth=relwidth;
    	rel.attrcnt=((argc-2)/2);          		/* number of attributes of the relation argv[1] */
    	rel.indexcnt=0;                     		/* start with 0 indexes */
 	i=2;
    	while(argv[i]!=NULL)
    	{
    		strcpy(rel_attrDesc[j].relname,argv[1]);
        	strcpy(rel_attrDesc[j].attrname,argv[i]);
		if(argv[i+1][1]=='i')                   /* length of current attribute */
          		rel_attrDesc[j].attrlength=sizeof(int);
        	else if(argv[i+1][1]=='f')           
          		rel_attrDesc[j].attrlength=sizeof(float);
        	else
          		rel_attrDesc[j].attrlength=atoi(argv[i+1]+2);

	        if(j!=0)
       	  		rel_attrDesc[j].offset=rel_attrDesc[j-1].offset + rel_attrDesc[j-1].attrlength ;
       	  		/*offset is sum of offset and length of the previous attribute.*/
      		else
          		rel_attrDesc[j].offset=0;      	/* if this is the first attribute,offset =0 */
        	if( argv[i+1][1]=='i' )                 /* attrtype of current attribute */
          		rel_attrDesc[j].attrtype='i';
        	else if( argv[i+1][1]=='f' )
          		rel_attrDesc[j].attrtype='f';
        	else
          		rel_attrDesc[j].attrtype='c';
        	rel_attrDesc[j].indexed=0;
        	rel_attrDesc[j].indexno=-1;
        	i=i+2;
        	j=j+1;
    	}/*while*/
    	if ( (rval=CFM_AddRel(rel,rel_attrDesc)) != UTE_OK ) 	/* Add relDesc and attrDesc to respective files */
    		return UT_errno = rval;
    	return UT_errno=UTE_OK;
}

/*
 * This function builds a new index 
 * on attribute argv[2] of relation argv[1]
 */
int UT_buildindex(int argc, char* argv[])
{
    	int	    i;
    	int         rval;
    	relDesc     relRec;
    	attrDesc    *attrs = NULL;
    
    	if( (rval=SCM_buildIndex(argc,argv))!=UTE_OK)		/* Semantic Check */
       		return UT_errno=rval;
    
    	if( (rval=CFM_Lookup(argv[1], &relRec, &attrs))!=UTE_OK)/* lookup enables us access the relDesc and attrDesc info of the relation argv[1] */
       		return UT_errno=rval;

    	for(i=0;i<relRec.attrcnt;i++)                     	/* find the position of attrs table where the attrname we look for is */
       		if(strcmp(attrs[i].attrname,argv[2])==0)
          		break;

    	if((rval=AM_CreateIndex(argv[1],relRec.indexcnt,attrs[i].attrtype,attrs[i].attrlength))!=AME_OK)    /*create the index*/
       		return UT_errno=rval;

    	if((rval=CFM_IndexAttribute(argv[1],argv[2],relRec.indexcnt))!= UTE_OK)	/* update the index related info for argv[2] of relation argv[1] */
       		return UT_errno=rval;
  	free(attrs);		          			/* free space allocated on CFM_Lookup */
    	return UT_errno=UTE_OK;
}



/*
 * This function destroys everything related 
 * to relation argv[1]
 */
int UT_destroy(int argc, char* argv[])
{
	int 	i=0;
    	int 	noofindexs;
    	int	recId;
    	int	rval;
    	int	attrcount;
    	int	relwidth=0;
    	relDesc relRec;
    	attrDesc *attrs = NULL;
    	char	 *rel,*name;
 
    	if( (rval=SCM_destroy(argc,argv))!=UTE_OK)		/* Semantic Check */
       		return UT_errno=rval;
      	if ( (rval=HF_DestroyFile(argv[1])) != HFE_OK )         /* destroy the argv[1]  file */
    		return UT_errno=rval;
    	if( (rval=CFM_Lookup(argv[1], &relRec, &attrs))!=UTE_OK)/* lookup enables us to access  relDesc and attrDesc info of the relation argv[1] */
       		return UT_errno=rval; 
    
    	for(i=0;i<relRec.indexcnt;i++)                         /* destroy all the indexes that exist for this relation */
    		if((rval=AM_DestroyIndex(argv[1],i))!=AME_OK)
        		return UT_errno=rval;
    
    	if ((rval=CFM_DeleteRel(argv[1]))!=UTE_OK)             	/*CFM_DeleteRel delete the info of this relation from the database catalogs*/ 
    		return UT_errno=rval;
	free(attrs);		          			/* free space allocated on CFM_Lookup */
   	return UT_errno=UTE_OK;
}

/*
 * This function closes the relCat and attrCat files
 */
int UT_quit(void)
{
	int rval;
	  
    	if( ( rval=HF_CloseFile(relCatFd) ) != HFE_OK)
       		return UT_errno=rval;
    
    	if( ( rval=HF_CloseFile(attrCatFd) ) != HFE_OK)
       		return UT_errno=rval;
        exit(1);    
}




/*
 *This function prints all the records of relation relname
 */
int UT_print(char* relName)
{
	int	rval;
	int	sd;
	int 	fd;
	int	i;
	int	help;
    	float   help1;
    	char	*string,*record;
    	relDesc relRec;
    	attrDesc *attrs = NULL;
    ///	if( (rval=SCM_print(relName))!=UTE_OK)			/* Semantic Check */
//       		return UT_errno=rval;
    
    	if( (rval=CFM_Lookup(relName , &relRec, &attrs))!=UTE_OK)      /* lookup enables us access the relDesc and attrDesc info of relation argv[1] */
       		return UT_errno=rval;
        if ( (rval=HF_OpenFile(relName)) < 0 )		/* opening file relName */
		return UT_errno=rval;
    
    	fd=rval;
    
    	if ( (sd=HF_OpenFileScan(fd,relRec.relwidth,' ',-1,-1,-1,(char *) NULL)) < 0 )	  
    	/* Start a new scan on records of file relName.This scan will return all the records of file relName*/
		return UT_errno=sd;
    
    	record = (char *) malloc((relRec.relwidth)*sizeof(char));
    	if(record==NULL)
    		return UT_errno=UTE_NOMEM;
    	while(HF_FindNextRec(sd, record) >= 0)               		/* bring every record of file relName */
	{
       		for(i=0;i<relRec.attrcnt;i++)                  		/* for all the attributes of the given record */
		{
         		if(attrs[i].attrtype=='i')             		/* if the given attribute is integer then read it like an integer */
            		{
 				record+=attrs[i].offset; 
             			memcpy( (void*)&help, (int*)record, sizeof(int));         //read it */
				record-=attrs[i].offset;
             			fprintf(stderr,"%d ",help);
            		}                                             	/* 'f' and 'c' are exactly the same */
         		if(attrs[i].attrtype=='f')
            		{
            			record+=attrs[i].offset;
            			memcpy( (void*)&help1, (float*)record, sizeof(float));
				record-=attrs[i].offset;
            			fprintf(stderr,"%.2f ",help1);
            		}
         		if(attrs[i].attrtype=='c')
         		{
             			string=malloc(sizeof(char)*attrs[i].attrlength);
            			if(string==NULL)
            				return UT_errno=UTE_NOMEM;
            			record+=attrs[i].offset;
            			memcpy((void*)string,  record, attrs[i].attrlength);
            			record-=attrs[i].offset;
            			string[attrs[i].attrlength-1]='\0';
            			fprintf(stderr,"%s ",string);
            			free(string);
            		}   
       		}/*for*/
	    	fprintf(stderr,"\n");
    	}/*while*/
	free(record);  
    	free(attrs);		          			/* free space allocated on CFM_Lookup */
        if ( (rval=HF_CloseFileScan(sd)) != HFE_OK )		/* Close open scan */
		return UT_errno=rval;
        if ( (rval=HF_CloseFile(fd)) != HFE_OK )		/* Close file relName */
		return UT_errno=rval;
	return UT_errno=UTE_OK;
}
