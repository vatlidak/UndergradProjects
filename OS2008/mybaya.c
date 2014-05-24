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
#include 	"Baya_Lib.h"
#include 	"supportfunct.h"

int main(int argc,char **argv) 
{ 
	int  	fd, i, entries, compress;	/* file descripitor, #entries */
	FILE* 	archieve_fp;			/* file pointer  */
	Treeptr root;				/* root of index */
	Header 	header;				/* struct header */
	tnode	node;				/* struct tnode  */
	
	if ( argc < 3 ){			/* arguments' chech */
		argerror:
		fprintf(stderr,"Usage: %s {-c|-a|-x|-m|-p|-j}   <Archive-file>   <file/directory list>\n",*argv);
		return FAILURE ;
	}
	if ( strcmp(argv[2],"-j") == 0 )	/* compress option. It is a variable   */
		compress=1;			/* used to shift arguments if compress */
	else					/* option is used */
		compress=0;

	if ( (fd = open(argv[2+compress], O_RDWR | O_CREAT , (S_IRUSR | S_IWUSR ))) == -1){	/* open file for reading, writing */
		perror("open..");									/* create if it doesn't exist	  */	
		return FAILURE ;								/* don't truncate if it exists    */
  	}
	if ( (archieve_fp=fdopen(fd,"wb+")) == NULL ){						/* associate with a file pointer  */
		perror("fdopen");
		return FAILURE ;
	}

	if ( strcmp(argv[1],"-c") == 0 ){ 	/* create new archieve */
		rewind(archieve_fp);								/* go to the beginning   */  
		header.offset=(off_t)sizeof(struct Header);					/* inform header struct  */
		header.entries=0;							
		if ( fwrite(&header,sizeof(struct Header),1,archieve_fp)!=1 ){			/* write it down to file */
			perror("write");
			return FAILURE ;
		}
		initialize(&root);								/* initialize root of index */

		for ( i=3+compress; i<argc; i++ )						
			AddToArchieve(archieve_fp,AbsPath(argv[i]),"-f",&root,compress);	/* add all files/directories to archieve */

		rewind(archieve_fp);
		if ( ( fread(&header,sizeof(struct Header),1,archieve_fp)) != 1 ){ /* read from header where data  end */
			perror("fread");
			return FAILURE ;
		}
		fseek(archieve_fp,header.offset,SEEK_SET);			   /* go to the end of real data       */
		entries=0;
		if ( save(&root,archieve_fp,&entries) != SUCCESS ){		   /* save index and count nodes-entries */
			fprintf(stderr,"save FAILURE\n");
			return FAILURE ;
		}
		header.entries=entries;						   /* inform header */
		rewind(archieve_fp);						   /* go to the begining */
		if ( fwrite(&header,sizeof(struct Header),1,archieve_fp)!=1 ){	   /* write it down */
			perror("write");
			return FAILURE ;
		}
	}
	else if ( strcmp(argv[1],"-a") == 0 ){ /* add  to existing archieve */
		rewind(archieve_fp);							/* go to the begining */
		if ( ( fread(&header,sizeof(struct Header),1,archieve_fp)) != 1 ){	/* read header */
			perror("fread");
			return FAILURE ;
		}
		fseek(archieve_fp,header.offset,SEEK_SET);				/* go to the beg of index */
		initialize(&root);							/* load index */ 
		if ( load(archieve_fp,header.entries,&root) != SUCCESS ){
			fprintf(stderr,"load FAILURE\n");
			return FAILURE ;
		}
		AddToArchieve(archieve_fp,AbsPath(argv[3]),NULL,&root,0);			/* add data to the  end of existing real data */
		entries=0;
		rewind(archieve_fp);							/* read header */
		if ( ( fread(&header,sizeof(struct Header),1,archieve_fp)) != 1 ){
			perror("fread");
			return FAILURE ;
		}
		fseek(archieve_fp,header.offset,SEEK_SET);				/* go to the end  of new data */
		if ( save(&root,archieve_fp,&entries) != SUCCESS ){			/* save infrmed index	      */
			fprintf(stderr,"save FAILURE\n");
			return FAILURE ;
		}
		rewind(archieve_fp);
		header.entries=entries;							/* inform header */
		rewind(archieve_fp);
		if ( fwrite(&header,sizeof(struct Header),1,archieve_fp)!=1 ){		/* write it down */
			perror("write");
			return FAILURE ;
		}
	}
	else if ( strcmp(argv[1],"-m") == 0 ){	/* print meta-data */
		rewind(archieve_fp);							/* read header */
		if ( ( fread(&header,sizeof(struct Header),1,archieve_fp)) != 1 ){
			perror("fread");
			return FAILURE ;
		}
		fseek(archieve_fp,header.offset,SEEK_SET);				/* go to the beginning of index */
		initialize(&root);
		if ( load(archieve_fp,header.entries,&root) != SUCCESS ){		/* load it */
			fprintf(stderr,"load FAILURE\n");
			return FAILURE ;
		}
		print(&root,1);								/* print hierarchy WITH meta-data */ 
	}
	else if ( strcmp(argv[1],"-p") == 0 ){ /* print hierarchy */
		rewind(archieve_fp);							/* read header */
		if ( ( fread(&header,sizeof(struct Header),1,archieve_fp)) != 1 ){
			perror("fread");
			return FAILURE ;
		}
		fseek(archieve_fp,header.offset,SEEK_SET);				/* go to the beginning of index */
		initialize(&root);
		if ( load(archieve_fp,header.entries,&root) != SUCCESS ){		/* load it */
			fprintf(stderr,"load FAILURE\n");
			return FAILURE ;
		}
		print(&root,2);								/* print hierarchy */ 
	}
	else if ( strcmp(argv[1],"-x") == 0 ){ /* extract */
		rewind(archieve_fp);							/* go to the begining */
		if ( ( fread(&header,sizeof(struct Header),1,archieve_fp)) != 1 ){	/* read header */
			perror("fread");
			return FAILURE ;
		}
		fseek(archieve_fp,header.offset,SEEK_SET);				/* go to the beg of index */
		initialize(&root);
		if ( load(archieve_fp,header.entries,&root) != SUCCESS ){		/* load it */
			fprintf(stderr,"load FAILURE\n");
			return FAILURE ;
		}
		if ( argc == 3 )							/* if there is no file/directory list */
			ExtrAll(archieve_fp,&root);
		else		
			for ( i=3; i<argc; i++ )					/* from the list given as command line argument */
				ExtrFromArchieve(archieve_fp, argv[i], &root);
	}
	else 
		goto argerror;

	fclose(archieve_fp);	/* close file pointer */
	close(fd);		/* close file descripitor */
	release(root);
	return SUCCESS;
}
