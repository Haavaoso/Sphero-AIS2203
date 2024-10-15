//
// Created by havso on 14/10/2024.
//
#include <vector>

#include <iostream>
#include <string>
#include <sstream>


    std::vector<std::string> result = {
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

char checksumCalculation(const std::string& line) {
//Adds the ASCII values of the characters torether. Then adjust for ASCII range
    int ascii_sum{};
    for (const char c : line) {
        ascii_sum += static_cast<int>(c);
    }
    const char checksum = (ascii_sum & 0x3F) + 0x30;
    return checksum;
}
bool verifyLidarChecksum(const std::string& line) {
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





int main() {


    bool checksum_valid = true;
    std::string lidarOutput_long;
    std::vector<int> lidar_ints;
    std::vector<std::string> lidar_output= result;
    for (size_t i = 1; i < lidar_output.size(); i++) {
        const std::string& line = lidar_output[i];
        if (verifyLidarChecksum(line)) {
            continue;
        } else {
            checksum_valid = false;
        }
    }

    std::cout << "Checksum valid: " << checksum_valid << std::endl;





    if (checksum_valid) {
        for (int i = 3; i < lidar_output.size(); i++) {
            std::string lidarReading = lidar_output[i].substr(0, lidar_output[i].length() - 1);
            std::cout  << lidarReading << std::endl;
            lidarOutput_long += lidarReading;
        }
    }
    std::cout << "Ogga: " << lidarOutput_long.size() << "        " << lidarOutput_long << std::endl;


    // lidarOutput_long.pop_back();
    // lidarOutput_long.pop_back();



    for (uint64_t i = 0; i < lidarOutput_long.length(); i += 3) {
        std::string c(3, ' ');
        c[0] = lidarOutput_long[i];
        c[1] = lidarOutput_long[i+1];
        c[2] = lidarOutput_long[i+2];
        int decodedValue = decode(c.c_str(), 3);
        lidar_ints.push_back(decodedValue);
    }


    // Print the decoded distances
    for (int lidar_ints : lidar_ints) {
        std::cout << lidar_ints << std::endl;
    }



    int oooo= decode("J50", 3);
    std::cout << oooo << std::endl;



    for (auto result : result) {
        std::cout << result << std::endl;
    }



    return 0;
}


