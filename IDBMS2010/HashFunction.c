/*
 *  HashFunction.c
 *  
 *
 *  Created by Natasa Sevastidou on 4/27/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "HashFunction.h"


unsigned long hash(unsigned char *str, int Buckets)
{
	unsigned long hash = 5381;
	int c;
	
	while (c = *str++)
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
	
	return hash % Buckets;
}


//unsigned long hash2(unsigned char *str, int Buckets)
//{
//        unsigned long hash = 5381;
//        int c;
//
//        while (c = *str++)
//                hash = ((hash << 15) + hash) + c; /* hash * 33 + c */
//
//        return hash % Buckets;
//}


