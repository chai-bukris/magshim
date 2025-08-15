import socket
import time
import random

server_socket = socket.socket()
server_socket.bind(("0.0.0.0", 8820))
server_socket.listen()
print("Server is up and running")
(client_socket, client_address) = server_socket.accept()
print("client connected")
while True:
    cmd = client_socket.recv(1024).decode()
    print("Client sent: " + cmd)
    if cmd == "NAME":
        answer = "chai"
    elif cmd == "TIME":
        answer = time.strftime("%H:%M:%S")
    elif cmd == "RAND":
        answer = str(random.randint(1, 10))
    elif cmd == "Quit":
        break
    else:
        answer = "error"
    client_socket.send(answer.encode())

client_socket.close()
server_socket.close()
