#include "ipv4.h"

#include <iostream>
#include <string>

int main() {
    std::string input;
    while (true) {
        std::cout << "Enter a string (or 'END' to quit): ";
        if (!std::getline(std::cin, input)) {
            break;
        }
        if (input == "END") {
            std::cout << "Program terminated.\n";
            break;
        }

        unsigned long address = 0;
        int port = -1;
        if (extractIPv4(input, address, port)) {
            std::cout << "Extracted IPv4 address: ";
            unsigned long parts[4] = {
                (address >> 24) & 255UL,
                (address >> 16) & 255UL,
                (address >> 8) & 255UL,
                address & 255UL
            };
            std::cout << parts[0] << '.' << parts[1] << '.' << parts[2] << '.' << parts[3]
                      << " (decimal value: " << address << ", port: ";
            if (port == -1) {
                std::cout << "none";
            } else {
                std::cout << port;
            }
            std::cout << ")\n";
        } else {
            std::cout << "Invalid input: no valid IPv4 address found\n";
        }
    }
    return 0;
}