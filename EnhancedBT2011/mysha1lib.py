#This module implements an Apllication Programming Interface allowing above    
#levels	to use sha1 hashes to check data integrity.
# Based on code found on the internet here:					
#		http://www.thegeekstuff.com/2010/04/inotify-c-program-example/  
#Author: V. Atlidakis
#Date: March 2011							
import sys,hashlib

#this is a function returning sha-1 hash respectibe to data.
def mysha1(data):
	createSha1 = hashlib.sha1(data)
	sha1_block = createSha1.hexdigest()
	return sha1_block

