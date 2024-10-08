#pragma once
#include <string>

#define TLE_LINE_LEN    69 // Nice

namespace orp {
    enum Class {
        CLASS_UNCLASSIFIED,
        CLASS_CLASSIFIED,
        CLASS_SECRET
    };

    enum EphemerisType {
        EPH_TYPE_NORMAL
    };

    struct IntlDesignator {
        int launchYear;
        int launchNumber;
        char piece[4];
    };

    class TLE {
    public:
        // Default constructor
        TLE();

        /**
         * Parse a TLE set from strings.
         * @param line1 First line of the TLE set.
         * @param line2 Second line of the TLE set.
        */
        TLE(const std::string& line1, const std::string& line2, int epochCentury = 0);

        // Line 1 data
        int catalogNumber;
        Class classification;
        IntlDesignator intlDesignator;
        int epochYear;
        double epochDay;
        double meanMotionDt;
        double meanMotionDt2;
        double dragTerm; // TODO: Better name
        EphemerisType ephemerisType;
        int elementSetNumber;

        // Line 2 data
        double inclination;
        double rightAscension; // TODO: Better name
        double excentricity;
        double perigeeArgument; // TODO: Better name
        double meanAnomaly;
        double meanMotion;
        int revolutionsAtEpoch; // TODO: Better name

    private:
        void verifyChecksum(const std::string& line);
    };
}