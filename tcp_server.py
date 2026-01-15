import socket
import time

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind(("127.0.0.1", 2001));
s.listen()
conn, addr = s.accept()

print("connection established")

while(True):
    data = conn.recv(13)
    if data:
        print(data)
    else:
        break

s.close()
