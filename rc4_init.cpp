/* Initialize the function */
// Argument 1 is a 256-length char array,  
// Parameter 2 is the key, whose contents can be arbitrarily defined:  
// Parameter 3 is the length of the key  
void rc4_init(unsigned char* s, unsigned char* key, unsigned long Len)
{
    int i = 0, j = 0;
    //char k[256]={0};
    unsigned char k[256] = { 0 };
    unsigned char tmp = 0;
    for (i = 0; i < 256; i++) {
        s[i] = i;
        k[i] = key[i % Len];
    }
    for (i = 0; i < 256; i++) {
        j = (j + s[i] + k[i]) % 256;
        tmp = s[i];
        s[i] = s[j];//exchange s[i]ºÍs[j]
        s[j] = tmp;
    }
}