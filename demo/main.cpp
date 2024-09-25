#include <stdio.h>
#include "tle.h"

#define TEST_LINE_1 "1 23455U 94089A   97320.90946019  .00000140  00000-0  10191-3 0  2621"
#define TEST_LINE_2 "2 23455  99.0090 272.6745 0008546 223.1686 136.8816 14.11711747148495"

int main() {
    try {
        // Parse the TLE
        orp::TLE tle(TEST_LINE_1, TEST_LINE_2);

        const char* classStr;
        switch (tle.classification) {
        case orp::CLASS_UNCLASSIFIED:
            classStr = "Unclassified";
            break;
        case orp::CLASS_CLASSIFIED:
            classStr = "Classified";
            break;
        case orp::CLASS_SECRET:
            classStr = "Secret";
            break;
        default:
            classStr = "Unknown";
            break;
        }

        printf("Catalog Number:                     %d\n", tle.catalogNumber);
        printf("Classification:                     %s\n", classStr);
        printf("International Designator:           %d-%03d%s\n", tle.intlDesignator.launchYear, tle.intlDesignator.launchNumber, tle.intlDesignator.piece);
        printf("Epoch Year:                         %d\n", tle.epochYear);
        printf("Epoch Day:                          %0.8lf\n", tle.epochDay);
        printf("First Derivative of Mean Motion:    %0.8lf\n", tle.meanMotionDt);
        printf("Second Derivative of Mean Motion:   %0.8lf\n", tle.meanMotionDt2);
    }
    catch (const std::exception& e) {
        fprintf(stderr, "%s\n", e.what());
    }

    return 0;
}