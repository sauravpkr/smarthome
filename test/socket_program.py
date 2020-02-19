import socket
'''
s= socket.socket()
host = "192.168.1.117"
port = 9999
s.bind((host,port))
s.listen(5)
print(host)

print("waiting for connection")
conn,addr = s.accept()
print(conn,"connection establish")
while True:
    data=input("Enter the message")
    conn.send(bytes(data,'utf-8'))
    print("data send successfully")
    print(conn.recv(1024).decode())
'''

hostname = socket.gethostname()
IPAddr = socket.gethostbyname(hostname)
print("Your Computer Name is:" + hostname)
print("Your Computer IP Address is:" + IPAddr)