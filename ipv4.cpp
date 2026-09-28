#include "ipv4.h"

namespace {
bool isDigit(char character) {
    return character >= '0' && character <= '9';
}

bool isTokenCharacter(char character) {
    return isDigit(character) || character == '.' || character == ':';
}
}

bool extractIPv4(const std::string& str, unsigned long& outAddress, int& outPort) {
    outAddress = 0;
    outPort = -1;

    for (std::size_t start = 0; start < str.size(); ++start) {
        if (!isDigit(str[start]) ||
            (start > 0 && isTokenCharacter(str[start - 1]))) {
            continue;
        }

        std::size_t position = start;
        unsigned int octets[4] = {0, 0, 0, 0};
        bool valid = true;

        for (int octetIndex = 0; octetIndex < 4 && valid; ++octetIndex) {
            if (position >= str.size() || !isDigit(str[position])) {
                valid = false;
                break;
            }

            const std::size_t firstDigit = position;
            unsigned int value = 0;
            int digitCount = 0;
            while (position < str.size() && isDigit(str[position])) {
                if (digitCount == 3) {
                    valid = false;
                    break;
                }
                value = value * 10 + static_cast<unsigned int>(str[position] - '0');
                ++digitCount;
                ++position;
            }

            if (!valid || (digitCount > 1 && str[firstDigit] == '0') || value > 255) {
                valid = false;
                break;
            }
            octets[octetIndex] = value;

            if (octetIndex < 3) {
                if (position >= str.size() || str[position] != '.') {
                    valid = false;
                    break;
                }
                ++position;
            }
        }

        if (!valid) {
            continue;
        }

        int port = -1;
        if (position < str.size() && str[position] == ':') {
            ++position;
            if (position >= str.size() || !isDigit(str[position])) {
                continue;
            }

            const std::size_t firstDigit = position;
            unsigned int value = 0;
            int digitCount = 0;
            while (position < str.size() && isDigit(str[position])) {
                if (digitCount == 5) {
                    valid = false;
                    break;
                }
                value = value * 10 + static_cast<unsigned int>(str[position] - '0');
                ++digitCount;
                ++position;
            }

            if (!valid || (digitCount > 1 && str[firstDigit] == '0') || value > 65535) {
                continue;
            }
            port = static_cast<int>(value);
        }

        if (position < str.size() && isTokenCharacter(str[position])) {
            continue;
        }

        outAddress = (static_cast<unsigned long>(octets[0]) << 24) |
                     (static_cast<unsigned long>(octets[1]) << 16) |
                     (static_cast<unsigned long>(octets[2]) << 8) |
                     static_cast<unsigned long>(octets[3]);
        outPort = port;
        return true;
    }

    return false;
}