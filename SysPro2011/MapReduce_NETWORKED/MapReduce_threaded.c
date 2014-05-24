#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <dirent.h>
#include <signal.h>
#include "buffers.h"
#include "mapreduce.h"
#define  perror2(s, e) fprintf(stderr, "%s: %s\n", s, strerror(e))
 

char *input_folder, *output_folder;
int numMappers, numReducers;
BUFFERS *buffers;


static void handler(int signo) 							//orizoume ton handler tou shmatos//
{
	int i;
	printf("signal catched from child\n");
	runflag=0;								//to runflag ginetai mhden otan lhf8ei kapoio shma//
	for ( i=0; i< numReducers; i++)						//gia oles tis metavlites sun8hkhs//
	{
		pthread_cond_broadcast(&buffers[i].mycond2);			//o mapper 8a 3ypnaei otan o edamieuths den einai gematos//
                pthread_cond_broadcast(&buffers[i].mycond1);			//o reducer 8a 3ypnaei otan o edamieuths den einai adeios//
	}
}



void *mapper(void* arg)								//kwdikas tou mapper//
{
	int i=*((int*)arg)+1;
	int filenumber;
	char filename[50];
	char *record;
	MRIFILE* fp;
	DIR  *dip;
	struct dirent   *dit;
	int *err=calloc(1,sizeof(int));						//desmevoume xwro sto swro ston opoio 8a apo8hkeusoume thn timh epistrofhs tou nhmatos etsi wste na boroume na thn prospelasoume meta to join//
	*err=-1;

	if ( (dip = opendir(input_folder)) == NULL)				//anoigoume ton inputfolder//
       	{
	        perror("Mapper::opendir");                         	
		return (void*)err;
        }
	while ((dit = readdir(dip)) != NULL  && runflag)			//oso exoume files gia diavasma//
        {
        	if ( strncmp(dit->d_name,"file_",5) == 0)			//an oi prwtoi 5 xarakthres twn 2 autwn string einai idioi,dhladh an einai "file_"//
		{
			sscanf(dit->d_name,"file_%d",&filenumber);		//kanw retrieve ton ari8mo tou trexodos arxeiou//
			if ( filenumber%numMappers+1==i)			//apofasizoume me katakermatismo poios mapper 8a diavazei apo ka8e file//
			{					
				sprintf(filename,"./%s%s",input_folder,dit->d_name);
				fp=input_open(filename);			//anoigoume to file//
				while ( (record=input_next(fp))!= NULL && runflag)	//kai oso uparxoun eggrafes gia diavasma//
					if ( addrecord(buffers,record,partition(map(record).key,numReducers)) == -1 )	//me addrecord grafoume ka8e eggrafh se buffer//
						return (void*)err;
				input_close(fp);				//kleinoume to file//
			}
		}
	}
	closedir(dip);
	*err=0;
	return (void*)err;
}

void *reducer(void* arg)							//kwdikas tou reducer//
{
        int i=*((int*)arg);
        int *err=calloc(1,sizeof(int));
        char **keys;
        char **values;
        char *tempkey;
        char **tempval;
        int counter;
        int total_records=0;
        long int memsize=100;
        char buffer[128];
        MROFILE *fp;


	*err=-1;								//se periptwsh la8ous kata th desmeush twn keys k twn values//
        if (  (keys=calloc(memsize,sizeof(char*))) == NULL || (values=calloc(memsize,sizeof(char*)))==NULL )
        {
                perror("calloc");
                return (void*)err;
        }

        while (MAPPERSOVER == 0 && runflag)					//oso den exoun teleiwsei oi mapper kai den exoume lavei shma//
        {
                if (*err = pthread_mutex_lock(&buffers[i].mylock))		//kleidwnoume ton mutex gia diavasma//
                {
                        perror2("pthread_mutex_lock", *err);
                        return (void*)err;
                }
                while ( buffers[i].records == 0 && MAPPERSOVER==0 && runflag)	//oso o edamieuths einai adeios k.l.p.,//
                        pthread_cond_wait(&buffers[i].mycond1, &buffers[i].mylock);	//o reducer 8a perimenei//
                if ( retrieve_records(buffers,i,&keys, &values, &total_records, &memsize) == -1 )	//kaleitai h retrieve_records//
		{
			return (void*)err;
		}
                buffers[i].full=0;						//o edamieuths den einai gematos//
                pthread_cond_broadcast(&buffers[i].mycond2);			//ara 3ypname ton mapper gia na grapsei//
                if (*err = pthread_mutex_unlock(&buffers[i].mylock))		//3ekleidwnoume ton mutex//
                {
                        perror2("pthread_mutex_lock", *err);
                        return (void*)err;
                }
        }
	if ( runflag == 1 )							//oso den exoume lavei shma//
	{
		sort(keys, values, total_records,compare);			//kaloume th sort//			
        	tempkey=keys[0];						//o deikths tempkey deixnei sthn 1h 8esh tou pinaka twn keys//
    	    	tempval=values;
        	counter=1;
		sprintf(buffer,"./%sfile_%d",output_folder,*((int*)arg)+1);	//ka8orismos twn files sto output folder gia ton ka8e reducer//
        	fp=output_open(buffer);
        	for ( i=1; i<total_records; i++)				//gia oles tis eggrafes//
        	{
        		if ( compare(tempkey,keys[i]) == 0 )			//an ta kleidia se dyo diadoxikes 8eseis tou pinaka einai idia//
           	        	counter++;					//au3anetai kata 1 to plh8os twn eggrafwn me to idio kleidi//	
                	else							//an ta kleidia se dyo diadoxikes 8eseis tou pinaka einai diaforetika//
                	{
				char *redrec=reduce(tempkey,tempval,counter);	
				if ( redrec == NULL )
				{
					*err=-1;
					return (void*) err;
				}	
				output_next(fp,redrec);				//kaleitai h reduce kai grafoume to apotelesma sto output file.//
                        	counter=1;					//epilegoume neo kleidi//
                        	tempkey=keys[i];				//h kainouria 8esh tou tempkey//
                      		tempval=values+i;				//h kainouria 8esh tou tempval//
               		}
        	}
		output_close(fp);
	}	
	if ( keys!=NULL && values!=NULL )					//apodesmeush ths dynamika desmeumenhs mnhmhs//
	{
       		for(i=0;i<total_records;i++)
	        {
			if ( keys[i] != NULL && values[i] != NULL )
			{
		       		free(keys[i]);
                		free(values[i]);
			}
        	}
        	free(keys);
        	free(values);     
	}
	*err=0;										//an ftasoume ews edw tote shmainei oti den exei ginei kanena la8os//
	return (void*)err;
}



int main(int argc, char** argv) 
{

	int i;
	int err, status;
	int *mapid, *redid;
	struct sigaction sig_act;
	pthread_t *mids, *rids;

	if ( argc!=6 )
	{
		printf("Usage:%s numMappers numReducers bufferSize input_folder output_folder\n",argv[0]);
		return -1;
	}
	runflag=1;
	MAPPERSOVER=0;
	sig_act.sa_handler=handler;     		    				//Signal Handler gia to arxiko nhma//
	sig_act.sa_flags=0;
											//prosthetw ta simata sto set tou arxikou nhmatos//
	if ((sigemptyset(&sig_act.sa_mask ) == -1) || (sigaction(SIGINT,&sig_act,NULL) == -1 ) )
	{
	      perror("FAIL TO INSTALL SIGNAL HANDLER FOR ---------------------------SIGUSR1");
	      return -1;
	}
	numMappers=atoi(argv[1]);
	numReducers=atoi(argv[2]);
	BuffSize=atoi(argv[3]);
	input_folder=argv[4];
	output_folder=argv[5];

	if ( mkdir(output_folder,0700) < 0 )						//dhmiourgoume ton output folder//
	{
		perror("mkdir");
		return -1;
	}
	if ( (mids=calloc(numMappers,sizeof(pthread_t))) == NULL || (rids=calloc(numReducers,sizeof(pthread_t))) == NULL 	//desmevw dynamika xwro gia M-R times id// 
	|| (mapid=calloc(numMappers,sizeof(int)))==NULL  || (redid=calloc(numReducers,sizeof(int)))==NULL )	//desmevw dynamika xwro gia M-R orismata//
	{
		perror("calloc");
		return -1;
	}

	if ( (buffers=calloc(numReducers,sizeof(struct BUFFERS))) == NULL )		//desmevw dynamika xwro gia ton buffer//
	{
		perror("calloc");
		return -1;
	}
	for (i=0; i<numReducers; i++ )
	{
		if ( (buffers[i].block=calloc(BuffSize,sizeof(char))) == NULL )
		{
			perror("calloc");
			return -1;
		}
		if ( initialize(buffers,i,BuffSize) ) 
			return -1;
				
	}
	for (i=0; i<numReducers; i++)
               redid[i]=i;
        for (i=0; i<numReducers; i++)							//dhmiourgw ta threads-reducers//
        {
                if (  err=pthread_create(rids+i, NULL, reducer, (void *)&redid[i]) )
                {
                        perror2("pthread_create", err);
                        return -1;
                }
        }
	for (i=0; i<numMappers; i++)		
		mapid[i]=i;
	for (i=0; i<numMappers; i++)							//dhmiourgw ta threads-mappers//
	{
        	if (  err=pthread_create(mids+i, NULL, mapper, (void *)&mapid[i]) )
		{
               		perror2("pthread_create", err);
               		return -1;
		}
	}	
	for ( i=0; i<numMappers; i++)
        {
		if (err = pthread_join(*(mids+i),(void**) &status))			//perimenei mexri na teleiwsei o stoxeumenos mapper// 
		{
                	perror2("pthread_join", err);
               		return -1;
		}
		printf("Mapper with %d terminated with status:%d\n",mapid[i],*(int*)status);
		if ( *(int*)status != 0 )						//an to return value einai diaforo tou 0//
                        kill(getpid(),SIGINT);						//steile shma gia la8os//
	}
	MAPPERSOVER=1;
	for ( i=0; i<numReducers; i++)							//3eblokarodai oi reducers apo th metavlhth syn8hkhs cond1//
	{
		buffers[i].full=1;
        	pthread_cond_signal(&buffers[i].mycond1);				
	}	

	for ( i=0; i<numReducers; i++)							
        {
		if (err = pthread_join(*(rids+i), (void**)&status)) 
		{
                	perror2("pthread_join", err);
               		return -1;
		}
		printf("Reducer with %d terminated with status:%d\n",redid[i],*(int*)status );
		if ( *(int*)status != 0 )
			kill(getpid(),SIGINT);
	}
	for (i=0; i<numReducers; i++ )							
        {
                free(buffers[i].block);							//apodesmevoume tous desmeumenous porous apo tis 2 metavlhtes syn8hkhs//
		pthread_cond_destroy(&buffers[i].mycond1);
		pthread_cond_destroy(&buffers[i].mycond2);
		pthread_mutex_destroy(&buffers[i].mylock);				//apodesmevoume ton mutex//
	}										//apodesmevoume olo to dynamika desmeumeno xwro//
	free(buffers);
	free(mapid);
	free(redid);
	free(rids);
	free(mids);
	
}

