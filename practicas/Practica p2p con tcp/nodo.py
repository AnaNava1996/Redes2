import socket
import _thread
import time
import sys
import os
import json

def manage_conn(conn,addr,BUFFER_SIZE):
    #MANEJA LA CONEXIÓN DE UN CLIENTE
    while 1:
        data = conn.recv(BUFFER_SIZE)
        if not data: break;
        
        data = bytes.decode(data)
        local = sys.argv[2]
        
        if data == "files" :    
            conn.send(str.encode(json.dumps(os.listdir(local))))  # echo
            
        elif json.loads(data)[0] == "giveme":
            try:
                if not os.path.isfile(local+"/"+json.loads(data)[1]):
                    print("El archivo '"+json.loads(data)[1]+"' no existe")
                    conn.send(str.encode("NO"))
                    break;
                conn.send(str.encode("OK"))
                with open(local+"/"+json.loads(data)[1],"rb") as filename:
                    f = filename.read(1024)
                    while(f):
                        conn.send(f)
                        f = filename.read(1024)

                print("Done!")
                conn.shutdown(socket.SHUT_WR)
            except Exception as ex:
                print("CONN: ",ex)
            
        else:
            print(":(")
    conn.close()

def start_tcp_server(TCP_IP,TCP_PORT,BUFFER_SIZE):
    
    print("\nIniciando servidor TCP...\n")
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.bind((TCP_IP, TCP_PORT))
    s.listen(1) #UN CLIENTE A LA VEZ
    print("[OK]")
    #MANTIENE EL SERVIDOR CORRIENDO EN ESCUCHA DE NUEVOS CLIENTES
    while True:
        conn, addr = s.accept()
        print ('Connection address:', addr)
        try:
            #_thread.start_new_thread(manage_conn,(conn,addr,BUFFER_SIZE))
            manage_conn(conn,addr,BUFFER_SIZE)
        except Exception as ex:
            print("TCP: ",ex)
            s.shutdown(socket.SHUT_RDWR)
            break;
    s.close()

def own_files():
    #MOSTRAR ARCHIVOS LOCALES
    local = sys.argv[2]
    return os.listdir(local)
    #print("Archivos locales")

def show_files():
    #MOSTRAR ARCHIVOS REMOTOS
    with open("servidores.txt","r") as f:
        for line in f:
            
            l = line.strip().split(",")

            print(l)
            
            s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            s.connect( (l[0] , int(l[1])) )
            print("help")
            s.send(str.encode("files"))
            
            data = s.recv(1024)
            print("Archivos: ",json.loads(data))
            s.close()  
    return

def select_files():
    #SELECCIONAR EL ARCHIVO PARA DESCARGAR
    show_files()
    host = input("Selecciona el servidor > ")
    name = input("Dame el nombre del archivo > ")
    local = sys.argv[2]
    
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect((host,5005))
    
    s.send(str.encode(json.dumps(["giveme",name])))
    confirm = bytes.decode(s.recv(3))

    f = open(local+'/'+name,'wb')
    
    if confirm == "OK":
        while True:
            data = s.recv(1024)
            if not data:
                break;
            f.write(data)
    else:
        print("El archivo no existe en el servidor")

    f.close()

    return ""

def main():

    #SELECTOR DE FUNCIONES EN EL CASE
    select = {
        1:own_files,
        2:show_files,
        3:select_files,
        0:()
    }
    
    #RECIBIMOS DE LA LÍNEA DE COMANDOS
    args = sys.argv[1:]
    if len(args)<2 :
        print("\nNo hay suficientes argumentos. Ingresar 2.\n\n"
              "Modo de uso:\n\n"
              "python nodo.py [dirección propia] [nombre del directorio local]\n")
        return
    
    #INICIALIZA EL HILO DEL SERVIDOR TCP
    _thread.start_new_thread(start_tcp_server,(args[0],5005,1024))
    time.sleep(1)
    #INICIALIZA EL HILO DEL SERVIDOR UDP
    #_thread.start_new_thread(coso de udp)
    
    #MENUCITO
    while True:
        print("\nSelecciona una opción:"
              "\n(1) Ver archivos locales."
              "\n(2) Ver archivos en la red."
              "\n(3) Seleccionar y descargar archivo."
              "\n(0) Salir"
              "\n")
    
        try:
            #SELECCIÓN DE LA FUNCIÓN A TRAVÉS DEL DICCIONARIO
            sel = int(input("> "))
            if not sel:
                return
            print(select[sel]())
            
        except Exception as ex:
            print("Main: ", ex)
        
main()
