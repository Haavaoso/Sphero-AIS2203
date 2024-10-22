//
// Created by morte on 22/10/2024.
//

#ifndef SERVER_HPP
#define SERVER_HPP

#include "simple_socket/TCPSocket.hpp"

class Server {
    public:
    explicit Server(const simple_socket::TCPServer server) : server_(server) {
        simple_socket::TCPServer server(port);
    }
private:
    simple_socket::TCPServer& server_;
};

/*

#include <iostream>
#include <ostream>
#include <opencv2/opencv.hpp>
#include "simple_socket/TCPSocket.hpp"
#include "network_helper.hpp"


std::vector<Rect> faceDetect(const Mat &image) {
    Mat gray;
    cvtColor(image, gray, COLOR_BGR2GRAY);
    CascadeClassifier faceCascade;
    if (!faceCascade.load("data/haarcascades/haarcascade_frontalface_default.xml")) {
        throw std::runtime_error("failed to load face-cascade classifier");
    }
    std::vector<Rect> faces;
    faceCascade.detectMultiScale(
            gray,
            faces,
            1.1,// scaleFactor (Specifies how much the image size is reduced at each scale (e.g., 1.1 means 10% reduction))
            5,  // minNeighbors (Determines how many neighbors each candidate rectangle should have to retain it. Higher values result in fewer detections but with higher quality.)
            0 | CASCADE_SCALE_IMAGE,
            Size(30, 30)// minSize (Minimum possible object size. Objects smaller than this are ignored.)
    );

    return faces;
}

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
