#ifndef UT_DM_DEFINES_H
#define UT_DM_DEFINES_H

#define MAXNAME 32

#define UTE_OK		  0
#define UTE_NOMEM	 -1
#define UTE_HFERROR	 -2
#define UTE_AMERROR	 -3
#define UTE_MALLOC	 -4
#define UTE_ATTRNOTFOUND -5
#define UTE_RELNOTFOUND  -6

#define UTE_SCM_ZEROARGS	-100
#define UTE_SCM_DUPLICATEARGS	-101
#define UTE_SCM_ARGNUM		-102
#define UTE_SCM_RELEXISTS	-103
#define UTE_SCM_RELNOTEXIST	-104
#define UTE_SCM_WRONGOP		-105
#define UTE_SCM_INDEXEXISTS	-106

#define SCM_ERROR	-108

#define DME_OK	   0
#define DME_NOMEM -107


#pragma pack(1)

typedef enum {
    FALSE = 0,
    TRUE = 1
}BOOLEAN;

typedef struct {
    char relname[MAXNAME];
    int relwidth;
    int attrcnt;
    int indexcnt;
} relDesc;

typedef struct {
    char relname[MAXNAME];
    char attrname[MAXNAME];
    int offset;
    int attrlength;
    char attrtype;
    int indexed;
    int indexno;
} attrDesc;


int relCatFd;
int attrCatFd;
int UT_errno;
int DM_errno;

#endif /* UT_DM_DEFINES_H */
