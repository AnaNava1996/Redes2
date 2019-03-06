
import socket
import time

HOST = '127.0.0.1'  # The server's hostname or IP address
PORT = 65432        # The port used by the server

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((HOST, PORT))
    while True:
        cadena=str(input("-->"))
        cadenabytes=cadena.encode()
        s.sendall(cadenabytes)#objeto tipo bytes
        data = s.recv(1024)
        if not data:
            break
        if(cadenabytes!=data):
            print(repr(data))
'''


import socket

s = socket.socket()
host = socket.gethostname()
port = 12221

s.connect((host, port))
print ('Connected to', host)

while True:
    z = str(input("Enter something for the server: "))
    s.send(z.encode())
    # Halts
    print ('[Waiting for response...]')
    print (s.recv(1024) )

'''
