import socket
import sys

def getNetworkIp():
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sock.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
    sock.connect(('<broadcast>', 0))
    return str(sock.getsockname()[0])

def main():
    # Create a UDP socket
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    server_address = ('localhost', 10001)
    #message = 'This is the message.  It will be repeated.'
    message = getNetworkIp()

    cont=1

    try: 
        message=str(input("--> Message: "))
        sent = sock.sendto(message.encode(), server_address) 
        data,address= sock.recvfrom(4096)
        if data:
            hilo = data.decode()
            print("Soy el cliente: "+hilo)

        while(True):        
            sock.settimeout(None)
            
            message=str(input("-->Message: "))        
            if(message == "hola"):
                print("sending message: "+message+" img")
                message=message+" img"
                sent = sock.sendto(message.encode(), server_address) 
                print("waiting to receive")
                data1, server = sock.recvfrom(40960000)
                try:
                    if (data1.decode()=="comp"):
                        print("try again...")
                except:
                    imagen="imagen_"+str(cont)+"_"+hilo+".jpg"
                    f1=open(imagen,"ab")
                    f1.write(data1)
                    f1.close()
                    print("IMAGE RECEIVED ")                       
            else:
                print("sending message: "+message)
                sent = sock.sendto(message.encode(), server_address)
                print("waiting to receive")
                data2, server = sock.recvfrom(4096)
            
            
            message=str(input("--> Message: "))
            if(message == "hola"):
                print("sending message: "+message+" pdf")
                message=message+" pdf"
                sent = sock.sendto(message.encode(), server_address) 
                print("waiting to receive")
                
                pedeefe="pedeefe_"+str(cont)+"_"+hilo+".pdf"
                f1=open(pedeefe,"ab")
                data1, server = sock.recvfrom(4096)
                try:
                    if(data1.decode()=="comp"):
                        print("Try again...")
                except:
                    f1.write(data1)
                    while data1:
                        sock.settimeout(1.0)
                        data1, server = sock.recvfrom(4096)
                        f1.write(data1)
                        print(sys.getsizeof(data1))
                        if(sys.getsizeof(data1) < 4096):
                            break 
                    f1.close()
                    print("PDF RECEIVED ")   
                                    
            else:
                print("sending message: "+message)
                sent = sock.sendto(message.encode(), server_address)
                print("waiting to receive")
                data2, server = sock.recvfrom(4096)
                
                

            cont+=1

    finally:
        print("closing socket")
        sock.close()

if __name__ == '__main__':
    main()
    
    

