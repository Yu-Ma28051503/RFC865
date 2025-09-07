# RFC865

This repository contains a simple implementation of the Quote of the Day Protocol as defined in [RFC 865](https://datatracker.ietf.org/doc/html/rfc865) using variety of programming languages. The Quote of the Day Protocol is a simple protocol that provides the current date and time to clients over TCP or UDP.

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

