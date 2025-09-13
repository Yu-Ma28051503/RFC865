# RFC865: Quote of the Day Protocol
#
# TCP Server code

import socket
import datetime
import random
import threading
import signal
import sys

class TCPServer:
    def __init__(self, host='localhost', port=17):
        self.server_address = (host, port)
        self.buffer_size = 512
        self.quotes = [
            "The only limit to our realization of tomorrow is our doubts of today. - Franklin D. Roosevelt",
            "In the middle of every difficulty lies opportunity. - Albert Einstein",
            "What you get by achieving your goals is not as important as what you become by achieving your goals. - Zig Ziglar",
            "Believe you can and you're halfway there. - Theodore Roosevelt",
            "Do not watch the clock. Do what it does. Keep going. - Sam Levenson"
        ]
        self.sock = None
        self.is_running = True
        self.today = datetime.date.today()
        self.quote = random.choice(self.quotes)

    def start(self):
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.sock.bind(self.server_address)
        self.sock.listen(5)
        print(f"Server listening on {self.server_address}")

        signal.signal(signal.SIGINT, self.shutdown)

        while self.is_running:
            try:
                conn, addr = self.sock.accept()
                print(f"Connection from {addr}")
                threading.Thread(target=self.handle_client, args=(conn, addr)).start()
            except Exception as e:
                print(f"Error accepting connections: {e}")

    def handle_client(self, conn, addr):
        today = datetime.date.today()
        if today != self.today:
            self.today = today
            self.quote = random.choice(self.quotes)
            print(f"Date changed to {self.today}, refreshing quotes if needed.")
        
        try:
            timestamp = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")
            message = f"Quote of the Day ({timestamp}):\n{self.quote}\n"
            conn.sendall(message.encode('utf-8'))
            print(f"Sent quote to {addr}")
        except Exception as e:
            print(f"Error handling client {addr}: {e}")
        finally:
            conn.close()
            print(f"Connection with {addr} closed")

    def shutdown(self, signum, frame):
        print("Shutting down server...")
        self.is_running = False
        if self.sock:
            self.sock.close()
        sys.exit(0)

if __name__ == "__main__":
    server = TCPServer()
    server.start()
