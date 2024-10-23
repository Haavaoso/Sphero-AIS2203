// Created by havso on 22/10/2024.
//

#ifndef NETWORK_HELPER_HPP
#define NETWORK_HELPER_HPP

#ifndef NETWORKING_DEMO_NETWORK_HELPER_HPP
#define NETWORKING_DEMO_NETWORK_HELPER_HPP

#include <vector>

enum class byte_order {
    LITTLE, BIG
};

std::vector<unsigned char> int_to_bytes(int n, byte_order order = byte_order::LITTLE) {
    std::vector<unsigned char> bytes(4);

    if (order == byte_order::LITTLE) {
        bytes[0] = n & 0xFF;
        bytes[1] = (n >> 8) & 0xFF;
        bytes[2] = (n >> 16) & 0xFF;
        bytes[3] = (n >> 24) & 0xFF;
    } else {
        bytes[0] = (n >> 24) & 0xFF;
        bytes[1] = (n >> 16) & 0xFF;
        bytes[2] = (n >> 8) & 0xFF;
        bytes[3] = n & 0xFF;
    }

    return bytes;
}

int bytes_to_int(const std::vector<unsigned char>& buffer, byte_order order = byte_order::LITTLE) {
    if (order == byte_order::LITTLE) {
        return int(buffer[0] |
                   buffer[1] << 8 |
                   buffer[2] << 16 |
                   buffer[3] << 24);
    } else {
        return int(buffer[3] |
                   buffer[2] << 8 |
                   buffer[1] << 16 |
                   buffer[0] << 24);
    }
}

#endif //NETWORKING_DEMO_NETWORK_HELPER_HPP
#endif //NETWORK_HELPER_HPP
