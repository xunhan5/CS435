#include"main.h"

//RC4 encryption
// 1 is the pointer to the scrambled s-box structure RC4 in the rc4_init function above;
// Parameter 2 is the data to be encrypted;
// Parameter 3 is the length of data.
void rc4_crypt( RC4_STATE* RC4_state, unsigned char* Data, unsigned long Len)
{
    int i = RC4_state->i, j = RC4_state->j, t = 0;
    unsigned long k = 0;
    unsigned char tmp;
    for (k = 0; k < Len; k++)
    {
        i = (i + 1) % 256;
        j = (j + RC4_state->s[i]) % 256;
        tmp = RC4_state->s[i];
        RC4_state->s[i] = RC4_state->s[j];//exchange RC4_state->s[x] and RC4_state->s[y]
        RC4_state->s[j] = tmp;
        t = (RC4_state->s[i] + RC4_state->s[j]) % 256;
        Data[k] ^= RC4_state->s[t];
    }

    RC4_state->i = i;
    RC4_state->j = j;
}