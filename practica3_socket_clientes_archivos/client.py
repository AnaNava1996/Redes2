import socket
import time
import glob

HOST = '127.0.0.1'  # The server's hostname or IP address
PORT = 65433       # The port used by the server

def getNetworkIp():
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sock.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
    sock.connect(('<broadcast>', 0))
    return str(sock.getsockname()[0])

def largo_archivo(path):
    f=open(path, "rb")
    tamano_archivo=1
    byte=f.read(1)
    while byte:
        tamano_archivo+=1
        byte = f.read(1)
        #print(byte,end=" ")
    print("")
    print("Largo del archivo: "+str(tamano_archivo))
    f.close()
    return(tamano_archivo)

def calcular_buffer(tamano_archivo):
    BUFFER_AUX = (tamano_archivo+1)//4
    print("tamano aprox del paquete: "+str(BUFFER_AUX))
    potencia=3
    while (BUFFER_AUX > pow(2,potencia)):
        potencia+=1
    print("tamano del buffer: "+str(pow(2,potencia)))
    return pow(2,potencia)


s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((HOST, PORT))
lista = glob.glob('/home/**/**/*.pdf',recursive=True) + glob.glob('/home/**/**/*.jpg',recursive=True) + glob.glob('/home/**/**/*.png',recursive=True)
#glob.glob('/**/**/**/*.jpg') + glob.glob('../../Pictures/**/*.jpg', recursive=True) + glob.glob('/**/**/**/*.pdf') + glob.glob('/**/**/**/*.png')
#glob.glob('/home/**/**/*.*',recursive=True)
num_archivos=len(lista)
i=0
print("Elementos en la lista: "+str(num_archivos))

cosa=str(input("-->[Press enter to send stuff]"))

while(True and i!=num_archivos-1):
    print(lista[i])
    for k in range(len(lista[i])-1,0,-1):
        if(lista[i][k] == '/'):
            break
    cad_nombre_archivo = lista[i][k+1:len(lista[i])]
    cadenabytes=cad_nombre_archivo.encode()#lista[i].encode()
    tamano_archivo = largo_archivo(lista[i])
    tamano_buffer = str(calcular_buffer(tamano_archivo))#calculo el tamaño del buffer
    
    s.sendall(getNetworkIp().encode())#primera cosa que le envio al servidor, el tamaño del buffer
    data = s.recv(4096)
    if not data:
        break
    if(cadenabytes!=data):
        print(repr(data))

            
    #time.sleep(0.5)
    
    s.sendall(cadenabytes)#le envío al servidor el nombre del archivo
    data = s.recv(4096)
    if not data:
        break
    if(cadenabytes!=data):
        print(repr(data))

            
    #time.sleep(0.5)

    bloque1 = tamano_archivo//4
    bloque2 = tamano_archivo//4
    bloque3 = tamano_archivo//4
    bloque4 = (tamano_archivo//4) + (tamano_archivo%4)
    
    f=open(lista[i],"rb")
    bloque_bytes = f.read(bloque1)
    s.sendall(bloque_bytes)
    #print(bloque_bytes)
    print('test1')
    data = s.recv(4096)
    print('test2')
    if not data:
        break
    if(cadenabytes!=data):
        print(repr(data))
    

    bloque_bytes = f.read(bloque2)
    s.sendall(bloque_bytes)
    #print(bloque_bytes)
    data = s.recv(4096)
    if not data:
        break
    if(cadenabytes!=data):
        print(repr(data))
    
    #time.sleep(0.5)
    
    bloque_bytes = f.read(bloque3)
    s.sendall(bloque_bytes)
    #print(bloque_bytes)
    data = s.recv(4096)
    if not data:
        break
    if(cadenabytes!=data):
        print(repr(data))

    #time.sleep(0.5) 

    bloque_bytes = f.read(bloque4)
    s.sendall(bloque_bytes)
    #print(bloque_bytes)
    data = s.recv(4096)
    if not data:
        break
    if(cadenabytes!=data):
        print(repr(data))
    
    #time.sleep(0.5)
    
    f.close()
    
        
    i+=1

s.close()
#s.shutdown(socket.SHUT_RDWR)




