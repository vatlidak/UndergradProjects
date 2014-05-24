/* ATLIDAKIS VANGELIS 		*/
/* 1115 2005 00010    		*/
/* EXERCISE-4 OPERATING SYSTEMS */
#define READ_FLAGS      O_RDONLY
#define WRITE_FLAGS     (O_WRONLY | O_CREAT | O_EXCL)
#define WRITE_PERMS     (S_IRUSR | S_IWUSR)
#define BLKSIZE         512
#define NAMESIZE        256
#define FAILURE         -1
#define SUCCESS         0

typedef struct Header{
        long    offset;
        int     entries;
}Header;

typedef struct tnode *Treeptr;
typedef struct tnode {         //struct tnode of rooted tree//
        int     kidsno, blocks;
        int     h_links;
        long    ino;
        long    begoff;
        long    datasize;
        char    name[NAMESIZE];
        char    abspath[NAMESIZE];
        char    owner[NAMESIZE];
        char    group[NAMESIZE];
        char    time[NAMESIZE];
        char    type, perms[10];
        Treeptr* kids;
}tnode;

int     ExtrFromArchieve(FILE*, char*, Treeptr*);
int 	ExtrAll(FILE*, Treeptr*);
int     detach_regfile(FILE*, Treeptr );
void    AddToArchieve(FILE* , char*, char*, Treeptr*, int);
int     attach_regfile(FILE*, char*, Treeptr*, char*, int);
int     save(Treeptr* , FILE*, int* );
int     load(FILE*, int, Treeptr* );
int     copyfile(char*);
void    initialize(Treeptr*);
void    print(Treeptr*,int);
int     insert(Treeptr* , tnode);
void    release(Treeptr );
Treeptr search(Treeptr*, char* );

