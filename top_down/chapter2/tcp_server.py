from socket import *

serverSocket = socket(AF_INET, SOCK_STREAM)
serverAddress = ('', 8000)
serverSocket.bind(serverAddress)
serverSocket.listen(5)

print ("Server Ready for Commands")

def response(message_encoded):
    message = message_encoded.decode('utf-8')
    message = "Server " + str(serverAddress) + " received " + message
    return message.encode('utf-8')

while True:

    try:
        connectionSocket, clientAddress = serverSocket.accept()
        message = connectionSocket.recv(8192)
        print("Client > ", message)
        connectionSocket.send(response(message))
    except KeyboardInterrupt as controlc:
        serverSocket.close()
        break
    finally:
        connectionSocket.close()
    
