# EECS581_A1

## Assignment 1

This repository contains the EECS 581 Assignment 1 submission. The assignment is a C or C++ program that scans one input line and extracts one fully valid IPv4 address, optionally followed by a port number.

## Required Behavior

- Read lines continuously until the user enters `END` exactly, with matching case.
- Ignore surrounding garbage while scanning for a candidate address.
- Accept an IPv4 address with four dot-separated octets.
- Require each octet to contain 1-3 digits, have a value from 0 through 255, and have no leading zero unless it is exactly `0`.
- Accept an optional port introduced immediately by `:`. The port must contain 1-5 digits, have a value from 0 through 65535, and follow the same leading-zero rule.
- Reject malformed candidates rather than truncating them or accepting a valid substring inside a longer period/colon-delimited run.
- On failure, report that no valid IPv4 address was found.
- On success, print the required dotted address, its 32-bit decimal value, and either the port or the literal text `none`.
- On termination, print `Program terminated.`.

## Function Contract

Implement the exact prototype for the selected language from the handout:

- C: `int extractIPv4(const char* str, unsigned long* outAddress, int* outPort);`
- C++: `bool extractIPv4(const std::string& str, unsigned long& outAddress, int& outPort);`

On success, return the success value and write the packed address and port. Use `-1` for a missing port. On failure, write address `0` and port `-1`.

## Implementation Restrictions

The parser must perform digit accumulation and validation itself, character by character. Do not use:

- String-to-number conversion functions such as `atoi`, `strtol`, `stoul`, `sscanf`, or numeric `scanf` conversions.
- Address parsing functions such as `inet_aton`, `inet_pton`, or `inet_addr`.
- Regular-expression facilities such as `std::regex` or `regex.h`.

Standard character-classification functions such as `isdigit` are allowed by the handout.

## Verification Checklist

Complete this checklist before submission and replace placeholders with factual evidence. Detailed AI history and evidence are in [AI_DISCLOSURE.md](AI_DISCLOSURE.md).

- [x] Source code implements the exact required `extractIPv4` prototype.
- [x] Candidate validation covers octet count, empty components, ranges, leading zeroes, optional port syntax, and adjacent periods/colons.
- [x] The input loop stops only on the exact line `END`.
- [x] Output text and decimal formatting match the handout exactly.
- [x] Tests cover valid addresses, garbage around addresses, malformed structure, numeric limits, leading zeroes, malformed ports, and no-match input.
- [x] On `cycle3.eecs.ku.edu`, automated tests compiled with `g++ -std=c++17 -Wall -Wextra -pedantic ipv4.cpp test_ipv4.cpp -o test_ipv4` with no compiler output, and `./test_ipv4` returned status `0`.
- [x] On `cycle3.eecs.ku.edu`, the main program compiled with `g++ -std=c++17 -Wall -Wextra -pedantic ipv4.cpp main.cpp -o ipv4`.
- [x] Manual checks confirmed the two valid sample extractions, rejection of `192.168.01.1` and `1.2.3.4:99999`, and `Program terminated.` after `END`.
- [x] AI use is documented in [AI_DISCLOSURE.md](AI_DISCLOSURE.md).
