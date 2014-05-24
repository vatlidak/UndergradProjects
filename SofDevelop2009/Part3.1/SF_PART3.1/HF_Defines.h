/*
 * File: HF_Defines.h
 *
 * Authors: Atlidakis Vaggelis, Aggelogiannopoulos Aris, Kuriazof Xristina
 * AM: 	    1115200500010, 1115200500004, 1115200600276
 * 
 * Date: 1.12.2009
 *
 */
#ifndef _HF_DEFINES_H
#define	_HF_DEFINES_H

#define HFE_OK           	0
#define HFE_EOF        		-24   /* End of file */
#define HFE_INVALIDREC  	-25   /* Invalid record */
#define HFE_STFULL     		-26   /* Scan table full */
#define HFE_INVALIDOP   	-27   /* Invalid scan operator */
#define HFE_RECEMPTY 		-28
#define HFE_ALLBLOCKSFULL 	-29
#define HFE_NOMEM               -30   /* Unable to aloc memory */
#define HFE_INVALIDSCANDESC  	-31   /* Invalid ScanDesc */
#define HFE_HASOPENSCANS	-32

#define MAXSCANS 		20	/* Maximux simultaneously open Scans */

#define EQUAL 1
#define LESS_THAN 2
#define GREATER_THAN 3
#define LESS_THAN_OR_EQUAL 4
#define GREATER_THAN_OR_EQUAL 5
#define NOT_EQUAL 6

int HF_errno;



#endif	/* _HF_DEFINES_H */
