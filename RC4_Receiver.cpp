#include"main.h"

// receiver
// Parameter 1: key
// Parameter 2: packet summary, packet array memory.
// Parameter 3: accepts the sequence, if the first digit is 0xFF, the default is 0, 1, 2, 3...
// Parameter 4: number of packets
void RC4_Receiver(char* key, Message Receive_Mes[], int* sequence, int num) {
	printf("********************************************** receiver start *************************************************\n");
	int sc = 0;//Record the packet segment.
	RC4_STATE rc4_state = { 0 };//rc4 state
	
	//Stores decrypted string data
	unsigned char* DeReceiveMes = (unsigned char*)malloc(MaxData);
	memset(DeReceiveMes, 0, MaxData);//Initialize to zero

	if (sequence[0] == 0xff) {
		for (int i = 0; i < num; i++) {
			sequence[i] = i;
		}
	}
	printf("The sequence of the received packets is: ");
	for (int i = 0; i < num; i++) {
		printf("%d,", sequence[i]);
	}
	printf("\n\n");

	//Initialize the S-box of RC4  
	rc4_init(rc4_state.s, (unsigned char*)key, strlen(key));
	for (int i = 0; i < num; i++) {

		/******************************/
		//Receive pMes  
		Message Mes = { 0 };

		memcpy(&Mes, &Receive_Mes[sequence[i]], 272);
		/******************************/
		//Adjust the RC4 state status
		if (sc == Mes.sc) {
			;
		}
		else if (sc < Mes.sc) {
			PRGA(&rc4_state, sc, Mes.sc);
			sc = Mes.sc;
		}
		else if (sc > Mes.sc) {
			IPRGA(&rc4_state, sc, Mes.sc);
			sc = Mes.sc;
		}

		rc4_crypt(&rc4_state, (unsigned char*)&Mes.data, SizeOfDataSegment + 16);
		byte md5[16] = { 0 };

		MyMd5((unsigned char*)md5, (unsigned char*)&Mes, 4 + SizeOfDataSegment);

		if (memcmp(md5, Mes.md5, 16)) {
			printf("Sorry! Data is lost during transmission!\n");
			//break;
		}
		else {
			printf("Packet SC:%d Received successfully, MD5 hash validates correctly!\n",Mes.sc);
		}
		int len_data = strlen((char*)(Mes.data));
		// When a data segment is full, it is joined to a hash segment whose length is larger than SizeOfDataSegment  
		if (len_data > SizeOfDataSegment) {
			len_data = SizeOfDataSegment;
		}
		// If the data segment is not of SizeOfDataSegment, the end of the data segment will be filled (100000......) before transmission.  Binary, the last bit is going to be 0x80;  
		if (Mes.data[len_data - 1] == 0x80) {
			Mes.data[len_data - 1] = 0;
		}
		sc++;


		char str[300] = { 0 };
		memcpy(&str, Mes.data, SizeOfDataSegment);
		printf("The length of the packet segment is: %d\nThe content is: %s\n\n",strlen(str), str);

		memcpy(DeReceiveMes + sequence[i] * SizeOfDataSegment, str, strlen(str));//
	}

	printf("All string data received by the receiver is: %s\n", DeReceiveMes);

	// Release the memory used to store the decrypted string
	free(DeReceiveMes);

	printf("********************************************** receiver end *************************************************\n");

}