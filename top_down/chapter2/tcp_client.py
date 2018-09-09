from socket import *

serverAddress = ('localhost', 8000)
clientSocket = socket(AF_INET, SOCK_STREAM)
clientSocket.connect(serverAddress)


while True:
    try:
        print (str(serverAddress) + " > ", end = '')
        command = input().encode('utf-8')
        clientSocket.send(command)
        response = clientSocket.recv(8192)
        print(response.decode('utf-8'))
    except KeyboardInterrupt as controlc:
        clientSocket.close()
        break
    finally:
        pass

