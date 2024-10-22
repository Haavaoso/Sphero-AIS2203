//
// Created by morte on 22/10/2024.
//

#ifndef SERVER_HPP
#define SERVER_HPP

#include "simple_socket/TCPSocket.hpp"
#include "network_helper.hpp"
#include <vector>
#include <string>


class Server : public simple_socket::TCPServer {
public:
    explicit Server(int port) : TCPServer(port), port_(port) {
    }

    void recieveData(const std::unique_ptr<simple_socket::SimpleConnection> &connection, std::vector<unsigned char> &data) {
        std::vector<unsigned char> sizeBuffer(4); // get msg size
        connection->readExact(sizeBuffer);

        const auto size = bytes_to_int(sizeBuffer);
        std::vector<unsigned char> Buffer(size);
        connection->readExact(Buffer);
        data = Buffer;
    };
    void sendData(const std::unique_ptr<simple_socket::SimpleConnection> &connection, const std::vector<unsigned char> &data) {
        std::vector<unsigned char> imgBuffer;
        auto bytes = int_to_bytes(imgBuffer.size());
        std::vector toSend(imgBuffer.begin(), imgBuffer.end());
        toSend.insert(toSend.begin(), bytes.begin(), bytes.end());

        connection->write(toSend);
    }

private:
    int port_;
};



#endif //SERVER_HPP
