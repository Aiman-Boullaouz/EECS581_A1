#ifndef IPV4_H
#define IPV4_H

#include <string>

bool extractIPv4(const std::string& str, unsigned long& outAddress, int& outPort);

#endif