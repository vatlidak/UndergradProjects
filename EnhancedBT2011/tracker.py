try:
    import cPickle as pickle
except:
    import pickle
import sys, socket, select, threading
import time, random
from bitmap import *
import UserLib
import UserDefs
import struct
import time
import mysha1lib
import myuuidlib
import metadataLib


Run=False
metadatalist = []
ips_list = []
ports_list = []
msg={}
msg_r={}
    
#ligo ta remove parakalw
    
def main():

	if not len(sys.argv) == 2:
		print("Usage:",sys.argv[0]," <listeningport> ")
		return                                                      

	try:
		server = socket.socket ( socket.AF_INET, socket.SOCK_STREAM )                   # Set up the server.
		server.setsockopt(socket.SOL_SOCKET,socket.SO_REUSEADDR,1)
		server.bind (('', int(sys.argv[1])))
		server.listen ( 25 )
	except (socket.error,socket.gaierror,OverflowError) as detail:
		print("Listening Socket error:",detail)
		return
	except Exception as detail:
		priunt("Unexpected exception",detail)
		return

	input=[server,sys.stdin]
	print("Coordinator listening at:",int(sys.argv[1]),"\n\n")
	global Run
	Run=True
	counter1=0
	counter2=0
	totaltime=0
	while Run:                                                                     # Have the server serve "forever".
		inputready, outputready, exceptionready = select.select(input,[],[])	# wait till a socket has data.
		#print("data on sock")
		for s in inputready:
			conn=s
			if s == server:							# if it's server, you have to accept a new connection
				print("accepted connection")
				try:
					conn, addr=server.accept()
				except socket.error as detail:
					print("Socket Error accepting connection:",detail)
					break 
				except Exception as detail:
					print("Unexpected error accepting connection:",detail)
					break 
				input.append(conn)					# append it to socket's set.
			elif  s == sys.stdin:
				Run=False
				remove_all_peers(input)
				break
			else:							# else you have data to an active socket
				try:
					recv_msg(input,s)
				except Exception:			
					continue
				if msg_r['type'] == 'join_swarm':        	# if it's a joinrequest.
								
					position=index_metadata(msg_r['FileMd5'])
#an den einai seeder poulo
#an exw metadata tote exw toulaxiston ena seed ara oxi poulo
					peerid=add_peer(position,msg_r,conn)
					#den thelw okens edw#
					if position<0: len(metadatalist)-1									
					
					join_swarm_response(msg_r,position,peerid)
					try:
						send_msg(conn)
					except Exception:
						continue

				elif msg_r['type'] == 'leave_swarm':

					leave_swarm(conn)
					remove_peerbyport(msg_r['listeningport'])
					conn.close()                                                                # this will leave LATER
					input.remove(conn)

				elif msg_r['type'] == 'peer_request':
					
					peer_response(msg_r['FileMd5'])
					try:
						send_msg(conn) 
					except Exception:
						continue
				elif msg_r['type'] == 'time_request':
					
					time_response()
					try:
						send_msg(conn) 
					except Exception:
						continue
				elif msg_r['type'] == 'leave':
					try:
						remove_peerbysock(conn)
					except Exception:
						continue	
				if metadatalist:
					print("Swarm Size:",len(metadatalist[0]['peerids']),"time:",time.ctime())
				else:
					print("Swarm Size:",0)	

			#print("\n\n\n---------------------------------\n",metadatalist,"\n----------------------------------------------------------------\n")

	server.close()
	return


def add_peer(position,dictionary,socket):
	
	global ips_list, ports_list


	peerid=myuuidlib.create_uuid()
	if position<0:

		metadata={}	#initialize metadata related to this file, including listening port.
		metadata['filename']=dictionary['filename']
		metadata['filesize']=dictionary['filesize']
		metadata['FileMd5']=dictionary['FileMd5']
		metadata['listeningports']=[dictionary['listeningport']]
		metadata['listeningips']=[dictionary['listeningip']]
		metadata['peerids']=[peerid]
		metadata['sockets']=[socket]
		metadatalist.append(metadata)		
		position=0
	
	elif position >= 0:                                                     # existing file.
		metadatalist[position]['listeningports'].append(dictionary['listeningport'])
		metadatalist[position]['listeningips'].append(dictionary['listeningip'])
		metadatalist[position]['sockets'].append(socket)
		metadatalist[position]['peerids'].append(peerid)

	return  peerid


def send_msg(sock):

	global msg
	try:
		pickledmsg = pickle.dumps ( msg )
		header=struct.pack("I",len(pickledmsg))
		sock.send ( header+pickledmsg )
	except socket.timeout as detail:
		print("<socket.timeout> error <send_msg> ::",detail)
		raise
	except socket.error as detail:
		print("<socket.eror> error <send_msg> ::",detail)
		raise
	except Exception as detail:
		print("Unexpected Exception <send_msg> ::",detail)
		raise
	#print("sent\n",msg['type'])


def recv_msg(input,s):

	global msg_r
	try:
		header=s.recv(struct.calcsize('I'))
		if not header:	
			#print("Going to terminate connection:",s)
			input.remove(s)
			remove_peerbysock(s)
			raise  ConnectionResetedByPeer
		else:
			msgsize=struct.unpack("I",header)[0]
		data=b""
		while msgsize > 0:
			newdata = s.recv(msgsize)
			if not newdata:
				#print("Going to terminate connection:",s)
				input.remove(s)
				#amfivolou poiotitas sunartisi
				remove_peerbysock(s)
				raise  ConnectionResetedByPeer	
			data+=newdata
			msgsize-=len(newdata)
		msg_r=pickle.loads(data)
	except ConnectionResetedByPeer:
		print("connection reseted by peer")
		raise
	except socket.timeout as detail:
		print("<socket.timeout> error <recv_msg> ::",detail)
		raise
	except socket.error as detail:
		print("<socket.eror> error <recv_msg> ::",detail)
		raise
	except Exception as detail:
		print("Unexpected Exception <recv_msg> ::",detail)
		raise
	#print("received\n",msg_r)
	

def time_response():
	
	global msg
	msg={   'type':'time_response'
		,'time':time.time()
	}
	


def peer_response(FileMd5):
	
	pos=index_metadata(FileMd5)
	if pos == -1:
		listeningports=[]
	else:

		listeningports=metadatalist[pos]['listeningports']
		listeningips=metadatalist[pos]['listeningips']
		peerids=metadatalist[pos]['peerids']

	global msg
	msg={   'type':'peer_response'
		,'listeningports':listeningports
		,'listeningips':listeningips
		,'peerids':peerids
	}	
	#print("peer response",msg)

def join_swarm_response(dictionary,position,peerid):

	global msg
	msg={'type':'join_swarm_response'
		,'filename':dictionary['filename']
		,'filesize':metadatalist[position]['filesize']
		,'FileMd5':metadatalist[position]['FileMd5']
		,'peerid':peerid
	}


def index_metadata(FileMd5):

	for i in range(0,len(metadatalist)):					# existing file in swarm?
		if metadatalist[i]['FileMd5'] == FileMd5:
			return i
	return -1


def find_port_bysock(s):
		
	for i in range(0,len(metadatalist)):             # find swarms participating listening port and remove it
		if s in metadatalist[i]['sockets']:
			ind=metadatalist[i]['sockets'].index(s)
			return	metadatalist[i]['listeningports'][ind]
	return False
	

def find_id_bysock(s):
		
	for i in range(0,len(metadatalist)):             # find swarms participating listening port and remove it
		if s in metadatalist[i]['sockets']:
			ind=metadatalist[i]['sockets'].index(s)
			return	metadatalist[i]['peerids'][ind]
	return False

			
def find_ip_bysock(s):
		
	for i in range(0,len(metadatalist)):             # find swarms participating listening port and remove it
		if s in metadatalist[i]['sockets']:
			ind=metadatalist[i]['sockets'].index(s)
			return	metadatalist[i]['listeningips'][ind]
	return False


def remove_all_peers(input):
	
	#print("remove all")
	for s in input:
		s.close()

def remove_peerbyportip(portip):
	
	#print('remove by peerid')
	for i in range(0,len(metadatalist)):             # find swarms participating listening port and remove it
		if portip[0] in metadatalist[i]['listeningports'] and portip[1] in metadatalist[i]['listeningips']:
			ind=metadatalist[i]['listeningports'].index(portip[0])
			metadatalist[i]['listeningports'].remove(portip[0]) 
			del	metadatalist[i]['sockets'][ind]
			del 	metadatalist[i]['peerids'][ind]
			del 	metadatalist[i]['listeningips'][ind]
			if not metadatalist[i]['listeningports']:
				del metadatalist[i]
	#print(metadatalist)


def remove_peerbysock(s):
	
	#print('remove by sock')
	for i in range(0,len(metadatalist)):             # find swarms participating listening port and remove it
		if s in metadatalist[i]['sockets']:
			ind=metadatalist[i]['sockets'].index(s)
			metadatalist[i]['sockets'].remove(s) 
			del	metadatalist[i]['listeningports'][ind]
			del 	metadatalist[i]['peerids'][ind]
			del 	metadatalist[i]['listeningips'][ind]
			if not metadatalist[i]['sockets']:
				del metadatalist[i]


def remove_peerbyport(port):

	#print('remove by port')
	for i in range(0,len(metadatalist)):             # find swarms participating listening port and remove it
		if port in metadatalist[i]['listeningports']:
			ind=metadatalist[i]['listeningports'].index(port)
			metadatalist[i]['listeningports'].remove(port) 
			del	metadatalist[i]['sockets'][ind]
			if not metadatalist[i]['listeningports']:
				del metadatalist[i]
				


def create_metadata(dictionary):

	filename=dictionary['filename']+'.ant'
	metadata={'filename':filename
		,'filesize':dictionary['filesize']
		,'FileMd5':dictionary['FileMd5']}

	p_dict=pickle.dumps(metadata)
	
	try:
		f=open(filename,'wb')			
	except IOError as detail:
		print("Error Opening File: ",filename,":: ",detail)
		return _FILE_ERROR
	try:
		f.seek(0)      # move into apropriate position in file.
	except IOError as detail:
		print("Error Seeking File: ",filename,":: ",detail)
		f.close()
		return _FILE_ERROR
	try:
		f.write(p_dict)                       # write chunk
	except Exception as detail:
		print("Error Writting File: ",filename,":: ",detail)
		f.close()
		return _FILE_ERROR
	return _OK	


if __name__=='__main__':
	main()
