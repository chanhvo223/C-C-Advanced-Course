#include "convertString2Bin.h"

void str2bin(char *str, int len)
{
    for (int i = 0; i < len; i++)
    {
        printf("%c: ", str[i]);

        for (int bit = 7; bit >= 0; bit--)
        {
            printf("%d", (str[i] >> bit) & 1);
        }

        printf("\n");
    }
}