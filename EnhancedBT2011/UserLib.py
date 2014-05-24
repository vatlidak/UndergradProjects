#In this module exceptions and global variables are defined.
#Author: V. Atlidakis
#Date: March 2011
import threading

class ConnectionResetedByPeer(Exception):pass		#Exception raised on connection's end when connection is closed from the other end
class EstablishConnError(Exception):pass		#Exception raised when connection established, though an active peer set received from coordinator
class BlockCorrupted(Exception):pass			#Exception raised when received corrupted block.
class TerminateThread(Exception):pass			#Exception raised when current thread should terminate
class AllConnectionsChoked(Exception):pass		#Exception raised when all connections are choked.
class FileCompletelyDownloaded(Exception):pass		#Exception raised upon completion of downloading.
class MaxRequestsSent(Exception):pass			#Exception raised when unable to requests block since maximum pending requests are sent.
class UnexpectedBlock(Exception):pass			#Exception raised when receive block, not corresponding to pending request.
class UnexpectedMessage(Exception):pass			#Exception raise when unexpected message received.

lock=threading.Lock()				        #lock for mutual exclusion when accessing bitmap

SocketLock=threading.Lock()				#lock for mutual exclusion when accessing socket set. 

BlocksSent=0
MessagesSent=0
InterestedSent=0
UninterestedSent=0
InterestedReceived=0
UninterestedReceived=0
RegUnchokesReceived=0
OptUnchokesReceived=0
InterestedPeersAtOpt=0

OptUnchokeTimes=[]
RegUnchokeTimes=[]
Uploading_t=[]
Downloading_t=[]
InterestedMsgReceived_t=[]


bmp = []						#bitmap of peer

sha1s_map=[]						#map of sha-1 hashes for each block

metadata_hash=[]					#file identifier 

PiecesDownloaded=0
BMPLENGTH = 0						#Length of bitmap, indicating number of blocks of file

mypeerid = ''						#peer identifier received from coordinator, when joining swarm.

requests = []						#list containing pending block requests.

TimedOutPeers = []					#list containing timed out remote peers. They will be mentioned when contacting coordinator.

DownConn_map=[]						#this is a list keeping neccessary information about all active 

							#connections from which current peer is downloading blocks.

							#Each entry of the list has the following format:
							#[ 0.socket of respective connection,	
							#  1.port of respective connection
							#  2.counter of blocks received from current connection,
							#  3.bitmap of respective peer,
							#  4.peer identifier of respective peer,
							#  5.choked/unchoked connection state,
							#  6.interested/uninterested connection state. 
							#  7.ip of respective connection
							#  8.time last block rceived
							#]


UpConn_map=[]						#this is a map keeping neccessary information about all active 
							#connections to which current peer is uploading blocks.
							#Each entry of the list has the following format:
							#[ 0.socket of respective connection,	
							#  1.port of respective connection
							#  2.peer identifier of respective peer,
							#  3.choked/unchoked connection state,
							#  4.interested/uninterested connection state. 
							#  5.intitialized
							#  6.number of "interested" remote peers
							#  7.counter of blocks send to respective remote downloader.
							#  8.time last unchoke
							#]


