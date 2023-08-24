# Network Socket Communication - Client and Server

This project demonstrates how network communication can be established through socket communication. The simulation includes communication between a client and a server, where the server stores information about sensors and equipment. Both client and server are developed using the C programming language and the standard C socket library.

## Introduction

The objective of this project is to showcase socket-based communication in computer networks. It involves implementing a client and server interaction, where the server manages data related to sensors and equipment. The development of the client and server components is done in C, using the standard socket library for communication.

## Development

Based on the materials provided in the moodle, a basic client and server application was developed. The communication involves sending messages from the client to the server using both IPv4 and IPv6. The client can send four types of valid commands: "add", "remove", "list", and "read". The application also handles invalid messages by closing the connection with the client. Each command involves referencing sensors and equipment. A static array of 15 positions (due to the project's specifications) is used to simulate a database.

## Challenges

String manipulation posed a challenge during development, as it requires a lower-level manipulation compared to other languages. Error handling in the server also proved challenging, particularly due to the need to handle edge cases, such as adding or removing multiple sensors, reading non-existent sensors, etc. Additionally, addressing the differences in data structure sizes between IPv4 and IPv6 communication was a challenge when ensuring compatibility between the client and server.

## Getting Started

To compile and run the client and server applications:

1. Navigate to the 'client' and 'server' directories.
2. Compile each application using the provided makefile or by using the following command:
   ```sh
   make all
3. Test application by using the following command:
   ```sh
   make test
