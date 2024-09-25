#include "tle.h"
#include <stdexcept>

namespace orp {
    // Space locations for verification of the TLEs
    const int LINE_1_SPACES[8] = { 1, 8, 17, 32, 43, 52, 61, 63 };
    const int LINE_2_SPACES[7] = { 1, 7, 16, 25, 33, 42, 51 };

    TLE::TLE() {}

    TLE::TLE(const std::string& line1, const std::string& line2) {
        // Verify the checksum of both lines
        verifyChecksum(line1);
        verifyChecksum(line2);

        // Verify line numbers
        if (line1[0] != '1') { throw std::runtime_error("First line does not start with number 1"); }
        if (line2[0] != '2') { throw std::runtime_error("Second line does not start with number 2"); }

        // Verify spaces
        verifySpaces(line1, LINE_1_SPACES, sizeof(LINE_1_SPACES) / sizeof(int));
        verifySpaces(line2, LINE_2_SPACES, sizeof(LINE_2_SPACES) / sizeof(int));
    }

    TLE::TLE(const TLE& b) {
        // TODO
    }

    void TLE::verifyChecksum(const std::string& line) {
        // Check the length of the line
        if (line.length() != TLE_LINE_LEN) { throw std::runtime_error("Invalid line length"); }

        // Compute the checksum
        int checksum = 0;
        for (char c : line) {
            if (!std::isdigit(c)) { continue; }
            checksum += c - '0';
        }

        // Throw an error if it's wrong
        if (checksum % 10) { throw std::runtime_error("Invalid line checksum"); }
    }

    void TLE::verifySpaces(const std::string& line, const int spaces[], int spaceCount) {
        // Check for spaces in all given locations
        for (int i = 0; i < spaceCount; i++) {
            if (line[spaces[i]] != ' ') { throw std::runtime_error("Expected space"); }
        }
    }
}