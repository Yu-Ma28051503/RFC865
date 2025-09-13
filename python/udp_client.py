# RFC865: Quote of the Day Protocol
#
# UDP Client code

import socket

class UDPClient:
    def __init__(self, host='localhost', port=17):
        self.server_address = (host, port)
        self.buffer_size = 512
        self.sock = None

    def connect(self):
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        print(f"UDP socket created to {self.server_address}")

    def receive_quote(self):
        try:
            self.sock.sendto(b'', self.server_address)  # Send empty datagram to request quote
            data, _ = self.sock.recvfrom(self.buffer_size)
            print("Received quote:")
            print(data.decode('utf-8'))
        except Exception as e:
            print(f"Error receiving quote: {e}")

    def close(self):
        if self.sock:
            self.sock.close()
            print("Socket closed")

if __name__ == "__main__":
    client = UDPClient()
    try:
        client.connect()
        client.receive_quote()
    finally:
        client.close()
