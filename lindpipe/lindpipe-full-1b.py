import sys
import os
import time
import threading
import lindpipe
import ctypes

def writeWrapper(writebufaddr, count, loopamount):

    for x in range(loopamount):
        byteswritten = pipe.pipewrite(writeaddr, count)


def readWrapper(readbufaddr, count, loopamount):

    data = 0

    for x in range(loopamount):
        data += pipe.piperead(readbufaddr +(x*count), count)


    # print("read " + str(data) + " bytes.")



pipe = lindpipe.LindPipe()

i = int(sys.argv[1])

size = 2 ** i
loopamount = 2 ** (30 - i)
readsize = 2 ** 17
readloopamount = 2 ** 13

pya = size * (b'A')

writebufs = list()

temp = ctypes.create_string_buffer(pya)
writeaddr = ctypes.addressof(temp)

readbuf = ctypes.create_string_buffer(size * loopamount)

print("Filesize " + str(size * loopamount) + " bytes")

readbufaddr = ctypes.addressof(readbuf)


writeThread = threading.Thread(target=writeWrapper, args=(writeaddr, size, loopamount,))
readThread = threading.Thread(target=readWrapper, args=(readbufaddr, readsize, readloopamount,))

starttime = time.clock()

writeThread.start()
readThread.start()
writeThread.join()
readThread.join()

endtime = time.clock()
totaltime = (endtime - starttime) * 1000000

print("Time: " + str(totaltime))

print("done")



