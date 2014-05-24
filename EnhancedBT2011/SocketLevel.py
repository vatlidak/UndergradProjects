#This module implements an Apllication Programming Interface allowing above 
#levels to send messages via sockets.
#Author: V. Atlidakis
#Date: March 2011
import pickle
import socket
import struct
import UserLib
import UserDefs
import UserLib
import time


#this is a function sending a created message via a socket of the map of established connections.
#The connection is indexed by connection_ind. Uppon  exception  connection is closed and removed 
#from connections map. Moreover if remove is "True" and connection_ind is not -1, meaning that we
#are not contacting tracker, pipelined requests respective to that connection should also removed.
def send_msg(connection_ind, tracker, connections, msg, RemoveRequests=False,timeout=UserDefs.SendTimeout):
	#index -1 indicates contacting coordinator.
	if connection_ind ==-1:
		s=tracker
		s.settimeout(UserDefs.TrackerTimeout)
	else:
		try:
			s=connections[connection_ind][0]
			s.settimeout(timeout)
		#Unable to index requested connection.
		except Exception as detail:
			raise
	try:
		pickledmsg = pickle.dumps ( msg )
		#header indicates the exact size of message.
		header=struct.pack("I",len(pickledmsg))
		mymsg=header+pickledmsg
		totalsent = 0
		msgsize=len(mymsg)
		while totalsent < msgsize: 
			try:
				totalsent+=s.send ( mymsg[totalsent:] )
			except Exception as detail:
				raise
	#Uppon Exception close and remove socket, respective requests and  raise exception.
	except socket.timeout as detail: 
		s.close()
		if not connection_ind==-1:
			#keep peer id of timed out peers so that not to re establish connection with them.
			if RemoveRequests == True:
				UserLib.TimedOutPeers.append([connections[connection_ind][1],connections[connection_ind][7]])
			#remove socket from connections map.	                            
			del connections[connection_ind]
			#If we are at Leecher thread and there are any pending
			#requests of recently removed peer, also delete them.
			if RemoveRequests == True:
				i=len(UserLib.requests)-1
				while i >= 0:
					if UserLib.requests[i][1] not in [ temp[4] for temp in connections ]:					
						del UserLib.requests[i]
					i-=1
		print("<send_msg>:: Socket Timeout:",detail)
		raise
	#Uppon Exception close and remove socket, respective requests and raise exception.
	except socket.error as detail: 
		s.close()
		if not connection_ind==-1: 
			#remove socket from connections map.	                            
			del connections[connection_ind]
			#If we are at Leecher thread and there are any pending
			#requests of recently removed peer, also delete them.
			if RemoveRequests == True:
				i=len(UserLib.requests)-1
				while i >= 0:
					if UserLib.requests[i][1] not in [ temp[4] for temp in connections ]:					
						del UserLib.requests[i]
					i-=1
		print("<send_msg>:: Socket Error:",detail)
		raise
	#Uppon Exception close and remove socket, respective requests and  raise exception.
	except Exception as detail:
		s.close()
		if not connection_ind==-1: 
			#remove socket from connections map.	                            
			del connections[connection_ind]
			#If we are at Leecher thread and there are any pending
			#requests of recently removed peer, also delete them.
			if RemoveRequests == True:
				i=len(UserLib.requests)-1
				while i >= 0:
					if UserLib.requests[i][1] not in [ temp[4] for temp in connections ]:					
						del UserLib.requests[i]
					i-=1
		print("<send_msg>:: Unexpected Exception:",detail)
		raise
	UserLib.MessagesSent+=1
	if msg['type']=='block':
		UserLib.BlocksSent+=1
		UserLib.Uploading_t.append([time.time(),UserLib.BlocksSent])
	elif msg['type']=='interested':
		UserLib.InterestedSent+=1
	elif msg['type']=='uninterested':
		UserLib.UninterestedSent+=1

#this is a function receiving a message via a socket of the map of established connection.
#The connection is indexed by connection_ind. Uppon exception connection is closed and removed 
#from connections map. Moreover if remove is "True" and connection_ind is not -1, meaning that we
#are not contacting tracker, pipelined requests respective to that connection should also removed.
def recv_msg(connection_ind, tracker, connections, RemoveRequests=False,timeout=UserDefs.RecvTimeout):
	#index -1 indicates contacting coordinator.
	if connection_ind ==-1:
		s=tracker
		s.settimeout(UserDefs.TrackerTimeout)
	else:
		try:
			s=connections[connection_ind][0]
		#Unable to index requested connection.
		except Exception as detail:
			raise
		s.settimeout(timeout)	
	#Initially retrieve header, informing the exact size of message.
	#In this way we guarantee that "recv call" receives all bytes of
	#message send by the respective "send call" or an exception is raised.
	try:
		header=s.recv ( struct.calcsize('I') )
		#conection is closed at the other end
		if not header:
			raise  UserLib.ConnectionResetedByPeer	
		else:
			msgsize=struct.unpack("I",header)[0]
		data=b""
		#receive all remaining bytes of message
		while msgsize>0:
			try:
				newdata=s.recv ( msgsize )
			except Exception as detail:
				raise
			if not newdata:
				raise  UserLib.ConnectionResetedByPeer
			data+=newdata
			msgsize-=len(newdata)
		msg=pickle.loads(data)
	#Uppon Exception close and remove socket, respective requests and raise exception.
	except UserLib.ConnectionResetedByPeer:
		s.close()
		if not connection_ind==-1: 
			#remove socket from connections map.	                            
			del connections[connection_ind]
			#If we are at Leecher thread and there are any pending
			#requests of recently removed peer, also delete them.
#			if RemoveRequests == True:
#				i=len(UserLib.requests)-1
#				while i >= 0:
#					if UserLib.requests[i][1] not in [ temp[4] for temp in connections ]:					
#						del UserLib.requests[i]
#					i-=1
			print("<recv_msg>:: Connection Reseted by peer.",time.time())
		else:
			print("<recv_msg>:: Connection Reseted by tracker.",time.time())
		raise 
	#Uppon Exception close and remove socket, respective requests and raise exception.
	except socket.timeout as detail: 
		s.close()     
		if not connection_ind==-1:
			if RemoveRequests == True:
				#keep peer id of timed out peers so that not to re establish connection with them.
				UserLib.TimedOutPeers.append([connections[connection_ind][1],connections[connection_ind][7]])
			#remove socket from connections map.	                            
			del connections[connection_ind]
			#If we are at Leecher thread and there are any pending
			#requests of recently removed peer, also delete them.
#			if RemoveRequests == True:
#				i=len(UserLib.requests)-1
#				while i >= 0:
#					if UserLib.requests[i][1] not in [ temp[4] for temp in connections ]:					
#						del UserLib.requests[i]
#					i-=1
		print("<recv_msg>:: Socket Timeout: ",detail,time.time())
		raise  
	#Uppon Exception close and remove socket, respective requests and raise exception.
	except socket.error as detail: 
		s.close()    
		if not connection_ind==-1: 	      
			#remove socket from connections map.	                            
			del connections[connection_ind]
			#If we are at Leecher thread and there are any pending
			#requests of recently removed peer, also delete them.
#			if RemoveRequests == True:                      
#				i=len(UserLib.requests)-1
#				while i >= 0:
#					if UserLib.requests[i][1] not in [ temp[4] for temp in connections ]:
#						del UserLib.requests[i]
#					i-=1
		print("<recv_msg>:: Socket Error: ",detail,time.time())
		raise
	#Uppon Exception close and remove socket, respective requests and raise exception.
	except Exception as detail:
		s.close()    
		if not connection_ind==-1: 
			#remove socket from connections map.	                            
			del connections[connection_ind]
			#If we are at Leecher thread and there are any pending
			#requests of recently removed peer, also delete them.
#			if RemoveRequests == True:
#				i=len(UserLib.requests)-1
#				while i >= 0:
#					if UserLib.requests[i][1] not in [ temp[4] for temp in connections ]:					
#						del UserLib.requests[i]
#					i-=1
		print("<recv_msg>:: Unexpected Exception:",detail,time.time())
		raise
	if msg['type'] == 'interested':
		UserLib.InterestedReceived+=1
		UserLib.InterestedMsgReceived_t.append([time.time(),UserLib.InterestedReceived])
	elif msg['type']=='uninterested':
		UserLib.UninterestedReceived+=1
	elif msg['type'] == 'block':
		UserLib.Downloading_t.append([time.time(),UserLib.PiecesDownloaded]) 
	elif msg['type'] == 'unchoke':
		interested=0
		for s in UserLib.UpConn_map:
			if s[4]=='interested':
				interested+=1

		if msg['mode'] == 'reg':
			UserLib.RegUnchokesReceived+=1
			UserLib.OptUnchokeTimes.append([time.time(),interested,UserLib.PiecesDownloaded,UserLib.BlocksSent,UserLib.RegUnchokesReceived])
		else:
			UserLib.OptUnchokesReceived+=1
			UserLib.InterestedPeersAtOpt+=interested
			UserLib.RegUnchokeTimes.append([time.time(),interested,UserLib.PiecesDownloaded,UserLib.BlocksSent,UserLib.OptUnchokesReceived])
	return msg

