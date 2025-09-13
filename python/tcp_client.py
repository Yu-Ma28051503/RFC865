# RFC865: Quote of the Day Protocol
#
# TCP Client code

import socket

class TCPClient:
    def __init__(self, host='localhost', port=17):
        self.server_address = (host, port)
        self.buffer_size = 512
        self.sock = None

    def connect(self):
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.sock.connect(self.server_address)
        print(f"Connected to {self.server_address}")

    def receive_quote(self):
        data = self.sock.recv(self.buffer_size)
        print("Received quote:")
        print(data.decode('utf-8'))

    def close(self):
        if self.sock:
            self.sock.close()
            print("Connection closed")

if __name__ == "__main__":
    client = TCPClient()
    try:
        client.connect()
        client.receive_quote()
    finally:
        client.close()
