#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "types.h"
#include "list.h"

int GetType(char *Block,FILE *fp)
{
	char type[30];
	sscanf(Block,"MessageType: %s\r\n",type);
	fprintf(fp,"message received:%s\n",type);
	if ( !strcmp(type,"JoinRequest") )
		return JOINREQUEST;
	else if ( !strcmp(type,"JoinResponse"))
		return JOINRESPONSE;
	else if (!strcmp(type,"AskFileList"))
		return ASKFILELIST;
	else if ( !strcmp(type,"FileList"))
		return FILELIST;
	else if ( !strcmp(type,"AskFile"))
		return ASKFILE;
	else if (!strcmp(type,"AskFileResponse") )
		return ASKFILERESPONSE;
	else if (!strcmp(type,"GetFile"))
		return GETFILE;
	else if (!strcmp(type,"GetFileResponse"))
		return GETFILERESPONSE;
	else if (!strcmp(type,"SendFile"))
		return SENDFILE;
	else if (!strcmp(type,"SendFileResponse"))
		return SENDFILERESPONSE;
	else if (!strcmp(type,"DeleteFile"))
		return DELETEFILE;
	else if (!strcmp(type,"DeleteFileResponse"))
		return DELETEFILERESPONSE;
	else
		return ERROR;
		
}

void JoinRequest(char *Block,char* ip,char* port)
{
	int offset=0;
	//create header//
	sprintf(Block,"MessageType: JoinRequest\r\n");
	offset+=strlen("MessageType:")+1+strlen("JoinRequest")+2;
	sprintf(Block+offset,"IP: %s\r\n",ip);
	offset=offset+strlen("IP:")+1+strlen(ip)+2;
	sprintf(Block+offset,"Port: %s\r\n",port);
	offset=offset+strlen("Port:")+1+strlen(port)+2;
	sprintf(Block+offset,"\r\n");

}
		
void JoinResponse(char* Block)
{
	int offset=0;
	//create header//
	sprintf(Block,"MessageType: JoinResponse\r\n");
	offset+=strlen("MessageType:")+1+strlen("JoinResponse")+2;
	sprintf(Block+offset,"\r\n");

}

void AskFileList(char* Block)
{
	int offset=0;
	//create header//
	sprintf(Block,"MessageType: AskFileList\r\n");
	offset+=strlen("MessageType:")+1+strlen("AskFileList")+2;
	sprintf(Block+offset,"\r\n");
}

void FileList(char* Block,fileptr metadata)
{
	
	int offset=0;
	//create header//
	sprintf(Block,"MessageType: FileList\r\n");
	offset+=strlen("MessageType:")+1+strlen("FileList")+2;
	sprintf(Block+offset,"\r\n");
	offset+=2;	
	while ( metadata != NULL )
	{
		sprintf(Block+offset,"%s %s\r\n",metadata->filename, metadata->md5);
		offset+=strlen(metadata->filename)+1+strlen(metadata->md5)+2;
		metadata=metadata->next;
	}
	sprintf(Block+offset,"\r\n");
}


void AskFile(char* Block,char* filename)
{
	int offset=0;
	//create header//
	sprintf(Block,"MessageType: AskFile\r\n");
	offset+=strlen("MessageType:")+1+strlen("AskFileList")+2;
	sprintf(Block+offset,"FileName: %s\r\n",filename);
	offset=offset+strlen("FileName:")+1+strlen(filename)+2;
	sprintf(Block+offset,"\r\n");
}

void AskFileResponse(char* Block,char* filename,char* ip,char* port)
{
		int offset=0;
		//create header//
		sprintf(Block,"MessageType: AskFileResponse\r\n");
		offset+=strlen("MessageType:")+1+strlen("AskFileResponse")+2;
		sprintf(Block+offset,"FileName: %s\r\n",filename);
		offset=offset+strlen("FileName:")+1+strlen(filename)+2;
		sprintf(Block+offset,"IP: %s\r\n",ip);
		offset=offset+strlen("IP:")+1+strlen(ip)+2;
		sprintf(Block+offset,"Port: %s\r\n",port);
		offset=offset+strlen("Port:")+1+strlen(port)+2;
		sprintf(Block+offset,"\r\n");

}

void GetFile(char* Block,char* filename,char* md5sum)
{
	int offset=0;
	//create header//
	sprintf(Block,"MessageType: GetFile\r\n");
	offset+=strlen("MessageType:")+1+strlen("GetFile")+2;
	sprintf(Block+offset,"FileName: %s\r\n",filename);
	offset=offset+strlen("FileName:")+1+strlen(filename)+2;
	sprintf(Block+offset,"File-md5sum: %s\r\n",md5sum);
	offset=offset+strlen("File-md5sum:")+1+strlen(md5sum)+2;
	sprintf(Block+offset,"\r\n");
	

}

void SendFile(int socket,char* filename,char* md5sum)
{
	int offset=0;
	int rval;
	size_t readbytes=0;
	long totalbytes;
	char buffer[BUFSIZE];
	char block[CHUNKSIZE];
	char size[10];
	FILE *fp;
	struct stat buf;
	long st_size;
	//create header//
	
	if ( (fp = fopen(filename,"rb")) == NULL )
	{
		perror("fopen");
	}
	if ( (rval=stat(filename, &buf)) == -1 )
	{
		perror("stat");
	}
	st_size=buf.st_size;
	sprintf(size,"%ld",st_size);
	sprintf(buffer,"MessageType: SendFile\r\n");
	offset+=strlen("MessageType:")+1+strlen("SendFile")+2;
	sprintf(buffer+offset,"FileName: %s\r\n",filename);
	offset=offset+strlen("FileName:")+1+strlen(filename)+2;
	sprintf(buffer+offset,"File-md5sum: %s\r\n",md5sum);
	offset=offset+strlen("File-md5sum:")+1+strlen(md5sum)+2;
	sprintf(buffer+offset,"FileSizeInBytes: %s\r\n",size);	
	offset=offset+strlen("FileSizeInBytes:")+1+strlen(size)+2;
	sprintf(buffer+offset,"\r\n");
	offset+=2;

	//ta dedomena tou arxeiou xwrane sto idio munima me to header
	if ( st_size < BUFSIZE-offset)
	{
		if ( fread(buffer+offset,1,st_size,fp) != st_size )
		{
			perror("fread");
			return;
		}
		printf("here\n");
		if(mywrite(socket,buffer,BUFSIZE) <= 0 )
		{
			perror("mywrite");
			return;
		}
	}
	//to arxeio einai megalutero-stelnw osa xwrane se auto to minima kai to upoloipo to spaw se paketa twn 4kb 
	//kai ta stelnw ena ena
	else
	{
		readbytes=fread(buffer+offset,sizeof(char),BUFSIZE-offset,fp);		
		if(mywrite(socket,buffer,BUFSIZE) <= 0 )
		{
			perror("write");
			return;
		}
		totalbytes=readbytes;
		while( totalbytes < st_size)
		{
			readbytes=fread(block,sizeof(char),CHUNKSIZE,fp);
			totalbytes+=readbytes;
			if(mywrite(socket,block,CHUNKSIZE) <= 0 )
			{
				perror("write");
				return;
			}
		}
	}
	fclose(fp);
}


void GetFileResponse(int socket,char* filename,char* md5sum)
{
	int offset=0;
	int rval;
	size_t readbytes=0;
	long totalbytes;
	char buffer[BUFSIZE];
	char block[CHUNKSIZE];
	char size[10];
	FILE *fp;
	struct stat buf;
	long st_size;
	//create header//
	
	if ( (fp = fopen(filename,"rb")) == NULL )
	{
		perror("ffopen");
	}
	if ( (rval=stat(filename, &buf)) == -1 )
	{
		perror("stat");
	}
	st_size=buf.st_size;
	sprintf(size,"%ld",st_size);
	sprintf(buffer,"MessageType: GetFileResponse\r\n");
	offset+=strlen("MessageType:")+1+strlen("GetFileResponse")+2;
	sprintf(buffer+offset,"ResponseStatus: FileFound\r\n");
	offset+=strlen("ResponseStatus:")+1+strlen("FileFound")+2;
	sprintf(buffer+offset,"FileName: %s\r\n",filename);
	offset=offset+strlen("FileName:")+1+strlen(filename)+2;
	sprintf(buffer+offset,"File-md5sum: %s\r\n",md5sum);
	offset=offset+strlen("File-md5sum:")+1+strlen(md5sum)+2;
	sprintf(buffer+offset,"FileSizeInBytes: %s\r\n",size);	
	offset=offset+strlen("FileSizeInBytes:")+1+strlen(size)+2;
	sprintf(buffer+offset,"\r\n");
	offset+=2;

	//ta dedomena tou arxeiou xwrane sto idio munima me to header
	if ( st_size < BUFSIZE-offset)
	{
		if ( fread(buffer+offset,1,st_size,fp) != st_size )
		{
			perror("fread");
			return;
		}
		printf("here\n");
		if(mywrite(socket,buffer,BUFSIZE) <= 0 )
		{
			perror("mywrite");
			return;
		}
	}
 	//to arxeio einai megalutero-stelnw osa xwrane se auto to minima kai to upoloipo to spaw se paketa twn 4kb 
	//kai ta stelnw ena ena
	else
	{
		readbytes=fread(buffer+offset,sizeof(char),BUFSIZE-offset,fp);		
		if(mywrite(socket,buffer,BUFSIZE) <= 0 )
		{
			perror("write");
			return;
		}
		totalbytes=readbytes;
		while( totalbytes < st_size)
		{
			readbytes=fread(block,sizeof(char),CHUNKSIZE,fp);
			totalbytes+=readbytes;
			if(mywrite(socket,block,CHUNKSIZE) <= 0 )
			{
				perror("write");
				return;
			}
		}
	}
	fclose(fp);
}



void DeleteFile(char* Block,char* filename,char* md5sum)
{
	int offset=0;
	//create header//
	sprintf(Block,"MessageType: DeleteFile\r\n");
	offset+=strlen("MessageType:")+1+strlen("DeleteFile")+2;
	sprintf(Block+offset,"FileName: %s\r\n",filename);
	offset=offset+strlen("FileName:")+1+strlen(filename)+2;
	sprintf(Block+offset,"File-md5sum: %s\r\n",md5sum);
	offset=offset+strlen("File-md5sum:")+1+strlen(md5sum)+2;
	sprintf(Block+offset,"\r\n");
	
}

void SendFileResponse(char* Block,char* filename,char* md5sum)
{
	int offset=0;
	//create header//
	sprintf(Block,"MessageType: SendFileResponse\r\n");
	offset+=strlen("MessageType:")+1+strlen("SendFileResponse")+2;
	sprintf(Block+offset,"ResponseStatus: SendFileOK\r\n");
	offset=offset+strlen("ResponseStatus:")+1+strlen("SendFileOK")+2;
	sprintf(Block+offset,"FileName: %s\r\n",filename);
	offset=offset+strlen("FileName:")+1+strlen(filename)+2;
	sprintf(Block+offset,"File-md5sum: %s\r\n",md5sum);
	offset=offset+strlen("File-md5sum:")+1+strlen(md5sum)+2;
	sprintf(Block+offset,"\r\n");
}


void DeleteFileResponse(char* Block,char* filename,char* md5sum)
{
	int offset=0;
	//create header//
	sprintf(Block,"MessageType: DeleteFileResponse\r\n");
	offset+=strlen("MessageType:")+1+strlen("DeleteFileResponse")+2;
	sprintf(Block+offset,"ResponseStatus: DeleteFileOK\r\n");
	offset=offset+strlen("ResponseStatus:")+1+strlen("DeleteFileOK")+2;
	sprintf(Block+offset,"FileName: %s\r\n",filename);
	offset=offset+strlen("FileName:")+1+strlen(filename)+2;
	sprintf(Block+offset,"File-md5sum: %s\r\n",md5sum);
	offset=offset+strlen("File-md5sum:")+1+strlen(md5sum)+2;
	sprintf(Block+offset,"\r\n");
	

}	

void ErrorMessage(char *Block,char* responsestatus)
{
	int offset=0;
	//create header//
	sprintf(Block,"MessageType: ErrorMessage\r\n");
	offset+=strlen("MessageType:")+1+strlen("ErrorMessage")+2;
	sprintf(Block+offset,"ResponseStatus: %s\r\n",responsestatus);
	offset=offset+strlen("ResponseStatus:")+1+strlen(responsestatus)+2;
	sprintf(Block+offset,"\r\n");
	offset+=2;
	sprintf(Block+offset,"%s\r\n",responsestatus);
	offset=offset+strlen(responsestatus)+2;
	sprintf(Block+offset,"\r\n");

}

void parse_JoinRequest(char *Block,char **clientip,char **clientport)
{
	int offset=0;

	*clientip=calloc(33,sizeof(char));
	*clientport=calloc(6,sizeof(char));

	offset+=strlen("MessageType:")+1+strlen("JoinRequest")+2;
	sscanf(Block+offset,"IP: %s\r\n",*clientip);
	offset=offset+strlen("IP:")+1+strlen(*clientip)+2;
	sscanf(Block+offset,"Port: %s\r\n",*clientport);
	offset=offset+strlen("Port:")+1+strlen(*clientport)+2;
}

void parse_FileList(char *Block, fileptr *temp)
{
	int offset=0;
	char filename[30], md5[MAXLENGTH+1];
	offset+=strlen("MessageType:")+1+strlen("FileList")+2;	
	offset+=2;
	while ( sscanf(Block+offset,"%s %s\r\n",filename, md5) != EOF )
	{
		offset+=strlen(filename)+1+strlen(md5)+2;
		add_file(temp, filename, md5);
	}
}


void parse_AskFile(char *Block,char **filename)
{
	int offset=0;
	
	*filename=calloc(50,sizeof(char));
	//override  header//
	offset+=strlen("MessageType:")+1+strlen("AskFileList")+2;
	sscanf(Block+offset,"FileName: %s\r\n",*filename);
	offset=offset+strlen("FileName:")+1+strlen(*filename)+2;
	
}


void parse_AskFileResponse(char *Block,char **filename,char **ip,char **port)
{
	int offset=0;
	
	*filename=calloc(50,sizeof(char));
	*ip=calloc(20,sizeof(char));
	*port=calloc(5,sizeof(char));

	offset+=strlen("MessageType:")+1+strlen("AskFileResponse")+2;
	sscanf(Block+offset,"FileName: %s\r\n",*filename);
	offset=offset+strlen("FileName:")+1+strlen(*filename)+2;
	sscanf(Block+offset,"IP: %s\r\n",*ip);
	offset=offset+strlen("IP:")+1+strlen(*ip)+2;
	sscanf(Block+offset,"Port: %s\r\n",*port);
	offset=offset+strlen("Port:")+1+strlen(*port)+2;
	

}


void parse_GetFile(char* Block,char** filename,char** md5sum)
{
	int offset=0;
	
	*filename=calloc(50,sizeof(char));
	*md5sum=calloc(1024,sizeof(char));
	
	
	offset+=strlen("MessageType:")+1+strlen("GetFile")+2;
	sscanf(Block+offset,"FileName: %s\r\n",*filename);
	offset=offset+strlen("FileName:")+1+strlen(*filename)+2;
	sscanf(Block+offset,"File-md5sum: %s\r\n",*md5sum);
	offset=offset+strlen("File-md5sum:")+1+strlen(*md5sum);
	
}




void parse_GetFileResponse(char *Block,char **filename,char **md5sum,char **filesizeinbytes,int socket)
{
	int offset=0;
	char data[BUFSIZE];
	long totalbytes=0,writtenbytes=0,readbytes=0;
	FILE *fp;
	char *chunk;
	
	*filename=calloc(50,sizeof(char));
	*md5sum=calloc(33,sizeof(char));
	*filesizeinbytes=calloc(20,sizeof(char));
	
	
	offset+=strlen("MessageType:")+1+strlen("GetFileResponse")+2;
	offset+=strlen("ResponseStatus:")+1+strlen("FileFound")+2;
	sscanf(Block+offset,"FileName: %s\r\n",*filename);
	offset=offset+strlen("FileName:")+1+strlen(*filename)+2;
	sscanf(Block+offset,"File-md5sum: %s\r\n",*md5sum);
	offset=offset+strlen("File-md5sum:")+1+strlen(*md5sum)+2;
	sscanf(Block+offset,"FileSizeInBytes: %s\r\n",*filesizeinbytes);
	offset=offset+strlen("FileSizeInBytes:")+1+strlen(*filesizeinbytes)+2;
	sscanf(Block+offset,"\r\n");
	offset+=2;
	if ( (fp=fopen(*filename,"wb")) == NULL )
	{
		perror("fopen");
		return;
	}
	//to arxeio periexetai olo  sto idio minima me tis header-plirofories
	if (atoi(*filesizeinbytes) < BUFSIZE-offset)
	{
		if ( fwrite(Block+offset,sizeof(char),atoi(*filesizeinbytes),fp) != atoi(*filesizeinbytes) )
		{
			perror("fwrite");
			return;
		}
	}
	//to arxeio einai megalutero-diavazw osa dedomena periexontai se auto to minima kai meta diavazw paketa twn 4kb
	else
	{
		chunk=calloc(CHUNKSIZE,sizeof(char));
		if ( (writtenbytes = fwrite(Block+offset,sizeof(char),BUFSIZE-offset,fp))!=  BUFSIZE-offset)
		{
			perror("fwrite");
			return;
		}
		totalbytes=writtenbytes;
		while( totalbytes < atoi(*filesizeinbytes) )
		{
			if ( (readbytes=myread(socket,chunk,CHUNKSIZE)) <=0 ) {
				perror("read");
				return;
			}
			int temp=(atoi(*filesizeinbytes)-totalbytes>CHUNKSIZE)?(CHUNKSIZE):(atoi(*filesizeinbytes)-totalbytes);

			if ( fwrite(chunk,sizeof(char),temp,fp) != temp )
			{
				perror("fwrite");
				return;
			}
			totalbytes+=readbytes;		
		}
		free(chunk);
	}
	fclose(fp);
}	




void parse_SendFile(char *Block,char **filename,char **md5sum,char **filesizeinbytes,int socket)
{
	int offset=0;
	char data[BUFSIZE];
	long totalbytes=0,writtenbytes=0,readbytes=0;
	FILE *fp;
	char *chunk;
	
	*filename=calloc(50,sizeof(char));
	*md5sum=calloc(33,sizeof(char));
	*filesizeinbytes=calloc(20,sizeof(char));
	
	
	offset+=strlen("MessageType:")+1+strlen("SendFile")+2;
	sscanf(Block+offset,"FileName: %s\r\n",*filename);
	offset=offset+strlen("FileName:")+1+strlen(*filename)+2;
	sscanf(Block+offset,"File-md5sum: %s\r\n",*md5sum);
	offset=offset+strlen("File-md5sum:")+1+strlen(*md5sum)+2;
	sscanf(Block+offset,"FileSizeInBytes: %s\r\n",*filesizeinbytes);
	offset=offset+strlen("FileSizeInBytes:")+1+strlen(*filesizeinbytes)+2;
	sscanf(Block+offset,"\r\n");
	offset+=2;
	if ( (fp=fopen(*filename,"wb")) == NULL )
	{
		perror("fopen");
		return;
	}
	//to arxeio periexetai olo  sto idio minima me tis header-plirofories
	if (atoi(*filesizeinbytes) < BUFSIZE-offset)
	{
		if ( fwrite(Block+offset,sizeof(char),atoi(*filesizeinbytes),fp) != atoi(*filesizeinbytes) )
		{
			perror("fwrite");
			return;
		}
	}
	//to arxeio einai megalutero-diavazw osa dedomena periexontai se auto to minima kai meta diavazw paketa twn 4kb
	else
	{
		chunk=calloc(CHUNKSIZE,sizeof(char));
		if ( (writtenbytes = fwrite(Block+offset,sizeof(char),BUFSIZE-offset,fp))!=  BUFSIZE-offset)
		{
			perror("fwrite");
			return;
		}
		totalbytes=writtenbytes;
		while( totalbytes < atoi(*filesizeinbytes) )
		{
			if ( (readbytes=myread(socket,chunk,CHUNKSIZE)) <=0 ) {
				perror("read");
				return;
			}
			int temp=(atoi(*filesizeinbytes)-totalbytes>CHUNKSIZE)?(CHUNKSIZE):(atoi(*filesizeinbytes)-totalbytes);

			if ( fwrite(chunk,sizeof(char),temp,fp) != temp )
			{
				perror("fwrite");
				return;
			}
			totalbytes+=readbytes;		
		}
		free(chunk);
	}
	fclose(fp);
}	


int parse_SendFileResponse(char *Block,char *filename,char *md5sum)
{
	int offset=0;
	char status[16], tempname[56], tempmd5sum[33];
	

	offset+=strlen("MessageType:")+1+strlen("SendFileResponse")+2;
	sscanf(Block+offset,"ResponseStatus: %s\r\n",status);
	if ( strcmp(status,"SendFileOK") ) 
		return -1;
	offset=offset+strlen("ResponseStatus:")+1+strlen("SendFileOK")+2;
	sscanf(Block+offset,"FileName: %s\r\n",tempname);
	if ( strcmp(filename,tempname) ) 
		return -1;
	offset=offset+strlen("FileName:")+1+strlen(filename)+2;
	sscanf(Block+offset,"File-md5sum: %s\r\n",tempmd5sum);
	if ( strcmp(md5sum,tempmd5sum) ) 
		return -1;
	offset=offset+strlen("File-md5sum:")+1+strlen(md5sum)+2;
	return 0;
}


void parse_DeleteFile(char *Block,char **filename,char **md5sum)
{
	int offset=0;
	
	*filename=calloc(50,sizeof(char));
	*md5sum=calloc(1024,sizeof(char));

	offset+=strlen("MessageType:")+1+strlen("DeleteFile")+2;
	sscanf(Block+offset,"FileName: %s\r\n",*filename);
	offset=offset+strlen("FileName:")+1+strlen(*filename)+2;
	sscanf(Block+offset,"File-md5sum: %s\r\n",*md5sum);
	offset=offset+strlen("File-md5sum:")+1+strlen(*md5sum)+2;
}


int parse_DeleteFileResponse(char *Block,char *filename,char *md5sum)
{
	int offset=0;
	char status[16], tempname[56], tempmd5sum[33];
	

	offset+=strlen("MessageType:")+1+strlen("DeleteFileResponse")+2;
	sscanf(Block+offset,"ResponseStatus: %s\r\n",status);
	if ( strcmp(status,"DeleteFileOK") ) 
		return -1;
	offset=offset+strlen("ResponseStatus:")+1+strlen("DeleteFileOK")+2;
	sscanf(Block+offset,"FileName: %s\r\n",tempname);
	if ( strcmp(filename,tempname) ) 
		return -1;
	offset=offset+strlen("FileName:")+1+strlen(filename)+2;
	sscanf(Block+offset,"File-md5sum: %s\r\n",tempmd5sum);
	if ( strcmp(md5sum,tempmd5sum) ) 
		return -1;
	offset=offset+strlen("File-md5sum:")+1+strlen(md5sum)+2;
	return 0;
}


void parse_ErrorMessage(char *Block,char **responsestatus)
{
	int offset=0;
	
	*responsestatus=calloc(50,sizeof(char));
	

	offset+=strlen("MessageType:")+1+strlen("ErrorMessage")+2;
	sscanf(Block+offset,"ResponseStatus: %s\r\n",*responsestatus);
	offset=offset+strlen("ResponseStatus:")+1+strlen(*responsestatus)+2;
	sscanf(Block+offset,"\r\n");
	offset+=2;
	sscanf(Block+offset,"%s\r\n",*responsestatus);
	offset=offset+strlen(*responsestatus)+2;

}


