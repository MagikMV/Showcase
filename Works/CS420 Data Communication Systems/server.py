# server.py
#
# Miguel Villanueva
# CS 420
# November 14, 2021

import socket

IP = "127.0.0.1"
PORT = 12345

server_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
server_socket.bind((IP, PORT))

print("This is the server")

while(True):
    data, address = server_socket.recvfrom(32)
    decoded_data = data.decode("utf-8")
    message = str(decoded_data)
    print(message)
    server_socket.sendto(data, address) # Echo back
