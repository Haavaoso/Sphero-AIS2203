//
// Created by morte on 22/10/2024.
//

#ifndef SERVER_HPP
#define SERVER_HPP

#include "simple_socket/TCPSocket.hpp"

class Server {
    public:
    explicit Server(const simple_socket::TCPServer &server) : server_(server) {

    }



private:
    const simple_socket::TCPServer& server_;
};

/*

#include <iostream>
#include <ostream>
#include <opencv2/opencv.hpp>
#include "simple_socket/TCPSocket.hpp"
#include "network_helper.hpp"



void receiveData(const std::unique_ptr<simple_socket::SocketConnection> &connection, std::vector<unsigned char> &data) {
    std::vector<unsigned char> sizeBuffer(4); // get msg size
    connection->readExact(sizeBuffer);

    const auto size = bytes_to_int(sizeBuffer);
    std::vector<unsigned char> Buffer(size);
    connection->readExact(Buffer);
    data = Buffer;
}

void sendData(const std::unique_ptr<simple_socket::SocketConnection> &connection, const std::vector<unsigned char> &data) {
    std::vector<unsigned char> imgBuffer;
    auto bytes = int_to_bytes(imgBuffer.size());
    std::vector toSend(imgBuffer.begin(), imgBuffer.end());
    toSend.insert(toSend.begin(), bytes.begin(), bytes.end());

    connection->write(toSend);

}

int main() {
    std::string input;

    std::string ip = "10.53.98.136";
    int port = 9090;
    simple_socket::TCPClientContext client;
    const auto conn = client.connect(ip, port);
    bool running = true;

    std::jthread clientThread([&] {
        std::cin >> input;
        if (input == "q") {
            conn->close();
            running = false;
        }
    });

    while(running) {
        std::vector<unsigned char> data;
        receiveData(conn, data);
        Mat image = imdecode(data, IMREAD_COLOR);

        auto rect = faceDetect(image);
        drawFaces(image, rect);

        std::vector<unsigned char> imgBuffer;
        //std::vector<int> params = {cv::IMWRITE_JPEG_QUALITY, 90};
        imencode(".jpg", image, imgBuffer);
        sendData(conn, imgBuffer);
    }
    return 0;
}
*/

#endif //SERVER_HPP
