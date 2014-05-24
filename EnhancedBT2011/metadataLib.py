#This module implements an Application Programming Interface 
#to create and access metadata files.
#Author: V. Atlidakis
#Date: March 2011
import UserDefs
import mymd5
import math
import bitmap
import mysha1lib
import hashlib
import pickle


#This is a function creating a metadata file for "filename".
#Metadata is named after respective file, with a suffix ".ant".
def create_metadatafile(filename):
	
	#try to open file for reading and go to the begginning.
	try:
		f=open(filename,'rb')
		filesize=f.seek(0,2)   					
		f.seek(0)
	#If an Exception occurs, raise it.
	except IOError as detail:
		print("Error Opening File:",detail)
		raise
	#If an Exception occurs, raise it.
	except Exception as detail:
		print("Unexpected Exception::",detail)
		raise
		
	block_size=UserDefs.PieceSize				#Block size
	FileMd5=mymd5.mymd5_file(f,1000*4096)                	#THIS WILL BE OF NO NEED	      				
	BMPLENGTH=math.ceil(filesize/UserDefs.PieceSize)	#calculate length of bitmap.
	f.seek(0)	
	sha1s=[]
	#constructor of sha-1 hash.
	metadata_hash=hashlib.new('sha1')			#create hash of metadata file, which will be used as file identifier.
	for i in range(0,BMPLENGTH):				
		try:
			chunk=f.read(UserDefs.PieceSize)	#read each block of file
		#If an Exception occurs, raise it.
		except 	IOError as detail:
			print("IOFile Error <block> at server thread:",detail)
			raise
		#If an Exception occurs, raise it.
		except Exception as detail:
			print("Unexpected Exception <block> at server thread:",detail)
			raise
		sha1s.append(mysha1lib.mysha1(chunk))		#create sha1 for current block.
		metadata_hash.update(chunk)			#update hash of metadata
	f.close()						#close file

	metadata_dict={'filename':filename			#create final metadata block
		,'filesize':filesize
		,'FileMd5':FileMd5
		,'sha1s_map':sha1s
		,'block_size':block_size
		,'metadata_hash':metadata_hash.hexdigest()
		}
	pickled=pickle.dumps(metadata_dict)
	#try to open file for writting and go to the begginning.			
	try:
		f=open(filename+'.ant','wb')
	#If an Exception occurs, raise it.			
	except IOError as detail:
		print("Error Opening File: ",filename,":: ",detail)
		raise
	#try to position at the begginning of the file.
	try:
		f.seek(0)   
	#If an Exception occurs close file and raise it.	  							 
	except IOError as detail:
		print("Error Seeking File: ",filename,":: ",detail)
		f.close()
		raise
	#try to write metadata block into file.
	try:
		f.write(pickled)               
        #If an Exception occurs close file and raise it.
	except Exception as detail:
		print("Error Writting File: ",filename,":: ",detail)
		f.close()
		raise
	f.close()						#close file
	print("metadata successfully written:",metadata_dict['metadata_hash'],BMPLENGTH," pieces in file.")
	return metadata_dict					#return metadata block.


#this is a function reading a metadata file and creates a
#dictionary from metadata included in file.
def read_metadatafile(filename):

	#try to open file for reading and go to the begginning.
	try:
		f=open(filename+'.ant','rb')	
	#If an Exception occurs, raise it.		
	except IOError as detail:
		print("IOError Opening File: ",filename,":: ",detail)
		raise
	#If an Exception occurs, raise it.
	except Exception as detail:
		print("Unexpected Exception Opening File::",detail)
		raise
	
	#try to position at the begginning of the file.
	try:
		f.seek(0)    
	#If an Exception occurs close file and raise it.							
	except IOError as detail:
		f.close()
		print("IOError Seeking File: ",filename,":: ",detail)
		raise
	#If an Exception occurs close file and raise it.
	except Exception as detail:
		f.close()
		print("Unexpected Exception Seeking File:",detail)
		raise
	#try to read metadata block from file.
	try:
		p_dict=f.read()   
	#If an Exception occurs close file and raise it.                   
	except IOError as detail:
		f.close()
		print("IOError Reading File: ",filename,":: ",detail)
		raise
	#If an Exception occurs close file and raise it.
	except Exception as detail:
		f.close()
		print("Unexpected Exception Reading File: ",filename,":: ",detail)
		raise

	metadata_dict=pickle.loads(p_dict)
	#return metadata block read.
	return metadata_dict
