# client.py
#
# Miguel Villanueva
# CS 420
# November 14, 2021

import socket
import random
import time

IP = "127.0.0.1"
PORT = 12345

client_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

message = "number="

print("\nPinging the server with random numbers:\n")

sum = 0.0;
count = 0;
while(True):
    if count == 5:
	break
    full_message = message + str(random.randrange(10))
    encoded_message = full_message.encode("utf-8")
    bytes_message = bytes(encoded_message)

    before = time.time() * 1000
    client_socket.sendto(bytes_message, (IP, PORT))
    data, address = client_socket.recvfrom(32)
    after = time.time() * 1000

    decoded_data = data.decode("utf-8")
    decoded_message = str(decoded_data)
    delay = " delay=" + str(round(after - before, 4)) + "ms"
    sum += round(after - before, 4)

    print("Reply from server: " + decoded_message + delay)
    count += 1
print("\nApproximate round trip time in mili-seconds:")
print("    Average = " + str(round(sum/5, 4)) + "ms\n")
