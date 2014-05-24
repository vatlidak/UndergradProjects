#include <stdio.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <dirent.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>
#include <string.h>
#include <fcntl.h>
#include "mapreduce.h"
#include "sort.h"
#include "buffers.h"
#define BLKSIZE 1024

pid_t pids[1000];
int Mappers;
int Reducers;

int r_wait(int* stat_loc){
	int rval;
	while( (rval=wait(stat_loc))==-1 && (errno==EINTR ));
	return rval;
}

static volatile sig_atomic_t error=0;  							//global metavlhth pou allazei timh asygxrona kai ypodeiknuei to telos ekteleshs//
static void handler1(int signo)								//orizoume ton handler tou patera//
 	
{
	int i;
	printf("signal catched from parent\n");
	for (i=0;i<Mappers+Reducers;i++)
		if ( pids[i]>0 )							//se ola ta paidia pou exoun prolavei na gennh8oun(pid>0)//
			kill(pids[i],SIGUSR1);						//steile shma SIGUSR1//
}
static void handler2(int signo) 							//orizoume ton handler tou paidiou//
{
	printf("signal catched from child\n");
	error=1;									//otan ena paidi piasei to shma apo ton patera 8a termatizei//
}

int main(int argc, char** argv) 
{
	char *record;
	char *block;									//endiamesos xwros mnhmhs ston opoio ekxwroun ta block oi reducers//
	int i,j,fd;
	char buffer[56];								//pinakas ston opoion sxhmatizoume to katallhlo format gia ta pipenames//
	pid_t pid;
	int status;
	fd_set read_set, active_set;							//ta set me tous file descriptors pou xrhsimopoiei h select//
	BUFFERS *buffers;								//deikths sthn arxh twn buffers//
	
	struct sigaction sig_act;

	if (argc!=3)									//onoma ektelesimou, #Mappers, #Reducers//
	{
		printf("Usage:%s  #Mappers  #Reducers\n",argv[0]);
		return -1;
	}
	
	sig_act.sa_handler=handler1;     		    				//Signal Handler1 gia ton patera//
	sig_act.sa_flags=0;
											//prosthetw ta simata sto set tou patera.
	if ((sigemptyset(&sig_act.sa_mask ) == -1) || (sigaction(SIGINT,&sig_act,NULL) == -1 ) 
	|| (sigaction(SIGQUIT,&sig_act,NULL) == -1 ) || (sigaction(SIGTERM,&sig_act,NULL) == -1 ))
	{
	      perror("FAIL TO INSTAL  SIGNAL HANDLER FOR SIGUSR1");
	      return -1;
	}
	Mappers=atoi(argv[1]);
	Reducers=atoi(argv[2]);
	for(i=0;i<Mappers;i++)								//dhmiourgia twn pipes prin dhmiourgh8oun ta paidia//
	{
		for (j=0;j<Reducers;j++)
		{
			buffer[0]='\0';
			sprintf(buffer,".pipe.%d.%d",i+1,j+1);				
			if ( mkfifo(buffer,0666 )==-1)	
       			{
                        	perror("mkfifo");
				removepipes(Mappers,Reducers);
                        	return -1;
                	}
		}
	}
	mkdir("./output_folder",0700);					//dhmiourgoume ton output folder//
	for(i=0;i<Mappers+Reducers;i++)							//kanena paidi den exei dhmiourgh8ei akoma//							
		pids[i]=0;
	for(i=0;i<Mappers+Reducers;i++)
	{
 		pids[i]=pid=fork();
		if (pid<0)								//periptwsh apotyxias fork()//
        	{									//epeidh den 3eroume posa paidia exoun gennh8ei epityxws,ara posa prepei na//
        		perror("fork failed\n");					//skotwsoume,o pateras stelnei ena SIGINT ston eauto tou kai o handler tou patera//
               		kill(getpid(),SIGINT);						//eidopoiei ta gennhmena paidia na termatisoun//
			removepipes(Mappers,Reducers);
                        return -1;
        	}
		else if ( pid==0 )							//to paidi vgainei apo to loop ka8ws mono h Initial prepei na kanei fork()//
			break;
	}
	if (pid==0)									//an eimaste sto paidi//
	{
		sigset_t ign_signals;
		
		//prosthetw sta 3 simata sto set twn paidiwn kai meta ta mplokarw//
		if ( (sigemptyset(&ign_signals ) == -1) || (sigaddset(&ign_signals,SIGINT) == -1 ) || (sigaddset(&ign_signals,SIGQUIT) == -1 ) 
				|| (sigaddset(&ign_signals,SIGTERM) == -1 ))
		{
	      		kill(getppid(),SIGINT);
		}
		else
			sigprocmask(SIG_BLOCK,&ign_signals,NULL);

 		
		sig_act.sa_handler=handler2;     		    			 //Signal Handler2-o handler twn paidiwn//
		sig_act.sa_flags=0;
		//orizw ton handler na antistoixei sto SIGUSR1, pou stelnei o parent//
		if ((sigemptyset(&sig_act.sa_mask ) == -1) || (sigaction(SIGUSR1,&sig_act,NULL) == -1 ))
	      		kill(getppid(),SIGINT);
		for(i=0;i<Mappers+Reducers;i++)						//anazhtw ston pinaka me ta pids to 10 mhdeniko,pou ypodeiknyei th seira gennhshs//
			if (pids[i]==0)
				break;
		i++;									//auti einai i thesi mou, gia na 3exwrizw an eimai maper i reducer//
		if (i<=Mappers)								//kwdikas tou mapper//
		{
			MRIFILE* fp;
			buffers=calloc(Reducers,sizeof(struct BUFFERS));		//desmeuoume mnhmh gia tosous buffers osoi einai kai oi reducers//	
			for (j=0;j<Reducers && !error ;j++)
			{
				buffer[0]='\0';
				sprintf(buffer,".pipe.%d.%d",i,j+1);			//dinoume onoma sta pipe//
				if ( (fd=open(buffer,O_WRONLY))<0 ) 			//anoigei to pipe gia grapsimo//
       		                {
					if ( errno != EINTR )				//an yparxei la8os k den einai apo shma//
        	                        	kill(getppid(),SIGINT);			//steile to shma //
	       	                	perror("Mapper::open");				//alliws ginetai allo la8os sthn open//
					free(buffers);					//kai apodesmevoume tous porous tou mapper//
					return -1;
        	                }
				initialize(buffers, j, fd);				//arxikopoioume tous buffers//
			}
			DIR             *dip;
			struct dirent   *dit;
			if ( (dip = opendir("input_folder")) == NULL)			//anoigoume ton inputfolder//
       			{
				if ( errno != EINTR )                           	//an yparxei la8os k den einai apo shma//
                                	kill(getppid(),SIGINT);                 	//steile to shma //
                                perror("Mapper::opendir");                         	//alliws ginetai allo la8os sthn open//
        		}
			while ((dit = readdir(dip)) != NULL  &&  !error)		//oso exoume files gia diavasma//
        		{
                		if ( strncmp(dit->d_name,"file_",5) == 0)		//an oi prwtoi 5 xarakthres twn 2 autwn string einai idioi,dhladh an einai file_//
				{
					int filenumber;					//ari8mos arxeiou input//
					
					sscanf(dit->d_name,"file_%d",&filenumber);	//kanw retrieve ton ari8mo tou trexodos arxeiou//
					if ( filenumber%Mappers+1==i)			//apofasizoume me katakermatismo poios mapper 8a diavazei apo ka8e file//
					{	
						char filename[50];
						sprintf(filename,"./input_folder/%s",dit->d_name);
						fp=input_open(filename);			//anoigoume to file//
						while ( (record=input_next(fp))!= NULL )	//kai oso uparxoun eggrafes gia diavasma//
						{						//kaleitai h addrecord gia pros8hkh eggrafwn stous buffers//
							addrecord(buffers,record,partition(map(record).key,Reducers));	
						}
						input_close(fp);			//kleinoume to file//
					}
				}
			}
			closedir(dip);							//kleinoume kai ton katalogo//
			for (j=0; j<Reducers && error==0; j++)				
			{
				if ( buffers[j].curbyte != 4 ){
					if ( my_write(buffers[j].pipedesc,buffers[j].block)!= BLKSIZE )	//grafoume sto pipe oses eggrafes exoun 3emeinei//
        	                       		printf("error here\n");
				}
			}
			for (j=0;j<Reducers;j++)
                       	{
				close(buffers[j].pipedesc);				//kleinoume ta pipe afou exoume diavasei//
			}
			free(buffers);							//afou teleiwnoume me to diavasma apodesmevoume taous buffers//
		}
		else									//kwdikas tou reducer//
		{
			char **keys;
			char **values;
			char *tempkey;							//deikths sthn prwth 8esh tou pinaka twn keys//
			char **tempval;							//deikths sthn prwth 8esh tou pinaka twn values//
			int counter;
			int total_records=0;
			int memsize=100;
			int whoami;							//8esh mias diergasias ston pinaka twn paidiwn//
			whoami=i;
			char buffer[40];
			MROFILE *fp;

			sprintf(buffer,"./output_folder/file_%d",whoami-Mappers);	//ka8orismos twn files sto output folder gia ton ka8e reducer
                        fp=output_open(buffer);

			if (  (keys=calloc(memsize,sizeof(char*))) == NULL		//an exoume provlhma me th desmeush tou pinaka gia ta keys,h' ta values// 
			|| (values=calloc(memsize,sizeof(char*)))==NULL 		//h' to block ,tote//
			|| (block=calloc(BLKSIZE,sizeof(char)))==NULL )
			{
			 	kill(getppid(),SIGINT);					//stelnoume shma ston patera//
			}
			FD_ZERO(&read_set);						//mhdenizoume to set twn file descriptors twn pipe//
			for (j=0;j<Mappers;j++)
			{
				buffer[0]='\0';
				sprintf(buffer,".pipe.%d.%d",j+1,i-Mappers);	
				if ( (fd=open(buffer,O_RDONLY))<0 ) 			//anoigoume to pipe gia diavasma//
       		                {
					if ( errno != EINTR )				//an yparxei la8os kai den einai apo shma//
						kill(getppid(),SIGINT);			//tote stelnoume to shma//
        	                	perror("Reducer::open");
					break;
        	                }
				FD_SET(fd,&read_set);					//pros8etoume ton fd sto readset//
			}
			active_set=read_set;
			int closed=0;							//arxikopoioume to plh8os twn diavasmenwn fds//
			while ( error==0 && closed != Mappers)				//oso uparxoun fds sto active set kai den lavei shma//
			{
				read_set=active_set;
				int chosen;
				if ( (chosen=select(FD_SETSIZE,&read_set,NULL,NULL,NULL)) < 0) 		
				{
					if ( errno != EINTR ){
                                                kill(getppid(),SIGINT);
						error=1;
					}
					perror("select");				//alliws yparxei provlhma sth select//
					break;
				}
				else							//h select epistrefei ton katallhlo fd//
				{
					for (i = 0; i < FD_SETSIZE; i++)		//gia olous tous fds pou yparxoun mesa sto set//
					{
             					if (FD_ISSET (i, &read_set))		//an o i fd einai melos tou read set otan epistrepsei h select//
						{
							if ( (chosen=my_read(i,block))<0 )		//diavase apo ton i fd//
							{
								if ( errno != EINTR )
								{
                                         			       	kill(getppid(),SIGINT);
                                                			error=1;
                                        			}
								perror("read");
								break;
							}
							else if ( chosen==0 )			
							{
								FD_CLR (i, &active_set); 	//afairei ton i fd apo to active set//
								closed++;			//au3anetai kata ena o ari8mos twn fds pou diavasthkan//
								close(i);			//kleinei o i fd//
								if ( closed == Mappers )
									break;
							}
							else
								retrieve_records(block,&keys,&values,&total_records,&memsize);
						}
					}
				}
			}
			printf("%s\n",keys[10000]);
			printf("%d\n",total_records);
			if ( error==0 )								//an den exoume lavei shma//
			{
				sort(keys, values, total_records,compare);						
        	                tempkey=keys[0];						//o deikths tempkey deixnei sthn 1h 8esh tou pinaka twn keys//
                	        tempval=values;
                        	counter=1;
                	        for ( i=1; i<total_records; i++)
                        	{
                               		if ( compare(tempkey,keys[i]) == 0 )			//an ta kleidia se dyo diadoxikes 8eseis tou pinaka einai idia//
                                	        counter++;					//au3anetai kata 1 to plh8os twn eggrafwn me to idio kleidi//	
                       		        else							//an ta kleidia se dyo diadoxikes 8eseis tou pinaka einai diaforetika//
                                	{
						output_next(fp,reduce(tempkey,tempval,counter));//kaleitai h reduce kai grafoume to apotelesma sto output file.//
                         	                counter=1;					//epilegoume neo kleidi//
                                	        tempkey=keys[i];				//h kainouria 8esh tou tempkey//
                                        	tempval=values+i;				//h kainouria 8esh tou tempval//
                                	}
        	                }
			}
			output_close(fp);							//kleinoume to output file tou kathe reducer//
			if ( block != NULL )							//apodesmeush twn porwn tou reducer//
				free(block);
			if ( keys != NULL && values!= NULL )					//an den exei ginei la8os kata th desmeush//
			{									//apodesmeuoume olh th dunamika desmeumenh mnhmh//
				for(i=0;i<memsize;i++)						
				{
					if ( keys[i]!=NULL && values[i]!=NULL )
					{
						free(keys[i]);
						free(values[i]);
					}
				}
				free(keys);
				free(values);
			}
			for (i = 0; i < FD_SETSIZE; i++)					//kleinoume olous tous file descriptors pou vriskodai sto active set//
                              if (FD_ISSET (i, &active_set))   
					close(i);
		}	
	}
	else											//alliws an eisai ston patera,Initial process//
	{
		while ( (pid=r_wait(NULL))>0 )							//perimenei ta paidia tou na teleiwsoun// 
		{	
			fprintf(stderr,"Child %d finished\n",pid);
		}	
		removepipes(Mappers,Reducers);							//svhsimo twn pipes//
	}
	return 0;
	
}

