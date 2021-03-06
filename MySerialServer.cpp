////
//// Created by yonatan on 14/01/2020.
////
//
//#include "MySerialServer.h"
//#include <iostream>
//#include <sys/socket.h>
//#include <unistd.h>
//#include <netinet/in.h>
//#include <thread>
//#include <mutex>
//
//static bool run = true;
//
//void MySerialServer::open(int port, ClientHandler *clientHandler) {
//    // open a new thread and listen to client
//    // make it at loop
//    thread serverThread(MySerialServer::openServer, port, clientHandler);
//    serverThread.join();
//}
//
//void MySerialServer::stop() {
//    run = false;
//}
//
//int MySerialServer::openServer(int port, ClientHandler *clientHandler) {
//    int opt = 1;
//    //create socket
//    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
//    if (socketfd == -1) {
//        //error
//        std::cerr << "Could not create a socket" << std::endl;
//        return -1;
//    }
//
//    struct timeval tv;
//    tv.tv_sec = 5;
//    // Forcefully attaching socket
//    if (setsockopt(socketfd, SOL_SOCKET, SO_RCVTIMEO,
//                   &tv, sizeof(tv))) {
//        perror("setsockopt");
//        exit(EXIT_FAILURE);
//    }
//    //bind socket to IP address
//    // we first need to create the sockaddr obj.
//    sockaddr_in address; //in means IP4
//    address.sin_family = AF_INET;
//    address.sin_addr.s_addr = INADDR_ANY; //give me any IP allocated for my machine
//    address.sin_port = htons(port);
//
//    //the actual bind command
//    if (::bind(socketfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
//        std::cerr << "Could not bind the socket to an IP" << std::endl;
//        return -2;
//    }
//
//    while (run) {
//        //making socket listen to the port
//        if (listen(socketfd, 5) == -1) { //can also set to SOMAXCON (max connections)
//            std::cerr << "Error during listening command" << std::endl;
//            return -3;
//        } else {
//            std::cout << "Server is now listening ..." << std::endl;
//        }
//
//        // accepting a client
//        int client_socket = accept(socketfd, (struct sockaddr *) &address,
//                                   (socklen_t *) &address);
//        if (errno == EWOULDBLOCK) {
//            std::cerr << "Time Out" << std::endl;
//            return -8;
//        }
//
//        if (client_socket == -1) {
//            std::cerr << "Error accepting client" << std::endl;
//            return -4;
//        }
//        clientHandler->handleClient(client_socket);
//    }
//    close(socketfd);//closing the listening socket
//}