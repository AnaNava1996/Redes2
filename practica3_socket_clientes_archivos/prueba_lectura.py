#b'/home/ana/Pictures/doge.jpg'
import socket

def getNetworkIp():
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    s.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
    s.connect(('<broadcast>', 0))
    return str(s.getsockname()[0])

print (getNetworkIp())


'''
with open("lightweightEncryption.pdf", "rb") as f:
    count=1
    byte=f.read(1024)
    while byte:
        count+=1
        byte = f.read(1024)
        print(byte)
    print("")
    print(count)
'''



