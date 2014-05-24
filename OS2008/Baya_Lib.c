/* ATLIDAKIS VANGELIS 		*/
/* 1115 2005 00010    		*/
/* EXERCISE-4 OPERATING SYSTEMS */
#include 	<stdio.h>
#include 	<stdlib.h>
#include 	<string.h>
#include 	<sys/stat.h>
#include 	<dirent.h>
#include 	<fcntl.h>
#include 	<unistd.h>
#include 	<errno.h>
#include 	<pwd.h>
#include 	<grp.h>
#include 	<time.h>
#include 	"Baya_Lib.h"
#include 	"supportfunct.h"

char 	*modes[] = {"---", "--x", "-w-", "-wx", "r--", "r-x", "rw-", "rwx"}, delims[] = "/";

void AddToArchieve(FILE* archieve_fp, char* dirname, char* arg, Treeptr* root, int compress) /* recursive function looping through directory entries */
{											     /* and calling attach if entry is regular file */	
	char 	newname[256];
	DIR 	*dir;
	struct 	dirent  *dp;
	struct 	stat     statbuf;
	tnode 	node;

	if ( (dir=opendir(dirname)) == NULL  &&  errno != ENOTDIR ){
        	perror ("Cannot open directory");
       		return;
    	}
	else if ( dir ==  NULL && errno == ENOTDIR )
	{	
		if (stat(AbsPath(dirname), &statbuf) == -1){						/* Get entry's information. */
	        		perror ("stat");
	       			return;
	    	}
		if ( attach_regfile(archieve_fp, AbsPath(dirname), root,  arg, compress) != SUCCESS ){
			fprintf(stderr,"attaching file:%s FAILURE\n",newname);
			return;	
		}
	}
	else 
	{
		while ((dp = readdir(dir)) != NULL) 							/* Loop through directory entries. */
		{ 	
			if ( strcmp(dp->d_name,".") == 0 || strcmp(dp->d_name,"..") == 0  )
				continue;
			bzero(newname,NAMESIZE);
			strcpy(newname,dirname);
			strcat(newname,"/");
			strcat(newname,dp->d_name);
			if (stat(newname, &statbuf) == -1){						/* Get entry's information. */
	        		perror ("stat");
	       			return;
		    	}
			if ( (statbuf.st_mode & S_IFMT) == S_IFREG ){
				if ( attach_regfile(archieve_fp, newname, root, arg, compress) != SUCCESS ){	/* attach it */
					fprintf(stderr,"attaching regfile:%s FAILURE\n",newname);
					return;	
				}
			}
			else if ( (statbuf.st_mode & S_IFMT) == S_IFDIR ){
				strcpy(node.abspath,AbsPath(newname));
				strcpy(node.name,newname);
				node.kidsno=node.blocks=node.begoff=node.datasize=0;
				if ( insert(root, node) != SUCCESS ){						/* insert into index */
					fprintf(stderr,"Insertion of node:%s FAILURE\n",AbsPath(newname));
					continue;	
				}
				AddToArchieve(archieve_fp,newname, arg, root, compress);			/*if Dir, recursion */
			}
		}
		closedir(dir);
	}
	return;
}


int attach_regfile(FILE* archieve_fp, char* name, Treeptr* root, char* arg, int compress) /* function attaching reg files, informing index & header */
{
	int 	blocks;
	size_t  n;
	char 	*buf, newname[NAMESIZE];
	tnode	node;
	FILE	*fp;
	pid_t 	pid;
	Header 	header;


	bzero(newname,NAMESIZE);
	strcpy(newname,name);
	if ( (buf=calloc(BLKSIZE,sizeof(char))) == NULL ){
		perror("calloc");
		return FAILURE;
	}
	if ( compress ){
		if ( copyfile(AbsPath(newname)) ){					/* copy file if before compression */
			fprintf(stderr,"Copy of file:%s FAILED\n",AbsPath(newname));	/* because initial file is removed */
			return EXIT_FAILURE;						/* after compression */
		}
		if ( (pid=fork()) == -1 ){
			perror("fork"); 
			return FAILURE ;
		}
		else if ( pid == 0 )
			execlp("./compress","./compress",arg,AbsPath(newname),NULL);
		while( r_wait(NULL) > 0 );  						/* r_wait for all of your children   */
			if ( strcmp(arg,"-f") == 0 )
				strcat(newname,".Z");
		
	}
	rewind(archieve_fp);
	if ( ( fread(&header,sizeof(struct Header),1,archieve_fp)) != 1 ){ /* get header's info */
		perror("fread");
		return FAILURE ;
	}
	fseek(archieve_fp,header.offset,SEEK_SET);		
	strcpy(node.abspath,AbsPath(newname));		/* inform node for index */
	strcpy(node.name,newname);			/* inform node for index */
	node.kidsno=0;					/* inform node for index */
	node.begoff=ftell(archieve_fp);			/* inform node for index */
	if ( (fp=fopen(newname,"rb+")) == NULL ){
		perror("open");
		return FAILURE ;
	}
	rewind(fp);
	bzero(buf,BLKSIZE);
	blocks=0;
	while( (n=fread(buf,sizeof(char),BLKSIZE,fp)) > 0 ){			/* copy file into archieve */
		if ( ( fwrite(buf,sizeof(char),n,archieve_fp)) != n ){
			perror("fwrite");
			return FAILURE ;
		}
		++blocks;
		bzero(buf,BLKSIZE);
	}
	fclose(fp);
	free(buf);		
	node.datasize=ftell(archieve_fp)-node.begoff;	/* inform node for index */
	node.blocks=blocks;				/* inform node for index */
	if ( insert(root, node) != SUCCESS ){		/* insert into index     */
		fprintf(stderr,"Insertion of node:%s FAILED\n",AbsPath(newname));
		return FAILURE ;	
	}
	header.offset=ftell(archieve_fp);
	rewind(archieve_fp);
	if ( fwrite(&header,sizeof(struct Header),1,archieve_fp)!=1 ){	/* inform header */
		perror("write");
		return FAILURE ;
	}
	if ( compress )			/* remove compressed file  from working directory after being attached */
		remove(newname); 
	return SUCCESS;
}

int ExtrAll(FILE* archieve_fp,Treeptr* p)
{
	int i;
  	if ( *p != NULL ){
		if ( (*p)->type == '-' )
			ExtrFromArchieve(archieve_fp,(*p)->abspath,p);		
  		for (i=0;  i < (*p)->kidsno ; i++ )
        		ExtrAll(archieve_fp, &(*p)->kids[i]);
	}

}

int ExtrFromArchieve(FILE* archieve_fp, char* filename, Treeptr* root) /* recursive function looping through archive's entries */
{									/* and calling detach, if entry is reg. file */
	char 	**tok, *buf, path[NAMESIZE];
	int 	i, j;
	Treeptr	temp;
	
//printf("extract for:%s\n",filename);
	if  ( (temp=search(root,AbsPath(filename))) == NULL ){				/* search index for the file that u want to extract */
		fprintf(stderr,"file:%s does not exist in archieve\n",filename);
		return FAILURE;
	}
	if ( (tok=calloc(1,sizeof(char**))) == NULL || (buf=calloc(BLKSIZE,sizeof(char)))==NULL ||(tok[i=0]=calloc(1,sizeof(char*))) == NULL ){
		perror("calloc");
		return FAILURE;
	}
	strcpy(buf,temp->abspath);
	tok[i] = strtok(buf,delims);	/* parse hierarchy of folders before currect file */
	while( tok[i] != NULL ){		
		if ( (tok=realloc(tok,(i+2)*sizeof(char *))) == NULL ){
			perror("realloc");
			return FAILURE;
		}	 
		tok[++i] = strtok(0,delims);
	}
	bzero(path,NAMESIZE);
	strcpy(path,"/");
	for( j=0; j<i; j++ ){		/* create hierarchy of folders before current file */
		if ( mkdir(path, WRITE_PERMS | S_IXUSR ) == FAILURE  &&  errno!=EEXIST ){
			fprintf(stderr,"creating directory:%s FAILURE\n",path);
			return FAILURE;
		}
		if ( j ) strcat(path,"/");
		strcat(path,tok[j]);
	}
	for ( j=0; j<i; j++ ){
		tok[j]=NULL;
		free(tok[j]);
	}
	tok=NULL; free(tok); free(buf);
	if ( temp->type == 'd' )
		for ( i=0;  i<temp->kidsno; i++)
			ExtrFromArchieve(archieve_fp, temp->kids[i]->abspath, root); /* if Dir, recursion */
	else if ( temp->type == '-' )
		detach_regfile(archieve_fp, temp);				     /* else detach it    */
}

int 	detach_regfile(FILE* archieve_fp, Treeptr temp)	/* function detaching reg files, informing index & header */
{
	int 	i, n,  CurBlockSize;
	char 	*buf;	
	pid_t 	pid;
	FILE*	fp;
	
	if ( (fp=fopen(temp->abspath,"wb+")) == NULL ){
		perror("fopen");
		return FAILURE;
	}
	if ( (buf=calloc(BLKSIZE,sizeof(char))) == NULL ){
		perror("calloc");
		return FAILURE;
	}
	fseek(archieve_fp,temp->begoff,SEEK_SET);			/* set offset to the point beginning real data of current file */
	for ( i=0; i < temp->blocks; i++ ){			
		if ( i == temp->blocks-1 )
			 CurBlockSize=temp->datasize-(long)i*BLKSIZE;
		else
			 CurBlockSize=BLKSIZE;
		bzero(buf,BLKSIZE);
		if ( (n=fread(buf,sizeof(char),CurBlockSize,archieve_fp)) < 0 ){	/* read from input-archieve */
			perror("fread");
			return FAILURE;
		}
		if ( ( fwrite(buf,sizeof(char),n,fp)) != n ){				/* write to output-destination file */
			perror("fwrite");
			return FAILURE ;
		}
	}
	free(buf);
	fclose(fp);
	if ( is_compressed(temp->abspath) ){	/* decompress file, if in compressed mode */
		if ( (pid=fork()) == -1 ){
			perror("fork"); 
			return FAILURE ;
		}
		else if ( pid == 0 )
			execlp("./compress","./compress","-d",AbsPath(temp->abspath),(char*)0);
		while( r_wait(NULL) > 0 );  					/* r_wait for all of your children   */
	}
	return SUCCESS;
}



int insert(Treeptr *root, tnode node) /* insert node into tree index */
{
	int	i, k, j;
	char	**tok, buf[NAMESIZE], abspath1[NAMESIZE], delims[] = "/";
	Treeptr temp, ttemp,tttemp;
 	struct 	group 	*grp;
	struct 	passwd 	*pwd;
	struct 	stat	statbuf;

 	if ( (temp=calloc(1,sizeof(tnode)))==NULL || (temp->kids=calloc(1,sizeof(Treeptr*)))==NULL ){
	        perror("calloc");
	        return FAILURE ;
	}
	bzero(buf,NAMESIZE);
	bzero(abspath1,NAMESIZE);
	strcpy(buf,node.abspath);
        if ( (tok=calloc(1,sizeof(char**))) == NULL || (tok[i=0]=calloc(1,sizeof(char*))) == NULL ){
		perror("calloc");
		return FAILURE;
	}
	tok[i] = strtok(buf,delims); 	/* parse hierarchy */ 
	while( tok[i] != NULL ){
		if ( (tok=realloc(tok,(i+2)*sizeof(char *))) == NULL ){
			perror("realloc");
			return FAILURE;
		}	 
		tok[++i] = strtok(0,delims);
	}
	tttemp=*root;
	i=0;
  	while( tok[i] != NULL  ){      /* create respective hierarchy into index */
		strcat(abspath1,"/");
		strcat(abspath1,tok[i]);
		if ( (temp=search(&tttemp, abspath1)) != NULL ){  /* insert nodes that don't exist */
			tttemp=temp;				  /* else continue */
			i++;
			continue;
		}
		if ( i == 0 )	temp=search(root,ret_par(abspath1));
		else 		temp=search(&tttemp,ret_par(abspath1)); 
		ttemp=calloc(1,sizeof(tnode));
		ttemp->kids=calloc(1,sizeof(Treeptr *));
		ttemp->kidsno=0;
		temp->kids=realloc(temp->kids,(temp->kidsno+2)*sizeof(Treeptr));
		strcpy(ttemp->name,tok[i]);	
		strcpy(ttemp->abspath,abspath1);
		if (stat(AbsPath(ttemp->abspath), &statbuf) == -1){				/* Get entry's information. */
	        		perror ("stat");
	       			return FAILURE ;
		}
	   	if 	( ( statbuf.st_mode & S_IFMT ) ==   S_IFREG ) 	ttemp->type = '-'; 	/* code of SysPro-2008 */
   		else if ( ( statbuf.st_mode & S_IFMT ) ==   S_IFDIR ) 	ttemp->type = 'd';      /* code of SysPro-2008 */
   		else							ttemp->type = '?'; 	/* code of SysPro-2008 */
		*ttemp->perms = '\0';								/* code of SysPro-2008 */
   		for (k=2 ; k >= 0 ; k--){     							/* code of SysPro-2008 */
     			j = (statbuf.st_mode >> (k*3)) & 07;					/* code of SysPro-2008 */
      			strcat(ttemp->perms, modes[j]); 					/* code of SysPro-2008 */
		}
		if ((pwd = getpwuid(statbuf.st_uid)) != NULL)
	    		sprintf(ttemp->owner," %s", pwd->pw_name);
		if ((grp = getgrgid(statbuf.st_gid)) != NULL)
	    		sprintf(ttemp->group," %s", grp->gr_name);
				strcpy(ttemp->time,ctime(&statbuf.st_mtime)+4);
		ttemp->h_links=(long)statbuf.st_nlink;
		ttemp->ino=(long)statbuf.st_ino;
		if ( ttemp->type == 'd' ){
			ttemp->blocks=0;
			ttemp->begoff=0;
			ttemp->datasize=0;	
		}
		else{
			ttemp->blocks=node.blocks;
			ttemp->begoff=node.begoff;
			ttemp->datasize=node.datasize;
		}
		temp->kids[temp->kidsno]=ttemp;
		temp->kidsno++;	
		i++;
		tttemp=temp;
	}
	for ( j=0; j<i; j++ ){
		tok[j]=NULL;
		free(tok[j]);
	}
	tok=NULL; free(tok);
  	return SUCCESS;
}

void release(Treeptr temp)  /* function releasing tree-index kept in m.memory, after it has been writen into archieve */
{
	int i;

	for ( i=0; i<temp->kidsno; i++){
		release(temp->kids[i]);
		temp->kids[i]=NULL;
		free(temp->kids[i]);
	}
	temp->kids=NULL;
	free(temp->kids);
	free(temp);
}


int save(Treeptr *p,FILE* fp, int *entries){	/* function saving index to the end of archieve file */
	int i;
  	if ( *p != NULL ){
  		if  ( fwrite((*p),sizeof(struct tnode),1,fp) < 0 )
			return -1;
		else
			(*entries)+=1;
		for ( i=0; i< (*p)->kidsno && (*p)->kids[i]!=NULL; i++ )
        		save(&(*p)->kids[i],fp,entries); 
	}
	return SUCCESS;
}


int load(FILE* fp,int entries, Treeptr *root)   /* function loading index from archive file */
{
	int	i, j, e;
	char	**tok, buf[NAMESIZE], abspath1[NAMESIZE];
	Treeptr temp, ttemp,tttemp;
	tnode node;

	for ( e=0;  e < entries ; e++ ){				/* for all entries-nodes */
		if  ( fread(&node,sizeof(struct tnode),1,fp) < 0 )
			return FAILURE ;
	 	if ( (temp=calloc(1,sizeof(tnode)))==NULL || (temp->kids=calloc(1,sizeof(Treeptr*)))==NULL ){
		        perror("calloc");
		        return FAILURE ;
		}
		bzero(buf,NAMESIZE);
		bzero(abspath1,NAMESIZE);
		strcpy(buf,node.abspath);
        	if ( (tok=calloc(1,sizeof(char**))) == NULL || (tok[i=0]=calloc(1,sizeof(char*))) == NULL ){
			perror("calloc");
			return FAILURE;
		}
		tok[i] = strtok(buf,delims); 	/* parse hierarchy */
		while( tok[i] != NULL ){
			if ( (tok=realloc(tok,(i+2)*sizeof(char *))) == NULL ){
				perror("realloc");
				return FAILURE;
			}	 
			tok[++i] = strtok(0,delims);
		}
		tttemp=*root;
		i=0;
  		while( tok[i] != NULL  ){		/* insert nodes into index with the respective info */
			strcat(abspath1,"/");
			strcat(abspath1,tok[i]);
			if ( (temp=search(&tttemp, abspath1)) != NULL ){
				tttemp=temp;
				i++;
				continue;
			}
			if ( i == 0 )	temp=search(root,ret_par(abspath1));
			else 		temp=search(&tttemp,ret_par(abspath1)); 
			ttemp=calloc(1,sizeof(tnode));
			ttemp->kids=calloc(1,sizeof(Treeptr *));
			ttemp->kidsno=0;
			temp->kids=realloc(temp->kids,(temp->kidsno+2)*sizeof(Treeptr));
			strcpy(ttemp->name,tok[i]);	
			strcpy(ttemp->abspath,temp->abspath);
			*ttemp->perms = '\0';								
			ttemp->type=node.type;
    			strcpy(ttemp->perms, node.perms); 					
		    	strcpy(ttemp->owner,node.owner);
	    		strcpy(ttemp->group,node.group);
			strcpy(ttemp->time,node.time);
			ttemp->h_links=node.h_links;
			ttemp->ino=node.ino;
			ttemp->blocks=node.blocks;
			ttemp->begoff=node.begoff;
			ttemp->datasize=node.datasize;	
			if ( i != 0 ) 
				strcat(ttemp->abspath,"/");   
			strcat(ttemp->abspath,ttemp->name);
			temp->kids[temp->kidsno]=ttemp;
			temp->kidsno++;	
			i++;
			tttemp=temp;
		}
		for ( j=0; j<i; j++ ){
			tok[j]=NULL;
			free(tok[j]);
		}
		tok=NULL; free(tok);
	}
	return SUCCESS;
}

void initialize(Treeptr *root) /* function initializing root of tree index */
{
	int 	i, j; 
	Treeptr temp;
	struct 	group 	*grp;
	struct 	passwd 	*pwd;
	struct 	stat	statbuf;


	temp=calloc(1,sizeof(tnode));
	temp->kids=calloc(1,sizeof(Treeptr *));

	if (stat("/", &statbuf) == -1){				/* Get entry's information. */
	        perror ("stat");
	       	return;
	}
	if ((pwd = getpwuid(statbuf.st_uid)) != NULL)		/* owner */	
		sprintf(temp->owner," %s", pwd->pw_name);	
	if ((grp = getgrgid(statbuf.st_gid)) != NULL)		/* group */
	 	sprintf(temp->group," %s", grp->gr_name);
	strcpy(temp->time,ctime(&statbuf.st_mtime)+4);		/* time of last modification */

   	if 	( (statbuf.st_mode & S_IFMT ) == S_IFREG) 	temp->type = '-'; 
	else if ( ( statbuf.st_mode & S_IFMT ) ==  S_IFDIR ) 	temp->type = 'd';                      
	else							temp->type = '?'; 

	*temp->perms = '\0';					/* permissions */
   	for (i=2 ; i >= 0 ; i--) {     
     		j = (statbuf.st_mode >> (i*3)) & 07;
      		strcat(temp->perms, modes[j]); 
	}

	temp->h_links=(long)statbuf.st_nlink;	/* number of hard links */
	temp->ino=(long)statbuf.st_ino;		/* number of respective i-node */
	temp->kidsno=0;				/* number of files/diretories under that entry */
	temp->blocks=0;				/* number of blocks into the archive file */
	temp->datasize=0;			/* datasize */
	temp->begoff=sizeof(struct Header);	/* beginning offset for the data */
	strcpy(temp->name,"/");			/* name */
	strcpy(temp->abspath,"/");		/* abspath */
	*root=temp;
}


Treeptr search(Treeptr *p,char* arg) /* search tree for node whose entry has particular attribute */
{
  int i;
  Treeptr temp=NULL;	/* NULL doesn't exist */
  if ( *p !=NULL ){  
	if ( strcmp((*p)->abspath,arg) == 0 )
		return *p;
	for ( i=0; i<(*p)->kidsno; i++ )
		if ( (temp=search(&((*p)->kids[i]),arg)) != NULL )
			break;
  }
  return temp;
}

void print(Treeptr* p,int mode){
	int i;
  	if ( *p != NULL ){
		if ( mode == 1 ) /* printf meta-data */
			fprintf(stderr,"%c%s%5d%10ld%10s /%-10s  %-3d %-7ld %.12s %-15s %s\n"
				,(*p)->type,(*p)->perms,(*p)->h_links,(*p)->ino,(*p)->owner,(*p)->group
						,(*p)->blocks,(*p)->datasize,(*p)->time,(*p)->name,(*p)->abspath);
		else if ( mode == 2 ) /* printt only hierarchy */
			fprintf(stderr,"%s\n",(*p)->abspath);
  		for (i=0;  i < (*p)->kidsno ; i++ )
        		print(&((*p)->kids[i]),mode); 
	}
}

int copyfile(char* name1) 	/* function coping a file but not if a copy exists */
{
   char buf[BLKSIZE], name2[256] ; 
   int 	bytesread, byteswritten;
   int 	fromfd, tofd;
 
   sprintf(name2,"%s.copy",name1);
   if ((fromfd = open(name1, READ_FLAGS)) == -1 || (tofd = open(name2, WRITE_FLAGS, WRITE_PERMS)) == -1) {
	perror("open");
	return FAILURE;
   }
   for (  ;  ;  ){
      if ((bytesread = read(fromfd, buf, BLKSIZE)) <= 0)
         break;     
      if ((byteswritten = write(tofd, buf, bytesread)) == -1)
         break;
   }
   return SUCCESS;
}
