EmptyQueue=0
class EmptyQueue(Exception):
    'doc for this class'

class priority_queue(EmptyQueue):
    
    def __init__(self):
        self._Q=[[],[],[],[],[]]

    def add(self,value,priority=2):
        if priority>=5 or priority<0:
            raise ValueError
        elif not isinstance(priority,int):
            raise TypeError
        self._Q[priority].insert(0,value)

    def pop(self):
        for queue in self._Q:
            if queue:
                return queue.pop()
        raise EmptyQueue("cannot pop from empty queue")

    def __len__(self):
        return sum(map(len,self._Q))
