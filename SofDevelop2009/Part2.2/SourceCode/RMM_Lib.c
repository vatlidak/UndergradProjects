/*
 * File: 	RMM_Lic.c
 * Description: This is the first part of Heap File Level.
 * 		At this part we are providing appropriate
 *		functions so that record management is 
 *		achieved.
 *
 * Authors: Atlidakis Vaggelis, Aggelogiannopoulos Aris, Kuriazof Xristina
 * AM: 	    1115200500010, 1115200500004, 1115200600267
 * 
 * Date: 1.12.2009
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "BF_Defines.h"
#include "BF_Lib.h"

#include "HF_Defines.h"
#include "RMM_Lib.h"

/*
 *This is a function returning the position
 *of the first 0 in one byte. Threat bytes
 *differently depending on whether it's header
 *byte or bitmaps byte.
 */
int iszero(char blockBuf,int mode)
{
    	int 		j;
    	unsigned char 	c=1;

    	if (mode==0)             		/* mode is zero when we search header */    		for(j=0;j<8;j++){
    		    	c=c << (7-j);
		        if((blockBuf & c) ==0)            
    		       		return j;
    		    	c=1;
    	}
	if(mode==1)               		/* mode is one when we search block's bitmap */
    		for(j=0;j<8;j++){
    		    if((blockBuf & c)==0)
    		       return j;
    		    c=c << 1;
    		 }
	return -1;
}


/*
 *This is a function returning the position
 *of the first 1 in one byte. Threat bytes
 *differently depending on whether it's header
 *byte or bitmaps byte.
 */
int isone(char blockBuf,int mode)
{
    	int 		j;
    	unsigned char 	c=1;

    	if (mode==0)             		/* mode is zero when we search header */    		for(j=0;j<8;j++){
    		    	c=c << (7-j);
		        if((~blockBuf & c) ==0)            
    		       		return j;
    		    	c=1;
    	}
	if(mode==1)               		/* mode is one when we search block's bitmap */
    		for(j=0;j<8;j++){
    		    if((~blockBuf & c)==0)
    		       return j;
    		    c=c << 1;
    		 }
	return -1;
}


/*
 *This is a function inserting a record with recordSize, pointed by "record",
 *into file with fileDesc.Return recId, if no error occurs,else return error
 *code. When searching for an empty block to insert record do not check validy
 *for every record sequentilly, but search in header which is first block with
 *available space.
 */
int RMM_InsertRec(int fileDesc,char *record,int recordSize)
{
	int 		i,r;
   	int 		Recs;
	int 		rvalue;
	int 		HeaderBlockNum,BlockNum;
   	int 		bitmaplength,found=0;
   	int		position,posinblock;
   	int 		counter,geter;
  	char 		*HF_Header,*block;
  	unsigned char 	c=1;
  	
   	Recs=(8*BF_BLOCK_SIZE)/((8*recordSize) + 1);	/* Records per block */
   	bitmaplength=(Recs/8)+(Recs%8 !=0);		/* bytes needed for bytemap */
   	
   	if((rvalue=BF_GetFirstBlock(fileDesc,&HeaderBlockNum,&HF_Header))!=BFE_OK)	/* Get HF_Header */
   		return (HF_errno=rvalue);   
   	BlockNum=-1;
   	for(counter=0;counter<(MAX_BLOCKS/8);counter++)                        		/* search HF_Header for an empty block */
     		if(  (position=iszero(HF_Header[counter],0)) != -1  ){
       			BlockNum=counter*8+position;   					/* Block Number of first Invalid block according to HF_Header */
       			break;
     		}
     	if ( BlockNum == -1 )								/* All Blocks full */
    		return (HF_errno=HFE_ALLBLOCKSFULL); 
   	if( (geter=BF_GetThisBlock(fileDesc,BlockNum+1,&block)) == BFE_INVALIDBLOCK ){/*BF_GetThisBlock for first Invalid block according to HF_Header */
     		if( (rvalue=BF_AllocBlock(fileDesc,&BlockNum,&block)) != BFE_OK )     /*If it's invalid block for BF_Level, so alloc a new empty block */
     			return (HF_errno=rvalue);   			    
     		BlockNum--;
     	}
	else if( geter!=BFE_OK )  
   		return (HF_errno=geter);  
   			   
   	for(i=0;i<bitmaplength;i++)                      				/* search first zero in block's bitmap */
     		if( (r=iszero(block[BF_BLOCK_SIZE-1-i],1)) != -1 )   			/* search from 1023 descending */
        			break;							/* we reached first zero */
        posinblock=r+i*8;
   	memcpy(block+posinblock*recordSize,record,recordSize);           		/* Insert record */
   	c=c << r;                                            
   	block[BF_BLOCK_SIZE-1-i]=block[BF_BLOCK_SIZE-1-i] | c;   			/* inform bitmap */
   	for(i=0;i<bitmaplength-1;i++)                            			/* search whole bitmap, exept for last byte */
     		if ((rvalue=iszero(block[BF_BLOCK_SIZE-1-i],1))!=-1){ 			/* if we find a zero we don't need to inform HF_Header AGAIN */
       			found=1;
       			break;
       		}
    	c=1;
   	for(i=0;i<Recs%8;i++){								/* check also bits of last byte */
      		if((block[BF_BLOCK_SIZE-bitmaplength] & c)==0){
		        found=1;
		        break;
		}
		c=c << 1;
	}
	if (found==0){              							/* found==0 means that we should inform HF_Header */
      		c=1;									/* since block is full */
      		c=c << (7-position);
      		HF_Header[counter]=HF_Header[counter] | c;
      		if((rvalue=BF_UnpinBlock(fileDesc,HeaderBlockNum, TRUE))!=BFE_OK) 	/* unpin, HF_Header dirty */
     			return (HF_errno=rvalue);    
 	}    													
   	else
     		if((rvalue=BF_UnpinBlock(fileDesc,HeaderBlockNum, FALSE))!=BFE_OK) 	/* Unpin */
     			return (HF_errno=rvalue);
     			
   	if((rvalue=BF_UnpinBlock(fileDesc,BlockNum+1, TRUE))!=BFE_OK) 
   		return (HF_errno=rvalue);
   		  		
   	return ((BlockNum*Recs) + posinblock) ;						/* Return RecId */
}


/*
 *This is a function deleting record, with recId and recordSize,
 *from file with fileDesc.Return error code if an error occurs,
 *otherwise HFE_OK.After deleting a record,informing block's bitmap.
 *Moreover,if it is the first deleting of record related to current block
 *inform also header that we have available space in current block.
 */
int RMM_DeleteRec(int fileDesc,int recId,int recordSize)
{
 
   	int		rvalue;
   	int		HeadBlockNum;
	int 		blockN, recN;
	int 		recs, bitmaplength;
	int 		RecByte,RecBit;
    	char 		*block;
    	char		*HF_Header;
    	unsigned char	 c=1;
    
	recs = (8 * BF_BLOCK_SIZE)/(8*recordSize + 1);	/* Records per block */
	bitmaplength = recs/8 + (recs%8!=0);		/* bytes needed for bytemap */		
	blockN = (recId/recs) + 1;			/* block cocntaining  rec */
	recN = recId % recs;				/* position of  rec in block */
	RecByte=recN/8;					/* bytemap's byte reffered to  rec */
	RecBit=recN%8;					/* bytemap's bit reffered to  rec */

     	if( (rvalue=BF_GetThisBlock(fileDesc,blockN,&block))!=BFE_OK ) 
    		return (HF_errno=rvalue);     
    	c=c << RecBit;                            				
    	if((block[BF_BLOCK_SIZE-1-RecByte] & c) == 0) 					/* check bitmap, record should be ivalid before deleting */
    		return (HF_errno=HFE_RECEMPTY); 
	block[BF_BLOCK_SIZE-1-RecByte]=block[BF_BLOCK_SIZE-1-RecByte] & ~c ;     	/* Inform bitmap */
    	if((rvalue=BF_GetFirstBlock(fileDesc,&HeadBlockNum,&HF_Header))!=BFE_OK) 	/* Get HF_Header */
    		return (HF_errno=rvalue); 
    	c=128;
    	c>>=(blockN-1)%8;
    	if((HF_Header[(blockN-1)/8] & c)!=0){           				/* Do we need to inform HF_Header? */
      		HF_Header[(blockN-1)/8]=HF_Header[(blockN-1)/8] & ~c ;           
      		if((rvalue=BF_UnpinBlock(fileDesc,HeadBlockNum, TRUE))!=BFE_OK) 	/* Unpin Header */
      			return (HF_errno=rvalue);          
      		if((rvalue=BF_UnpinBlock(fileDesc,blockN, TRUE))!=BFE_OK) 		/* Unpin current Block */
      			return (HF_errno=rvalue);
      		return (HF_errno=HFE_OK);           
      	}
    	if((rvalue=BF_UnpinBlock(fileDesc,blockN, TRUE))!=BFE_OK) 			/* Unpin current Block */
    		return (HF_errno=rvalue);          
    	if((rvalue=BF_UnpinBlock(fileDesc,HeadBlockNum, FALSE))!=BFE_OK) 		/* Unpin Header */
    		return (HF_errno=rvalue);
    	return (HF_errno=HFE_OK);           
} 


/*
 *This is a function returning recId of first valid record in file
 *with fileDesc,if no error occurs,otherwise error code is returned.
 *Moreover, after success pointer "record" points to record.
 */
int RMM_GetFirstRec(int fileDesc, char *record, int recordSize)
{
	int 	i,j;
	int 	rval;
	int	BlockNum;
	int 	position;
	int 	recs, bitmaplength;
	char 	*blockbuf;
	
	recs = (8 * BF_BLOCK_SIZE)/(8*recordSize + 1);			/* Records per block */
	bitmaplength = recs/8 + (recs%8!=0);				/* bytes needed for bytemap */	
	BlockNum=0;
	while( (rval = BF_GetNextBlock(fileDesc, &BlockNum, &blockbuf))==BFE_OK )  
	{
		for(i=0; i<bitmaplength; i++)
		{
			if( (position=isone(blockbuf[BF_BLOCK_SIZE-1-i],1)) != -1 ){
       				j = i*8+position;               	/* Nuber of first valid record in block */
				memcpy(record,blockbuf+j*recordSize,recordSize);
			  	if((rval=BF_UnpinBlock(fileDesc,BlockNum, FALSE))!=BFE_OK) 
			   		return (HF_errno=rval);
				return recs*(BlockNum-1)+j;		/* RecId */
			}
		}
	  	if((rval=BF_UnpinBlock(fileDesc,BlockNum, FALSE))!=BFE_OK) 
	   		return (HF_errno=rval);
	}
	return (HF_errno = HFE_EOF);
}


/*
 *This is a function returning recId of first valid record after recId in
 *file with fileDesc,if no error occurs,otherwise error code is returned.
 *Moreover, after success pointer "record" points to record.
 */
int RMM_GetNextRec(int fileDesc, int recId ,char *record, int recordSize)
{
	int 		i,bit;
	int 		rval;
	int 		blockN, recN;
	int 		recs, bitmaplength;
	int 		RecByte,RecBit;
	char 		*blockbuf;
	unsigned char 	c=1;

	recId++;					/* Next Record */
	recs = (8 * BF_BLOCK_SIZE)/(8*recordSize + 1);	/* Records per block */
	bitmaplength = recs/8 + (recs%8!=0);		/* bytes needed for bytemap */		
	blockN = (recId/recs) + 1;			/* block cocntaining next rec */
	recN = recId % recs;				/* position of  next rec in block */
	RecByte=recN/8;					/* bytemap's byte reffered to next rec */
	RecBit=recN%8;					/* bytemap's bit reffered to next rec */
	blockN--;					/* Don't surpass block of next rec */

	while( (rval = BF_GetNextBlock(fileDesc, &blockN , &blockbuf)) == BFE_OK )
	{
		for(i=RecByte,bit=RecBit,c<<=RecBit; i<bitmaplength; i++,c=1,bit=0)	/* Start from appropriate offset for next record */ 
		{									/* and search all bits of next bytes */
			while(1)
			{
				if( (c&blockbuf[BF_BLOCK_SIZE-1-i]) != 0)		/* we reached vaid bit */
				{
					memcpy(record,blockbuf+(8*i+bit)*recordSize,recordSize);	
			  		if((rval=BF_UnpinBlock(fileDesc,blockN, FALSE))!=BFE_OK) 		
			    			return (HF_errno=rval);
  					return recs*(blockN-1)+8*i+bit;	 		/* RecId */
  				}
  				if ( c == 128 )
  					break;
  				c<<=1;	
  				bit++;				  	 	 	/* next bit */
 			}
 								 	 		/* 128 = 10000000,means we checked all bits from that byte */
		}
	  	if((rval=BF_UnpinBlock(fileDesc,blockN, FALSE))!=BFE_OK) 	 	/* Unpin current Block */
	    		return (HF_errno=rval);          
	    	RecByte=RecBit=0;
	    	c=1;						 	 		/* in need of searchig next blocks, begin from byte 0 */
	}
	return (HF_errno = HFE_EOF);
}


/*
 *This is a function setting pointer "record" pointing to record.
 *Upon successful execution HFE_OK is returned, otherwise 
 *appropriateerror code.
 */
int RMM_GetThisRec(int fileDesc, int recId, char* record,int recordSize)
{
	int  		rval;
	int 	 	blockN, recN;
	int 		RecByte,RecBit;
	int  		recs;
	char 		*blockbuf;
	unsigned int 	c=1;

	recs = (8 * BF_BLOCK_SIZE)/(8*recordSize + 1);	/* Records per block */
	blockN = (recId/recs) + 1;			/* block containing this rec */
	recN = recId % recs;				/* position of this rec in block */
	RecByte=recN/8;					/* bytemap's byte reffered to next rec */
	RecBit=recN%8;					/* bytemap's bit reffered to next rec */
	c=c<<RecBit;					/* bitmap's bit reffered to this rec */

	if ( (rval = BF_GetThisBlock(fileDesc, blockN , &blockbuf)) != BFE_OK )
		return (HF_errno = rval);
	if( (blockbuf[1023-RecByte] & c)  == 0 ){
		if((rval=BF_UnpinBlock(fileDesc,blockN, FALSE))!=BFE_OK) 		/* Unpin this Block */
			return (HF_errno=rval); 
		return HF_errno=HFE_INVALIDREC;
	}
	memcpy(record,blockbuf+recN*recordSize,recordSize);
	if((rval=BF_UnpinBlock(fileDesc,blockN, FALSE))!=BFE_OK) 			/* Unpin this Block */
		return (HF_errno=rval); 	
	return HFE_OK;
}
