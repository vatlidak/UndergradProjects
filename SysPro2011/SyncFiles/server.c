/*inet_str_server.c: Internet stream sockets server */
#include <stdio.h>
#include <dirent.h>
#include <sys/wait.h>	     /* sockets */
#include <sys/types.h>	     /* sockets */
#include <sys/socket.h>	     /* sockets */
#include <netinet/in.h>	     /* internet sockets */
#include <netdb.h>	         /* gethostbyaddr */
#include <unistd.h>	         /* fork */		
#include <stdlib.h>	         /* exit */
#include <ctype.h>	         /* toupper */
#include <signal.h>          /* signal */
#include <pthread.h>
#include <string.h>
#include "types.h"
#include "list.h"
#define perror2(s,e) fprintf(stderr, "%s: %s\n", s, strerror(e))



//handler gia ta simata SIGINT,SIGPIPE
static volatile sig_atomic_t runflag=1;

static void	 handler(int signo) {
	printf("Signal  catched \n");
	runflag=0;
}

fileptr metadata;			//lista arxeiwn tou server
pthread_mutex_t serverlist_mux;		//mutex gia ti lista tou server
char myip[25];
char myport[15];

void* serving_thread(void * argp);
int initialize(char *filename, fileptr *metadata);




int main(int argc, char *argv[]) {
    	int 	port, sock, newsock;
	int 	err;
	int 	*temp;
	char	workdir[50];
	char	prints[45];
	pthread_t 	thr;
	int 	i;
	char 	*config;
	char 	title[30];
	FILE 	*fp_config;
	socklen_t clientlen;
    	struct sockaddr_in server, client;	
    	struct sockaddr *serverptr=(struct sockaddr *)&server;
    	struct sockaddr *clientptr=(struct sockaddr *)&client;
    	struct hostent *rem;
	static struct sigaction act;

	

    	if (argc != 2) {
       	 	printf("Please give <configuration file>\n");
		return -1;
	}
	config=argv[1];
	if ( (fp_config=fopen(config,"rb")) == NULL )
	{
		perror("open config");
		return -1;
	}
	for(i=0;i<3;i++)
	{
		if (i == 0){
			fscanf(fp_config,"%s %s",title,workdir);
			printf("%s\n",workdir);
		}
		else if (i == 1){
			fscanf(fp_config,"%s %s",title,myip);
			printf("%s\n",myip);
		}
		else if (i == 2){
			fscanf(fp_config,"%s %s",title,myport);
			printf("%s\n",myport);
		}
	}
	fclose(fp_config);
  	port = atoi(myport);
	act.sa_handler=handler;
	sigfillset(&(act.sa_mask));
	sigaction(SIGPIPE,&act,NULL);
	sigaction(SIGINT,&act,NULL);
        

	pthread_mutex_init(&serverlist_mux,NULL);		//init to mutex tis listas
	if ( chdir(workdir) < 0 )				//metavasi sto fakelo twn arxeiwn gia sugxronismo
	{
		perror("chdir");
		return -1;
	}

	//dimiourgia socket
    	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{	
        	perror("socket");
		return -1;
	}	
    	server.sin_family = AF_INET;       			/* Internet domain */
    	server.sin_addr.s_addr = inet_addr(myip);
    	server.sin_port = htons(port);     			 /* The given port */
   	
	//bind socket
    	if (bind(sock, serverptr, sizeof(server)) < 0)
	{
		perror("bind");
        	return -1;
	}
	metadata=NULL;
	printf("going to initialize\n");
	//arxikopoiisi listas prosthetontas osa arxeia exei o fakelos
	initialize("./",&metadata);	
	printf("initialize over\n");
	printfile(metadata);
	
    	// Listen connections 
    	if (listen(sock, 5) < 0)
	{ 
		perror("listen");
		return -1;
	}
    	printf("Listening for connections to port %d\n", port);
    	while (1) 
	{
		temp=calloc(1,sizeof(int));
	
        	// accept connections 
    		if ( (newsock = accept(sock, clientptr, &clientlen)) < 0) 
		{	
			perror("accept");
			return -1;
		}	
		printf("newsock %d\n",newsock);
		*temp=newsock;
		if (err = pthread_create (&thr, NULL, serving_thread ,(void*)temp))
		{
			/* New thread */
			perror2("pthread_create ",err); 
			return -1; 
		}
    	}
	close(sock);
	//destroy mutex
	if ( err = pthread_mutex_destroy(&serverlist_mux ) ) 
	{ 
		/* Destroy mutex */
		perror2 (" pthread_mutex_destroy", err); 
		return -1; 
	}
}

void *serving_thread(void *argp) 
{
	char 	buffer[BUFSIZE];
	char	*clientip,*clientport;
	char 	*type,*data=NULL;
	int 	rval;
	int err;
	char 	*filename,*md5sum="xxx",*filesize="12324";
	int 	socket = *(int*)argp;
	fileptr tempnode;
	FILE 	*fp;
	char 	prints[45];
	
	printf("in thread:%d\n",socket);
	
	
	sprintf(prints,"../serverLog.%u",(unsigned int)pthread_self());
	if ( (fp = fopen(prints,"wb")) == NULL )
	{
		perror("fopen");
		return NULL;
	}
	if	(err=pthread_detach (pthread_self ()))	
	{
		// Detach thread  
		perror2("pthread_detach ",err);
		return NULL; 
	}
	////////////////////////////////////////////////////////////////


	if ((rval=myread(socket, buffer, BUFSIZE)) <= 0)
	{
		perror("read"); 
		return NULL;
	}
	if ( GetType(buffer,fp) == JOINREQUEST)
	{ 
		parse_JoinRequest(buffer,&clientip,&clientport);
		JoinResponse(buffer);
		fprintf(fp,"JoinResponse to client with ip: %s\n",clientip);
		if(mywrite(socket,buffer,BUFSIZE) <= 0 )
		{
			perror("write");
			return NULL;
		}
				
	}	
	while (runflag)
	{
	
		///Ask FileList///
		int rval;
		if ( (rval=myread(socket, buffer , BUFSIZE)) < 0)
		{	
			perror("read"); 
			break;
		}
		//an to socket exei kleisei
		else if ( rval == 0 )
		{
			close(socket);	
			break;
		}
		else if (GetType(buffer,fp) == ASKFILELIST) 
		{	
			//if (err = pthread_mutex_lock(&serverlist_mux) ){ 
			//	perror2(" pthread_mutex_lock ",err ); exit(1); }
			fprintf(fp,"upadate server's list\n");	
			initialize("./",&metadata);
			printf("initialization:\n");
			printfile(metadata);
			//chekarw ti lista me ta arxeia pou diatiro kai gia kathe komvo tha ftiaxno 2 orismata pou tou 
			//antistixoun filename kai md5 na mi ksexasw teleuteoorisma NULL
			FileList(buffer,metadata);
			fprintf(fp,"Send FileList to client with ip: %s\n",clientip);
			//if (err = pthread_mutex_unlock(&serverlist_mux) ){ 
			//	perror2(" pthread_mutex_unlock ",err ); exit(1); }
			if(mywrite(socket,buffer,BUFSIZE) <= 0 )
			{
				perror("write");
				break;
			}		
		}
		///AskFile///
		else if (GetType(buffer,fp) == ASKFILE)
		{ 
			parse_AskFile(buffer,&filename);
			fprintf(fp,"client with ip: %s asked for file:%s\n",clientip,filename);
			//lock list gia anazitisi tou arxeiou
			if (err = pthread_mutex_lock(&serverlist_mux) ){ 
				perror2(" pthread_mutex_lock ",err ); exit(1); }
			tempnode=filenode(metadata,filename,NULL);
			if (err = pthread_mutex_unlock(&serverlist_mux) ){ 
				perror2(" pthread_mutex_unlock ",err ); exit(1); }
			AskFileResponse(buffer,filename,myip,myport);
			fprintf(fp,"server is going to send the file to client \n");
			if(mywrite(socket,buffer,BUFSIZE) <= 0 )
			{	
				perror("write");
				break;
			}	
		}
		///GetFile///	
		else if (GetType(buffer,fp) == GETFILE)
		{
			parse_GetFile(buffer,&filename,&md5sum);
			//stelnei to arxeio pou tou zita kai sti lista tou oti autos o client exei pleon to arxeio
			//lock list gia na ton prosthesei sti lista
			GetFileResponse(socket,filename,md5sum);	
			if (err = pthread_mutex_lock(&serverlist_mux) ){ 
				perror2(" pthread_mutex_lock ",err ); exit(1); }
			tempnode=filenode(metadata,filename,md5sum);
			add_peer(&tempnode,clientip,clientport);
			if (err = pthread_mutex_unlock(&serverlist_mux) ){ 
				perror2(" pthread_mutex_unlock ",err ); exit(1); }
			fprintf(fp,"send  File %s to client with ip: %s\n",filename,clientip);		
		}
		///SendFile	
		else if (GetType(buffer,fp) == SENDFILE)
		{ 
			parse_SendFile(buffer,&filename,&md5sum,&filesize,socket);
			//lock list gia na prosthesei to arxeio
			if (err = pthread_mutex_lock(&serverlist_mux) ){ 
				perror2(" pthread_mutex_lock ",err ); exit(1); }
			add_file(&metadata,filename,md5sum);
			tempnode=filenode(metadata,filename,md5sum);
			add_peer(&tempnode,clientip,clientport);
			if (err = pthread_mutex_unlock(&serverlist_mux) ){ 
				perror2(" pthread_mutex_unlock ",err ); exit(1); }
			SendFileResponse(buffer,filename,md5sum);
			fprintf(fp,"new File %s from client with ip: %s\n",filename,clientip);
			if(mywrite(socket,buffer,BUFSIZE) <= 0 )
			{
				perror("write");
				break;
			}	
		
		}
		///DeleteFile	
		else if (GetType(buffer,fp) == DELETEFILE)
		{ 
			printf("DeleteFile\n");
			parse_DeleteFile(buffer,&filename,&md5sum);
			fprintf(fp,"File to delete: %s \n",filename);
			//lock list mux
			if (err = pthread_mutex_lock(&serverlist_mux) ){ 
				perror2(" pthread_mutex_lock ",err ); exit(1); }
			tempnode=filenode(metadata,filename,NULL);
			if (err = pthread_mutex_unlock(&serverlist_mux) ){ 
				perror2(" pthread_mutex_unlock ",err ); exit(1); }
			//lock file mux
			if (err = pthread_mutex_lock(&tempnode->file_mux) ){ 
				perror2(" pthread_mutex_lock ",err ); exit(1); }
			if( remove(filename) != 0 )
    				perror( "Error deleting file" );
  			else
    				printf("File  %s successfully deleted\n",filename);
			if (err = pthread_mutex_unlock(&tempnode->file_mux) ){ 
				perror2(" pthread_mutex_unlock ",err ); exit(1); }
			//lock list mux
			if (err = pthread_mutex_lock(&serverlist_mux) ){ 
				perror2(" pthread_mutex_lock ",err ); exit(1); }
			delete_file(&metadata,filename,md5sum);
			if (err = pthread_mutex_unlock(&serverlist_mux) ){ 
				perror2(" pthread_mutex_unlock ",err ); exit(1); }
			DeleteFileResponse(buffer,filename,md5sum);
			fprintf(fp,"file deleted %s\n",filename);
			if(mywrite(socket,buffer,BUFSIZE) <= 0 )
			{
				perror("write");
				break;
			}	
		}	
	}
	close(socket);
	fprintf(fp,"Closing connection.\n");
	fclose(fp);
	free(argp);
}

int initialize(char *filename, fileptr *metadata)
{
        DIR             *dip;
        struct dirent   *dit;
        int             i = 0;
	char 		md5[32+1];
 
	//anoigma katalogou
        if ((dip = opendir(filename)) == NULL)
        {
                perror("opendir");
                return -1;
        }
        // struct dirent *readdir(DIR *dir);
	// Read in the files from argv[1] and print 
        while ((dit = readdir(dip)) != NULL)
        {
                i++;
		if ( dit->d_type != DT_REG )
			continue;
		if ( !strcmp(dit->d_name,".") || !strcmp(dit->d_name,"..") )
			continue;
		if ( MD5Sum_File(dit->d_name,md5)<0 )
		{
			fprintf(stderr,"MD5Sum_File error\n");
			continue;
		}
		//upadate listas 
		if ( !file_in(*metadata,dit->d_name, md5) )
			add_file(metadata,dit->d_name, md5);
        }
        // int closedir(DIR *dir);
        if (closedir(dip) == -1)
        {
                perror("closedir");
                return -1;
        }
        return 0;
}
