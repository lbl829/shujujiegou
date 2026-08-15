#include <stdio.h>
#include <string.h>

char* longestCommonPrefix(char** strs, int strsSize)
{
    if (strsSize == 0) {
        return "";
    }
    int mindex = 0;
    for (int i = 0; i < strsSize; i++) {
        if (strlen(strs[i]) < strlen(strs[mindex])) {
            mindex = i;
        }
    }
    size_t samelength = strlen(strs[mindex]);
    for (int i = 0; i < strsSize; i++) {
        size_t currentlength = 0;
        for (int j = 0; j < samelength; j++) {
            if (strs[i][j] != strs[mindex][j]) {
                break;
            }
            currentlength++;
        }
        if (currentlength < samelength) {
            samelength = currentlength;
        }
    }
    strs[mindex][samelength] = '\0';
    return strs[mindex];
}

int main()
{
    int strsSize = 3;
    char s0[] = "flower";
    char s1[] = "flow";
    char s2[] = "flight";
    char* strs[3] = {s0, s1, s2};

    char* result = longestCommonPrefix(strs, strsSize);
    printf("Longest Common Prefix: %s\n", result);
    return 0;
}
