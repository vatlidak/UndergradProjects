#This module implements an Apllication Programming Interface allowing above 
#levels to use md5 hashes to check integrity of blocks and files. 
#Author: V. Atlidakis
#Date: March 2011
import sys,hashlib

#create md5 hash for file f, taking block size as argument.
def mymd5_file(f, block_size):
    md5 = hashlib.md5()
    while True:
        data = f.read(block_size)
        if not data:
            break
        md5.update(data)
    return md5.digest()

#create md5 hash for data.
def mymd5_chunk(data):
    md5 = hashlib.md5()
    md5.update(data)
    return md5.digest()
