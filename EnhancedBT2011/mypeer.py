#This modules implements main thead that commences execution of our client.
#In seeder mode metadata file is created if requested, while in leecher mode
#metadata file is read. Afterwards tracker is contacted in order to join 
#swarm, server thread is constructed  and leecher, if in leecher mode.
#Author: V. Atlidakis
#Date: March 2011
import pickle
import sys, socket, threading
import math, time
import bitmap
import UserDefs
import UserLib
import metadataLib
import SocketLevel
import LeecherThread
import ServerThread


msg={}		#global variable keeping message to send.
msg_r={}	#global variable keeping received message.

def main():

	global msg, msg_r	
	if not  len(sys.argv) in [7,8]:
		print("Usage:",sys.argv[0],"(<trackerip> <trackerport>) <listeningport> <seed/peer> <filename> <optimistic/optimal> [<create metadata file>]")
		return

	#assign command line arguments to local variables
	trackerip=socket.gethostbyname(sys.argv[1])
	trackerport=int(sys.argv[2])
	listeningport=int(sys.argv[3])	
	hostname=socket.gethostname()
	listeningip=socket.gethostbyname(hostname)
	mode=sys.argv[4]
	filename=sys.argv[5]
	choice=sys.argv[6]
	print(trackerip,trackerport,listeningip,listeningport,mode,filename,choice)

	#The first uploader is also the creator of metadata file.
	#All other peers receiving metadata file from a site
	#acting as a global directory.
	if len(sys.argv) == 8 and  sys.argv[7] == "create":		
		metadata_dict=metadataLib.create_metadatafile(filename)
	else:
		metadata_dict=metadataLib.read_metadatafile(filename)		
	print("size of metadata")
	
	if mode == "peer":
	      #create file so that following server and leecher thread open it.
	      try:
		      filename=filename+str(listeningport)
		      f=open(filename,'wb+')
	      #Uppon Exception, make clen up job and terminatethread.                  
	      except IOError as detail:
		      print("IOError:",detail)
		      return
	      #Uppon Exception, make clen up job and terminate thread.
	      except  Exception as detail:
		      print("0.Unexpected exception:",detail)
		      return
	      else:
		      f.close()


	
	
	#initialize bitmap, sha1's of each chunk and file identifier(metadata hash).	
	UserLib.BMPLENGTH=math.ceil(metadata_dict['filesize']/UserDefs.PieceSize)
	bitmap.bmp_init(UserLib.bmp,UserLib.BMPLENGTH)     
	UserLib.sha1s_map=metadata_dict['sha1s_map']
	UserLib.metadata_hash=metadata_dict['metadata_hash']
	#print("metadata_hash",UserLib.metadata_hash)
	#In seeder mode all blocks are available. 
	if mode == "seed":            	
		bitmap.bmp_setallvalid(UserLib.bmp,UserLib.BMPLENGTH)			

	#creation of a socket to establish  TCP connection with coordinator.
	try:
		tracker = socket.socket ( socket.AF_INET, socket.SOCK_STREAM )     
		tracker.connect((trackerip,trackerport ))                   	
	except socket.error as detail:
		print("Tracker communication Socket error",detail)
		return
	except Exception as detail:
		print("Unexpected Exception:",detail)
		return	
	
	#prepare a "join_swarm" message" to send to coordinator. 
	join_swarm(metadata_dict['filename'],metadata_dict['filesize'],metadata_dict['FileMd5'],listeningip,listeningport)	
	try:	
		SocketLevel.send_msg(-1,tracker,[],msg)
	except Exception as detail:
		print("Unexpected Exception:",detail)
		tracker.close()
		return

	#receive a "join_response" message from coordinator.
	try:	
		msg_r=SocketLevel.recv_msg(-1,tracker,[])
	except Exception as detail:
		print("Unexpected Exception:",detail)
		tracker.close()
		return		
	#upon successful communication retrieve your peer identifier.
	else:
		UserLib.mypeerid=msg_r['peerid']

	#constructor of "ServerThread" for that peer
	#size, md5 and name of file to seed
	#port and ip listening for requests of TCP connections
	#socket of established connection with coordinator.
	Sthread=ServerThread.ServerThread(metadata_dict['filesize'],metadata_dict['FileMd5'],filename,listeningport,listeningip,mode,choice,tracker)
	Sthread.start()

	#constructor of "LeecherThread" for that peer-if not in seeder mode.
	if mode == "peer":                                      
		Lthread=LeecherThread.LeecherThread(metadata_dict['filesize'],metadata_dict['FileMd5'],filename,listeningport,listeningip,tracker)
		Lthread.start()

	#Main Thread waiting threads to terminate.
	Sthread.join()
	if sys.argv[3] == "peer":
		Lthread.join()
	tracker.close()
	print('Programm is going to terminate')
	return


#this is a function creating "join_swarm" message.
def join_swarm(filename,filesize,FileMd5,listeningip,listeningport):

	global msg
	msg = {'type':'join_swarm'
		,'filename':filename
		,'filesize':filesize
		,'FileMd5':FileMd5
		,'listeningip':listeningip
		,'listeningport':listeningport}


if __name__=='__main__':
    main()
