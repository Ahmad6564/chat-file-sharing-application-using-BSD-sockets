# Chat-file-sharing-application-using-BSD-sockets
This is simply chat file sharing application using BSD socket programming in cpp language. I have created the community of four members in which there are three clients and one server.
Each client can send the file and chat with other two clients and server.
# What is BSD Socket?
BSD sockets, or Berkeley Software Distribution sockets, refer to a programming interface for network communication in Unix-like operating systems. In simpler terms, it's a set of tools and functions that allows software applications to communicate over a network, such as the internet.
Imagine you have two computers, and you want them to exchange information. BSD sockets provide a standardized way for software on these computers to send and receive data. It includes functions that help in creating connections, sending data, and receiving data between these computers.
## Project Requirement
The application must comply with the following requirements:

1. When a client joins the chat, details about all the files in the client’s shared directory must be shared with the community.
  
2. There should be at least 4 members in the community.
  
3. Each client share the list of files in its directory.
  
4. Each client to able the download the files and share it files to other clients and server.


## Overview of Project:

A single TCP server with three connected clients with each client having a different file to send to other clients. Whenever a message is sent by a client, it first goes to the server which then relays that message to all the connected clients. Same is the case with file sharing. A client sends a file, it is then received by the server which then sends that same file to all other connected clients. The server can also broadcast its own messages to other clients. Client also shows the files in their directory.


## How to run the project? 

1. I have the run the project using wsl in windows. I have made three folders named server, client1, client2 and client3. Each of folder contains the files that they want to share and also contain the cpp files.

![image](https://github.com/Ahmad6564/chat-file-sharing-application-using-BSD-sockets/assets/89437620/f52966ab-137f-4cda-8ec1-6011348db435)


![image](https://github.com/Ahmad6564/chat-file-sharing-application-using-BSD-sockets/assets/89437620/80a70167-cbf4-4847-81b9-2fec2bafcf2c)



![image](https://github.com/Ahmad6564/chat-file-sharing-application-using-BSD-sockets/assets/89437620/4cf07ae1-3727-4369-b14f-287a3f135284)

2. Now you have too open the wsl terminal in each of folder or directory.

![image](https://github.com/Ahmad6564/chat-file-sharing-application-using-BSD-sockets/assets/89437620/adeb174e-7cc4-4146-8d74-14e3edadefef)

3. Run the linux command **g++ server.cpp -o server**  and **./server** in server terminal.
4.  And run the command **g++ client.cpp -o client**  and **./client** in each client terminal window.
5.  Write the **get_files_list** in terminal to get the lsit of file in directory of clients.
6.  Write the **file** to share the file with each client and server.


![image](https://github.com/Ahmad6564/chat-file-sharing-application-using-BSD-sockets/assets/89437620/e80184e6-167d-4f56-ae25-689270aad322)


 ![image](https://github.com/Ahmad6564/chat-file-sharing-application-using-BSD-sockets/assets/89437620/258cbe27-82d2-4a7e-aac4-83e9bf3b94fd)



![image](https://github.com/Ahmad6564/chat-file-sharing-application-using-BSD-sockets/assets/89437620/48bf513d-fb61-4853-9dce-285cff5a1839)



![image](https://github.com/Ahmad6564/chat-file-sharing-application-using-BSD-sockets/assets/89437620/0ffdc8d0-5715-49cb-b226-b9c4f8aff469)

## Dependencies:
- The code uses standard C++ libraries and does not have external dependencies.
## License:
This project is licensed under the MIT License, allowing you to use and modify the code for your purposes. Please see the LICENSE file for details.

## Acknowledgments:
- The project is designed to provide insights into wireless network topology design and routing algorithms.
  Feel free to enhance this README to include specific details or instructions relevant to your use case.














      

