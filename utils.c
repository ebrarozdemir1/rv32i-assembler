#include <string.h>
#include <ctype.h>
#include "utils.h"

void trim(char *str) {
    int start = 0;
    while (isspace((unsigned char)str[start])) start++;

    int end = strlen(str) - 1;
    while (end >= start && isspace((unsigned char)str[end])) {
        str[end] = '\0';
        end--;
    }

    if (start > 0)
        memmove(str, str + start, strlen(str + start) + 1);
}
