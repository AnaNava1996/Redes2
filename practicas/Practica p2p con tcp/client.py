import socket
import json

TCP_IP = '127.0.0.1'
TCP_PORT = 5005
BUFFER_SIZE = 1024
MESSAGE = "files"

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

s.bind(('127.0.0.4',0))
s.connect((TCP_IP, TCP_PORT))
s.send(str.encode(MESSAGE))
data = s.recv(BUFFER_SIZE)

s.close()

print ("received data:", json.loads(data) )
