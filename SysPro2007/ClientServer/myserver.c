#include <sys/types.h> /* For sockets */
#include <sys/socket.h> /* For sockets */
#include <sys/select.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <netinet/in.h> /* For Internet sockets */
#include <netdb.h> /* For gethostbyaddr */
#include <stdio.h> /* For I/O */
#include <stdlib.h> /* For exit */
#include <string.h> /* For strlen, bzero */
#include <signal.h>
#include <time.h>
#include <errno.h>
#define  READ 0
#define  WRITE 1
#define  BUFSIZE   256
#define  DGR_SIZE  45
#define  NAME_SIZE 40

int port,dgr_sock,sock,newsock,fd[2],i,j,command_count,bytesread,sent_flag,ready,NUMCHILDREN,packets,first;
float probFail;
fd_set active_fd_set, read_fd_set;
pid_t parent_pid,pid, pid_code[100];
char dgr_port[DGR_SIZE],name[NAME_SIZE],temp[512],PID_COMMAND[512],command[256],testedcommand[256],ch;
FILE *fp;

void clean_up_children_process();
void timeToStop();
int read_from_client (int,struct hostent* );


int main(int argc, char *argv[]) 
{  
   int retval,yes=1;
   long curtime;
   unsigned int serverlen, clientlen;
   struct sockaddr_in server,client,clientname;
   struct hostent *rem;
   size_t size;
   sigset_t intmask;
   struct sigaction sigchild_action,act_stop;

   if (argc < 4  || atoi(argv[2])<1 || atof(argv[3])<0.00 || atof(argv[3])>1.00) { // Check arg's //
      printf("Usage:name TCP port number NUMCHILDREN>=1\n");
      return 1; }
   NUMCHILDREN=atoi(argv[2]);
   if (pipe(fd)==-1) {                        // Create pipe//
      perror("pipe");
      return 1; }
   if ((sock = socket(PF_INET, SOCK_STREAM, 0)) < 0) { //Create socket for TCP communication-passive// 
      perror("parent:socket");                         //communication endpoint                    //
      return 1; }
   port = atoi(argv[1]);                       // Convert port number to integer //
   server.sin_family = PF_INET;                // Internet domain //
   server.sin_addr.s_addr = htonl(INADDR_ANY); // My Internet address //
   server.sin_port = htons(port);              // The given port //
   while ( (retval=setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(yes)))==-1 && errno==EINTR );
   if ( (retval)>0){
      perror("Reusing ADDR failed");//option in order to reuse immediately port//
      return 1;}
   while( (retval=bind(sock,(struct sockaddr *)&server,sizeof(server) ))==-1 && errno==EINTR);
   if (retval < 0) {// Bind socket to address //
      perror("bind");
      return 1; }
   if (listen(sock, 5) < 0) { // Set up queue for incoming connections. //
      perror("parent:listen");
      return 1; }
   parent_pid=getpid();

   for(i=0;i<NUMCHILDREN;i++)
      if ((pid_code[i]=pid=fork())<=0) // Create children processes //
         break;

   if ( pid==0 ){//childcode//
      curtime = time(NULL);
      srand((unsigned int) curtime);
      probFail=atof(argv[3]);
      fprintf(stderr,"child:%ld is born and ready\n",(long)getpid());
      act_stop.sa_handler=timeToStop;     //handler for act_stop//
      act_stop.sa_flags=0;
      if ((sigemptyset(&act_stop.sa_mask ) == -1) || (sigaction(SIGUSR1,&act_stop,NULL) == -1 ) ){
         perror("FAIL TO INSTAL  SIGNAL HANDLER FOR SIGUSR1");//install handler for SIGUSR1//
         return 1;}
      if ((sigemptyset(&intmask) == -1) || (sigaddset(&intmask,  SIGPIPE) == -1)){//create signal mask//
         perror("Failed to initialize the signal mask");
         return 1;}
      if (sigprocmask(SIG_BLOCK, &intmask, NULL) == -1){  //ignore the signal of intmask//
         perror("Failed to block SIGPIPE");
         return 1;}
      close(fd[WRITE]);//close unnecessary writing end//
      ready=0; 
      command_count=0;
      while(1){
          srand((unsigned int) curtime);
          bzero(temp,sizeof(temp));
          while( (bytesread=read(fd[READ], temp, sizeof(temp)+1))==-1 && errno==EINTR );
          if (bytesread < 0 ){
             perror("child:read");//read from pipe-parent writter//
             return 1;}
          i=j=0;
          bzero(dgr_port,sizeof(dgr_port));//figure out DGR port//
          do{
            ch=dgr_port[j]=temp[j++];
          }while(ch!='\n');
          port=atoi(dgr_port);
          bzero(name,sizeof(name));//figure oudt client's name//
          i=0;
          do{
            if(temp[j]==' ')
              break;
            name[i++]=temp[j++];
          }while(1);
          i=0;
          j++;
          bzero(command,sizeof(command));//figure out command//
          while(1){
             if (temp[j]=='\0')
                break;
             ch=command[i++]=temp[j++];
          }
          fprintf(stderr,"child:%ld is going to execute command:%s- for client:%s\n",
                   (long)getpid(),command,name);
          server.sin_family = PF_INET; // Internet domain //
          server.sin_port = htons(port); // Server's Internet address and port //
          if ((rem = gethostbyname(name)) == NULL) { // Find client's address //
             perror("child:gethostbyname");
             return 1; }
          if ((dgr_sock = socket(PF_INET, SOCK_DGRAM, 0)) < 0) { // Create socket //
             perror("child:socket");
             return 1; }
          bcopy((char *) rem -> h_addr, (char *) &server.sin_addr,rem -> h_length);
          client.sin_family = PF_INET; // Internet domain //
          client.sin_addr.s_addr = htonl(INADDR_ANY); // My Internet address //
          client.sin_port = htons(0); // Select any port //
          while ( (retval=setsockopt(dgr_sock,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(yes)))==-1 && errno==EINTR );
          if ( (retval)>0){
             perror("Reusing ADDR failed");//option in order to reuse immediately port//
             return 1;}
          while( (retval=bind(dgr_sock,(struct sockaddr *)&client,sizeof(client)))==-1 && errno==EINTR);
          if (retval < 0) {// Bind socket to address //
             perror("bind");
             return 1; }
          ready=1;
          if (strcmp(command,"end ")==0){  //do you catch end?//
             if (sendto(dgr_sock, "all",strlen("all"),0,(struct sockaddr *)&server,sizeof(server)) < 0) {
                perror("3 sendto");
                exit(1); }
             close(fd[READ]);//close your fd'ds//
             close(dgr_sock);
             fprintf(stderr,"child:%ld closing its fd's and killing itself\n",(long)getpid());
             if ( kill(getppid(),SIGUSR2) ||  kill(getpid(),SIGTERM)){//send signal to parent //
                perror("kill");                                     //and then kill yourself//
                return 1;}
             return 0;
          }
          if (strcmp(command,"timeToStop ")==0){//do you catch timeToStop?//
             fprintf(stderr,"time to stop\n");
             if (kill(getppid(),SIGUSR1)){//send signal to parent //
                perror("kill");
                return 1;}
             sleep(1);
             break;//break so as not to execute command TimeToStop which doesn't exist//
          }
          if ( (fp = popen(command, "r"))==NULL ){
             perror("popen:");//open file and execute command//
             return 1;}
          bzero(PID_COMMAND,sizeof(PID_COMMAND));
          sprintf(PID_COMMAND,"%s:%ld:results:\n",command,getpid());//PID:COMMAND//            
          bzero(temp,sizeof(temp));
          j=i=packets=0;
          first=1;
          while((ch= getc(fp)) != EOF ){
             temp[i++]=ch;
             sent_flag=0;
             if ( i==(BUFSIZE-1)){
                if (first && ((float)(rand()%100+1))>(100*probFail)){
                   while ((retval=sendto(dgr_sock,PID_COMMAND,sizeof(PID_COMMAND)+1,0,(struct sockaddr *)&server,sizeof(server)))==-1 
                          && (errno==EINTR));
                   if (retval < 0) {
                      perror("1 sendto");//PID:COMMAND//
                      return 1; } 
                   first=0;
                }
                if (((float)(rand()%100+1))>(100*probFail)){
                   while ((retval=sendto(dgr_sock,temp,sizeof(temp),0,(struct sockaddr *)&server,sizeof(server)))==-1 
                         &&(errno==EINTR));
                   if (retval < 0) {
                      perror("1 sendto"); 
                      return 1; } //RESULTS//
                   packets++;
               }
                bzero(temp,sizeof(temp));
                sent_flag=1;
                i=0;
             }
          }
          if (sent_flag!=1 && ((float)(rand()%100+1))>(100*probFail)){
             if (first && ((float)(rand()%100+1))>(100*probFail)){
                while( (retval=sendto(dgr_sock,PID_COMMAND,sizeof(PID_COMMAND)+1,0,(struct sockaddr *)&server,sizeof(server)))==-1 
                       && (errno==EINTR));//PID:COMMAND//
                   if (retval < 0) {
                      perror("1 sendto");
                      return 1; }
                   first=0;
             }
             while((retval=sendto(dgr_sock,temp,sizeof(temp),0,(struct sockaddr *)&server,sizeof(server)))==-1 &&(errno==EINTR));
             if (retval < 0) {
                perror("2 sendto");
                return 1;} //RESULTS//
             packets++;
          }
          if (((float)(rand()%100+1))>(100*probFail)){
             while ((retval=sendto(dgr_sock,"all",strlen("all"),0,(struct sockaddr *)&server,sizeof(server)))==-1 
                      &&(errno==EINTR));
             if (retval <0) {
                perror("1 sendto");//send phrase for end of packets//
                return 1; } 
          }
          fprintf(stderr,"packets send:%d\n\n",packets);
          close(dgr_sock);
          pclose(fp);
          command_count++;
      }   
   }
   else{//father code//
      printf("big papa is borned and ready with pid:%ld\n",(long)getpid());
      close(fd[READ]);//close unnecessary readind end//
      FD_ZERO (&active_fd_set);
      FD_SET (sock, &active_fd_set);
      if ((sigemptyset(&intmask) == -1) || (sigaddset(&intmask,  SIGPIPE) == -1)){//create signal mask//
         perror("Failed to initialize the signal mask");
         return 1;}
      if (sigprocmask(SIG_BLOCK, &intmask, NULL) == -1){  //ignore the signal of intmask//
         perror("Failed to block SIGPIPE");
          return 1;}
      act_stop.sa_handler=timeToStop;     //TimeToStop handler//
      act_stop.sa_flags=0;
      if ((sigemptyset(&act_stop.sa_mask ) == -1) || (sigaction(SIGUSR1,&act_stop,NULL) == -1 ) ){
         perror("FAIL TO INSTAL  SIGNAL HANDLER FOR SIGUSR1");//install handler for SIGUSR1//
          return 1;}
      sigchild_action.sa_handler = clean_up_children_process;//clean_up_child_process handler//
      sigchild_action.sa_flags=0;
      if ((sigemptyset(&sigchild_action.sa_mask ) == -1) || (sigaction(SIGUSR2,&sigchild_action,NULL) == -1 ) ){
         perror("FAIL TO INSTAL  SIGNAL HANDLER FOR SIGUSR2");//install handler for SIGUSR@//
         return 1;}
      do{
         read_fd_set = active_fd_set;
         while((retval=(select (FD_SETSIZE, &read_fd_set, NULL, NULL, NULL))==-1) && errno==EINTR); 
            if (retval < 0){
               perror ("parent::select");//wait untill one or more fd's become ready//
               return 1;}
         for (i = 0; i < FD_SETSIZE; ++i){//for each fd//
            if (FD_ISSET (i, &read_fd_set) ){//belong to the set?//
               if (i == sock){//we have new request for conection to thr listening sockets//
                  size = sizeof (clientname);
                  clientlen = sizeof client;
                  if ((newsock = accept(sock, (struct sockaddr *)&client, &clientlen)) < 0) {
                     perror("parent:accept");//accept and create active communication endpoint//
                     return 1; }
                  if ((rem = gethostbyaddr((char *) &client.sin_addr.s_addr,sizeof
                             (client.sin_addr.s_addr),client.sin_family)) == NULL){
                     perror("parent:gethostbyaddr");
                     return 1; }
                  fprintf(stderr,"Accepted TCP connection from listening port:%d to newsock:%d from:%s\n",
                        (port),(newsock),(rem -> h_name), client.sin_port);
                  FD_SET (newsock, &active_fd_set);//and to active set//
               }
               else{//we have new data to a connected client//
                  size = sizeof (clientname);
                  clientlen = sizeof client;
                  getpeername(i,(struct sockaddr *) &client,&clientlen);//get client's name connected to sock//
                  if ((rem = gethostbyaddr((char *) &client.sin_addr.s_addr,sizeof
                         (client.sin_addr.s_addr),client.sin_family)) == NULL){
                     perror("parent:gethostbyaddr");
                     return 1;}                 
                  if (read_from_client (i,rem) < 0){//client no more connected//
                     fprintf(stderr,"client:%s is no more connected...i am going to close unused filedescripitor:%d\n",
                         (rem -> h_name),i);
                     close (i);
                     FD_CLR (i, &active_fd_set);}//remove from active set//
               }
            }
        }
      }while(1);
   }
   return 1;
}

int read_from_client (int filedes,struct hostent* rem)
{
   char tosend[256],TEMP[256],TEMP1[256],TEMP2[256],*com1="ls",*com2="tr",*com3="cat",*com4="cut",*com5="grep",*com6="end",*com7="timeToStop";
 
   int bytesread,i,j=0,blank=0,b=0;
   bzero(command,sizeof(command));
   while( (bytesread=read(filedes, command, sizeof(command)+1))==-1 && errno==EINTR );
   if (bytesread < 0){
      perror ("read");//read from socket//
      return -1;}
   else if (bytesread == 0)
      return -1;
   else if(bytesread>0){
      for(i=0;i<256;i++)
         if (command[i]=='\0')
            break;
      if (i==255 ){                 //ignore commands with more than 256 chars//
         fprintf(stderr,"command will be ignored\n");
         if ((write(filedes,"invalid command",strlen("invalid command")+1)) < 0 ) { 
             perror("parent:write");//sent to client flag for invalidcommand//
             return -1;}
         return 0;}
         for(i=0;i<256;i++){
            if(command[i]==' ' && blank==0){           //find the first void and check the command
              blank=1;
              j=0;
              bzero(TEMP1,sizeof(TEMP1));
              for(j=0;j<i;j++)TEMP1[j]=command[j];
              if(strcmp(TEMP1,com1)!=0 && strcmp(TEMP1,com2)!=0 && strcmp(TEMP1,com3)!=0 && strcmp(TEMP1,com4)!=0  
                && strcmp(TEMP1,com5)!=0 &&  strcmp(TEMP1,com6)!=0 &&  strcmp(TEMP1,com7)!=0){
                 j=-1;      //if first command is invalid 
                 break;
                  }
            }
            if(command[i]=='|'){    //if you find a pipeline character
                j=i+2; b=0;
                while(command[j]!=' ' &&  command[j]!='\0'){b++;j++;}
                bzero(TEMP2,sizeof(TEMP2));
                b=0;j=i+2;
                while(command[j]!=' '){TEMP2[b]=command[j]; b++; j++;}    //place the command in TEMP2 and compare for validness
                if(strcmp(TEMP2,com1)!=0 && strcmp(TEMP2,com2)!=0 && strcmp(TEMP2,com3)!=0 && strcmp(TEMP2,com4)!=0 
                   && strcmp(TEMP1,com5)!=0 && strcmp(TEMP1,com6)!=0 && strcmp(TEMP1,com7)!=0 ){
                   bzero(TEMP,sizeof(TEMP));
                   for(j=0;j<i;j++) TEMP[j]=command[j];
                   bzero(command,sizeof(command));
                   for(j=0;j<256;j++) command[j]=TEMP[j];
                   break;
                  }
            }
            if (command[i]==';'){     //if you find a ';' character execute the command until then
               bzero(TEMP,sizeof(TEMP));
               for(j=0;j<i;j++) TEMP[j]=command[j];
               bzero(command,sizeof(command));
               for(j=0;j<256;j++) command[j]=TEMP[j];
                  break;
            }
         }
         if (j==-1) {              // invalid command//
            fprintf(stderr,"command will be ignored\n");
            if ((write(filedes,"invalid command",strlen("invalid command")+1)) < 0 ) {
               perror("parent:write");//sent to client flag for invalidcommand//
               return -1;}
         return 0;}


      
      if ((write(filedes,"dgr_port" ,strlen("dgr_port")+1)) < 0 ) {//sent to client flag for dgr_port//
         perror("parent:write");
         return -1;}
      bzero(dgr_port,sizeof(dgr_port));
      while( (bytesread=read(filedes, dgr_port, sizeof(dgr_port)+1))==-1 && errno==EINTR );
      if (bytesread < 0){//read dgr_port//
         perror("Parent:read");
         return -1;}
      bzero(temp,sizeof(temp));
      strncat(temp,dgr_port,strlen(dgr_port));//child need that information//
      strncat(temp,rem -> h_name,strlen(rem -> h_name));//child need that information as well//
      strncat(temp," ",strlen(rem -> h_name)+1);//seperate information and command with a blank//
      strncat(temp,command,sizeof(command));
      if ((write(fd[WRITE], temp ,sizeof(temp)+1)) < 0 ) {  // writter father //
           perror("write");
           return -1;}
      return 0;
   }
}




void timeToStop()//handler for SIGUSR1//
{
   int i;
   if (getpid()==parent_pid){//parent's handling//
      for(i=0;i<NUMCHILDREN;i++){
         kill((long)pid_code[i],SIGUSR1);//send SIGUSR1 to every child//
         fprintf(stderr,"PARENT with PID:%ld send signal to child:%ld\n",
                (long)getpid(),(long)pid_code[i]);
      }
      while(wait(NULL)>0);//wait all children//
      close(fd[WRITE]);//close your fd's//
      close(newsock);
      close(sock);
      fprintf(stderr,"PARENT with PID:%ld is killing himself\n",(long)getpid());
      kill(getpid(),SIGTERM);//terminate//
   }
   else{//children's handling//
      fprintf(stderr,"CHILD:%ld closing its file descripitors and is dying after executing:%d commands\n",
               (long)getpid(),command_count);
      close(fd[READ]);//close your fd's//
      close(dgr_sock);
      kill(getpid(),SIGTERM);//terminate//
   }
}


void clean_up_children_process ()//clean zombies-defunct//
{
   int status;
   wait (&status);
   printf("i cleaned that zobie\n");
}



