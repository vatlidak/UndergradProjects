#define MAXLENGTH 32
//pthread_mutex_t metadata_mux;


typedef struct peer* peerptr;
typedef struct peer{
	char   ip[MAXLENGTH];
	char   port[MAXLENGTH+1];
	peerptr next;
}peer;


typedef struct file* fileptr;
typedef struct file{
	pthread_mutex_t file_mux;
	char filename[MAXLENGTH];
	char   md5[MAXLENGTH+1];
	fileptr next;
	peerptr peers;
}file;


//epistrefei 1 an uparxei to antistoixo arxeio sti lista//
int file_in(fileptr metadata, char *filename, char *md5);

//prosthetei to file sti lista an to file den uparxei(ara kalw prwta tin "in")
void add_file(fileptr *metadata, char *filename, char *md5);

//delete file
void delete_file(fileptr *metadata, char *filename, char *md5);

//release all
void release_metadata(fileptr metadata);

//epistrefei ton komvo ston opoio vrisketai to antistixo arxeio
fileptr filenode(fileptr metadata, char *filename, char *md5);

void printfile(fileptr metadata);

//epistrefei 1 anb o peer uparxei stin lista tou komvou pou pairnei ws orisma
int peer_in(fileptr node, char *ip, char *port);

//prosthetei ton peer ston antisixo komvo
void add_peer(fileptr *node, char *ip, char *port);

//delete peer
void delete_peer(fileptr *node, char *ip, char *port);

//release peers
void release_peers(fileptr node);


void printpeer(fileptr metadata);
