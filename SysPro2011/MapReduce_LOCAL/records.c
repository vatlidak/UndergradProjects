#include <stdio.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <dirent.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include "records.h"
#include "buffers.h"
#include "mapreduce.h"
#define BLKSIZE 1024

//synarthsh h opoia pros8etei mia eggrafh ston buffer pou ypodeiknyei h partition//
void addrecord(BUFFERS *buffers, char *record, int i)					
{
		int j;
		char delim='\0';
		char *block=buffers[i].block;						//deikths sto block tou ka8e buffer//
		char temp[56];
		
 		if ( strlen(record)+buffers[i].curbyte+1< BLKSIZE-1 )			//oso uparxei xwros sto buffer//
                {
                        memcpy(block+buffers[i].curbyte,record,strlen(record)); 	//adigrafoume sth 8esh curbyte to record//	
                        buffers[i].curbyte+=strlen(record);				//orizoume th nea 8esh curbyte//
                        memcpy(block+buffers[i].curbyte,&delim,sizeof(char));		//sthn kainouria 8esh pros8etoume ton delimeter//
                        buffers[i].curbyte++;
                        buffers[i].records++;
                        memcpy(block,&buffers[i].records,sizeof(int));
                }
                else									//an gemisei o buffer//
                {
			if ( my_write(buffers[i].pipedesc,block) != BLKSIZE )
				printf("error here\n");
			memset(block,0,BLKSIZE);
                        buffers[i].curbyte=4;						//oi 4 prwtes 8eseis enos buffer einai o int pou leei poses eggrafes exei o 
                        memcpy(block+buffers[i].curbyte,record,strlen(record) );	//adigrafoume sth 8esh curbyte to record//
			buffers[i].curbyte+=strlen(record);				//orizoume th nea 8esh curbyte//
                        memcpy(block+buffers[i].curbyte,&delim,sizeof(char));		//sthn kainouria 8esh pros8etoume ton delimeter//
                        buffers[i].curbyte++;
                        buffers[i].records=1;
                        memcpy(block,&buffers[i].records,sizeof(int));

                }
}

//synarthsh h opoia pros8etei to key kai to value mias eggrafhs stous pinakes kai enhmerwnei ton ari8mo twn synolikwn eggrafwn prokeimenou na kanoume realloc otan einai// 
//anagaio//
void update_vectors(char ***keys,char ***values, char *record, int *total_records, int *memsize)
{
        pair p;
        p=map(record);

	
	char **t;
	if ( *total_records == *memsize )						//an gemisei o pinakas//
	{	
		*memsize=(*memsize)*2;							
		*keys=realloc(*keys,(*memsize)*sizeof(char*));				//diplasiase to mege8os tou pinaka twn keys//
		*values=realloc(*values,(*memsize)*sizeof(char*));			//diplasiase to mege8os tou pinaka twn values//
	}
	
	if (  ( (*keys)[*total_records] = calloc(strlen(p.key)+1,sizeof(char)) ) == NULL )
	{
		perror("calloc");
		return;
	}
	strcpy((*keys)[*total_records],p.key);						//adegrapse sthn 1h kenh 8esh tou pinaka keys to key tou ekastote zeugariou//
	if (  ( (*values)[*total_records] = calloc(strlen(p.value)+1,sizeof(char)) ) == NULL )
        {
                perror("calloc");
                return;
        }
	
	strcpy((*values)[*total_records] ,p.value);					 //adegrapse sthn 1h kenh 8esh tou pinaka values to value tou ekastote zeugariou//
	*total_records=*total_records+1;
}

//synarthsh h opoia kanei retrieve oles tis eggrafes enos block kai gia ka8e eggrafh kalei thn update_vectors//
void retrieve_records(char *block,char ***keys, char ***values, int *total_records, int *memsize)
{
        int records,i,curbyte;

        memcpy(&records,block,sizeof(int));
        curbyte=4;
        for ( i=0; i<records; i++ )							//8a diavasw oles tis eggrafes pou uparxoun sto buffer//
        {
                update_vectors(keys,values,block+curbyte,total_records, memsize);	//gemizoun oi pinakes twn keys kai twn values oso..//
                while ( block[curbyte++]!='\0' );					//proxwra mexri to telos ths trexousas eggrafhs gia na vre8oume sthn arxh ths// 
//epomenhs// 
        }
}

