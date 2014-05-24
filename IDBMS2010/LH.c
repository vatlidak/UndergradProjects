/*
 *  LH.c
 *  
 *
 *  Created by Natasa Sevastidou on 5/26/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "LH.h"
#include "BF.h"
#include "record.h"
#include "HashFunction.h"

int HashStatistics( char* filename )
{
    int i,rec_counter,b_overflow,fd, var, sum, min, max,  total_sum , buckets_with_overflow ;
    void *block ;
    LHheader header;
    
    fd = BF_OpenFile(filename); 
	if(fd<0)	
	{
		BF_PrintError("Open File");
		return -1;
	}
    
    var = BF_GetBlockCounter(fd);
    if (var<0)
    {
       BF_PrintError("Get Block Counter");
       return -1;        
    }
    printf("a)To arxeio exei %d blocks\n",var-1);
    
    var = BF_ReadBlock(fd,0,&block);
	if(var<0)
	{
       BF_PrintError("Read Block");
       return -1;    
	}
	memcpy(&header,block,sizeof(LHheader));
	total_sum = 0;
	min=10000000;
	max=-1;
	
    for(i=1; i<header.buckets; i++)
    {
             sum=0;
             b_overflow=i;
             do{
		        var = BF_ReadBlock(fd,b_overflow,&block);
		        if(   var<0)  
		        {
			          BF_PrintError("Read Block");
			          return -1;    
                 }
                 memcpy(&rec_counter,block + BLOCK_SIZE - 2 * sizeof(int),sizeof(int));
                 memcpy(&b_overflow,block + BLOCK_SIZE - sizeof(int),sizeof(int));
                 sum=sum+rec_counter;
	         }while (b_overflow > 0);/*Exoume vrei to sunolo twn eggrafwn tou i kadou*/
	         
	         if(sum<min)
	                    min=sum;
             if(sum>max)
                        max=sum;
	         total_sum = total_sum + sum;
    }
    printf("b)to elaxisto plithos twn eggrafwn enos kadou einai: %d\n",min);
    printf("b)to megisto plithos twn eggrafwn enos kadou einai: %d\n",max);
    printf("b)to meso plithos twn eggrafwn twn kadwn einai: %.2f\n", (float)total_sum/(float)header.buckets);
    
    var = BF_GetBlockCounter(fd);
    if (var<0)
    {
       BF_PrintError("Get Block Counter");
       return -1;        
    }
    var=var-1;                                 /* Gia na afairesoume to header block */
    printf("c)to meso plithos twn blocks ana bucket einai: %.2f\n", (float)var/(float)header.buckets);
    
    buckets_with_overflow=0;
    for(i=1; i<header.buckets; i++)
    {
             sum=0;                                        /* To sum twra anaparista to plithos blocks yperxeilhshs kathe bucket */
             b_overflow=i;
             do{
		        var = BF_ReadBlock(fd,b_overflow,&block);
		        if(   var<0)  
		        {
			          BF_PrintError("Read Block");
			          return -1;    
                 }
                 memcpy(&rec_counter,block + BLOCK_SIZE - 2 * sizeof(int),sizeof(int));
                 memcpy(&b_overflow,block + BLOCK_SIZE - sizeof(int),sizeof(int));
                 if(b_overflow != -1)
                               sum++;
	         }while (b_overflow > 0);/*Exoume vrei to sunolo twn eggrafwn tou i kadou*/
	         if(sum > 0)
             {
                    buckets_with_overflow++;
                    printf("O kados %d exei %d block uperxeilhshs\n",i,sum);
             }
    }	         
	printf("Exoun uperxeilhsh %d kadoi\n",buckets_with_overflow);            
	return 0;
}

int LH_CreateIndex(char *fileName,	 char* attrName, char attrType, int attrLength, int buckets, float loadThrs)
{
	LHheader header;
	void *block;
	int fd,var,i;
	int b_overflow=0, rec_counter=0 ,previous = -1;
	
	var=BF_CreateFile(fileName);                                    /*Dhmiourgia arxeiou me onoma filename pou apoteleitai apo block*/
	if(var<0)
	{
		BF_PrintError("Create File");
		return -1;
	}
	header.FileKind=0;
	header.split = 1;
	header.level = 0;
	header.total_rec = 0;
	header.loadThrs = loadThrs;										/*Katallhlh arxikopoihsh twn melwn toy header block toy arxeioy katakermatismou*/
	header.maxrecs = ( BLOCK_SIZE - 3*sizeof(int) ) / sizeof(Record);
	header.attrType=attrType;
	strcpy(header.attrName,attrName);
	header.attrLength = attrLength;
	header.buckets = buckets;
	MaxRecs=header.maxrecs;
	fd = BF_OpenFile(fileName);                                     /*Anoigma arxeiou me onoma filename*/
	if(fd<0)
	{
		BF_PrintError("Open File");
		return -1;
	}
	var=BF_AllocateBlock(fd);                                       /*Desmeysh kainouriou block me anagnwristiko fd*/
	if(var<0)
	{
		BF_PrintError("Allocate Block");
		return -1;
	}
	var=BF_AllocateBlock(fd);                                       /*Desmeysh kainouriou block me anagnwristiko fd*/
	if(var<0)
	{
		BF_PrintError("Allocate Block");
		return -1;
	}
	
	var = BF_ReadBlock(fd,0,&block);                                /*Diavasma tou block apo to arxeio me onoma filename*/
	if(var<0)
	{
		BF_PrintError("Read Block");
		return -1;
	}
	memcpy(block,&header,sizeof(LHheader));                         /*Katallhlh enhmerwsh tou block me ta melh tou struct header */
	var = BF_WriteBlock(fd,0);                                      /*Grapsimo to disko to desmeymeno block*/
	if(var<0)
	{
		BF_PrintError("Write Block1");
		return -1;
	}
	for(i = 0;i<buckets;i++)                                        /*Dhmiourgia kenwn block sto arxeio katakermatismou ektos tou header block*/
	{
		var=BF_AllocateBlock(fd);                               /*Desmeysh neou block*/
		if(var<0)
		{
			BF_PrintError("Allocate Block");
			return -1;
		}
	 	var = BF_ReadBlock(fd,i+1,&block);                                /*Diavasma tou block apo to arxeio me onoma filename*/
		if(var<0)
		{
			BF_PrintError("Read Block");
			return -1;
		}
		memcpy(block+BLOCK_SIZE - 3*sizeof(int),&previous,sizeof(int));
		memcpy(block+BLOCK_SIZE - 2* sizeof(int),&rec_counter,sizeof(int));     /*topotheshsh ths metavlhths rec_ccounter sthn prwteleutaias theshs toy block  */
		memcpy(block+BLOCK_SIZE-sizeof(int),&b_overflow,sizeof(int));           /*Topothethsh ths metavlhths b_overflow sthn teleutaia thesh toy block */
		printf("%d\n",*((int*)(block+1)));
		var = BF_WriteBlock(fd,i+1);                                            /*Grapsimo tou block pisw sto disko*/
		if(var<0)
		{
			BF_PrintError("Write Block2");
			return -1;
		}
	}

//	printf("%d %d\n",BF_GetBlockCounter(fd),buckets  );
	var = BF_CloseFile(fd);                                         /*Kleisimo toy arxeiou katakermatismou me anagnwristiko fd*/
	if(var<0)
	{
		BF_PrintError("Close File");
		return -1;
	}
	return 0;
}

LH_info* LH_OpenIndex(char *filename)
{
	LHheader header;
	int rval;
	int fd;
	void *block;
	LH_info *lh;
	
	lh= calloc(1,sizeof(LH_info));                  /*Desmeysh tou deikth htmesw ths calloc gia na mporei na epistrafei h domh ht typou HT_info*/
	fd = BF_OpenFile(filename);                     /*Anoigma toy arxeioy me onoma filename*/
	if(fd<0)
	{
		BF_PrintError("Open File");
		return NULL;
	}
	rval = BF_ReadBlock(fd,0,&block);               /*Diavasma tou block*/
	if(rval<0)
	{
		BF_PrintError("Read Block");
		return NULL;
	}
	memcpy(&header,block,sizeof(LHheader)); 
							/*Antigrafh toy block sto header*/
	if(header.FileKind==0)                          /*An to filekind deixnei oti einai arxeio katakermatismou tote enhmerwnontai ta melh ths neas domhs pou
													 epistrefetai san deikths apo thn OpenIndex */
	{
		lh->fileDesc=fd;
		lh->attrType=header.attrType;
		strcpy(lh->attrName,header.attrName);
		lh->attrLength= header.attrLength;
		lh->buckets=header.buckets;
		lh->loadThrs=header.loadThrs;
		lh->split = header.split;
		lh->total_rec = header.total_rec;
		lh->level = header.level;
		lh->loadThrs = header.loadThrs;
		
		return lh;
	}
	else
		return NULL;
}


int LH_CloseIndex(LH_info* header_info)
{
	int var,val;
	void* block;
	LHheader header;
	
	var = BF_ReadBlock(header_info->fileDesc,0,&block);                                /*Diavasma tou block apo to arxeio me onoma filename*/
	if(var<0)
	{
		BF_PrintError("Read Block");
		return -1;
	}
	memcpy(&header,block,sizeof(LHheader));
	
	
	header.split = header_info->split;
	header.loadThrs =header_info->loadThrs;
	header.level = header_info->level;
	header.total_rec = header_info->total_rec;
	memcpy(block,&header,sizeof(LHheader));
	var = BF_WriteBlock(header_info->fileDesc,0);                                      /*Grapsimo to disko to desmeymeno block*/
	if(var<0)
	{
		BF_PrintError("Write Block");
		return -1;
	}
	val = BF_CloseFile(header_info->fileDesc);      /*Kleisimo tou anoixtou arxeiou me anagnwristiko fileDesc*/
											
	if(val<0)
	{
		BF_PrintError("Close File!");
		return -1;
	}
	else
		return 0;
	free(header_info);
}



int LH_InsertEntry (LH_info *header_info, Record record)
{
	int hf_val;
	int tmp,rec_counter,b_overflow,previous = -1;
	int var,blockcounter,tmp_rec_counter,tmp_b_overflow;
	int tmpfd;
	void *block,*tmpblock,*lastblock;
	int i,j;
	
	if(strcmp(header_info->attrName,ID) == 0 )       /*Efarmozoume th synarthsh katakermatismou analoga me to pedio kleidi gia na vroume ton kado ston opoio thaeisagoume eggrafes */
		hf_val=hash((char*)&record.id,pow(2,header_info->level)*header_info->buckets );
	else if (strcmp(header_info->attrName,NAME) == 0 )
		hf_val=hash(record.name,pow(2,header_info->level)*header_info->buckets );
	else if (strcmp(header_info->attrName,SURNAME) == 0 )
		hf_val=hash(record.surname,pow(2,header_info->level)*header_info->buckets );
	else if (strcmp(header_info->attrName,CITY) == 0 )
		hf_val=hash(record.city,pow(2,header_info->level)*header_info->buckets );
	hf_val++;											/*Aykshsh tou hf_val gia na agnoume to header block */
	if (hf_val<header_info->split) {
		if(strcmp(header_info->attrName,ID) == 0 )       /*Efarmozoume th synarthsh katakermatismou analoga me to pedio kleidi gia na vroume ton kado ston opoio thaeisagoume eggrafes */
			hf_val=hash((char*)&record.id,pow(2,header_info->level+1)*header_info->buckets );
		else if (strcmp(header_info->attrName,NAME) == 0 )
			hf_val=hash(record.name,pow(2,header_info->level+1)*header_info->buckets );
		else if (strcmp(header_info->attrName,SURNAME) == 0 )
			hf_val=hash(record.surname,pow(2,header_info->level+1)*header_info->buckets );
		else if (strcmp(header_info->attrName,CITY) == 0 )
			hf_val=hash(record.city,pow(2,header_info->level+1)*header_info->buckets );
		hf_val++;										/*Aykshsh tou hf_val gia na agnoume to header block */
	}
	do {
		tmp=hf_val;
		var = BF_ReadBlock(header_info->fileDesc,hf_val,&block);         /*Grafoume to block */
		if(var<0)
		{
			BF_PrintError("Read Block 0");
			return -1;
		}
		memcpy(&rec_counter,block + BLOCK_SIZE - 2 * sizeof(int),sizeof(int));  /*Topothethsh ths metavlhths rec_counter sthn proteleutaia tehsh tou block */
		memcpy(&b_overflow,block + BLOCK_SIZE - sizeof(int),sizeof(int));       /*TOpothethsh ths metavlhths b_overflow sth teleutaia thesh tou block */
		hf_val=b_overflow;
	} while (b_overflow > 0);                                                       /*Enoso vriskomaste se kado yperxeilhshs diavazoume blocks*/
	previous = tmp;
printf(	"%d\n",previous);
	if (rec_counter < MaxRecs)                                                      /*An to block den exei gemisei apo eggarfes */
	{
		memcpy(block + rec_counter*sizeof(Record),&record,sizeof(Record));      /*KAtallhlh enhmerwsh tou rec_counter*/
		rec_counter++;                                                          /*Aykshsh tou reccounter gia na kseroume poses eggrafes einai sto block*/
		memcpy(block + BLOCK_SIZE - 2 *sizeof(int),&rec_counter,sizeof(int));   /*Katallhlh enhmerwsh tou b_overflow */
		var = BF_WriteBlock(header_info->fileDesc,tmp);                          /*Meta apo thn katallhlh enhmerwsh grafoume piso to block sto disko */
		if(var<0)
		{
			BF_PrintError("Write Block 0");
			return -1;
		}
	}
	else                                                                            /*An exei gemisei to block ftiaxnw block yperxhlisis  */
	{

		printf("uperxeilisi\n");

		var=BF_AllocateBlock(header_info->fileDesc);                             /*Desmeysh neou block*/
		if(var<0)
		{
			BF_PrintError("Allocate Block");
			return -1;
		}
		b_overflow=BF_GetBlockCounter(header_info->fileDesc)-2;                  /*To b_overflow exei ton arithmo tou kadou pou exei gemisei*/
		if(b_overflow<0)
		{
			BF_PrintError("Get Block Counter");
			return;
		}
		memcpy(block+BLOCK_SIZE-sizeof(int),&b_overflow,sizeof(int));           /*Enhmerwsh ths teleuteas theshs tou block me ton arithmo tou b_overflow */
		var = BF_WriteBlock(header_info->fileDesc,tmp);                          /*Grapsimo tou block piso sto disko*/
		if(var<0)
		{
			BF_PrintError("Write Block 0");
			return -1;
		}
		var = BF_ReadBlock(header_info->fileDesc,b_overflow,&block);             /*Diavazw to block*/
		if(var<0)
		{
			BF_PrintError("Read Block 0");
			return -1;
		}
		
		tmp=b_overflow;
		memcpy(block,&record,sizeof(Record));
		b_overflow=-1;
		
		memcpy(block+BLOCK_SIZE-sizeof(int),&b_overflow,sizeof(int));
		rec_counter=1;                                                          /*Arxikopoihsh tou rec_counter me 1 gt vriskomaste sth prwth eggrafh tou block yperxhleishs*/
		memcpy(block+BLOCK_SIZE-2*sizeof(int),&rec_counter,sizeof(int)); /*Enhmerwsh ths proteleutaias theshs me ton arithmo tou rec_counter*/
		printf("previouuus:%d\n",previous);	
		memcpy(block+BLOCK_SIZE - 3*sizeof(int),&previous,sizeof(int));
		var = BF_WriteBlock(header_info->fileDesc,tmp);                          /*Grafw to block piso sto disko*/
		if(var<0)
		{
			BF_PrintError("Write Block 0");
			return -1;
		}
	}
printf("blocks till now:%d\n",BF_GetBlockCounter(header_info->fileDesc)-1   );
	header_info->total_rec++;
	if (((float)header_info->total_rec/(float)(MaxRecs*(header_info->buckets*pow(2,header_info->level)+header_info->split - 1))) > header_info->loadThrs ) {
		printf("lala:%d\n",previous);
		var=BF_CreateFile("tmp");                                    /*Dhmiourgia arxeiou me onoma filename pou apoteleitai apo block*/
		if(var<0)					/*header_info.buckets*pow(2,level)+header_info.header_info.header_info.split - 1): Autos einai o pragmatikos arithos twn kadwn*/
		{
			BF_PrintError("Create File");
			return -1;
		}
		tmpfd = BF_OpenFile("tmp");                                     /*Anoigma arxeiou me onoma filename*/
		if(tmpfd<0)
		{
			BF_PrintError("Open File");
			return -1;
		}
		tmp=header_info->split;										/*Sto tmp krataw to 1o block tou kadou pou tha kanw split*/
		i = 0;
		do {									/*Gia ola ta block toy kadoy pou kanoume header_info.header_info.header_info.split*/
			
			var = BF_ReadBlock(header_info->fileDesc,tmp,&block);       /*Diavazoume ta block tou kadou*/
			if(var<0)
			{
				BF_PrintError("Read Block 1");
				return -1;
			}
			memcpy(&rec_counter,block + BLOCK_SIZE - 2 * sizeof(int),sizeof(int));  /*Topothethsh ths metavlhths rec_counter sthn proteleutaia tehsh tou block */
			var=BF_AllocateBlock(tmpfd);                                       /*Desmeysh kainouriou block me anagnwristiko fd*/
			if(var<0)
			{
				BF_PrintError("Allocate Block");
				return -1;
			}
			var = BF_ReadBlock(tmpfd,i,&tmpblock);                                /*Diavasma tou block apo to arxeio me onoma filename*/
			if(var<0)
			{
				BF_PrintError("Read Block2");
				return -1;
			}
			memcpy(tmpblock,block,BLOCK_SIZE);
			var = BF_WriteBlock(tmpfd,i);                                      /*Grapsimo to disko to desmeymeno block*/
			if(var<0)
			{
				BF_PrintError("Write Block1");
				return -1;
			}
			tmp_rec_counter = 0;
			tmp_b_overflow = -1;
			memcpy(block + BLOCK_SIZE - 2 * sizeof(int),&tmp_rec_counter,sizeof(int));
			memcpy(block + BLOCK_SIZE - sizeof(int),&tmp_b_overflow,sizeof(int));
			var = BF_WriteBlock(header_info->fileDesc,tmp);                                      /*Grapsimo to disko to desmeymeno block*/
			if(var<0)
			{
				BF_PrintError("Write Block2");
				return -1;
			}
			
			i++;							
			memcpy(&tmp,block + BLOCK_SIZE - sizeof(int),sizeof(int));       /*TOpothethsh ths metavlhths b_overflow sth teleutaia thesh tou block */
									/*Twra exoume metaferei sto tmp arxeio ta block toy kadou pou kaname header_info.header_info.header_info.split*/
		} while (tmp > 0); 
		blockcounter=BF_GetBlockCounter(header_info->fileDesc);                  /*To b_overflow exei ton arithmo tou kadou pou exei gemisei*/
		if(blockcounter<0)
		{
			BF_PrintError("Get Block Counter");
			return;
		}
		blockcounter=blockcounter -2;
printf("Exw:%d\n",blockcounter);
		if ((int)header_info->buckets*pow(2,header_info->level)+header_info->split-1==blockcounter)/*Periptwsi kata thn opoia den yparxei diathesimo block gia ton kado pou prokyptei apo to header_info.header_info.header_info.split*/
		{
printf("Den exw block\n");
			var=BF_AllocateBlock(header_info->fileDesc);                                       /*Desmeysh kainouriou block me anagnwristiko fd*/
			if(var<0)
			{
				BF_PrintError("Allocate Block");
				return -1;
			}
			var = BF_ReadBlock(header_info->fileDesc,header_info->split,&block);                                /*Diavasma tou block apo to arxeio me onoma filename*/
			if(var<0)
			{
				BF_PrintError("Read Block 3");
				return -1;
			}
			previous = -1;
			rec_counter = 0;
			b_overflow = -1;
printf("1  %d\n",previous);
			memcpy(block+BLOCK_SIZE - 3*sizeof(int),&previous,sizeof(int));
			memcpy(block+BLOCK_SIZE - 2* sizeof(int),&rec_counter,sizeof(int));     /*topotheshsh ths metavlhths rec_ccounter sthn prwteleutaias theshs toy block  */
			memcpy(block+BLOCK_SIZE-sizeof(int),&b_overflow,sizeof(int));   
			var = BF_WriteBlock(header_info->fileDesc,header_info->split);                                      /*Grapsimo to disko to desmeymeno block*/
			if(var<0)
			{
				BF_PrintError("Write Block 3");
				return -1;
			}
			blockcounter=BF_GetBlockCounter(tmpfd) - 2;                  /*To b_overflow exei ton arithmo tou kadou pou exei gemisei*/
			if(blockcounter<0)
			{
				BF_PrintError("Get Block Counter");
				return;
			}
			for (i=0;i<blockcounter; i++) {			/*Epanaeisagwgi twn eggrafwn tou tmp arxeiou sto arxiko me statiko katakermatismo*/
				memcpy(&tmp_rec_counter,block+BLOCK_SIZE-2*sizeof(int),sizeof(int));
				for (j=0; j<tmp_rec_counter; j++) 
				{
					memcpy(&record,block + j*sizeof(Record),sizeof(Record));
					if(strcmp(header_info->attrName,ID) == 0 )       /*Efarmozoume th synarthsh katakermatismou analoga me to pedio kleidi gia na vroume ton kado ston opoio thaeisagoume eggrafes */
						hf_val=hash((char*)&record.id,pow(2,header_info->level+1)*header_info->buckets );
					else if (strcmp(header_info->attrName,NAME) == 0 )
						hf_val=hash(record.name,pow(2,header_info->level+1)*header_info->buckets );
					else if (strcmp(header_info->attrName,SURNAME) == 0 )
						hf_val=hash(record.surname,pow(2,header_info->level+1)*header_info->buckets );
					else if (strcmp(header_info->attrName,CITY) == 0 )
						hf_val=hash(record.city,pow(2,header_info->level+1)*header_info->buckets );
					hf_val++;										/*Aykshsh tou hf_val gia na agnoume to header block */
					do {
						tmp=hf_val;
						var = BF_ReadBlock(header_info->fileDesc,hf_val,&block);         /*Grafoume to block */
						if(var<0)
						{
							BF_PrintError("Read Block 4");
							return -1;
						}
						memcpy(&rec_counter,block + BLOCK_SIZE - 2 * sizeof(int),sizeof(int));  /*Topothethsh ths metavlhths rec_counter sthn proteleutaia tehsh tou block */
						memcpy(&b_overflow,block + BLOCK_SIZE - sizeof(int),sizeof(int));       /*TOpothethsh ths metavlhths b_overflow sth teleutaia thesh tou block */
						hf_val=b_overflow;
					} while (b_overflow > 0);                                                       /*Enoso vriskomaste se kado yperxeilhshs diavazoume blocks*/
					previous = tmp;
					printf("%d\n",previous);		
					if (rec_counter < MaxRecs)                                                      /*An to block den exei gemisei apo eggarfes */
					{
						memcpy(block + rec_counter*sizeof(Record),&record,sizeof(Record));      /*KAtallhlh enhmerwsh tou rec_counter*/
						rec_counter++;                                                          /*Aykshsh tou reccounter gia na kseroume poses eggrafes einai sto block*/
						memcpy(block + BLOCK_SIZE - 2 *sizeof(int),&rec_counter,sizeof(int));   /*Katallhlh enhmerwsh tou b_overflow */
						var = BF_WriteBlock(header_info->fileDesc,tmp);                          /*Meta apo thn katallhlh enhmerwsh grafoume piso to block sto disko */
						if(var<0)
						{
							BF_PrintError("Write Block 4");
							return -1;
						}
					}
					else                                                                            /*An exei gemisei to block ftiaxnw block yperxhlisis  */
					{
printf("uperxeilisi\n");
						var=BF_AllocateBlock(header_info->fileDesc);                             /*Desmeysh neou block*/
						if(var<0)
						{
							BF_PrintError("Allocate Block");
							return -1;
						}
						b_overflow=BF_GetBlockCounter(header_info->fileDesc)-2;                  /*To b_overflow exei ton arithmo tou kadou pou exei gemisei*/
						if(b_overflow<0)
						{
							BF_PrintError("Get Block Counter");
							return;
						}
						memcpy(block+BLOCK_SIZE-sizeof(int),&b_overflow,sizeof(int));           /*Enhmerwsh ths teleuteas theshs tou block me ton arithmo tou b_overflow */
						var = BF_WriteBlock(header_info->fileDesc,tmp);                          /*Grapsimo tou block piso sto disko*/
						if(var<0)
						{
							BF_PrintError("Write Block 4");
							return -1;
						}
						var = BF_ReadBlock(header_info->fileDesc,b_overflow,&block);             /*Diavazw to block*/
						if(var<0)
						{
							BF_PrintError("Read Block 5");
							return -1;
						}
						
						tmp=b_overflow;
						memcpy(block,&record,sizeof(Record));
						b_overflow=-1;
						
						memcpy(block+BLOCK_SIZE-sizeof(int),&b_overflow,sizeof(int));
						rec_counter=1;                                                          /*Arxikopoihsh tou rec_counter me 1 gt vriskomaste sth prwth eggrafh tou block yperxhleishs*/
						memcpy(block+BLOCK_SIZE-2*sizeof(int),&rec_counter,sizeof(int)); /*Enhmerwsh ths proteleutaias theshs me ton arithmo tou rec_counter*/
						memcpy(block+BLOCK_SIZE - 3*sizeof(int),&previous,sizeof(int));
						var = BF_WriteBlock(header_info->fileDesc,tmp);                          /*Grafw to block piso sto disko*/
						if(var<0)
						{
							BF_PrintError("Write Block 5");
							return -1;
						}
					}//else//
				}//for (j=0; j<rec_counter; j++)//
			}//for (i=0; ;i<blockcounter; i++)//
		}//if//
		else{
			var = BF_ReadBlock(header_info->fileDesc,pow(2,header_info->level)*header_info->buckets+header_info->split,&block);             /*Diavazw to block*/
			if(var<0)
			{
				BF_PrintError("Read Block");
				return -1;
			}
			memcpy(&previous,block+BLOCK_SIZE - 3*sizeof(int),sizeof(int));

printf("else:%d %d\n",previous,(int)pow(2,header_info->level)*header_info->buckets+header_info->split);
			if (previous != header_info->split) {
			printf("mplok pou dn mou anikei\n");	
				var=BF_AllocateBlock(header_info->fileDesc);                             /*Desmeysh neou block*/
				if(var<0)
				{
					BF_PrintError("Allocate Block");
					return -1;
				}
				blockcounter=BF_GetBlockCounter(header_info->fileDesc)-2;                  /*To b_overflow exei ton arithmo tou kadou pou exei gemisei*/
				if(blockcounter<0)
				{
					BF_PrintError("Get Block Counter");
					return;
				}
printf("eftia3a mplok %d\n",blockcounter);
				var = BF_ReadBlock(header_info->fileDesc,blockcounter,&lastblock);                                /*Diavasma tou block apo to arxeio me onoma filename*/
				if(var<0)
				{
					BF_PrintError("Read Block 6");
					return -1;
				}
				memcpy(lastblock,block,BLOCK_SIZE);
				var = BF_WriteBlock(header_info->fileDesc,blockcounter);                          /*Grafw to block piso sto disko*/
				if(var<0)
				{
					BF_PrintError("Write Block6");
					return -1;
				}
				 var = BF_ReadBlock(header_info->fileDesc,previous,&block);                                /*Diavasma tou block apo to arxeio me onoma filename*/
                                if(var<0)
                                {
					printf("%d\n",previous);
                                        BF_PrintError("Read Block7");
                                        return -1;
                                }
                                b_overflow=blockcounter;
                                memcpy(block + BLOCK_SIZE - sizeof(int),&b_overflow,sizeof(int));
                                var = BF_WriteBlock(header_info->fileDesc,previous);                          /*Grafw to block piso sto disko*/
                                if(var<0)
                                {
                                        BF_PrintError("Write Block7");
                                        return -1;
                                }
				 var = BF_ReadBlock(header_info->fileDesc,pow(2,header_info->level)*header_info->buckets+header_info->split,&block);             /*Diavazw to block*/
                        	if(var<0)
                        	{
                                	BF_PrintError("Read Block");
                                	return -1;
                        	}
				b_overflow = -1;
				memcpy(block+BLOCK_SIZE-sizeof(int),&b_overflow,sizeof(int));
				rec_counter = 0;
                                memcpy(block+BLOCK_SIZE-2*sizeof(int),&rec_counter,sizeof(int));
				previous = -1;
printf("2 %d\n",previous);
                                memcpy(block+BLOCK_SIZE-3*sizeof(int),&previous,sizeof(int));
				var = BF_WriteBlock(header_info->fileDesc,pow(2,header_info->level)*header_info->buckets+header_info->split);                          
			
                                if(var<0)
                                {
                                        BF_PrintError("Write Block6");
                                        return -1;
                                }

			}
			var = BF_ReadBlock(header_info->fileDesc,header_info->split,&block);             /*Diavazw to block*/
			if(var<0)
			{
				BF_PrintError("Read Block 8");
				return -1;
			}
			previous = -1;
			rec_counter = 0;
			b_overflow = -1;
printf("3 %d\n",previous);
			memcpy(block+BLOCK_SIZE - 3*sizeof(int),&previous,sizeof(int));
			memcpy(block+BLOCK_SIZE - 2* sizeof(int),&rec_counter,sizeof(int));     /*topotheshsh ths metavlhths rec_ccounter sthn prwteleutaias theshs toy block  */
			memcpy(block+BLOCK_SIZE-sizeof(int),&b_overflow,sizeof(int));
			var = BF_WriteBlock(header_info->fileDesc,header_info->split);                          /*Grafw to block piso sto disko*/
			if(var<0)
			{
				BF_PrintError("Write Block 8");
				return -1;
			}
			blockcounter=BF_GetBlockCounter(tmpfd) -2;                  /*To b_overflow exei ton arithmo tou kadou pou exei gemisei*/
			if(blockcounter<0)
			{
				BF_PrintError("Get Block Counter");
				return;
			}
			for (i=0;i<blockcounter; i++) {			/*Epanaeisagwgi twn eggrafwn tou tmp arxeiou sto arxiko me statiko katakermatismo*/
				memcpy(&tmp_rec_counter,block+BLOCK_SIZE-2*sizeof(int),sizeof(int));
				for (j=0; j<tmp_rec_counter; j++) 
				{
					memcpy(&record,block + j*sizeof(Record),sizeof(Record));
					if(strcmp(header_info->attrName,ID) == 0 )       /*Efarmozoume th synarthsh katakermatismou analoga me to pedio kleidi gia na vroume ton kado ston opoio thaeisagoume eggrafes */
						hf_val=hash((char*)&record.id,pow(2,header_info->level+1)*header_info->buckets );
					else if (strcmp(header_info->attrName,NAME) == 0 )
						hf_val=hash(record.name,pow(2,header_info->level+1)*header_info->buckets );
					else if (strcmp(header_info->attrName,SURNAME) == 0 )
						hf_val=hash(record.surname,pow(2,header_info->level+1)*header_info->buckets );
					else if (strcmp(header_info->attrName,CITY) == 0 )
						hf_val=hash(record.city,pow(2,header_info->level+1)*header_info->buckets );
					hf_val++;										/*Aykshsh tou hf_val gia na agnoume to header block */
					do {
						tmp=hf_val;
						var = BF_ReadBlock(header_info->fileDesc,hf_val,&block);         /*Grafoume to block */
						if(var<0)
						{
							BF_PrintError("Read Block 9");
							return -1;
						}
						memcpy(&rec_counter,block + BLOCK_SIZE - 2 * sizeof(int),sizeof(int));  /*Topothethsh ths metavlhths rec_counter sthn proteleutaia tehsh tou block */
						memcpy(&b_overflow,block + BLOCK_SIZE - sizeof(int),sizeof(int));       /*TOpothethsh ths metavlhths b_overflow sth teleutaia thesh tou block */
						hf_val=b_overflow;
					} while (b_overflow > 0);                                                       /*Enoso vriskomaste se kado yperxeilhshs diavazoume blocks*/
					previous = tmp;
					printf("4 %d\n",previous);
					if (rec_counter < MaxRecs)                                                      /*An to block den exei gemisei apo eggarfes */
					{
						memcpy(block + rec_counter*sizeof(Record),&record,sizeof(Record));      /*KAtallhlh enhmerwsh tou rec_counter*/
						rec_counter++;                                                          /*Aykshsh tou reccounter gia na kseroume poses eggrafes einai sto block*/
						memcpy(block + BLOCK_SIZE - 2 *sizeof(int),&rec_counter,sizeof(int));   /*Katallhlh enhmerwsh tou b_overflow */
						var = BF_WriteBlock(header_info->fileDesc,tmp);                          /*Meta apo thn katallhlh enhmerwsh grafoume piso to block sto disko */
						if(var<0)
						{
							BF_PrintError("Write Block 9");
							return -1;
						}
					}
					else                                                                            /*An exei gemisei to block ftiaxnw block yperxhlisis  */
					{
printf("uperxeilisi\n");
						var=BF_AllocateBlock(header_info->fileDesc);                             /*Desmeysh neou block*/
						if(var<0)
						{
							BF_PrintError("Allocate Block");
							return -1;
						}
						b_overflow=BF_GetBlockCounter(header_info->fileDesc)-2;                  /*To b_overflow exei ton arithmo tou kadou pou exei gemisei*/
						if(b_overflow<0)
						{
							BF_PrintError("Get Block Counter");
							return;
						}
						memcpy(block+BLOCK_SIZE-sizeof(int),&b_overflow,sizeof(int));           /*Enhmerwsh ths teleuteas theshs tou block me ton arithmo tou b_overflow */
						var = BF_WriteBlock(header_info->fileDesc,tmp);                          /*Grapsimo tou block piso sto disko*/
						if(var<0)
						{
							BF_PrintError("Write Block 9 ");
							return -1;
						}
						var = BF_ReadBlock(header_info->fileDesc,b_overflow,&block);             /*Diavazw to block*/
						if(var<0)
						{
							BF_PrintError("Read Block 10");
							return -1;
						}
						
						tmp=b_overflow;
						memcpy(block,&record,sizeof(Record));
						b_overflow=-1;
						
						memcpy(block+BLOCK_SIZE-sizeof(int),&b_overflow,sizeof(int));
						rec_counter=1;                                                          /*Arxikopoihsh tou rec_counter me 1 gt vriskomaste sth prwth eggrafh tou block yperxhleishs*/
						memcpy(block+BLOCK_SIZE-2*sizeof(int),&rec_counter,sizeof(int)); /*Enhmerwsh ths proteleutaias theshs me ton arithmo tou rec_counter*/
						memcpy(block+BLOCK_SIZE - 3*sizeof(int),&previous,sizeof(int));

printf("6 %d\n",previous);							
						var = BF_WriteBlock(header_info->fileDesc,tmp);                          /*Grafw to block piso sto disko*/
						if(var<0)
						{
							BF_PrintError("Write Block 9");
							return -1;
						}
					}//else//
				}//for (j=0; j<rec_counter; j++)//
			}//for (i=0; ;i<blockcounter; i++)//
		}
		var = BF_CloseFile(tmpfd);										/*Kleisimo toy arxeiou katakermatismou me anagnwristiko fd*/
		if(var<0)														/*Diagarafoume to prosorino arxeio*/
		{
			BF_PrintError("Close File");
			return -1;
		}
		remove("tmp");													
		
	}//if//
	return 0;
}



int LH_FindAllEntries(LH_info header_info, void *value)
{
	int hf_val,rec_counter,i,var,j=0,b_overflow;
	void *block;
	Record record;
	
        var = BF_ReadBlock(header_info.fileDesc,hf_val,&block);         /*divasma tou block*/
	if(var<0)
	{
		BF_PrintError(".Read Block.");
		return ;
	}
        if(strcmp(header_info.attrName,ID) == 0 )       /*Efarmozoume th synarthsh katakermatismou analoga me to pedio kleidi gia na vroume ton kado ston opoio thaeis$
                hf_val=hash((char*)&record.id,pow(2,header_info.level)*header_info.buckets );
        else if (strcmp(header_info.attrName,NAME) == 0 )
                hf_val=hash(record.name,pow(2,header_info.level)*header_info.buckets );
        else if (strcmp(header_info.attrName,SURNAME) == 0 )
                hf_val=hash(record.surname,pow(2,header_info.level)*header_info.buckets );
        else if (strcmp(header_info.attrName,CITY) == 0 )
                hf_val=hash(record.city,pow(2,header_info.level)*header_info.buckets );
        hf_val++;                                                                                       /*Aykshsh tou hf_val gia na agnoume to header block */
        if (hf_val<header_info.split) {
                if(strcmp(header_info.attrName,ID) == 0 )       /*Efarmozoume th synarthsh katakermatismou analoga me to pedio kleidi gia na vroume ton kado ston opoi$ */
                        hf_val=hash((char*)&record.id,pow(2,header_info.level+1)*header_info.buckets );
                else if (strcmp(header_info.attrName,NAME) == 0 )
                        hf_val=hash(record.name,pow(2,header_info.level+1)*header_info.buckets );
                else if (strcmp(header_info.attrName,SURNAME) == 0 )
                        hf_val=hash(record.surname,pow(2,header_info.level+1)*header_info.buckets );
                else if (strcmp(header_info.attrName,CITY) == 0 )
                        hf_val=hash(record.city,pow(2,header_info.level+1)*header_info.buckets );
                hf_val++;                                                                               /*Aykshsh tou hf_val gia na agnoume to header block */
        }

	do {
		j++;
		var = BF_ReadBlock(header_info.fileDesc,hf_val,&block);
		if(var<0)
		{
			BF_PrintError("Read Block..");
			return;
		}
		memcpy(&rec_counter,block + BLOCK_SIZE - 2*sizeof(int),sizeof(int));    /*grafw sto rec_counter oti einai stin proteleutaia thesh tou block */
		memcpy(&b_overflow,block + BLOCK_SIZE - sizeof(int),sizeof(int));       /*Grafw sto b_overflow oti yparxei sth teleutaia thesh tou block*/
		hf_val=b_overflow;
		for (i=0; i <rec_counter; i++)
		{
			memcpy(&record,block + i*sizeof(Record),sizeof(Record));
				if(strcmp(header_info.attrName,ID) == 0 )                        /*Euresh eggrafwn me timi value*/
			
				{
					if ( record.id == *(int*)value )
						printf("%d %s %s %s \n",record.id,record.name,record.surname,record.city);
				}
				else if (strcmp(header_info.attrName,"name") == 0 )
				{
					if(strcmp(record.name,(char*)value) == 0)
						printf("%d %s %s %s \n",record.id,record.name,record.surname,record.city);
				}
				else if (strcmp(header_info.attrName,"surname") == 0 )
				{
					if(strcmp(record.surname,(char*)value) == 0)
						printf("%d %s %s %s \n",record.id,record.name,record.surname,record.city);
				}
				else if (strcmp(header_info.attrName,"city") == 0 )
				{
					if(strcmp(record.city,(char*)value) == 0)
						printf("%d %s %s %s \n",record.id,record.name,record.surname,record.city);
				}
			}


        } while (b_overflow > 0);               /*Enoso iparxei yperxeilisi*/
        printf("read %d blocks\n",j);           /*Ektypwsh olon twn block pou diavastikan*/
	return j;
}

