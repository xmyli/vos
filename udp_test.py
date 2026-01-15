import socket

print("Sending UDP packet...")

s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
s.sendto(b'xyz', ("127.0.0.1", 2000))
message, address = s.recvfrom(64)
print(message)
print(address)
