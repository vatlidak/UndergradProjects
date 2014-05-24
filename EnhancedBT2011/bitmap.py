#This module implements an Apllication Programming Interface allowing above 
#levels to accomplish bitmap operations. Functions trying to access or modify 
#bitmap should acquire a lock so that mutual exclusion is ensured.
#Author: V. Atlidakis
#Date: March 2011
import math
import random
import threading

#Initialize bitmap named "bmp" containing "length" bits.
#It is implemented as a lists of integers.
def bmp_init(bmp,length):
    for i in range(0,math.ceil(length/8)):
        bmp.append(0)


#Set valid "which"-th bit of bitmap "bmp".
def bmp_setvalid(bmp,which, lock):
	if lock == -1:
		c=128
		c=c>>(which % 8)
		bmp[which//8] = bmp[which//8] | c
	else:
		with lock:
			c=128
			c=c>>(which % 8)
			bmp[which//8] = bmp[which//8] | c

#Set valid all bits of bitmap "bmp".We will set 
#to 255 last bit which will not affect us, since 
#we will check only length bits.
def bmp_setallvalid(bmp,length):	
    for i in range(0,math.ceil(length/8)):
        bmp[i]=255
      
  
#Check if "which"-th bit of bitmap "bmp" is valid.
def bmp_isvalid(bmp, which, lock):
	c=128
	c=c>>(which%8)
	if lock == -1:
		rval=(( bmp[which//8] & c ) != 0 )
	else:
		with lock:
			rval=(( bmp[which//8] & c ) != 0 )
	return rval

#Check if you are interested in any pieces of a remote
#peer. Achieve that comparing bitmaps.
def interested(mybmp,senderbmp,length, lock):
	
	lock.acquire()
	for i in range (0,math.ceil(length/8)):
		c = 128
		for j in range(0,8):
			if mybmp[i] & c == 0 and senderbmp[i] & c != 0 and (8*i+j)<length :
				lock.release()
				return 'interested'
			c=c>>1
	lock.release()
	return 'uninterested'
