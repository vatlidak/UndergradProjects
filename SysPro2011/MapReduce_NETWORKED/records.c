#include <stdio.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <dirent.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include "records.h"
#include "buffers.h"
#include "mapreduce.h"

#define  perror2(s, e) fprintf(stderr, "%s: %s\n", s, strerror(e))

//synarthsh h opoia pros8etei mia eggrafh ston buffer pou ypodeiknyei h partition//
int addrecord(BUFFERS *buffers, char *record, int i)					
{
		int err;
		char delim='\0';
		char *block=buffers[i].block;						//deikths sto block tou ka8e buffer//
		char temp[56];
		
		if (  err=pthread_mutex_lock(&buffers[i].mylock) )			//kleidwnoume ton mutex// 
		{
			perror2("pthread_mutex_lock", err); 
			return -1;
		}
 		if ( strlen(record)+buffers[i].curbyte< BuffSize-1  )			//oso uparxei xwros sto buffer//
                {
                        memcpy(block+buffers[i].curbyte,record,strlen(record)); 	//adigrafoume sth 8esh curbyte to record//	
                        buffers[i].curbyte+=strlen(record);				//kratame th nea 8esh (telos eggrafwn) sto curbyte//
                        memcpy(block+buffers[i].curbyte,&delim,sizeof(char));		//sthn prwth 8esh meta thn teleutaia eggrafh pros8etoume ton delimeter//
                        buffers[i].curbyte++;
                        buffers[i].records++;
			pthread_cond_broadcast(&buffers[i].mycond1);			//3ypname ton reducer giati uparxoun dedomena gia diavasma//
                        if (err = pthread_mutex_unlock(&buffers[i].mylock)) 		//3ekleidwnoume ton mutex//
			{
				perror2("pthread_mutex_lock", err); 
				return -1;
			}
                }
                else									//an gemisei o buffer//
                {
			
			buffers[i].full=1;
			while (  buffers[i].full==1 && runflag)				//oso o edamieuths einai gematos kai den exoume lavei shma//
  	                	pthread_cond_wait(&buffers[i].mycond2, &buffers[i].mylock);	//o mapper koimatai mexri na adeiasei o buffer-----------------//
			if ( strlen(record)+buffers[i].curbyte< BuffSize-1  )                   //an uparxei xwros sto buffer//
                	{
                        	memcpy(block+buffers[i].curbyte,record,strlen(record));         //adigrafoume sth 8esh curbyte to record//
                	        buffers[i].curbyte+=strlen(record);                             //kratame th nea 8esh (telos eggrafwn) sto curbyte//
        	                memcpy(block+buffers[i].curbyte,&delim,sizeof(char));           //sthn prwth 8esh meta thn teleutaia eggrafh pros8etoume ton delimeter//
      		                buffers[i].curbyte++;
                 	       	buffers[i].records++;
                        	pthread_cond_broadcast(&buffers[i].mycond1);			//3ypname ton mapper//			
                	}
			if (err = pthread_mutex_unlock(&buffers[i].mylock)) 			//3ekleidwnoume ton mutex//
			{
				perror2("pthread_mutex_lock", err); 
				return -1;
			}
                }
		return 0;
}


//synarthsh h opoia pros8etei to key kai to value mias eggrafhs stous pinakes kai enhmerwnei ton ari8mo twn synolikwn eggrafwn prokeimenou na kanoume realloc otan einai// 
//anagaio//
int update_vectors(char ***keys,char ***values, char *record, int *total_records, int *memsize)
{
        pair p;
        p=map(record);
	
	char **t;
	if ( *total_records == *memsize )							//an gemisei o pinakas//
	{	
		*memsize=(*memsize)*2;							
		if ( (*keys=realloc(*keys,(*memsize)*sizeof(char*))) == NULL			//diplasiase to mege8os tou pinaka twn keys//
		|| ( *values=realloc(*values,(*memsize)*sizeof(char*))) == NULL )		//diplasiase to mege8os tou pinaka twn values//
		{
			perror("calloc");
			return -1;
		}
	}
	
	if (  ( (*keys)[*total_records] = calloc(strlen(p.key)+1,sizeof(char)) ) == NULL )
	{
		perror("calloc");
		return -1;
	}
	strcpy((*keys)[*total_records],p.key);							//adegrapse sthn 1h kenh 8esh tou pinaka keys to key tou ekastote zeugariou//
	if (  ( (*values)[*total_records] = calloc(strlen(p.value)+1,sizeof(char)) ) == NULL )
        {
                perror("calloc");
                return -1;
        }
	
	strcpy((*values)[*total_records] ,p.value);					 	//adegrapse sthn 1h kenh 8esh tou pinaka values to value tou ekastote zeugariou//
	*total_records=*total_records+1;
}

//synarthsh h opoia kanei retrieve oles tis eggrafes enos block kai gia ka8e eggrafh kalei thn update_vectors//
int retrieve_records(BUFFERS* buffers, int i,char ***keys, char ***values, int *total_records, int *memsize)
{
        int  curbyte,j;
	char *block=buffers[i].block;
	int records=buffers[i].records;

        curbyte=0;
        for ( j=0; j<records; j++ )								//8a diavasw oles tis eggrafes pou uparxoun sto buffer//
        {
                if ( update_vectors(keys,values,block+curbyte,total_records, memsize) == -1 )	//gemizoun oi pinakes twn keys kai twn values oso..//
			return -1;
                while ( block[curbyte++]!='\0' );						//proxwra mexri to telos ths trexousas eggrafhs gia na vre8oume sthn arxh ths// 
//epomenhs// 
        }
	buffers[i].records=0;
	buffers[i].curbyte=0;
}

