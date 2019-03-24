import socket
import sys
import threading


sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)


server_address = ('localhost', 10001)
print("starting up on "+str(server_address[0])+" port "+str(server_address[1]))
sock.bind(server_address)

class Hilo_cliente(threading.Thread):
    def run(self):
        self.data=data
        self.address=address
        print("FUNCION DEL HILO: "+threading.currentThread().getName())
        print("data"+repr(self.data))
        
        sent = sock.sendto(threading.currentThread().getName().encode(), self.address)#le envio el nombre del hilo al cliente
        print("sent "+str(sent)+ " bytes back to "+str(self.address))    
        
        while True:
            data2, self.address = sock.recvfrom(4096)#devuelve cantidad de bytes enviados y address    
            
            if data2:
                print("data: "+repr(data2.decode()))
                if(data2.decode()[0:4]!="hola"):
                    sent = sock.sendto("ok".encode(), self.address)
                    print("sent "+str(sent)+ " bytes back to "+str(self.address))
                else:
                    #data2, self.address = sock.recvfrom(4096)#devuelve cantidad de bytes enviados y address    
                    print("se pidió archivo: "+ data2.decode()[4:] )
                    if (data2.decode()[5:]=="img"):
                        f=open("doge.jpg","rb")
                        buff=f.read()
                        if data2:
                            sent = sock.sendto(buff, self.address)
                            print("sent "+str(sent)+ " bytes back to "+str(self.address))
                        f.close()
                    else:
                        f=open("Intro_Flex_Bison.pdf","rb")
                        buff="abc".encode()
                        while buff:
                            buff=f.read(4096)          
                            sent = sock.sendto(buff, self.address)
                            print("sent "+str(sent)+ " bytes back to "+str(self.address))
                            print(sys.getsizeof(buff))
                            if (sys.getsizeof(buff)<4096):
                                break
                        f.close()
                    print("acabado")
                    #sent = sock.sendto("listo".encode(), self.address)
            
            
num_max_clientes=10  
threads=[None]*num_max_clientes
#connections=[None]*num_max_clientes
addresses=[None]*num_max_clientes
count=0    
while True:
    try:
        print("WAITING for client")
        data,address = sock.recvfrom(4096)#devuelve cantidad de bytes enviados y address
        if(address not in addresses):
            addresses[count] = address
            threads[count]=Hilo_cliente(name=str(count),args=(data.decode(),address))
            threads[count].start()
            count+=1 
        else:
            sent = sock.sendto("comp".encode(), address)#sock.sendto(str(address).encode(), address)
            print("COMPROBANDO CON: "+str(address))    
    except Exception as e:
        print(e)
        break  
sock.shutdown(socket.SHUT_RDWR)
        
        
        
        
        
        
        
        
        
        
        
        
