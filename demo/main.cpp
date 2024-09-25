#include <stdio.h>
#include "tle.h"

#define TEST_LINE_1 "1 23455U 94089A   97320.90946019  .00000140  00000-0  10191-3 0  2621"
#define TEST_LINE_2 "2 23455  99.0090 272.6745 0008546 223.1686 136.8816 14.11711747148495"

int main() {
    try {
        // Parse the TLE
        orp::TLE tle(TEST_LINE_1, TEST_LINE_2);
    }
    catch (const std::exception& e) {
        fprintf(stderr, "%s\n", e.what());
    }

    return 0;
}