from __future__ import generators  # only in Python 2.2

def myenumerate(data,start=0):
    ind=0
    while ind<len(data):
        yield (ind+start, data[ind])
        ind+=1


def test_enumerate(my_version):
    data = 'hello'

    # Check values
    assert list(enumerate(data)) == list(my_version(data))

    # Check optional argument
    start = 3
    assert list(enumerate(data, start)) == list(my_version(data, start))
    
    # Check laziness
    e,m = enumerate(data), my_version(data)
    while True:
        try:
            assert e.next() == m.next()
        except StopIteration:
            break

    # Check that we are not relying on len
    x=my_version(iter(data))
    x.next()
    print "All OK"


if __name__=="__main__":
    test_enumerate(myenumerate)
