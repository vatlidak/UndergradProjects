#This module implements an Application Programming Interface allowing above 
#levels to establish connections between peers.
#Author: V. Atlidakis
#Date: March 2011
import socket
import UserLib
import bitmap
import SocketLevel


#This is a function taking as argument listening ports, listening ips, respective ids, connections map
#and index of current connection. It is sending a handshake message to respective peer and appends
#newly established connection to connections map. Uppon exception connection is not appended.
def establish_connection(listeningports,listeningips,peerids,connections,i):

	#try to create a socket and send a TCP connection request to each peer of the set.
	try:
		newsock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)  
		newsock.connect ((listeningips[i], listeningports[i]))
	#Uppon Exception close recently created socket and raise Exception.
	except socket.error:
		print("<establish_connection>:: Socket Error Unable to establish connection with peer at port:",listeningports[i])
		newsock.close()
		raise
	#Uppon Exception close recently created socket and raise Exception.
	except Exception as detail:
		print("<establish_connection>:: Unexpected exception Unable to establish connection with peer at port:",listeningports[i],":",detail)
		newsock.close()
		raise
	#Uppon success, append to connections map a tuple containing (socket, port, 
	#counter of blocks received, bitmap, peerid, and state info) of recently 
	#established connection.
	connections.append([newsock,listeningports[i],0,[],0,'choked','',listeningips[i],0])
	#create and send handshake message
	msg={'type':'handshake'
		,'metadata_hash':UserLib.metadata_hash
		,'peer_id':UserLib.mypeerid
	}
	try:
		SocketLevel.send_msg(len(connections)-1,-1,connections,msg, True)
	except Exception as detail: 
		print("<establish_connection>:: 1.Unable to establish connection with peer at port:",listeningports[i],":",detail)
		raise
	#receive handshake response
	try:	
		msg_r=SocketLevel.recv_msg(len(connections)-1, -1, connections, True)
	except Exception as detail:  
		print("<establish_connection>:: 2.Unable to establish connection with peer at port:",listeningports[i],":",detail)
		raise
	else:	
		#if not a handshake response received, ro peed id received is not valid.	
		if not msg_r['type'] == 'handshake_response' or not msg_r['peerid'] in peerids:
			print("------------------------>",msg_r)
			newsock.close()
			#remove socket from connections map.
			del connections[-1]
			raise UserLib.UnexpectedMessage
		else:	
			#keep peer id from last message.
			peerid=msg_r['peerid']
			#receive bitmap of recently appened peer.
			try:	
				msg_r=SocketLevel.recv_msg(len(connections)-1, -1, connections,True)
			except Exception as detail:  
				print("<establish_connection>:: 4.Unable to establish connection with peer at port:",listeningports[i],":",detail)
				raise
			if not msg_r['type'] == 'bitfield':
				newsock.close()
				#remove socket from connections map.
				del connections[-1]
				raise UserLib.UnexpectedMessage
			connections[-1][3]=msg_r['bmp']   
			connections[-1][4]=peerid
			#check if u are interested in blocks of this remote peer or not.
			try:
				connections[-1][6]=bitmap.interested(UserLib.bmp,msg_r['bmp'],msg_r['bmplen'],UserLib.lock)
			except Exception as detail:
				print("<establish_connection>:: 5.Unable to establish connection with peer at port:",listeningports[i],":",detail)
				#remove socket from connections map.
				del connections[-1]
				raise
			if connections[-1][6]=='uninterested':
				msg={'type':'uninterested'}	
			else:
				msg={'type':'interested'}
			#inform this remote peer if interested or not.
			try:
				SocketLevel.send_msg(len(connections)-1,-1,connections,msg,True)
			except Exception as detail: 
				print("<establish_connection>:: 6.Unable to establish connection with peer at port:",listeningports[i],":",detail)
				raise
		
		
