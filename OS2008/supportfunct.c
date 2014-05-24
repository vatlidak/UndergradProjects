/* ATLIDAKIS VANGELIS 		*/
/* 1115 2005 00010    		*/
/* EXERCISE-4 OPERATING SYSTEMS */
#include 	<stdio.h>
#include 	<stdlib.h>
#include 	<string.h>
#include 	<sys/stat.h>
#include 	<fcntl.h>
#include 	<unistd.h>
#include 	<errno.h>
#include 	<pwd.h>
#include 	"supportfunct.h"

char* ret_par(char* abspath)		/* function taking absolute path of a file and returning absolute path  of parent */ 
{
	int 	i, j;
	char 	**tok,*buf1, *buf2, delims[] = "/";

	if ( (buf1=calloc(NAMESIZE,sizeof(char)))==NULL || (buf2=calloc(NAMESIZE,sizeof(char)))==NULL){
		perror("calloc");
		return NULL;
	}
	strcpy(buf1,abspath);
	bzero(buf2,NAMESIZE);
	if ( (tok=calloc(1,sizeof(char**))) == NULL || (tok[i=0]=calloc(1,sizeof(char*))) == NULL ){
		perror("calloc");
		return NULL;
	}
	tok[i] = strtok(buf1,delims);
	while( tok[i] != NULL  ){
		tok[++i] = strtok(0,delims);
		if ( (tok=realloc(tok,(i+2)*sizeof(char*))) == NULL ){
			perror("realloc");
			return NULL;
		}
	}
	if ( i == 1 )
		strcpy(buf2,"/");
	else
		strncpy(buf2,abspath,(strlen(abspath)-strlen(tok[i-1])-1));
	for ( j=0; j<i; j++ ){
		tok[j]=NULL;
		free(tok[j]);
	}
	tok=NULL;
	free(tok);
	return buf2;

}

char* AbsPath(char* name){	/* function converting relative into absolute path */
	char 	*cwd, *pcwd;
	struct 	passwd  *pwd=getpwuid(getuid());

	if ( (cwd=calloc(NAMESIZE,sizeof(char))) == NULL || (pcwd=calloc(NAMESIZE,sizeof(char))) == NULL){
		perror("calloc");
		return NULL;}
	if ( name[0] == '.'  ){
		if ( getcwd(cwd,NAMESIZE) == NULL ){
			perror("getcwd");
			return NULL;}
		if 	( name[1] == '.' && name[2] == '/' ){name+=2; strcpy(pcwd,ret_par(cwd));strcat(pcwd,name); printf("\n%s\n",pcwd); return pcwd;}	
		else if ( name[1] == '/' )		    {name++;	 strcat(cwd,name); return cwd;}
		else 					    {return   name;}
	}
	else if ( name[0] == '~' ){
		sprintf(cwd,"/home/%s/%s",pwd->pw_name,++name);
		return cwd;
	}		
	return name;
}

pid_t r_wait(int *stat_loc){/* wait function , which restart is suspended from signal */
   pid_t retval;
   while (((retval = wait(stat_loc)) == -1) && (errno == EINTR));
   return retval;
}

int is_compressed( char* p){	/* function checking if a filename respond to a compressed file */
	int i=strlen(p);
	return 	(p[i-2]=='.'  && p[i-1]=='Z' )?1:0;
}
