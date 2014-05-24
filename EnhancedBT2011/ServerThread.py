#This module implements the Server thread of our client.
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


#ServerThread is receiving incoming requestes and sending outgoing 
#responses related to that peer, ON THE SCOPE OF UPLOADER.
class ServerThread ( threading.Thread ):                                       
	
	#Constructor 
	def __init__(self,filesize,FileMd5,filename,listeningport,listeningip,mode,choice,tracker,name="Serving Thread"):

		threading.Thread.__init__(self)
		self.name=name					#name of thread
		self.listeningport=listeningport		#port listening for TCP connections requests.
		self.listeningip=listeningip			#ip listening for TCP connections requests.
		self.filesize=filesize				#size of served file.
		self.FileMd5=FileMd5				#md5 of served file.
		self.filename=filename				#name of served file.
		self.unchokeflag=0				#flag used for unchocking.
		self.timer=threading.Timer(UserDefs.UnchokeInterval,self.unchoke)
		self.criticaldecisions=0
		self.plannedOpt=[]
		self.seedkeptunchoked=[]
		self.unchokeinvoked=0
		self.lastunchoketime=0
		self.mode=mode
		self.choice=choice
		self.tracker=tracker

	def run (self):
		random.seed(time.time())
		#create a socket, bind it to your listening ip and port 
		#in order to listen for incoming TCP connection requests.
		try:
			server = socket.socket ( socket.AF_INET, socket.SOCK_STREAM )   
			server.setsockopt(socket.SOL_SOCKET,socket.SO_REUSEADDR,1)
			server.bind((self.listeningip, self.listeningport))
			server.listen ( 1 )
		#Uppon Exception close listening socket and terminate thread.
		except (socket.error,socket.gaierror,OverflowError) as detail:
			print("Listening Socket error:",detail)
			server.close()
			UserDefs.Run=False
			return			
		#Open file to seed.
		try:
			self.f=open(self.filename,'rb')
		except IOError as detail:
			print("IOError Opening File",detail)
			self.terminate()
		except Exception as detail:
			print("Unexpected Exception opening file at server thread:",detail)
			self.terminate()
		#Loop forever
		while UserDefs.Run:
			self.sockset=[ temp[0] for temp in UserLib.UpConn_map ]
			if len(UserLib.UpConn_map)==UserDefs.ActiveSetSize:
				#print("max size")
				self.sockset=self.sockset+[sys.stdin]
			else:
				self.sockset=self.sockset+[server,sys.stdin]
			# wait till a socket has data.
			try:
				inputready, outputready, exceptionready = select.select(self.sockset,[],[])
			except ValueError as detail:
				print("select at server thread:",detail,self.sockset)		
			#search on which socket there are available data.
			for s in inputready:
				#if it is in server socket, it is a TCP connection request.
				if s == server:
					if len(UserLib.UpConn_map)==UserDefs.ActiveSetSize:
						continue
					try:
						conn, addr=server.accept()
						conn.setsockopt(socket.SOL_SOCKET,socket.SO_REUSEADDR,1)
					except socket.timeout:
						print("timeout")
						pass
					except Exception as detail: 	
						print("Accepting connection error:",detail)
					#Uppon success, append socket into watched set.	
					#append socket, peer ip and port, peer id and connection's
					#state info to Uploading connections map.
					else:
						#if len(UserLib.UpConn_map)>=UserDefs.ActiveSetSize:
						#	print("here")
						#	conn.close()
						#	continue						
						self.sockset.append(conn)
						UserLib.UpConn_map.append([conn,conn.getpeername(),0,'choked','uninterested',False,0,0,0])
				elif s == sys.stdin:
					##command = s.readline()
					##if command == 'quit\n':
					UserDefs.Run=False
					break
				#otherwise there are data in socket of an established connection.
				else:	
					#find position of current socket into uploading connections map
					try:
						ind=[ temp[0]==s for temp in UserLib.UpConn_map].index(True)
					except ValueError as detail:
						print("Unable to index connection at server Thread:",detail,s)
						continue
					#try to receive message via socket indexed by ind.
					try:
						UserLib.SocketLock.acquire()
						self.msg_r=SocketLevel.recv_msg(ind, -1, UserLib.UpConn_map)
					#Uppon Exception socket indexed by ind had been removed from "recv_msg".
					except UserLib.ConnectionResetedByPeer:
						print("2. ConnectionResetedByPeer at Server Thread:")
						UserLib.SocketLock.release()
						self.unchoke()
						continue	
					except Exception as detail:
						print("2. Unexpected exception at Server Thread:",detail)
						UserLib.SocketLock.release()
						self.unchoke()
						continue
					else:
						UserLib.SocketLock.release()
					try:
						msgtype = self.msg_r['type']
					except Exception as detail:
						print("Key error at Server Thread:",detail)
						self.unchoke()
						continue
					#if message is a "block request"
					if msgtype == 'request':
						#create and send response via socket s.
						try:
							self.block(self.msg_r)
							UserLib.SocketLock.acquire()
							SocketLevel.send_msg(ind,-1,UserLib.UpConn_map,self.msg)
							UserLib.UpConn_map[ind][7]+=1
						#Uppon Exception socket indexed by ind had been removed from "send_msg".
						except Exception as detail:
							print("3. Unexpected exception at Server Thread:",detail)
							UserLib.SocketLock.release()
							self.unchoke()
							continue
						else:
							UserLib.SocketLock.release()
					#if message is a "handshake request"
					elif msgtype == 'handshake':
						#check file id of requested file.
						#Connection should be closed	
						if not self.msg_r['metadata_hash'] == UserLib.metadata_hash :
							print("Unable to seed requested file")
							s.close()
							del UserLib.UpConn_map[ind]
							continue	
						#response including peer id of current peer.
						try:
							self.handshake_response()
							UserLib.SocketLock.acquire()
							SocketLevel.send_msg(ind,-1,UserLib.UpConn_map,self.msg)
						#Uppon Exception socket indexed by ind had been removed from "send_msg".
						except Exception as detail:
							print("4. Unexpected exception at Server Thread:",detail)
							UserLib.SocketLock.release()
							self.unchoke()
							continue
						else:
							UserLib.SocketLock.release()
						#send bitmap to remote peer.
						try:
							self.bitfield()
							UserLib.SocketLock.acquire()
							SocketLevel.send_msg(ind,-1,UserLib.UpConn_map,self.msg)
						#Uppon Exception socket indexed by ind had been removed from "send_msg".
						except Exception as detail:
							print("5. Unexpected exception at Server Thread:",detail)
							UserLib.SocketLock.release()
							self.unchoke()
							continue
						else:
							UserLib.SocketLock.release()
						UserLib.UpConn_map[ind][5]=True
						try:
							print('\nNew Leecher:',s.getpeername(),"#accepted connections:",len(UserLib.UpConn_map)," ",time.time())
						except Exception as detail:
							print("5.1 Unexpected exception at Server Thread:",detail)
							pass
						#and add peer identifier after a successful handshake.
						UserLib.UpConn_map[ind][2]=self.msg_r['peer_id']
					elif msgtype == 'interested':
						UserLib.UpConn_map[ind][4]='interested'	
						if UserLib.UpConn_map[ind][5]=='unchoked':
							self.unchoke()
						if self.unchokeinvoked == 0:
							self.unchoke()
							self.unchokeinvoked=1
					elif msgtype == 'uninterested':
						UserLib.UpConn_map[ind][4]='uninterested'
						if UserLib.UpConn_map[ind][3]=='unchoked':
							self.unchoke()
					#acknowledgment received.
					elif msgtype == 'have':
						UserLib.UpConn_map[ind][6]=self.msg_r['interested']
						#iii=[]
						#for i in range(0,len(UserLib.UpConn_map)):
						#	if UserLib.UpConn_map[i][4]=='interested':
						#		iii.append(UserLib.UpConn_map[i][6])
						#print("iii:",iii)
						continue
					#unexpected message.				
					else:
						print('Unexpected message type:',msgtype)
						continue	
		#make "clean up" job.	
		self.terminate()
		return


	#this is a function creating  a "choke" message.
	def choke(self):
	
		self.msg={'type':'choke'}


	# this is a functin applying unchocking policy.
	def unchoke(self):
		#reset timer
		self.timer.cancel()
		##if there are active connections to your uploading set cancel and reset unchoke.
		if not UserLib.UpConn_map:
			self.unchokeflag=0
			self.unchokeinvoked=0
			return
		UserLib.SocketLock.acquire()
		
		if self.mode == 'seed':
			suggestedOpt=-1
			mymin=10000
			#remote peers (downloaders) that were recently (less than 20 seconds) unchoked
			remotedownloaders1=[]	
			#rest of remote peer
			remotedownloaders2=[]			
			curtime=time.time()			
			for i in range(0,len(UserLib.UpConn_map)):
				unchoketime=UserLib.UpConn_map[i][8]
				if curtime-unchoketime<UserDefs.RecentUnchokeInterval:
					remotedownloaders1.append([unchoketime,i])
				else:
					remotedownloaders2.append([UserLib.UpConn_map[i][7],i])
				if UserLib.UpConn_map[i][6]<mymin:
					mymin=UserLib.UpConn_map[i][6]
					suggestedOpt=[0,i]
			remotedownloaders1.sort(reverse=True)
			remotedownloaders2.sort(reverse=True)
			remotedownloaders=remotedownloaders1+remotedownloaders2
			if self.unchokeflag in [0,1]:
				if time.time()-self.lastunchoketime>=3*UserDefs.UnchokeInterval:
					self.lastunchoketime=time.time()
					if self.choice == 'optimistic':
						self.plannedOpt=random.choice(remotedownloaders)
					elif self.choice == 'optimal':
						self.plannedOpt=suggestedOpt
					
					try:
						peerpos=self.plannedOpt[1]
						UserLib.UpConn_map[peerpos][3]='unchoked'
						SocketLevel.send_msg(peerpos,-1,UserLib.UpConn_map,{'type':'unchoke','mode':'opt'})
						UserLib.UpConn_map[peerpos][8]=time.time()
					except Exception as detail:
						print("<unchoke>::1.Unexpected exception: ",detail) 
				for i in range(0,len(remotedownloaders)):
					peerpos=remotedownloaders[i][1]
					if not self.plannedOpt:
						continue
					elif self.plannedOpt[1]==remotedownloaders[i][1]:
						continue
					if i<UserDefs.RegularUnchokedNum:
						try:
							UserLib.UpConn_map[peerpos][3]='unchoked'
						except Exception as detail:
							print("<unchoke>:: 2.Unexpected exception:",detail)
							continue
						msg={'type':'unchoke','mode':'reg'}
					else:
						try:
							UserLib.UpConn_map[peerpos][3]='choked'
						except Exception as detail:
							print("<unchoke>:: 2.Unexpected exception:",detail)
							continue
						msg={'type':'choke'}
					try:
						SocketLevel.send_msg(peerpos,-1,UserLib.UpConn_map,msg)
						if msg['type'] == 'unchoke':
							UserLib.UpConn_map[peerpos][8]=time.time()
					except Exception as detail:
						print("<unchoke>:: Unexpected exception: ",detail) 
						continue
			else:
				for i in range(0,len(remotedownloaders)):
					peerpos=remotedownloaders[i][1]
					if i<UserDefs.RegularUnchokedNum+1:
						#print("296:",peerpos,len(UserLib.UpConn_map))
						try:
							UserLib.UpConn_map[peerpos][3]='unchoked'
						except Exception as detail:
							print("<unchoke>:: 3.Unexpected exception:",detail)
							continue
						msg={'type':'unchoke','mode':'reg'}
					else:
						try:
							UserLib.UpConn_map[peerpos][3]='choked'
						except Exception as detail:
							print("<unchoke>:: 4.Unexpected exception:",detail)
							continue
						msg={'type':'choke'}
					try:
						SocketLevel.send_msg(peerpos,-1,UserLib.UpConn_map,msg)
						if msg['type'] == 'unchoke':
							UserLib.UpConn_map[peerpos][8]=time.time()
					except Exception as detail:
						print("<unchoke>:: Unexpected exception: ",detail) 
						continue			
			#####---------------
		else:
			interestedpeers=[]
			remoteuploaders=[]
			suggestedOpt=-1
			mymin=10000
			for i in range(0,len(UserLib.UpConn_map)):
				#for all remote peers (downloaders) that are interested to your content
				if UserLib.UpConn_map[i][4]=='interested':
					#keep their peer identifier
					peerid=UserLib.UpConn_map[i][2]
					interestedpeers.append([0,peerid,i])
					if UserLib.UpConn_map[i][6]<mymin:
						mymin=UserLib.UpConn_map[i][6]
						suggestedOpt=[0,peerid,i]
					#and if they are also uploaders to you
					if peerid in [ s[4] for s in UserLib.DownConn_map ]:
						#find their position in the map of your downloaders
						peerpos=[ peerid==s[4] for s in UserLib.DownConn_map].index(True)
						#and for everyone that have send you at least one block at the last 30 seconds
						if UserLib.DownConn_map[peerpos][2]>0 and time.time()-UserLib.DownConn_map[peerpos][8]<3*UserDefs.UnchokeInterval:
							#keep position in uploading map, their peer id and number of blocks having sent to you.
							remoteuploaders.append([UserLib.DownConn_map[peerpos][2],peerid,i])
			if len(interestedpeers)>0:
				if self.unchokeflag==0 and time.time()-self.lastunchoketime>=3*UserDefs.UnchokeInterval:
					self.lastunchoketime=time.time()
					if self.choice == 'optimistic':
						self.plannedOpt=random.choice(interestedpeers)
					elif self.choice == 'optimal':
						self.plannedOpt=suggestedOpt
					msg={'type':'unchoke','mode':'opt'}
					#print("1-->",self.plannedOpt,interestedpeers)
					#print("Opt unchoke",peerpos);
					try:
						peerpos=self.plannedOpt[2]
						UserLib.UpConn_map[peerpos][3]='unchoked'
						SocketLevel.send_msg(peerpos,-1,UserLib.UpConn_map,msg)
						UserLib.UpConn_map[peerpos][8]=time.time()
					except Exception as detail:
						print("<unchoke>:: 5.Unexpected exception: ",detail) 
				#remote uploaders consists of [#blocks received, peerid, position at map of uploaders] for every remote uploader.
				remoteuploaders.sort(reverse=True)
				regularunchoked=[]	
				if not remoteuploaders:
					regularunchoked=[]
				elif len(remoteuploaders)<=UserDefs.RegularUnchokedNum:
					regularunchoked=remoteuploaders
				else:
					for i in range(0,UserDefs.RegularUnchokedNum):
						regularunchoked.append(remoteuploaders[i])
				#print("remote uploaders:",remoteuploaders)
				#print("The three fastest peers(Regular Unchoked) are:",regularunchoked)
				#print("planned optimistic unchoked:",self.plannedOpt)
				#print("2-->",self.plannedOpt)
				for i in range(0,len(remoteuploaders)):
					if remoteuploaders[i] == self.plannedOpt:
						continue
					try:
						peerpos=remoteuploaders[i][2]
						if remoteuploaders[i] in regularunchoked:
							msg={'type':'unchoke','mode':'reg'}
							UserLib.UpConn_map[peerpos][3]='unchoked'
						else:
							msg={'type':'choke'}
							UserLib.UpConn_map[peerpos][3]='choked'
					except IndexError:
						continue
					try:
						SocketLevel.send_msg(peerpos,-1,UserLib.UpConn_map,msg)
						if msg['type']=='unchoke':
							UserLib.UpConn_map[peerpos][8]=time.time()
					except Exception as detail:
						print("<unchoke>:: Unexpected exception: ",detail) 
						continue
				if not self.plannedOpt:
					pass
				elif self.plannedOpt[1] in  [ s[1] for s in regularunchoked ]:
					while True:
						peerpos=random.randint(0,len(UserLib.UpConn_map)-1)
						peerid=UserLib.UpConn_map[peerpos][2]
						self.plannedOpt=[0,peerid,peerpos]
						msg={'type':'unchoke','mode':'reg'}
						UserLib.UpConn_map[peerpos][3]='unchoked'
						try:
							SocketLevel.send_msg(peerpos,-1,UserLib.UpConn_map,msg)	
							UserLib.UpConn_map[peerpos][8]=time.time()
						except Exception as detail:
							print("<unchoke>:: Unexpected exception: ",detail) 
							continue
						if UserLib.UpConn_map[peerpos][4] == 'interested':
							break	
		UserLib.SocketLock.release()
		#if thread has not terminated
		if UserDefs.Run:
			self.timer=threading.Timer(UserDefs.UnchokeInterval,self.unchoke)
			self.timer.start()
		self.unchokeflag=(self.unchokeflag+1)%3
	
	#this is a function creating a "time_request" message.
	def time_request(self):
	
		self.msg={'type':'time_request'}


	#this is a function creating a "handshake response" message.	
	def handshake_response(self):
		
		with UserLib.lock:
			self.msg={'type':'handshake_response'	
				,'peerid':UserLib.mypeerid	#include peer identifier of current peer.
				,'bmp':UserLib.bmp		#include bitmap of current peer.
				,'bmplen':UserLib.BMPLENGTH}	#THIS WILL BE PROBABLY REMOVED.


	#this is a function creating a "handshake response" message.	
	def bitfield(self):
		
		with UserLib.lock:
			self.msg={'type':'bitfield'	
				,'bmp':UserLib.bmp		#include bitmap of current peer.
				,'bmplen':UserLib.BMPLENGTH}	#THIS WILL BE PROBABLY REMOVED.

	#this is a function creating a block response message.
	def block(self,msg):
	
		self.msg={}
		self.msg['type']='block'
		self.msg['chunkpos']=msg['chunkpos']
		try:
			self.f.seek(int(msg['chunkpos'])*UserDefs.PieceSize)
			self.msg['chunk']=self.f.read(UserDefs.PieceSize)
		except 	IOError as detail:
			print("IOFile Error <block> at server thread:",detail)
			raise
		except Exception as detail:
			print("<block>:: Unexpected Exception:",detail)
			raise	

	
	#This is a function terminating server thread and doing "clean up" job.
	def terminate(self):

		self.f.close()
		for s in self.sockset:
			#if not s==sys.stdin:
			s.close()
		print(self.getName()," is going to terinate\n")
		print("Pieces sent:",UserLib.BlocksSent)
		print("Messages Sent:",UserLib.MessagesSent)
		print("Interested Received:",UserLib.InterestedReceived)
		print("Uninterested Received:",UserLib.UninterestedReceived)
		print("Interested Sent:",UserLib.InterestedSent)
		print("Uninterested Sent:",UserLib.UninterestedSent)
		print("Optimistic Unchokes Received:",UserLib.OptUnchokesReceived)
		print("Regular Unchokes Received:",UserLib.RegUnchokesReceived)
		if not UserLib.OptUnchokesReceived == 0:
			print("Interested connected peers per Opt Unchoke:%.2f"%(UserLib.InterestedPeersAtOpt/UserLib.OptUnchokesReceived))
		print("OptUnchokeTimes:",UserLib.OptUnchokeTimes)
		print("RegUnchokeTimes:",UserLib.RegUnchokeTimes)
		print("Uploading_t:",UserLib.Uploading_t)
		print("Downloading_t:",UserLib.Downloading_t)
		print("InterestedMsgReceived_t:",UserLib.InterestedMsgReceived_t)
		msg={'type':'leave'}
		SocketLevel.send_msg(-1, self.tracker, [],msg)
		return

	
