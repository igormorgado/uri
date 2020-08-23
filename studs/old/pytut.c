#include <stdio.h>
#include <string.h>

void subset(char sofar[4], char pref[4], size_t pos) {

    printf("%s\n", sofar);

    size_t i;
    size_t n = strlen(pref);
    char sofar0[4];
    char pref0[4];
    for (i = 0; i < n; ++i) {
        memset(sofar0, 0, 4);
        memset(pref0, 0, 4);
        sprintf(sofar0, "%s%c", sofar, pref[i]);
        sprintf(pref0, "%s", pref + i + 1);
        subset(sofar0, pref0, pos + 1);
    }
}

int main() {
    char pref[5] = "acco";
    char sofar[5] = "";
    subset(sofar, pref, 0);
    return 0;
}
