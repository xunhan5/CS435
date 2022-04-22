#include"main.h"

int main()
{
	//char key[] = "ABCDEF0123456789ABC2021200386545";
	char key[256] = { 0 };
	printf("Please input the  security key: ");
	scanf("%s", &key);
	//Memory, which stores packets sent by the sender.
	//+200 When the maximum length of the character string is 2000, the total size of the sent packet is larger than 2000, and there are SC and MD5 data  
	unsigned char* MessageData = (unsigned char*)malloc(MaxData+200);	
	memset(MessageData, 0, MaxData+200);// initialize to 0
	int num=0;//Number of segments to be sent by the sender.
	num = RC4_Sender(key,MessageData);

	printf("\n\n");
	//If the first digit is 0xFF, it indicates the sequence 0, 1, 2, 3......
	//int sequence[10] = { 0xFF };
	int sequence[10] = { 0,1,2,3 };
	//int sequence[10] = { 1,0,3,2 };
	//int sequence[10] = { 3,2,1,0 };
	
	RC4_Receiver(key, (Message*)MessageData, sequence, num );
	

	//Release the memory for storing the packets sent by the sender.
	free(MessageData);
	return 0;
}