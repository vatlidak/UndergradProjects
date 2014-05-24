from __future__ import generators
from time import time 


#def mycount(start=0, step=1):
#    n=start
#    while 1:
#        new_step = yield n
#        if new_step is not none:
#            step = new_step
#         n+=step

def mycount(start=0, step=1):
    n=start
    while True:
        new_step = yield n
        try:
            n+=new_step
        except TypeError:
            n+=step
        else:
            step=new_step


def fibg():
    previous, current=0,1 
    while True:
        yield current
        current, previous= current+previous, current

def fibi(n):
    a,b=0, 1
    for i in range(n):
       a, b = b, a + b
    return a

def timer(funct, *args):
    start=time()
    rval=funct(*args)
    end=time()
    return rval, end-start

class  memo():
    def __init__(self, func):
        self._func=func
        self._cache={}
    def __call__(self,val):
        try:
            return self._cache[val]
        except:
            rval=self._func(val)
            self._cache[val]=rval
            return rval

def memoclosure(func):
    cache={}
    def calc(val):
        try:
            return cache[val]
        except:
            rval=func(val)
            cache[val]=rval
            return rval
    return calc 



class rectangle(object):

    def __init__(self, b,h):
        self.b = b
        self.h = h
       
    def geta(self):
        return self.h*self.b

    a=property(geta)

if __name__ == "__main__":
    

  """  r=rectangle(3,4)
    assert r.b == 3
    assert r.h == 4
    assert r.a == 12
    r.b = 6
    assert r.b == 6
    assert r.h == 4 
    assert r.a == 24
    r.h = 8
    assert r.b == 6
    assert r.h == 8
    assert r.a == 48
    print "ALL OK"
    #a=mycount()
    #print a.next()
    #print a.next()
    #print a.send(2)
    #print a.next()
    #print a.next()
   # a.send('a')
    #print a.next()
#    print timer(fib,300)
#    print timer(fibi,300)
    #print timer(fibi,10000)
    #fib=memo(fibi)
    #print timer(fibi,10000)
#    print timer(mfib,35)
#    print timer(mfib,35)



    #print timer(fib,10) """
