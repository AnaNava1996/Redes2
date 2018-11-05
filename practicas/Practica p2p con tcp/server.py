import socket
import _thread
import time

def manage_conn(conn,addr):
    
    while 1:
        data = conn.recv(BUFFER_SIZE)
        if not data: break;
        print ("received data:", data, "from ", addr)
        conn.send(data)  # echo
    conn.close()

def start_server(ip,port,buffer):
    
    TCP_IP = '127.0.0.2'
    TCP_PORT = 5005
    BUFFER_SIZE = 1024  # Normally 1024, but we want fast response

    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.bind((TCP_IP, TCP_PORT))
    s.listen(3)

    while True:
        conn, addr = s.accept()
        print ('Connection address:', addr)
        try:
            _thread.start_new_thread(manage_conn,(conn,addr))
            #manage_conn(conn,addr)
        except:
            print("SHALE")
            break;
        
    s.close()

def own_files():
    pass

def show_files():
    pass

def select_files(server,listed_file):
    pass

def main():
    print("Selecciona una opción:\n(1) Ver archivos disponibles.\n(2) Seleccionar y descargar archivo.")
