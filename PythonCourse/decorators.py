
def one(_):
    return 1

def inc(n):
    return n+1

def inc_by(m):
    def inc(n):
        return n+m
    return inc

@inc_by(10)
@inc
@one
def hello():
    print hello
print hello
print "-------"

from functools import wraps

def report_result(func):
    @wraps(func)
    def dec(*args,**kwds):
        val=func(*args,**kwds)
        print func.__name__, val
        return val
    return dec 

def report_args(func):
    @wraps(func)
    def dec(*args,**kwds):
        print args, kwds
        return func(*args,**kwds)
    return dec

#@chain('up down'.split())
class X:
    def __init__(self,n):
        self._n = n
    
    def up(self,n):
        self._n += n

    def down(self,n):
        self._n -= n

print X(1)



@report_result
#@report_args
def my_add(a,b):
    "adds to things"
    return a+b

#if __name__=="__main__":



