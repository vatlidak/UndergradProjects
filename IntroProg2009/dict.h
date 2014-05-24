float per;
typedef struct tnode *Treeptr;
typedef struct tnode				/*node of the the tree at compression function*/ 
{
	int	code;
	char *word;
  	Treeptr left;
  	Treeptr right;
}Treenode;


typedef struct transcode			/*items of translation table at the decompression function*/
{
	int code;
	char* word;
}transcode;


void addtree(Treeptr* , char*,int);
void treeprint(Treeptr, int);
int treesearch(Treeptr, char *);
int searchcode(Treeptr, char *);
void deletetree(Treeptr);



