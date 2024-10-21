//
// Created by havso on 14/10/2024.
//
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <cmath>

#include "../cmake-build-debug/_deps/threepp-src/include/threepp/math/MathUtils.hpp"

std::vector<std::string> lidar_output = {
        "GD0044072501",
        "00P",
        "00819",
        "00R00R00R00T00W00T00Q00O00I00I00I0\\W0\\W0\\W0\\W0\\W0]80000000000070k",
        "0000000000000000000000000000000000000000000010G10C10<1061061060o=",
        "k0ok0o^0o<0o70o10nb0nW0nQ0nM0nE0nA0n80n70mj0mg0m^0m\\0mZ0mM0mJ0mHK",
        "0mB0m?0m90lm0ll0ll0ll0m50mB0n200000000000710C10C12M12M12M12N12M1T",
        "2112112811i11i11i0m`0m`0m^0m^0m\\0m\\0mV0mV0mQ0mQ0mQ0mW0mY0md0mh0mB",
        "n0n10n10n10m90m90m90m<0m=0m>0m=0m>0mE00000000000000010a0oa0oa10V;",
        "10V11G12;12;12;10c10U10U10^10c11512\\13\\13^13c13c13e14E14[14[14[1g",
        "4S14Q14I14I14I00000000000000000000000000018N17g17g17g17M16A15l15@",
        "k15c15414O14O14O14e15315B16:000000000000000000000000000000000000F",
        "0001:Z1:Z1:Z1;;1;<1;[1;e1<>1<?1<K1<e1<k1=L1=j1>?1>V1>_1>_1?81?_18",
        "Cn1DD1DD1D:1D:1CZ1CZ1CZ1Cn1DG1Dd00000000000000000000000000000000R",
        "0000000000000000000000000000000000000000006006006006006006000000T",
        "0000000000060060060060060060060060060060060060060060060060060060\\",
        "0600600600600600600600600600600600600600600600600600600600600600n",
        "60060061FL1FA1F<1Ej1Ec1ET1EE1E@1E?1E21Dc1D[1DS1DP1DN1DJ1D@1Co1C`4",
        "1C`1C[1CV1CJ1CE1CD1C;1C:1C71C51C31B=1B<1B81B21Aj1Ah1Ah1Ah1Ag1Ag1`",
        "A`1A]1AZ1AZ1AZ1AZ1AZ1AZ1AZ1AZ1AZ1AY1AY1AY1AS1AZ1A\\1A\\1AZ1A]1A_1A8",
        "_1Af1Aj1Aj1Am1Aj1Aj1Aj1B11Ak1B11B<1Bf1Bl1Bl1C01C51C:1C<1C@1CM1CO`",
        "1CW1Ca1Cc1D01D11D31D61DB1DN1DX1Dd1Dh1E41E=1EE1EF1EU1EW1Ei1F;1F>1e",
        "FT00600600600600600600600600600600600600600600600600600600600600b",
        "6006006006006006006006006006006000006006006006006006006006006006n",
        "0060060060060000000000000000000000000000000000000000000000000000H",
        "00000000000000000000000000000000000000000000000000000000000000000",
        "00000000000000000000000000000000000000000000000000000000000000000",
        "00000000000000000000000000000000000000000000000000000000000000000",
        "00000000000000000000000000000000000000000000000000000000000000000",
        "0000000000000000000000006006006006006006006006006006006000006006>",
        "0060060060060060060060060060060060060060060060000000000000000000J",
        "0000004904404404900000000600000000000000700600600600600600600600Q",
        "60060060060060060060060060060060000000000000000000000000000000002",
        "0000JM0JJ0Ia0Ia0Ia0Ie0Ij0Ij0Io0Ij0If0I\\0H80H80Gl0Ge0G[0GZ0GZ0GZ0P",
        "GX0GX0GX0Gh0Gh0Gi0Gj0Gk0H80H;0HJ0HP0HU0H[0H_0Hm0I40I@0IQ0J50JP@"
    };


std::vector<double> message{};

float scale_value(float input_value) {
    float input_min=0;
    float input_max=5000;
    float output_min=0;
    float output_max=200;
    float calc = ((input_value - input_min) * (output_max - output_min)) / (input_max - input_min) + output_min;
    return calc;
}


char checksumCalculation(const std::string& line) {
//Adds the ASCII values of the characters torether. Then adjust for ASCII range
    int ascii_sum{};
    for (const char c : line) {
        ascii_sum += static_cast<int>(c);
    }
    const char checksum = (ascii_sum & 0x3F) + 0x30;
    return checksum;
}
bool verifyLidarLineChecksum(const std::string& line) {
    if (line.empty()) {
        return false;
    }
    const char checksumFromReading = line.back();
    //Extract the checksum from the last char from lidar reading
    const std::string lidarReading = line.substr(0, line.length() - 1);
    //Remove checksum from reading
    const char checksumCalculated = checksumCalculation(lidarReading);
    return checksumCalculated == checksumFromReading;
}
bool verifyChecksum(const std::vector<std::string>) {
    bool checksum_valid = true;
    for (size_t i = 1; i < lidar_output.size(); i++) {
        const std::string& line = lidar_output[i];
        if (verifyLidarLineChecksum(line)) {
            continue;
        } else {
            checksum_valid = false;
        }
    }
    return checksum_valid;
}
int decode(const char code[], int byte) {
    int value = 0;
    int i;
    for (i = 0; i < byte; ++i) {
        value <<= 6;
        value &= ~0x3f;
        value |= code[i] - 0x30;
    }
    return value;
}

void drawRadiusLine(sf::RenderWindow& window, sf::CircleShape& circle, float angle_deg) {
    float angle_radians = angle_deg * (threepp::math::PI / 180.0f);
    sf::Vector2f endpoint(window.getSize().x / 2 + circle.getRadius() * cos(angle_radians),
                          window.getSize().y / 2 + circle.getRadius() * sin(angle_radians));
    sf::Vertex line[] = {
        sf::Vertex(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2), sf::Color::Magenta), // Start at the center
        sf::Vertex(endpoint, sf::Color::Magenta)
    };
    window.draw(line, 2, sf::Lines);
}

std::vector<int> lidarReadingDecoded(std::vector<std::string> input) {
    std::vector<int> int_vector;

    std::string lidarOutput_long;
    for (int i = 3; i < input.size(); i++) {
        std::string lidarReading = input[i].substr(0, input[i].length() - 1);
        //std::cout  << lidarReading << std::endl;
        lidarOutput_long += lidarReading;
    }

    for (uint64_t i = 0; i < lidarOutput_long.length(); i += 3) {
        std::string c(3, ' ');
        c[0] = lidarOutput_long[i];
        c[1] = lidarOutput_long[i+1];
        c[2] = lidarOutput_long[i+2];
        int decodedValue = decode(c.c_str(), 3);
        int_vector.push_back(decodedValue);
    }
    return int_vector;
}

sf::Vector2f polarToCartesian(float angle_degrees, float distance, const sf::Vector2f& center) {
    float angle_radians = angle_degrees * (3.14159f / 180.0f); // Convert degrees to radians
    float x = cos(angle_radians) * distance;  // Scale these based on your window dimensions or desired scale factor
    float y = sin(angle_radians) * distance;
    return sf::Vector2f(center.x + x, center.y - y);
}


void drawRadarOutput(sf::RenderWindow& window, std::vector<int> dist) {
    float start_ang = 150;
    float end_ang = 150+240;
    float ang_step = 240.0f / static_cast<float>(dist.size());

    std::vector<float> ang_rad_array(dist.size());
    std::vector<float> ang_dist_array(dist.size());
    std::cout << ang_step <<  "      SDHUAIFDHIUAE "  << std::endl;

    for (int i = 0; i < dist.size(); i++) {
        ang_dist_array[i] = scale_value(dist[i]);
        if (ang_dist_array[i] > 250) {
            std::cerr << "Calculation error" << std::endl;
        }
    }
    for (int i = start_ang; i < end_ang; i++) {
        float ang = start_ang + ang_step * i;
        ang_rad_array[i] = ang * threepp::math::PI/180;
    }


    for (int i = 0; i < ang_rad_array.size(); i++) {
        std::cout << "Rad " << ang_rad_array[i] << "  dist: " << ang_dist_array[i] << std::endl;
    }


    for (int i = 0; i < dist.size(); i++) {
        sf::CircleShape point(3*i*0.01);
        point.setFillColor(sf::Color::Green);

        float x = cos(ang_rad_array[i]) * ang_dist_array[i] + window.getSize().x/2;
        float y = sin(ang_rad_array[i]) * ang_dist_array[i] + window.getSize().y/2;
        point.setPosition(x,y);
        window.draw(point);
    }
    sf::CircleShape point2(10);
    point2.setFillColor(sf::Color::Blue);
    point2.setPosition( 300, 400);
    window.draw(point2);
}

void drawRadarPoint(sf::RenderWindow& window, float angle_deg, float distance, const sf::Vector2f& center) {
    sf::Vector2f pointPosition = polarToCartesian(angle_deg, distance, center);
    sf::CircleShape point(3); // Smaller radius for clarity
    point.setPosition(pointPosition);
    point.setFillColor(sf::Color::Black);
    window.draw(point);
}


int main() {
    std::vector<int> lidar_ints;

    if (verifyChecksum(lidar_output)) {
        lidar_ints = lidarReadingDecoded(lidar_output);
        for (int lidar_ints : lidar_ints) {
            std::cout << lidar_ints << std::endl;
        }
        std::cout << "Checksum valid: " << "Yes" << std::endl;
    }
    else {
        std::cout << "Checksum valid: " << "NO :(" << std::endl;
        std::cout << "Lidar bogos output" << std::endl;
    }




    sf::RenderWindow window(sf::VideoMode(800, 600), "Nerdar");

    window.setFramerateLimit(60);

    sf::CircleShape circle(270);
    circle.setFillColor(sf::Color::Transparent);
    circle.setOutlineThickness(5);
    circle.setOutlineColor(sf::Color::Red);
    float centerX = (window.getSize().x - 2 * circle.getRadius()) / 2.0f;
    float centerY = (window.getSize().y - 2 * circle.getRadius()) / 2.0f;
    circle.setPosition(centerX, centerY);


    sf::Vertex line[] = {
        sf::Vertex(sf::Vector2f(0, window.getSize().y / 2), sf::Color::Yellow),
        sf::Vertex(sf::Vector2f(window.getSize().x, window.getSize().y / 2), sf::Color::Yellow)
    };

    sf::Vertex lineFWD[] = {
        sf::Vertex(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2), sf::Color::Magenta),
        sf::Vertex(sf::Vector2f(window.getSize().x/2, 0), sf::Color::Magenta)
    };


    // Define the center point (origo)
    sf::CircleShape centerPoint(5); // small radius for the center point
    centerPoint.setFillColor(sf::Color::Green);
    // Position it at the center of the circle
    centerPoint.setPosition(395, 295); // slight adjustment for the radius of the center point

    // Define the midpoint between the center and the edge of the circle
    sf::CircleShape midPoint(5);
    midPoint.setFillColor(sf::Color::Blue);
    // Calculate the midpoint position
    float midX = circle.getPosition().x + circle.getRadius() + circle.getRadius() * 0.5f * cos(45 * (3.14159265 / 180)); // 45 degrees for example
    float midY = circle.getPosition().y + circle.getRadius() + circle.getRadius() * 0.5f * sin(45 * (3.14159265 / 180));
    midPoint.setPosition(midX - 5, midY - 5); // adjust for the radius of the midpoint

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);  // Clear the previous frame

        // Draw the circle, center point, and midpoint
        window.draw(circle);
        window.draw(centerPoint);
        window.draw(midPoint);
        window.draw(line, 2, sf::Lines);
        window.draw(lineFWD, 2, sf::Lines);
        drawRadiusLine(window, circle, 150+240);
        drawRadiusLine(window, circle, 30+120);
        drawRadarOutput(window, lidar_ints);



        window.display(); // Display everything drawn

    }



    return 0;

}


