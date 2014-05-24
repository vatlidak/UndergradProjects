#This module implements the Leecher thread of our client.
#Author: V. Atlidakis
#Date: March 2011
import pickle
import sys, socket, threading
import math, time, random
import select
import bitmap
import mymd5 
import mysha1lib
import queue
import UserDefs
import UserLib
import myuuidlib
import SocketLevel
import ConnectionLevel


class LeecherThread ( threading.Thread ):


	def __init__(self,filesize,FileMd5,filename,listeningport,listeningip,tracker,name="LeecherThread"):

		threading.Thread.__init__(self)
		self.name=name					#name of thread
		self.FileMd5=FileMd5				#md5 of requested file
		self.filename=filename				#name of requested file
		self.filesize=filesize				#size of requested file
		self.listeningport=listeningport		#port listening for TCP connections requests.
		self.listeningip=listeningip			#ip listening for TCP connections requests.
		self.listeningports=[]				#listening ports of peer in swarm.
		self.listeningips=[]				#listening ips of peer in swarm.
		self.peerids=[]					#peer ids of peers in swarm.
		UserLib.DownConn_map=[]				#map of downloading connections
		self.tracker=tracker				#tacker port.
		self.unchokes=0

	def run ( self ):
		print("my peer id:",UserLib.mypeerid)
		#keep beginning time
		self.begtime=time.time()    
		random.seed(time.time())#self.begtime)
		#try to open file to write received chunks.                                                      
		try:
			self.f=open(self.filename,'wb') 
		#Uppon Exception, make clen up job and terminatethread.                  
		except IOError as detail:
			print("IOError at Leecher thread:",detail)
			self.terminate()
			return
		#Uppon Exception, make clen up job and terminate thread.
		except  Exception as detail:
			print("0.Unexpected exception in Leecher thread:",detail)
			self.terminate()
			return	
		#while thread should not terminate.
		t=self.begtime
		while UserDefs.Run:
			#If there are no peers in peer set, new connections should be established.
			#THIS WILL BE DONE IF CONNECTIONS ARE LESS THAN A THREASHOLD.
			if time.time()-t > UserDefs.PeerListReqInterval or not UserLib.DownConn_map:
				t=time.time()
				if not UserLib.DownConn_map:
					print("Empty connections")
				try:
					self.establish_connections()
				except UserLib.EstablishConnError as detail:
					print("establish connections error at Leecher thread:",detail)
					time.sleep(UserDefs.PeerListReqInterval)
					continue
				except UserLib.TerminateThread:
					break
				except Exception as detail:
					print("2.Unexpected Exception in Leecher thread:",detail)
					time.sleep(UserDefs.PeerListReqInterval)
					continue
			#NOW WE HAVE AS MUCH AS MAXDOWNCONN established connections and tokens to send requests.
			#but connections are choked.So watch the set to receive unchoke messages.
			self.sockset=[ temp[0] for temp in UserLib.DownConn_map ]
			try:
				inputready, outputready, exceptionready = select.select(self.sockset,[],[],UserDefs.SelectTimeout)
			except (ValueError, select.error) as detail:
				print("Select Exception in Leecher thread:",detail)
				continue
			#1.) In case a descripitor from your set has data that is state oriented msg. 
			for s in inputready:
				#find position of socket having data into downloading connections map
				try:
					ind=[ temp[0]==s for temp in UserLib.DownConn_map].index(True)
				except ValueError as detail:
					print("Value Error at Leecher Thread:",detail,s)
					continue
				#try to receive message via socket indexed by ind.
				try:
					UserLib.SocketLock.acquire()
					self.msg_r=SocketLevel.recv_msg(ind, -1, UserLib.DownConn_map,True)
				#Uppon Exception socket indexed by ind had been removed from "recv_msg".	
				except UserLib.ConnectionResetedByPeer:
					print("3.ConnectionResetedByPeer in Leecher thread:")
					continue
				except Exception as detail:
					print("3.Unexpected Exception in Leecher thread:",detail)
					continue
				finally:
					UserLib.SocketLock.release()
				try:
					msgtype=self.msg_r['type']
				except Exception as detail:
					print("4.Unexpected Exception in Leecher thread:",detail)
					continue
				if msgtype == 'unchoke':
					if self.unchokes == 0:
						print("First unchoke after:%.2f"%(time.time()-self.begtime),"seconds")
					self.unchokes+=1
					UserLib.DownConn_map[ind][5]='unchoked'
				elif msgtype == 'choke':
					UserLib.DownConn_map[ind][5]='choked'
					#delete pending requests to chocking remote peer.
					UserLib.requests=[ r for r in UserLib.requests if not r[1] == UserLib.DownConn_map[ind][4]]
				elif msgtype == 'have':
					#update bitmap of peer having a new piece
					try:
						bitmap.bmp_setvalid(UserLib.DownConn_map[ind][3],self.msg_r['chunkno'],-1)
						#check if you are interested in this peer
						state=bitmap.interested(UserLib.bmp,UserLib.DownConn_map[ind][3],UserLib.BMPLENGTH,UserLib.lock)
						#if there is a change in your state about this peer
					except Exception:
						continue
					if UserLib.DownConn_map[ind][6]== 'uninterested' and state=='interested':
						#inform your map
						UserLib.DownConn_map[ind][6]=state
						#inform remote peer
						try:
							self.interested()
							UserLib.SocketLock.acquire()
							SocketLevel.send_msg(ind,-1,UserLib.DownConn_map,self.msg,True)
						except Exception as detail:
							print("5.Unexpected Exception in Leecher thread:",detail)
							continue
						finally:
							UserLib.SocketLock.release()
				#if received message is "block respose" 
				#try to write block to resective position in file.:
				elif msgtype == 'block':
					chunkno=self.msg_r['chunkpos']
					try:
						self.block(ind,self.msg_r)
					#Exception indication requested block is not available
					#to peer last request was send.
					except UserLib.BlockCorrupted:
						print("6.BlockCorrupted in Leecher thread:")
						continue
					except UserLib.UnexpectedBlock:
						#print("6.UnexpectedBlock in Leecher thread:")
						continue
					#Uppon Exception Terminate thread
					except Exception as detail:
						print("6.Unexpected Exception in Leecher thread:",detail)
						continue
					self.have(chunkno)
					try:
						UserLib.SocketLock.acquire()
						SocketLevel.send_msg(ind,-1,UserLib.DownConn_map,self.msg,True)
					except Exception as detail:
						print("7.1.Unexpected Exception in Leecher thread:",detail)
						continue
					finally:
						UserLib.SocketLock.release()
					i=len(UserLib.UpConn_map)-1
					UserLib.SocketLock.acquire()
					while i >=0:
						try:
							if UserLib.DownConn_map[ind][4]==UserLib.UpConn_map[i][2]:
								i-=1
								continue
						except Exception as detail:
							i-=1
							print("7.1.2.Unexpected Exception in Lecher thread:",detail,ind,UserLib.UpConn_map,UserLib.DownConn_map)
							continue
						#inform all downloaders directly conected to you that you
						#receive a new piece.
						try:
							#UserLib.SocketLock.acquire()
							SocketLevel.send_msg(i,-1,UserLib.UpConn_map,self.msg)
						except Exception as detail:
							i=len(UserLib.UpConn_map)-1
							print("7.2.Unexpected Exception in Lecher thread:",detail,i,len(UserLib.UpConn_map))
						else:
							i-=1
						#finally:
						#	UserLib.SocketLock.release()	
					UserLib.SocketLock.release()
					for i in range(0,len(UserLib.DownConn_map)):		
						try:
							state=bitmap.interested(UserLib.bmp,UserLib.DownConn_map[i][3],UserLib.BMPLENGTH,UserLib.lock)
						except Exception:
							continue
						if UserLib.DownConn_map[i][6]=='interested' and state=='uninterested':
							UserLib.DownConn_map[i][6]=state
							try:
								#print("here",UserLib.DownConn_map,UserLib.bmp)
								self.uninterested()
								UserLib.SocketLock.acquire()
								SocketLevel.send_msg(i,-1,UserLib.DownConn_map,self.msg,True)
							except Exception as detail:
								print("9.Unexpected Exception in Leecher thread:",detail)
								continue
							finally:
								UserLib.SocketLock.release()
			#select block and uploader.
			try:
				ind, self.blockno =self.select_block()
			except UserLib.FileCompletelyDownloaded:
				break
			except  UserLib.AllConnectionsChoked:
				#print("11.AllConnectionsChoked or unintetresting in Leecher thread")
				continue
			except  UserLib.MaxRequestsSent:
				#print("11.MaxRequestsSent in Leecher thread")
				continue
			except Exception as detail:
				print("11.Unexpected Exception in Leecher thread:",detail)
				break
			#if it is a pending block request, dont do anything.
			#prepare request for the selected block.
			self.request(self.blockno)
			try:
				UserLib.SocketLock.acquire()
				SocketLevel.send_msg(ind,-1,UserLib.DownConn_map,self.msg,True)
			except Exception as detail:
				print("12.Unexpected Exception in Leecher thread:",detail)
				continue
			else:
				UserLib.requests.append([self.blockno,UserLib.DownConn_map[ind][4],0])
			finally:
				UserLib.SocketLock.release()
		#while Run
		#make "clen up" job and terminate thread.
		self.terminate()
		return


	#This is a function selecting which block going to request and from which uploader.
	def select_block(self):

		#aging pipelined requests.
		for i in range(0,len(UserLib.requests)):
			UserLib.requests[i][2]+=1
		if UserLib.PiecesDownloaded == UserLib.BMPLENGTH:
			raise UserLib.FileCompletelyDownloaded	
		#if there is no space to send new requests, delete aged requests.
		elif len(UserLib.requests) == UserDefs.MaxPendingReq:
			UserLib.requests=[ r for r in UserLib.requests if r[2] < UserDefs.AgedRequestLimit]
			raise UserLib.MaxRequestsSent
		#print("-----------------------------------------")
		#for i,con in enumerate(UserLib.DownConn_map):
		#	print("connection:",i,con[3],con[5],con[6])
		#print("-----------------------------------------")
		ind=-1
		chunks_available=[]
		#for each chunk append to list: [its occurence, its number, ind of connections that has this chunk]. 		
		for i in range(0,UserLib.BMPLENGTH):
			chunks_available.append([0,i,[]])
		for i in range(0,len(UserLib.DownConn_map)):
			if UserLib.DownConn_map[i][6]=='interested' and UserLib.DownConn_map[i][5]=='unchoked':
				for j in range(0,UserLib.BMPLENGTH):
					if bitmap.bmp_isvalid(UserLib.DownConn_map[i][3],j,-1):
						ind=1
						chunks_available[j][0]+=1
						chunks_available[j][2].append(i)
		#########################################################################################
		#  In example: [[2, 0, [0, 2]], [3, 1, [0, 1, 2]], [3, 2, [0, 1, 2]], [2, 3, [1, 2]]]	#
		#											#
		#  2 connections: 0,2   have piece 0							#
		#  3 connections: 0,1,2 have piece 1							#
		#  3 connections: 0,1,2 have piece 2							#
		#  2 connections: 1,2   have piece 3							#
		#										    	#	
		#  After sort: [[2, 0, [0, 2]], [2, 3, [1, 2]], [3, 1, [0, 1, 2]], [3, 2, [0, 1, 2]]]	#
		#########################################################################################
		#if there is no connection to send block request.
		if ind == -1:		
			raise UserLib.AllConnectionsChoked
		#Random Policy
		#for the first chunks:
		#find a random chunk from list 	
		#if you do have it or noone else has it, choose another one.
		#Repeat till you find a chunk some peers have but you don't.
		if UserLib.PiecesDownloaded < UserDefs.RandomChunks:
			i=random.randint(0,len(chunks_available)-1)
			for reps in range(0,len(chunks_available)):
				try:
					isvalid=bitmap.bmp_isvalid(UserLib.bmp,chunks_available[i][1],UserLib.lock)
				except exception as detail:
					print("<select_block>: ",i,detail)
					raise
				if not isvalid and chunks_available[i][0]>0 and chunks_available[i][1] not in [r[0] for r in UserLib.requests]:
					return random.choice(chunks_available[i][2]), chunks_available[i][1]
				i=(i+1)%len(chunks_available)
		else:
			chunks_available.sort()	
			#Rarest First policy
			#chunks are sorted increasingly according to their occurence
			#request the rarest chunk that you dont have, from a randlom 
			#peer that posses it.
			if UserLib.BMPLENGTH-UserLib.PiecesDownloaded > UserDefs.MaxPendingReq:	
				for i in range(0,UserLib.BMPLENGTH):
					isvalid=bitmap.bmp_isvalid(UserLib.bmp,chunks_available[i][1],UserLib.lock)
					if not isvalid and chunks_available[i][0]>0 and chunks_available[i][1] not in [r[0] for r in UserLib.requests]:
						return random.choice(chunks_available[i][2]), chunks_available[i][1]
			#if less than MaxPendingReq pieces remain
			#request to everyone.
			#End Game Mode LIKE
			else:
				for i in range(0,UserLib.BMPLENGTH):
					isvalid=bitmap.bmp_isvalid(UserLib.bmp,chunks_available[i][1],UserLib.lock)
					if not isvalid and chunks_available[i][0]>0:
						return random.choice(chunks_available[i][2]), chunks_available[i][1]
		raise UserLib.MaxRequestsSent
	

	#this is a function creating  an "interested" message.
	def interested(self):

		self.msg={'type':'interested'}
		

	#this is a function creating  an "interested" message.
	def have(self,chunkno):

		interested=0
		for i in range(0, len(UserLib.UpConn_map)):
			if UserLib.UpConn_map[i][4] == 'interested':
				interested+=1
		self.msg={'type':'have'
		,'chunkno':chunkno
		,'interested':interested
		}
		#print("-->",interested)


	#this is a function creating  an "uninterested" message.
	def uninterested(self):

		self.msg={'type':'uninterested'
		}					


	#this is a function creating a request for "blockno" block
	def request(self,blockno):
		self.msg={'type':'request'
			,'chunkpos':blockno
		}
		


	#create a peer request message to the coordinator.
	#this message include the file id of the requested file,
	#so the coordinator will respond with a set of peers
	#related to that file.
	def peer_request(self):
			
		self.msg={'type':'peer_request',
			  'FileMd5':self.FileMd5	##~~~~> FILE IDENTIFIER SHOULD BE USED.		
		}


	#this is a function creating a handshake message.
	#the sender of a handshake includes file identifier
	#of requested file.
	def handshake(self):

		self.msg={'type':'handshake'
			,'metadata_hash':UserLib.metadata_hash
			,'peer_id':UserLib.mypeerid
		}
		

	#this is a function writing into file a newly received block.
	#exception is raised, if occurred.
	def block(self,connection_ind,msg):

		#IF BLOCK IF FOUND THIS WILL BE REMOVED
		#and it is not corrupted, try to write it to 
		#the respective position in file,].
		l=-1
		for s in UserLib.requests:
			if s[0] == msg['chunkpos']:
				l=0
				UserLib.requests.remove(s)
				break
		if l == -1 or bitmap.bmp_isvalid(UserLib.bmp,msg['chunkpos'],UserLib.lock) :
			raise UserLib.UnexpectedBlock
		if mysha1lib.mysha1(msg['chunk'])==UserLib.sha1s_map[msg['chunkpos']]:
			try:
				self.f.seek(int(msg['chunkpos'])*UserDefs.PieceSize) 
				self.f.write(msg['chunk'])                       
			#if an Exception occurs close file stream and raise it.
			except IOError as detail:
				print("<block>:: File Error at Leecher thread:",detail)
				self.f.close()
				raise
			#if an Exception occurs close file stream and raise it.
			except Exception as detail:
				print("<block>:: Unexpected Exception :",detail)
				self.f.close()
				raise
			try:
				# mutual exclusion before informing bitmap.
				bitmap.bmp_setvalid(UserLib.bmp,msg['chunkpos'],UserLib.lock)
			except Exception as detail:
				print("<block>:: Unexpected Exception while setting bitmap:",detail)
				raise
			# increase chunks downloaded from current connection.
			UserLib.DownConn_map[connection_ind][2]+=1 
			UserLib.DownConn_map[connection_ind][8]=time.time()
			# inclease total chunks downloaded.                       
			UserLib.PiecesDownloaded+=1   
			sys.stderr.flush()
			sys.stderr.write("%.2f%%\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b"%(100*UserLib.PiecesDownloaded/UserLib.BMPLENGTH))
		else:
			print("Received corrupted block")
			raise UserLib.BlockCorrupted
	

	#this is a function receiving peer set from coordinator.
	def get_peerset(self):
	
		#remove port's and ip's from your set.
		self.listeningports=[]
		self.listeningips=[]
		#request a new peer set.
		while UserDefs.Run:
			#prepare message
			self.peer_request()
			#try to send it to coordinator
			try:
				SocketLevel.send_msg(-1, self.tracker, [], self.msg)
			except Exception as detail:
				print("<get_peerset>:: 1.Exception while contacting coordinator.:",detail)
				raise
			#receive request from coordinator
			try:	
				msg=SocketLevel.recv_msg(-1, self.tracker, [])					
				#for each peer of the received set keep its ip,port and id.
				self.listeningports=msg['listeningports']
				self.listeningips=msg['listeningips']
				self.peerids=msg['peerids']
				i=len(self.listeningports)-1
				while i>=0:
					if self.listeningports[i] in [ temp[0] for temp in UserLib.TimedOutPeers ] \
					and self.listeningips[i]  in [ temp[1] for temp in UserLib.TimedOutPeers ]:
						del self.listeningports[i]
						del self.listeningips[i]
						del self.peerids[i]
					i-=1
				#if identifier of current peer is present in received set
				try:
					mypos=self.peerids.index(UserLib.mypeerid)
				except ValueError as detail:
					print("<get_peerset>::wtf???",detail)
					pass
				#remove it, and its ip and its port, since it is useless to try
				#to establish connection with tself.
				else:
					del self.listeningports[mypos]
					del self.listeningips[mypos]
					del self.peerids[mypos]
			#Uppon Exception raise it
			except Exception as detail:
				print("<get_peerset>:: 2.Exception in while contacting coordinator.",detail)
				raise
			if not self.listeningports:
				#if there is no peer in swarm wait 15 seconds 
				#before you ask again a list of listening peers.
				time.sleep(UserDefs.PeerListReqInterval)
			else:	
				break
		#print("--------------")
		#print('active peer set:','\n',self.listeningports,'\n',self.listeningips,'\n',self.peerids)
		#print("-------------")
		if not UserDefs.Run:
			raise UserLib.TerminateThread
			return
			
	#This is a function establishing as many as MAXDOWNCONN connections.
	def establish_connections(self):

		#get peer set.
		try:
			self.get_peerset()
		except Exception as detail:
			print("<establish_connections>:: Error while getting peer set:",detail)
			raise
		if self.listeningports:
			beg=random.randint(0,len(self.listeningports)-1)
		#if we reach this point of execution, we have a set of peers to try to connect with.
		for i in range(0,len(self.listeningports)):
			if len(UserLib.DownConn_map)>UserDefs.ActiveSetSize:
				break 
			#if current peer identifier is not in the list of connected peers' id
			#try to establish connection, since it's a new peer.
			if self.peerids[beg] not in [ temp[4] for temp in UserLib.DownConn_map ]:
				try:
					ConnectionLevel.establish_connection(self.listeningports,self.listeningips,self.peerids,UserLib.DownConn_map,beg)
				except  UserLib.UnexpectedMessage:
					continue
				except Exception as detail:
					print("<establish_connections>:: Unexpected Exception:: ",detail)
					continue
				else:
					print('connection established with peer at',self.listeningips[beg],'and port',self.listeningports[beg])
			beg=(beg+1)%len(self.listeningports)
		if not UserLib.DownConn_map:
			print("No connection established, though an active peer set received from coordinator.")
			raise UserLib.EstablishConnError
	

	#this is a fuction making the "clean up" job.
	def terminate(self):
		
		print('Downloading time:{0:.3f} seconds.'.format(time.time()-self.begtime))
		for i in range(0,len(UserLib.DownConn_map)):
			print('from:',UserLib.DownConn_map[i][1]," ",UserLib.DownConn_map[i][7],'received',(UserLib.DownConn_map[i][2]),'chunks')
			UserLib.DownConn_map[i][0].close()
		print("Pieces downloaded:",UserLib.PiecesDownloaded)
		UserLib.DownConn_map=[]
		UserLib.requests=[]
		#close file.		
		self.f.close()
		#reopen file to check if successfully downloaded.				
		#THIS WILL BE REMOVED
#		try:
#			self.f=open(str(self.listeningport)+self.filename,'rb')
#		except IOError as detail:
#			print("IOError <terminate> at Leecher thread:",detail)
#			return
#		except Exception as detail:
#			print("<terminate>:: Unexpected Exception:",detail)
#			return
#		if mymd5.mymd5_file(self.f,1000*4096) == self.FileMd5:                             
#			print('\n\n\n############################\nFile successfully downloaded\n############################\n\n\n')
#		else:
#			print('\n\n\n################################\nFile NOT successfully downloaded\n################################\n\n\n')
#		self.f.close()
		print(self.getName()," is going to terinate")
		sys.stderr.flush()
		sys.stderr.writelines("downloading over\n")
		return


