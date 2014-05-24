/* inet_str_client.c: Internet stream sockets client */
#include <stdio.h>
#include <dirent.h>
#include <sys/wait.h>	     	/* sockets */
#include <sys/types.h>	     	/* sockets */
#include <sys/socket.h>	     	/* sockets */
#include <netinet/in.h>		/* internet sockets */
#include <netdb.h>	     	/* gethostbyaddr */
#include <unistd.h>	     	/* fork */		
#include <stdlib.h>	       	/* exit */
#include <ctype.h>	       	/* toupper */
#include <signal.h>          	/* signal */
#include <sys/stat.h>
#include <pthread.h>
#include <string.h>
#include "types.h"
#include "list.h"
#define perror2(s,e) fprintf(stderr, "%s: %s\n", s, strerror(e))



fileptr 	metadata;
pthread_mutex_t clientlist_mux;
char 	server_ip[20];
int 	server_port;
char 	myport[15];
char 	myip[20];


int 	initialize(char *filename, fileptr *metadata);
void* 	client_thread(void * argp);
static volatile sig_atomic_t runflag=1;
///handler gia ta simata SIGINT,SIGPIPE
static void	 handler(int signo) {
	printf("Signal  catched \n");
	runflag=0;
}

int main(int argc, char *argv[]) {
    	int     port, sock,listening_sock,newsock, i,err;
	int	*temp;
    	char    buffer[BUFSIZE];
	char 	workdir[50];
	char	*type;
	char	**args;
	char 	prints[20];
	char 	*config;
	char title[30];
	char serverport[10];
	FILE 	*fp_config;
	pthread_t thr;
	socklen_t clientlen;
   	struct	sockaddr_in server,client;	
   	struct	sockaddr *serverptr = (struct sockaddr*)&server;
	struct 	sockaddr *clientptr=(struct sockaddr *)&client;
    	struct	hostent *rem;
	static struct sigaction act;
	


    	if (argc != 2) 
	{
	    	printf("Please give <configuration file>\n");
	       	return -1;
	}
	pthread_mutex_init(&clientlist_mux,NULL);		//initialiazation mutex tis listas

	config=argv[1];
	if ( (fp_config=fopen(config,"rb")) == NULL )
	{
		perror("open config");
		return -1;
	}
	for(i=0;i<5;i++)
	{
		if (i == 0){
			fscanf(fp_config,"%s %s",title,workdir);
			printf("%s\n",workdir);
		}
		else if (i == 1){
			fscanf(fp_config,"%s %s",title,server_ip);
			printf("%s\n",server_ip);
		}
		else if (i == 2){
			fscanf(fp_config,"%s %s",title,serverport);
			printf("%s\n",serverport);
		}
		else if (i == 3 ){
			fscanf(fp_config,"%s %s",title,myip);
			printf("%s\n",myip);
		}
		else if (i == 4){
			fscanf(fp_config,"%s %s",title,myport);
			printf("%s\n",myport);
		}			
	}
	fclose(fp_config);
	server_port = atoi(serverport);

	act.sa_handler=handler;
	sigfillset(&(act.sa_mask));
	sigaction(SIGPIPE,&act,NULL);
	sigaction(SIGINT,&act,NULL);

	
	//dimiourgia socket
    	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		perror("socket");
		return -1;
	}
	// Find server address
    	if ((rem = gethostbyname(server_ip)) == NULL) {	
	   	herror("gethostbyname"); 
		return -1;
    	}
    	server.sin_family = AF_INET;      		 		/* Internet domain */
    	memcpy(&server.sin_addr, rem->h_addr, rem->h_length);
    	server.sin_port = htons(server_port);         			/* Server port */


	if ( chdir(workdir) < 0 )			//metavasi sto katalogo gia to sugxronismo arxeiwn
	{
		perror("chdir");
		return -1;
	}

	metadata=NULL;
	initialize("./",&metadata);	
	printf("initialize over\n");
	printfile(metadata);
	
	//connection me to server
    	if (connect(sock, serverptr, sizeof(server)) < 0)
	{
		perror("connect");
		return -1;
	}
    	printf("Connecting to %s port %d\n", server_ip,server_port);
	// New thread
	if (err = pthread_create(&thr, NULL,client_thread,&sock))
	{
		perror2("pthread_create ",err); 
		return -1; 
	}

	////////////////////////////////////////////////////////////////////
	// dimiourgia listening socket gia serving
    	if ((listening_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{	
		perror("socket");
		return -1;
	}	
	server.sin_family = AF_INET;      		 //* Internet domain 
	server.sin_addr.s_addr = inet_addr(myip) ;
	server.sin_port = htons(atoi(myport));      		//* The given port 

	// Bind socket to address 
    	if (bind(listening_sock, serverptr, sizeof(server)) < 0)	////////////////////////////////////////////
	{
		perror("bind");
		return -1;
	}	
    	// Listen for connections 
    	if (listen(listening_sock, 5) < 0)
	{ 
		perror("listen");
		return -1;
	}
    	printf("Listening for connections to port %s\n",myport);

   	while (runflag) 
	{
		temp=calloc(1,sizeof(int));
        	// accept connection 
    		if ((newsock = accept(listening_sock, clientptr, &clientlen)) < 0) 
		{	
			perror("accept");
			return -1;
		}	
		printf("accept new connection serving thread of client %d\n",newsock);
		*temp=newsock;	
//den ulopiithike telika		
/*		if (err = pthread_create (&thr, NULL, serving_thread ,(void*)temp))
		{
			perror2("pthread_create ",err); 
			return -1; 
		}
*/
		free(temp);
	}
	if ( err = pthread_mutex_destroy(&clientlist_mux ) ) 		// Destroy mutex
	{ 
		perror2 (" pthread_mutex_destroy", err); 
		return -1; 
	}
	release_metadata(metadata);
	close(listening_sock);
}			     


void* client_thread(void* argp)
{
	char 	buffer[BUFSIZE];
	fileptr temp,temp1,temp2;
	FILE 	*fp;
	char	prints[45];
	int 	ssocket = *(int*)argp;
	int 	sock;
	int 	err;
	int 	rval;
	struct 	stat buf;
	long 	st_size;
   	struct	sockaddr_in server;
   	struct	sockaddr *serverptr = (struct sockaddr*)&server;
    	struct	hostent *rem;
	char 	*filename,*ip,*port,*md5sum,*filesize,*data;


	/* Detach thread */
	if	( err=pthread_detach(pthread_self()) )	
	{ 
		perror2("pthread_detach ",err);
		return NULL; 
	}
	//anoigma arxeiou gia ektupwsi pliroforiwn
	sprintf(prints,"../clientLog.%u",(unsigned int)pthread_self());
	if ( (fp = fopen(prints,"wb")) == NULL )
	{
		perror("fopen");
		return NULL;
	}
	///JoinRequest///
	JoinRequest(buffer,myip,myport);
	if ( mywrite(ssocket,buffer,BUFSIZE)<=0 ) {
		perror("write");
		return NULL;
	}
	fprintf(fp,"JoinRequest to server %s\n",server_ip);
	if (myread(ssocket,buffer,BUFSIZE) <=0 ) {
		perror("read");
		return NULL;
	}
	///JoinResponse///
	if (GetType(buffer,fp) == JOINRESPONSE)
		fprintf(fp,"Join succeded\n");
	else
	{
		fprintf(fp,"Join Failed\n");
		return NULL;
	}
	while(runflag)
	{	
		///AskFileList///
		AskFileList(buffer);
		if ( mywrite(ssocket,buffer,BUFSIZE)<=0 ) {
			perror("write");
			return NULL;
		}
		fprintf(fp,"AskFileList\n\n");
		if (myread(ssocket,buffer,BUFSIZE) <=0 ) {
			perror("read");
			return NULL;
		}
		///FileList///	
		if (GetType(buffer,fp) == FILELIST)
		{
			parse_FileList(buffer,&temp);			//temp: to filelist tou server
			temp1=temp;
			while (temp != NULL) 
			{	
				//o client vlepei apo to filelist tou server osa den exei kai ta zita
				if ( (temp2=filenode(metadata,temp->filename,NULL)) == NULL ) 
				{				
					printf("Ready to ask file:<%s> <%s>\n",temp->filename,temp->md5);
					///AskFile///
					AskFile(buffer,temp->filename);
					if ( mywrite(ssocket,buffer,BUFSIZE)<=0 ) {
						perror("write");
						return NULL;
					}
					fprintf(fp,"AskFile: %s\n",temp->filename);
					if (myread(ssocket,buffer,BUFSIZE) <=0 ) {
						perror("read");
						return NULL;
					}
					///AskFileResponse
					if (GetType(buffer,fp) == ASKFILERESPONSE) {
						parse_AskFileResponse(buffer,&filename,&ip,&port);
					}
					//to arxeio tha to parei apeutheias apo ton server,oxi apo kapoio allo client
					if ( strcmp(ip,server_ip) == 0 )
					{
						printf("GetFile\n");
						GetFile(buffer,filename,temp->md5);
						fprintf(fp,"GetFile: %s from server\n",filename);
						if ( mywrite(ssocket,buffer,BUFSIZE)<=0 ) {
							perror("write");
							return NULL;
						}
						if (myread(ssocket,buffer,BUFSIZE) <=0 ) {
							perror("read");
							return NULL;
						}
						//o client pernei to arxeio kai to prosthetei kai sti lista tou
						if (GetType(buffer,fp) == GETFILERESPONSE)
						{	
							//pernw to arxeio prwti fora-de xreiazete filelock gt den uparxei 
							//akoma sti lista opote de tha to zitisei kaneis
							parse_GetFileResponse(buffer,&filename,&md5sum,&filesize,ssocket);
							if (err = pthread_mutex_lock(&clientlist_mux) ){ 
								perror2(" pthread_mutex_lock ",err ); exit(1); }
							add_file(&metadata,filename,md5sum);
							if (err = pthread_mutex_unlock(&clientlist_mux) ){ 
								perror2 ("pthread_mutex_lock ",err); exit(1); }	
							printf("GetFileResponse\n");
						}
					}
					//to arxeio tha to parei apo kapoio allo client me vash to ip+port pou tou edwse o server
					//dimiourgei neo socket me ton client auto kai zita to arxeio
					/*else
					{
						/* Create socket */
    					/*	if ((sock = socket(PF_INET, SOCK_STREAM, 0)) < 0){
							perror("socket");
							return NULL;
						}
						/* Find server address */
    					/*	if ((rem = gethostbyname(ip)) == NULL) {	
	   						perror("gethostbyname"); 
							return NULL;
    						}
						server.sin_family = AF_INET;      		 	/* Internet domain */
    					/*	memcpy(&server.sin_addr, rem->h_addr, rem->h_length);
    						server.sin_port = htons(atoi(port));         		/* Server port */
						/*connect*/
    					/*	if (connect(sock, serverptr, sizeof(server)) < 0)
						{
							perror("connect");
							return NULL;
						}
    						printf("Connecting to %s port %d\n",ip,atoi(port));
						GetFile(buffer,filename,temp->md5);
						fprintf(fp,"GetFile: %s from client with ip %s\n",filename,ip);
						if ( mywrite(sock,buffer,BUFSIZE)<=0 ) {
							perror("write");
							return NULL;
						}
						if (myread(sock,buffer,BUFSIZE) <=0 ) {
							perror("read");
							return NULL;
						}
						if (GetType(buffer,fp) == GETFILERESPONSE)
						{
	
							parse_GetFileResponse(buffer,&filename,&md5sum,&filesize,sock);
							if (err = pthread_mutex_lock(&clientlist_mux) ){ 
								perror2(" pthread_mutex_lock ",err ); exit(1); }
							add_file(&metadata,filename,md5sum);
							if (err = pthread_mutex_unlock(&clientlist_mux) ){ 
								perror2 ("pthread_mutex_lock ",err); exit(1); }
							printf("GetFileResponse\n");
						}
						close(sock);
					}*/
								
				}


			//to arxeio uparxei sti lista tou client alla tha prepei na ginei elegxos gia pithanes allages
			//o client,o server h kai oi duo mporei na exoun tropopoihsei to arxeio 
				else
				{ 
					char tempmd5[33];
					int filefound=1;
					//elegxw an exei ginei allagi se kapoio arxeio tou client 
					if ( MD5Sum_File(temp2->filename,tempmd5) < 0 )
						filefound=0;
										//temp->md5:  md5 tou arxeiou tou server
										//temp2->md5: md5 tou arxeiou sti lista tou client
										//tempmd5:    md5 tou arxeiou tou client sto disko
					if ( filefound )
					{
						if ( strcmp(tempmd5,temp2->md5) && !strcmp(temp->md5,temp2->md5) )
						{
							//to arxeio exei tropopoieithei apo ton client 
							//o server prepei na parei tin kainouria ekdosi ,opote sendfile

							//lock to filemux oso stelnw to arxeio
							if (err = pthread_mutex_lock(&(temp2->file_mux)) ){ 
								perror2(" pthread_mutex_lock ",err ); exit(1); }
							SendFile(ssocket,temp->filename,temp->md5);
							fprintf(fp,"SendFile: %s to server,file modified\n",temp->filename);
							if (err = pthread_mutex_unlock(&(temp2->file_mux)) ){ 
								perror2(" pthread_mutex_unlock ",err ); exit(1); }
							if (myread(ssocket,buffer,BUFSIZE) <=0 ) 
							{
								perror("read");
								return NULL;
							}
							///SendFileResponse///
							if (GetType(buffer,fp) == SENDFILERESPONSE)
							{
								parse_SendFileResponse(buffer,filename,md5sum);
								fprintf(fp,"File send to server\n");
								
							}
							//enimerwsi tis listas me to neo md5 tou arxeiou 
							strcpy(temp2->md5,tempmd5);					
						}
					}
					if (   strcmp(temp->md5,temp2->md5)   )
					{
					//to arxeio mporei na exei tropopoieithei apo ton client i oxi alla
					//o server exei kainouria ekdosi ,opote prepei na antikatastathei tou client
						printf("Ready to ask file:<%s> <%s>\n",temp2->filename,temp2->md5);
						///AskFile///
						AskFile(buffer,temp->filename);
						fprintf(fp,"AskFile: %s from server,file modified\n",temp->filename);
						if ( mywrite(ssocket,buffer,BUFSIZE)<=0 ) {
							perror("write");
							return NULL;
						}
						if (myread(ssocket,buffer,BUFSIZE) <=0 ) {
							perror("read");
							return NULL;
						}
						if (GetType(buffer,fp) == ASKFILERESPONSE) {
							parse_AskFileResponse(buffer,&filename,&ip,&port);
						}
						//to arxeio tha to parei apeutheias apo ton server,oxi apo kapoio allo client
						if ( strcmp(ip,server_ip) == 0 )
						{	
							printf("GetFile\n");
							GetFile(buffer,filename,temp->md5);
							fprintf(fp,"GetFile: %s from server\n",filename);
							if ( mywrite(ssocket,buffer,BUFSIZE)<=0 ) {
								perror("write");
								return NULL;
							}
							if (myread(ssocket,buffer,BUFSIZE) <=0 ) {
								perror("read");
								return NULL;
							}
							//o client pernei to arxeio kai to prosthetei kai sti lista tou
							if (GetType(buffer,fp) == GETFILERESPONSE)
							{
								//lock file
								if (err = pthread_mutex_lock(&(temp2->file_mux)) ){ 
									perror2(" pthread_mutex_lock ",err ); exit(1); }
								parse_GetFileResponse(buffer,&filename,&md5sum,&filesize,ssocket);
								if (err = pthread_mutex_unlock(&(temp2->file_mux)) ){ 
									perror2(" pthread_mutex_unlock ",err ); exit(1); }
								//lock list gia tin antikatastasi
								if (err = pthread_mutex_lock(&clientlist_mux) ){ 
									perror2(" pthread_mutex_lock ",err ); exit(1); }
								delete_file(&metadata,temp2->filename,temp2->md5);
								add_file(&metadata,filename,md5sum);
								if (err = pthread_mutex_unlock(&clientlist_mux) ){ 
									perror2(" pthread_mutex_unlock ",err ); exit(1); }
								printf("GetFileResponse\n");
							}
						}

					}
				}
				temp=temp->next;
			}
			//o client stelnei ta arxeia pou exei autos kai de ta exei o server
			temp=metadata;
			printfile(temp);			//temp:	to filelst tou client
			while (temp != NULL)			//temp1:to filelist tou server
			{
				FILE *ft;
				//elegxw prwta an exei diagrafei kapoio arxeio gia na steilw deletefile sto server
				//i periptwsi pou to arxeio exei diagrafei alla exei ananewthei tou server-opote prepei na
				//parei tou server sumperilamvanetai sti genikoteri periptwsi parapanw 
				if ( (ft=fopen(temp->filename,"r")) == NULL )
				{
					printf("file not found\n");
					///DeleteFile///
					DeleteFile(buffer,temp->filename,temp->md5);
					fprintf(fp,"DeleteFile: %s from server",temp->filename);
					if ( mywrite(ssocket,buffer,BUFSIZE)<=0 ) 
					{
						perror("write");
						return NULL;
					}
					if (myread(ssocket,buffer,BUFSIZE) <=0 ) 
					{
						perror("read");
						return NULL;
					}
					///DeletreFileResponse///
					if (GetType(buffer,fp) == DELETEFILERESPONSE) 
					{
						parse_DeleteFileResponse(buffer,filename,md5sum);
						fprintf(fp,"File Deleted from server\n");
					}
					//lock list gia na kanw to delete apo ti lista tou client
					if (err = pthread_mutex_lock(&clientlist_mux) ){ 
						perror2(" pthread_mutex_lock ",err ); exit(1); }
					delete_file(&metadata,temp->filename,temp->md5);
					if (err = pthread_mutex_unlock(&clientlist_mux) ){ 
						perror2(" pthread_mutex_unlock ",err ); exit(1); }
				}
				else 
					fclose(ft);
				//osa den exei katholou o server ta stelnei o client
				if (!file_in(temp1,temp->filename,temp->md5)){
					//lock file gia na to steilw swsta
					if (err = pthread_mutex_lock(&(temp->file_mux)) ){ 
						perror2(" pthread_mutex_lock ",err ); exit(1); }
					SendFile(ssocket,temp->filename,temp->md5);
					fprintf(fp,"SendFile: %s from server",temp->filename);
					if (err = pthread_mutex_unlock(&temp->file_mux) ){ 
						perror2(" pthread_mutex_unlock ",err ); exit(1); }
					if (myread(ssocket,buffer,BUFSIZE) <=0 ) 
					{
						perror("read");
						return NULL;
					}
					if (GetType(buffer,fp) == SENDFILERESPONSE)
					{
						parse_SendFileResponse(buffer,filename,md5sum);
						fprintf(fp,"File Send to server\n");
					}					
				}
				temp=temp->next;
			}

		}

		sleep(20);
		fprintf(fp,"upadate client's list\n");
		//update list gia tin epomeni periodo
		initialize("./",&metadata);
	}
	fclose(fp);
	
	return NULL;
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
	//update-mono nea arxeia mpainoun sti lista
	while ((dit = readdir(dip)) != NULL)
	{
		i++;
		if ( dit->d_type != DT_REG )
			continue;
		if ( !strcmp(dit->d_name,".") || !strcmp(dit->d_name,"..") )
			continue;
		if ( MD5Sum_File(dit->d_name,md5)<0 )
		{
			fprintf(stderr,"MD5Sum_File error at file:%s\n",dit->d_name);
			continue;
		}
		if ( !file_in(*metadata,dit->d_name, NULL) )
			add_file(metadata,dit->d_name, md5);
	}
	//kleisimo katalogou
	if (closedir(dip) == -1)
	{
		perror("closedir");
		return -1;
	}
	return 0;
}




//void *serving_thread(void *argp) 	
//{
//	char buffer[BUFSIZE];
//	char *type;
//	int socket = *(int*)argp;
//	int err;
//		
//	if	(err=pthread_detach (pthread_self ()))	
///	{
		/* Detach thread */ 
	//	perror2("pthread_detach ",	err);
	//	return NULL; 
	//}
		
	//if (myread(socket, buffer, BUFSIZE) <= 0)
	//{	
	//	perror("read"); 
	///	goto ERROR;
	//}	
//	if (GetType(buffer) == JOINREQUEST)
//	{ 
//		printf("JoinRequest\n");
//		bzero(buffer,BUFSIZE);
///		JoinResponse(buffer);
	///	if(mywrite(socket,buffer,BUFSIZE) <= 0 )
	//	{
	//		perror("write");
	//	
	//goto ERROR;
	//	}	
	//		
	//}	
	////Ask File///
	//if (myread(socket, buffer , BUFSIZE) <= 0)
	//{	
	//	perror("read"); 
	//	goto ERROR;
	//}	
	//if (GetType(buffer) == AskFile) {
	///	printf("AskFile\n");
		//FileList(buffer); //chekarw ti lista me ta arxeia pou diatiro kai gia kathe komvo tha ftiaxno 2 orismata pou tou antistixoun filename kai md5 na mi ksexasw teleuteo orisma NULL.
		//if(mywrite(socket,buffer,BUFSIZE) <= 0 )
		//{
		//	perror("write");
		//	goto ERROR;
		//}	
	//}
	
	//printf("%s\n",buffer);
//	printf("Closing connection.\n");
	
//		free(argp);
//}



