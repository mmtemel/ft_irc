# Internet Relay Chat

(International standard	RFC 1459)
Internet Relay Chat (IRC) is a text-based chat system for instant messaging. IRC is designed for group communication in discussion forums, called channels but also allows one-on-one communication via private messages as well as chat and data transfer, including file sharing.

Internet Relay Chat is implemented as an application layer protocol to facilitate communication in the form of text. The chat process works on a client–server networking model. Users connect, using a client—which may be a web app, a standalone desktop program, or embedded into part of a larger program—to an IRC server

# Clients
Client software exists for various operating systems or software packages, as well as web-based or inside games. Many different clients are available for the various operating systems, including Windows, Unix and Linux, macOS and mobile operating systems (such as iOS and Android). On Windows, Hexchat is one of the most popular clients.

# Mindmap
<img width="944" alt="Mindmap_irc" src="https://user-images.githubusercontent.com/73845925/236683123-f782a004-5c81-41fa-8d6d-215e8fdc7349.png">

# What is Socket and What is Socket Programming?

Sockets are commonly used for client and server interaction. 
Typical system configuration places the server on one machine, with the clients on other machines. 
The clients connect to the server, exchange information, and then disconnect.

A socket has a typical flow of events.
In a connection-oriented client-to-server model, the socket on the server process waits for requests from a client. To do this, 
the server first establishes (binds) an address that clients can use to find the server. When the address is established, 
the server waits for clients to request a service. 
The client-to-server data exchange takes place when a client connects to the server through a socket. 
The server performs the client's request and sends the reply back to the client.

![socket](https://user-images.githubusercontent.com/73845925/230378632-a7e795d3-e6e4-406a-a50d-5f37f4883da1.png)
![1280px-Ircnetz-Schema svg](https://user-images.githubusercontent.com/73845925/235754479-3b10f34f-0b5d-4e1b-af07-f27a7ae1ee26.png)


