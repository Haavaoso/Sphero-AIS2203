//
// Created by havso on 22/10/2024.
//

#include <iostream>
#include "Server.hpp"


int main() {
    for (int i = 99; i < 103; i++){
    std::cerr << "main" << std::endl;
    }
    std::string ip = "localhost";
    int port = 9090;

    Server server(port);
    std::cout << "Server is running and waiting for a client connection on port " << port << "..." << std::endl;

    auto ok = server.accept();

    std::cout << "Client connected!" << std::endl;

    std::vector<unsigned char> receivedData;

    server.recieveData(ok,receivedData);

    std::string data(receivedData.begin(), receivedData.end() );
    std::cout << "Received from client: " << data << std::endl;



    std::string response = "I have aaaaaaaaa monster!";
    std::vector<unsigned char> responseData(response.begin(), response.end());
    server.sendData(ok, responseData);


    ok->close();

    return 21;
}


