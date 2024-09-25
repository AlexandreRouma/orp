#include "tle.h"
#include <stdexcept>
#include <cmath>
#include <chrono>
#include <ctime>

#define FIRST_LAUNCH_OF_2000    26052

namespace orp {
    TLE::TLE() {}

    TLE::TLE(const std::string& line1, const std::string& line2, int epochCentury) {
        // Verify the checksums
        verifyChecksum(line1);
        verifyChecksum(line2);

        // Verify line numbers
        if (line1[0] != '1') { throw std::runtime_error("First line does not start with number 1"); }
        if (line2[0] != '2') { throw std::runtime_error("Second line does not start with number 2"); }

        // If the epoch century wasn't given, assume it's the current one
        int currentYear;
        int currentCentury;
        if (!epochCentury) {
            auto now = std::chrono::system_clock::now();
            std::time_t tt = std::chrono::system_clock::to_time_t(now);
            std::tm* tm = std::localtime(&tt);
            currentYear = tm->tm_year % 100;
            currentCentury = (tm->tm_year / 100) + 20;
        }

        // Parse the catalog number
        catalogNumber = std::stoi(line1.substr(2, 5));
        if (!catalogNumber) { throw std::runtime_error("Invalid catalog number"); }

        // Parse the classification
        char classc = std::toupper(line1[7]);
        switch (classc) {
        case 'U':
            classification = CLASS_UNCLASSIFIED;
            break;
        case 'C':
            classification = CLASS_CLASSIFIED;
            break;
        case 'S':
            classification = CLASS_SECRET;
            break;
        default:
            throw std::runtime_error("Invalid classification");
        }

        // Parse the international designator launch year
        std::string launchYearStr = line1.substr(9, 2);
        intlDesignator.launchYear = std::stoi(launchYearStr);
        if (!intlDesignator.launchYear && launchYearStr != "00") {
            throw std::runtime_error("Invalid launch year");
        }
        intlDesignator.launchYear += (catalogNumber >= FIRST_LAUNCH_OF_2000) ? 2000 : 1900;

        // Parse the international designator launch number
        intlDesignator.launchNumber = std::stoi(line1.substr(11, 3));
        if (!intlDesignator.launchNumber) { throw std::runtime_error("Invalid launch number"); }

        // Pars the international designator piece
        int pieceLen = 0;
        for (int i = 0; i < 3; i++) {
            // Get a character
            char pc = line1[14 + i];

            // If it's a space, skip it
            if (pc == ' ') { continue; }

            // Copy the character
            intlDesignator.piece[pieceLen++] = pc;
        }
        intlDesignator.piece[pieceLen] = 0;

        // Parse the epoch year
        std::string epochYearStr = line1.substr(18, 2);
        epochYear = std::stoi(epochYearStr);
        if (!epochYear && epochYearStr != "00") { throw std::runtime_error("Invalid epoch year"); }
        if (epochCentury) {
            epochYear += (epochCentury - 1) * 100;
        }
        else {
            epochYear += (currentCentury - ((epochYear > currentYear) ? 2 : 1)) * 100;
        }

        // Parse the epoch day
        epochDay = std::stod(line1.substr(20, 12));
        if (std::isnan(epochDay)) { throw std::runtime_error("Invalid epoch day"); }

        // Parse first derivative of mean motion
        meanMotionDt = std::stod(line1.substr(33, 10));
        if (std::isnan(meanMotionDt)) { throw std::runtime_error("Invalid derivative of mean motion"); }

        // Parse second derivative of mean motion
        int meanMotionDt2Decimals = std::stoi(line1.substr(44, 6));
        int meanMotionDt2Exponent = std::stoi(line1.substr(51, 1));
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
}