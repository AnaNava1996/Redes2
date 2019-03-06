
import socket

HOST = '127.0.0.1'  # Standard loopback interface address (localhost)
PORT = 65432        # Port to listen on (non-privileged ports are > 1023)

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.bind((HOST, PORT))
    s.listen()
    conn, addr = s.accept()#tupla con los valores (host, port) de ipv4
    with conn:
        print('Connected by', addr)
        while True:
            data = conn.recv(1024)
            if not data:
                break
            print(repr(data))#imprime versión imprimible de data que está en bytes
            cadena=str(input("-->"))
            cadenabytes=cadena.encode()
            conn.sendall(cadenabytes)
'''
import socket

s = socket.socket()
host = socket.gethostname()
port = 12221
s.bind((host, port))

s.listen(5)
c = None

while True:
   if c is None:
       # Halts
       print ('[Waiting for connection...]')
       c, addr = s.accept()
       print ('Got connection from', addr)
   else:
       # Halts
       print ('[Waiting for response...]')
       print (c.recv(1024))
       q = str(input("Enter something to this client: "))
       c.send(q.encode())


'''
