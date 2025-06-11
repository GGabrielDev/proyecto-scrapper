#include "StringUtils.h"

void copyString(char* dest, const char* src, int maxLen) {
    int i = 0;
    while (i < maxLen - 1 && src[i] != '\0') {
        dest[i] = src[i];
        ++i;
    }
    dest[i] = '\0';
}

int compareString(const char* a, const char* b) {
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] != b[i]) return a[i] - b[i];
        ++i;
    }
    return a[i] - b[i];
}
