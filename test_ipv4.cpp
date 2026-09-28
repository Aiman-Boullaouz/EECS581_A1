#include "ipv4.h"

#include <cassert>
#include <string>

void expectValid(const std::string& input, unsigned long address, int port) {
    unsigned long actualAddress = 99;
    int actualPort = 99;
    assert(extractIPv4(input, actualAddress, actualPort));
    assert(actualAddress == address);
    assert(actualPort == port);
}

void expectInvalid(const std::string& input) {
    unsigned long address = 99;
    int port = 99;
    assert(!extractIPv4(input, address, port));
    assert(address == 0);
    assert(port == -1);
}

int main() {
    expectValid("connecting to 192.168.1.1 now", 3232235777UL, -1);
    expectValid("server=10.0.0.255:8080end", 167772415UL, 8080);
    expectValid("192a168.1.1.1", 2818638081UL, -1);
    expectValid("0.0.0.0:0", 0UL, 0);
    expectValid("255.255.255.255:65535", 4294967295UL, 65535);
    expectValid("prefix 1.2.3.4 suffix", 16909060UL, -1);
    expectValid("noise: 8.8.8.8!", 134744072UL, -1);

    expectInvalid("192.168.1.1.");
    expectInvalid(".192.168.1.1");
    expectInvalid(":192.168.1.1");
    expectInvalid("1.2.3.4:80:90");
    expectInvalid("192.168.01.1");
    expectInvalid("1.2.3.4:99999");
    expectInvalid("1.2.3.4:65536");
    expectInvalid("1.2.3");
    expectInvalid("1.2.3.4:1.2");
    expectInvalid("1.2.3.4:00");
    expectInvalid("1.2.3.4:");
    expectInvalid("1.2.3.4::5");
    expectInvalid("1.2.3.4.5");
    expectInvalid("1.2.3:4.5");
    expectInvalid("1..2.3.4");
    expectInvalid("1.2.3..4");
    expectInvalid("01.2.3.4");
    expectInvalid("256.1.1.1");
    expectInvalid("1234.1.1.1");
    expectInvalid("1.2.3.4:123456");
    expectInvalid("no number here");

    expectValid("1.2.3.4:99999 then 8.8.8.8", 134744072UL, -1);

    return 0;
}