#include "UT_DM_Defines.h"

#pragma pack(1)

/*typedef struct {
	char relname[MAXNAME]; 	
	int relwidth; 		
     	int attrcnt; 	
    	int indexcnt; 	
}relDesc;


typedef struct {
	char relname[MAXNAME]; 
    	char attrname[MAXNAME];
    	int offset; 		
    	int attrlength; 	
    	char attrtype; 		
    	int indexed; 		
    	int indexno; 		
}attrDesc;
*/
int CFM_Create(void);
int CFM_AddRel(relDesc, attrDesc*);
int CFM_DeleteRel(char* );
int CFM_IndexAttribute(char*, char*, int);
int CFM_Lookup(char*, relDesc*, attrDesc**);

