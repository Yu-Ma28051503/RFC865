# RFC865

This repository contains a simple implementation of the Quote of the Day Protocol as defined in [RFC 865](https://datatracker.ietf.org/doc/html/rfc865) using variety of programming languages. The Quote of the Day Protocol is a simple protocol that provides the Todays Quote to clients over TCP or UDP.

## C Implementation
The C implementation includes both a TCP server and a TCP client. The server listens for incoming connections on port 13 and sends the current date and time to the connected client. The client connects to the server and displays the received date and time.

### Files

```
c/
|-- tcp_server.c   # TCP server implementation
|-- tcp_client.c   # TCP client implementation
|-- udp_server.c   # UDP server implementation
|-- udp_client.c   # UDP client implementation
|-- common.c       # Common functions and definitions
|-- common.h       # Common header file
|-- Makefile       # Makefile for building the server and client
```

### Usage

0. **Prerequisites**:
   - Ensure you have a C compiler (like `gcc`) and `make` installed on your system.

```bash
# Debian/Ubuntu
sudo apt update
sudo apt install gcc make

# macOS (using Homebrew)
brew install gcc make
```

1. **Build the Server and Client**:

```bash
cd c
make
```

2. **Run the TCP Server and Client**:

```bash
./tcp_server
```

```bash
# ready in another terminal
./tcp_client
```

3. **Run the UDP Server and Client**:

```bash
./udp_server
```

```bash
# ready in another terminal
./udp_client
```

4. **Clean Up**:

```bash
make clean
```

### Notes

- The tcp_client connects to `127.0.0.1` by default.
    - To connect to a different server, provide the server IP as edited SERVER_IPv4 in `common.h`.

## C++ Implementation
The C++ implementation also includes both a TCP server and a TCP client. The server listens for incoming connections on port 17 and sends the Quote of the Day to the connected client. The client connects to the server and displays the received quote.

### Files

```c++/
|-- tcp_server.cpp # TCP server implementation
|-- tcp_client.cpp # TCP client implementation
|-- udp_server.cpp # UDP server implementation
|-- udp_client.cpp # UDP client implementation
|-- common.cpp     # Common functions and definitions
|-- common.h       # Common header file
|-- Makefile       # Makefile for building the server and client
```

### Usage

0. **Prerequisites**:
   - Ensure you have a C++ compiler (like `g++`) and `make` installed on your system.

```bash
# Debian/Ubuntu
sudo apt update
sudo apt install g++ make

# macOS (using Homebrew)
brew install g++ make
```

1. **Build the Server and Client**:

```bash
cd c++
make
```

2. **Run the TCP Server and Client**:

```bash
./tcp_server
```

```bash
# ready in another terminal
./tcp_client
```

3. **Run the UDP Server and Client**:

```bash
./udp_server
```

```bash
# ready in another terminal
./udp_client
```

4. **Clean Up**:

```bash
make clean
```

### Notes

- The tcp_client connects to `127.0.0.1` by default.
    - To connect to a different server, provide the server IP as edited SERVER_IP in `common.hpp`.
- The C++ implementation **DOES NOT** use modern C++ features and the C++ Standard Library

## Python Implementation
The Python implementation includes both a TCP server and a TCP client. The server listens for incoming connections on port 17 and sends the Quote of the Day to the connected client. The client connects to the server and displays the received quote.

### Files

```
|-- tcp_server.py  # TCP server implementation
|-- tcp_client.py  # TCP client implementation
|-- udp_server.py  # UDP server implementation
|-- udp_client.py  # UDP client implementation
```

### Usage

0. **Prerequisites**

    - Ensure you have Python 3 installed on your system.

```bash
# Debian/Ubuntu
sudo apt update
sudo apt install python3
```

1. **Run the TCP Server and Client**

    - The TCP Server requires superuser privileges to bind to port 17.

```bash
sudo python3 tcp_server.py
```

```bash
# ready in another terminal
python3 tcp_client.py
```

2. **Run the UDP Server and Client**

    - The UDP Server requires superuser privileges to bind to port 17.

```bash
sudo python3 udp_server.py
```

```bash
# ready in another terminal
python3 udp_client.py
```

## Java Implementation
The Java implementation includes both a TCP server and a TCP client. The server listens for incoming connections on port 17 and sends the Quote of the Day to the connected client. The client connects to the server and displays the received quote.

### Files

```
java/
|-- tcp/
|   |-- tcp_server.java  # TCP server implementation
|   |-- tcp_client.java  # TCP client implementation
|-- udp/
    |-- udp_server.java  # UDP server implementation
    |-- udp_client.java  # UDP client implementation
```

### Usage

0. **Prerequisites**:

Ensure you have Java Development Kit (JDK) installed on your system by following the [download site](https://www.java.com/ja/download/help/download_options.html)

1. **Run the TCP Server and Client**:

```bash
cd java/udp
javac tcp_server.java
sudo java tcp_server

# ready in another terminal
javac tcp_client.java
java tcp_client
```

2. **Run the UDP Server and Client**:

```bash
cd java/udp
javac udp_server.java
sudo java udp_server

# ready in another terminal
javac udp_client.java
java udp_client
```

### Notes

- Java Download Site
    - https://www.java.com/ja/download/help/download_options.html
- Java network library document
    - https://docs.oracle.com/javase/jp/8/docs/api/java/net/package-summary.html
