import socket

my_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
my_socket.connect(("127.0.0.1", 8820))

while True:
    cmd = input("enter a command: ")
    my_socket.send(cmd.encode())

    if cmd == "Quit":
        print(my_socket.recv(1024).decode())
        break

    data = my_socket.recv(1024).decode()
    print("The server sent " + data)

my_socket.close()
