/*
 * File:   UT_DM_Defines.h
 */
 
#ifndef _UT_DM_DEFINES_H
#define _UT_DM_DEFINES_H

#define UTE_OK		0
#define UTE_NOMEM       -33   /* Unable to aloc memory */
#define SCM_ERROR	-34

#define relCat		"RELCAT"
#define attrCat 	"ATTRCAT"
#define MAXNAME		40

int UT_errno;	/* error code */
int relCatFd;   /* file descripitor of relCat */
int attrCatFd;  /* file descripitor of attrCat */


#endif

