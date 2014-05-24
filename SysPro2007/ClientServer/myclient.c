#include <sys/types.h> /* For sockets */
#include <sys/time.h>
#include <sys/socket.h> /* For sockets */
#include <netinet/in.h> /* For Internet sockets */
#include <netdb.h> /* For gethostbyname */
#include <stdio.h> /* For I/O */
#include <stdlib.h> /* For exit */
#include <string.h> /* For strlen, bzero, bcopy */
#include <errno.h>
#include <signal.h>
#include <unistd.h>
#define  DGR_SIZE 15

int port,dgr_port,doneflag, sock,dgr_sock,bytesread,i,yes=1,retval,wait,packets,recovering;

void myhandler()
{
    fprintf(stderr,"\ni catch alarm,probably some packets have been lost...i am going to ask for new command");
    doneflag=recovering=0;
}

void sigpipehandler()
{
   fprintf(stderr,"i catch sigpipe...server probably crashed...i am going to terminate...\n");
   close(dgr_sock);
   close(sock);
   exit(1);
}
main(int argc, char *argv[]) /* Client with Internet stream sockets */
{ 
   sigset_t intmask;
   char buf[256],str_dgr_port[DGR_SIZE],command[512],ch; 
   unsigned int serverlen,serverlen1,clientlen1;
   struct sockaddr_in server, server2,server1,client1;
   struct sockaddr *serverptr,*serverptr1,*clientptr1;
   struct hostent *rem;
   struct sigaction act,act2;
   struct itimerval old, new,new2,new3;
   
   new.it_interval.tv_usec = 0;
   new.it_interval.tv_sec = 0;
   new.it_value.tv_usec = 0;
   new.it_value.tv_sec = (long int) 20;   

   new2.it_interval.tv_usec = 0;
   new2.it_interval.tv_sec = 0;
   new2.it_value.tv_usec = 0;
   new2.it_value.tv_sec = (long int) 5000;

   new3.it_interval.tv_usec = 0;
   new3.it_interval.tv_sec = 0;
   new3.it_value.tv_usec =800000;
   new3.it_value.tv_sec = (long int) 0;

   act.sa_handler=myhandler;
   act.sa_flags=0;
   
   act2.sa_handler=sigpipehandler;
   act2.sa_flags=0;

   if ((sigemptyset(&act.sa_mask ) == -1) || (sigaction(SIGALRM,&act,NULL) == -1 ) ){
      perror("FAIL TO INSTAL  SIGNAL HANDLER");//instal handler for SIGALRM//
      return 1;}
   if ((sigemptyset(&act2.sa_mask ) == -1) || (sigaction(SIGPIPE,&act2,NULL) == -1 ) ){
      perror("FAIL TO INSTAL  SIGNAL HANDLER");//instal handler for SIGPIPE//
      return 1;}

   if (argc < 4) { /* Are server's host name and port number given? */
      printf("Please give host name and port number and DGR+port number\n");
      exit(1); }
   if ((sock = socket(PF_INET, SOCK_STREAM, 0)) < 0) { /* Create socket for TCP communication*/
      perror("socket"); 
      exit(1); }
   if ((rem = gethostbyname(argv[1])) == NULL) { /* Find server address */
      perror("gethostbyname"); 
      exit(1); }
   port = atoi(argv[2]); 
   server.sin_family = PF_INET; /* Internet domain */
   bcopy((char *) rem -> h_addr, (char *) &server.sin_addr,rem -> h_length);
   server.sin_port = htons(port); /* Server's Internet address and port */
   serverptr = (struct sockaddr *) &server;
   serverlen = sizeof server;
   while(   (retval=connect(sock, serverptr, serverlen)==-1)  && (errno==EINTR) );
   if (retval < 0) { /* Request TCP connection */
      perror("connect"); 
      exit(1); }
   printf("request for TCP connection to:%s and port:%d\nfrom socket:%d binded to port:%d\n",
          (argv[1]),port,sock,server.sin_port);
   while( (retval=getsockname(sock, (struct sockaddr *)&server2, &serverlen))==-1 && (errno==EINTR) );
   if (retval < 0) {
      perror("Getsockname"); 
      exit(1); }
   if ((dgr_sock = socket(PF_INET, SOCK_DGRAM, 0)) < 0) { /* Create socket for UDP communication*/
      perror("socket");
      exit(1); }
   if ((rem = gethostbyname(argv[1])) == NULL) { /* Find server address */
      perror("gethostbyname"); 
      exit(1); }
   dgr_port = atoi(argv[3]);
   server1.sin_family = PF_INET; /* Internet domain */
   bcopy((char *) rem -> h_addr, (char *) &server.sin_addr,rem->h_length);
   server1.sin_port = htons(dgr_port); /* Server's Internet address and port */
   serverptr1 = (struct sockaddr *) &server;
   serverlen1 = sizeof server1;
   client1.sin_family = PF_INET; /* Internet domain */
   client1.sin_addr.s_addr = htonl(INADDR_ANY); /* My Internet address */
   client1.sin_port = htons(dgr_port); /* Select any port */
   clientptr1 = (struct sockaddr *) &client1;
   clientlen1 = sizeof client1;
   while ( (retval=setsockopt(dgr_sock,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(yes)))==-1 && errno==EINTR );
   if ( (retval)>0){
      perror("Reusing ADDR failed");//immideate reuse//
      exit(1);}
   while( (retval=bind(dgr_sock, clientptr1, clientlen1))==-1 && errno==EINTR);
   if (retval < 0) {/* Bind socket to address */
      perror("bind");
      exit(1); }
   while(1) {
      recovering=0;
      bzero(buf, sizeof buf); /* Initialize buffer */
      bzero(command,sizeof(command));
      fprintf(stderr,"\nClient:Give input command:");
      setitimer(ITIMER_REAL ,&new2,&old);  //hold on  5000 sec for user's input//
      fgets(command,sizeof(command),stdin);
      fprintf(stderr,"\n");
      setitimer(ITIMER_REAL ,&new,&old);  //reset and hold on 25 sec for server's responce//
      if ( (command[0]=='/') && (command[1]=='/') ){
         fprintf(stderr,"\nClient:command with comments won't sent to server");
         continue;}
      for (i=0;i<511;i++)
          if (command[i]=='\n'){
             command[i]=' ';
             command[i+1]='\0';
             break;
          }
      if (write(sock, command, sizeof buf)<0){ /* Send command */
         perror("write"); 
         exit(1); }
      bzero(buf, sizeof buf); /* Initialize buffer */
      while( (bytesread=read(sock, buf, sizeof buf))==-1 && errno==EINTR);
      if (bytesread < 0) { /* Receive message */
         perror("read");
         exit(1); }
      if (strcmp(buf,"dgr_port")==0){
         bzero(str_dgr_port,sizeof(str_dgr_port));
         sprintf(str_dgr_port,"%s\n",argv[3]);
         if ((write(sock, str_dgr_port, sizeof(str_dgr_port)+1))< 0) { /* Send message */
            perror("write");
            exit(1); }
      }
      if(strcmp(command,"timeToStop ")==0){//timeToStop???terminate//
         fprintf(stderr,"timeToStop\nClient is going to terminate\n");
//         sleep(2);
         close(dgr_sock);
         close(sock);
         exit(0);
      }
      else if(strcmp(buf,"invalid command")==0){//invalid command?go on with other command//
         fprintf(stderr,"%s\n",buf);
         continue;}
      bzero(buf,sizeof(buf));
      packets=0;
      doneflag=1;
      while(doneflag ){
          bzero(buf,sizeof(buf));  
          while((bytesread = recvfrom(dgr_sock,buf,sizeof(buf), 0,serverptr1,&serverlen1))==-1 && errno==EINTR && bytesread==ETIME);
          if(doneflag==0)break;
          recovering=1;
          setitimer(ITIMER_REAL ,&new3,&old);  // for each packet of results,after receiving the first//
          if (bytesread < 0){                 //if there is no packet for 0.5 sec go on with        // 
            perror("recvfrom error");        //next command                                       // 
            exit(1);}
         if (strcmp(buf,"all")==0){
            if(packets>0)packets--;
            break;}
         fprintf(stderr,"%s",buf);
         packets++;
      }      
      fprintf(stderr,"\ncommand's packets received:%d\n",packets);
      fprintf(stderr,"--------------------------------------------\n");
   }
}

