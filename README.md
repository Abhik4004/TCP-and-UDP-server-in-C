# TCP-and-UDP-server-in-C

## Overview

This repository contains implementations of both **TCP** and **UDP** servers in C, demonstrating fundamental network programming concepts.

## Features

- Basic TCP and UDP server implementations
- Handling multiple client connections
- Efficient socket programming
- Example code with comments for clarity

## Server Protocols

### **TCP (Transmission Control Protocol)**

- **Connection-oriented:** Establishes a dedicated connection before data transmission.
- **Reliable:** Ensures complete data transfer and correct sequencing.
- **Uses stream sockets:** Facilitates communication between sender and receiver.
- **Example use cases:** File transfer, messaging applications.

### **UDP (User Datagram Protocol)**

- **Connectionless:** No need for an established connection before sending data.
- **Fast but unreliable:** Data packets may arrive out of order or get lost.
- **Uses datagram sockets:** Suitable for real-time applications where speed is crucial.
- **Example use cases:** Video streaming, online gaming.

## Getting Started

### **Clone the repository**

```sh
git clone https://github.com/Abhik4004/TCP-and-UDP-server-in-C.git
```

### **Compile the server code**

```sh
gcc -o tcp_server tcp_server.c
gcc -o udp_server udp_server.c
```

### **Run the servers**

- **TCP Server:**
  ```sh
  ./tcp_server
  ```
- **UDP Server:**
  ```sh
  ./udp_server
  ```

## Contributing

Feel free to contribute by submitting issues or pull requests. Any improvements to the implementations or additional features are always welcome!
