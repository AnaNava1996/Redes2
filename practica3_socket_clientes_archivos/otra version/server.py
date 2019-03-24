import glob
import socket
import selectors
import sys
from random import randint
import threading
import time
from queue import Queue
import os

#HOST = '127.0.0.1'  # Standard loopback interface address (localhost)
HOST = '0.0.0.0'
PORT = 65433        # Port to listen on (non-privileged ports are > 1023)



class Hilo_cliente(threading.Thread):
    def run(self):
        print("Entra el hilo tal")
        print("I'm thread: "+threading.currentThread().getName())
        self.conn=conexion
        self.addr=direccion
        print (self.addr)
        
        #se crea el directorio para los archivos de este hilo
        cadena_directorio="./carpeta_"+threading.currentThread().getName()
        createFolder( cadena_directorio )
        data_aux="cualquier cosa".encode()    
        while (True):
            data = self.conn.recv(1024)#pedazo que recibe el tamaño para el buffer... ahora solo sirve para corroborar que se esté sincronizado
            if not data:
                break
            try:
                print(int(data))#tamaño del buffer para poder recibir los pedazos de archivo(cambiar por la ip)
            except Exception as e:
                print(e)
                cadena="error"
                cadenabytes=cadena.encode()
                self.conn.sendall(cadenabytes)
                break
            cadena="recibido"#nada más con el fin de sincronizar
            cadenabytes=cadena.encode()
            self.conn.sendall(cadenabytes)
            

            path = self.conn.recv(1024)#pedazo que recibe el nombre del archivo
            if not path:
                break
            while(path == cadenabytes):
                print(sincronizando)
                path=self.conn.recv(1024)


            cad_name_of_file = path.decode()
            print(cad_name_of_file)
            print("")
            
            cadena="recibidotl"#con el fin de sincronizar
            cadenabytes=cadena.encode()
            self.conn.sendall(cadenabytes)
                
            
            
            cad_folder = cadena_directorio +"/"+ cad_name_of_file
            new_file = open(cad_folder,'ab')
            

            
            for i in range(0,4):#los cuatro pedazos del archivo
                
                data = self.conn.recv(1024)
                new_file.write(data)
                while len(data)==1024:
                    print(data)
                    print('----------------',len(data),'----------------')
                    data = self.conn.recv(1024)
                    new_file.write(data)
                    print(':)')
                data_aux=data  
                print('received')
                cadena="recibido"#con el fin de sincronizar
                cadenabytes=cadena.encode()
                self.conn.sendall(cadenabytes)
                print('sent')  
            new_file.close()            


def leer_parrafo():
    f=open("instrucciones.txt",'r')
    num=randint(0,13)
    for i, line in enumerate(f):
        if (i==num):
            #print(line)
            f.close()
            return(line)

def createFolder(directory):
    try:
        if not os.path.exists(directory):
            os.makedirs(directory)
    except OSError:
        print ('Error: Creating directory. ' +  directory)
    
#####################################################      MAIN      ##########################################################
#CREATE THE SOCKET
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
print("the socket has been created")

#BIND THE SOCKET
try:
    s.bind((HOST, PORT))
except Exception as e:
    print(e)
    sys.exit()
print("the socket has been bounded")

num_max_clientes = 5
s.listen(num_max_clientes)
print("The socket is listening")
threads=[None]*num_max_clientes
connections=[None]*num_max_clientes
addresses=[None]*num_max_clientes
count=0

while (True):
    try:
        connections[count], addresses[count] = s.accept()#tupla con los valores (host, port) de ipv4
        #with connections[count]:
        s.setblocking(1)
        print('Connected by', addresses[count])
        conexion=connections[count]
        direccion=addresses[count]
        threads[count]=Hilo_cliente(name=str(count),args=(conexion,direccion))
        threads[count].start()
        print(count)
    except Exception as e:
        print(e)
        print(count)
        print("Not connected")
        s.shutdown(socket.SHUT_RDWR)
        break;
    count+=1
s.shutdown(socket.SHUT_RDWR)
     
################################################# a partir de aqui ####################################################3






















