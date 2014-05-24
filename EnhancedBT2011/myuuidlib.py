#This module implements an Apllication Programming Interface allowing above 
#levels to Universally unique identifiers to identify peers.
#Author: V. Atlidakis
#Date: March 2011
import time, uuid


#this is a function returning a UUID
#from a host ID, sequence number, and the current time
def create_uuid():
	return  uuid.uuid1(int(time.time()))


#this is a function to get a posix timestamp from a type 1 UUID.
#Based on code found on the internet address:
#     http://code.activestate.com/recipes/576420-get-a-posix-timestamp-from-a-type-1-uuid/
def get_posixtime(uuid1):
    """Convert the uuid1 timestamp to a standard posix timestamp"""
    assert uuid1.version == 1, ValueError('only applies to type 1')
    t = uuid1.time
    t = t - 0x01b21dd213814000
    t = t / 1e7
    return t


