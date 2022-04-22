#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include<string.h>
#include<stdio.h>
#include<windows.h>
#define MaxData 2000//The maximum length of a customized input string is 2000 bytes
#define SizeOfDataSegment 252//The data segment size is 252 bytes

typedef struct mes {
	int sc;
	unsigned char data[SizeOfDataSegment];
	unsigned char md5[16];
} Message, * pMessage;

typedef struct RC4 {
	unsigned char s[256];
	unsigned int i;
	unsigned int j;
}RC4_STATE,*pRC4_STATE;



// Encapsulates the MD5 function  
// Parameter 1:out, accepts the return pointer of MD5, parameter 2: data to be encrypted,;  Parameter 2: The length of data  
// Return value: none  
void MyMd5(unsigned char* md5, unsigned char* data, int len);


/* Initialize the function */
// Argument 1 is a 256-length char array,  
// Parameter 2 is the key, whose contents can be arbitrarily defined:  
// Parameter 3 is the length of the key  
void rc4_init(unsigned char* s, unsigned char* key, unsigned long Len);

//RC4 encryption
// 1 is the pointer to the scrambled s-box structure RC4 in the rc4_init function above;
// Parameter 2 is the data to be encrypted;
// Parameter 3 is the length of data.
void rc4_crypt(RC4_STATE* RC4_state, unsigned char* Data, unsigned long Len);

// the sender
// Parameter 1: key
// Parameter 2: memory pointer that stores the sent packets
// Return value: the number of segments
int RC4_Sender(char* key,unsigned char* MessageData);


// receiver
// Parameter 1: key
// Parameter 2: packet summary, packet array memory.
// Parameter 3: accepts the sequence, if the first digit is 0xFF, the default is 0, 1, 2, 3...
// Parameter 4: number of packets
void RC4_Receiver(char* key, Message Receive_Mes[],int* sequence, int num);


//(S*, I*, j*) = PRGA(S, I, j).The encrypted data of each packet is SizeOfDataSegment + 16, and the data segment + hash value
// Parameter 1: state of RC4, including (s, I,j)
// Parameter 2: receiver sc, sc &lt; Mes.sc
// Parameter 3, Mes_Sc in the packet
void PRGA(RC4_STATE* RC4_state, int sc, int Mes_Sc);


//RC4 state moving backwards£¬£¨s,i,j£© = IPRGA£¨S*,i*,j*£©£¬The encrypted data of each packet is SizeOfDataSegment+16, and the data segment + hash value
// Parameter 1: state of RC4, including (s, I,j)
// Parameter 2: receiver sc, sc &gt; Mes.sc
// Parameter 3, Mes_Sc in the packet
void IPRGA(RC4_STATE* RC4_state, int sc, int Mes_Sc);