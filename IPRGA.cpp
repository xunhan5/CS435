#include"main.h"



//RC4 state moving backwards£¬£¨s,i,j£© = IPRGA£¨S*,i*,j*£©£¬The encrypted data of each packet is SizeOfDataSegment+16, and the data segment + hash value
// Parameter 1: state of RC4, including (s, I,j)
// Parameter 2: receiver sc, sc &gt; Mes.sc
// Parameter 3, Mes_Sc in the packet
void IPRGA(RC4_STATE* RC4_state, int sc, int Mes_Sc) {


    for (int s = sc; s > Mes_Sc; s--) {

        int i = RC4_state->i, j = RC4_state->j, t = 0;
        unsigned long k = 0;
        unsigned char tmp;
        int len = SizeOfDataSegment + 16;

        for (k = 0; k < len; k++)
        {
            tmp = RC4_state->s[i];
            RC4_state->s[i] = RC4_state->s[j];//exchange RC4_state->s[x] and RC4_state->s[y]
            RC4_state->s[j] = tmp;

            j = (j - RC4_state->s[i]+256) % 256;
            i = (i - 1+256) % 256;
        }

        RC4_state->i = i;
        RC4_state->j = j;

    }


}