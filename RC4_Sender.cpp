#include"main.h"



// the sender
// Parameter 1: key
// Parameter 2: memory pointer that stores the sent packets
// Return value: the number of segments
int RC4_Sender(char* key, unsigned char* MessageData){

	printf("********************************************** sender start *************************************************\n");
	//char InputData[] = "1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222233333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333334444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555566666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666667777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888899999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999990000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";

	char* InputData = (char*)malloc(MaxData );// The default maximum input is 2000 bytes
	memset(MessageData, 0, MaxData + 200);// initialize to 0

	printf("Please enter incoming data for RC4 encryption: ");
	scanf("%s", InputData);
	printf("\n");

	int num = 0;// Number of segments
	int len_data = strlen(InputData);
	int sc = 0;// Record the packet segment.
	RC4_STATE rc4_state = { 0 };//rc4 state
	// Initialize the s-box of RC4
	rc4_init(rc4_state.s, (unsigned char*)key, strlen(key));
	for (int i = 0; i < len_data; i+=SizeOfDataSegment) {
		Message Mes = { 0 };
		Mes.sc = sc++;
		int len_data = strlen(InputData + i);
		if (len_data > SizeOfDataSegment) {
			len_data = SizeOfDataSegment;
		}
		memcpy(Mes.data, InputData + i, len_data);

		int len_Mes = strlen((char*)Mes.data);
		// Encapsulate the data segment. The size of the data segment is not enough to SizeOfDataSegment.  (binary)  
		if (len_Mes < SizeOfDataSegment) {
			Mes.data[len_Mes] = 0x80;
		}
		// Encapsulate the data segment and calculate the MD5 value
		MyMd5(Mes.md5, (unsigned char*)&Mes, 4+SizeOfDataSegment);//4+SizeOfDataSegment Indicates the length of the SC. 4 bytes +SizeOfDataSegment indicates the length of the data segment  
		
		// Data segments and MD5 values are encrypted
		rc4_crypt(&rc4_state, (unsigned char*)(Mes.data), SizeOfDataSegment+16);//SizeOfDataSegment+16 is the length of the data segment + the length of the hash value 	


		/******************************/
		//Send data packet Mes, (that is, write to the corresponding memory, the receiver then according to the receiving sequence out  
		memcpy(MessageData+num*sizeof(Message), &Mes, sizeof(Message));
		/******************************/

		num++;//Number of packet segments ++
	}

	

	len_data = strlen(InputData);
	rc4_init(rc4_state.s, (unsigned char*)key, strlen(key));
	rc4_crypt(&rc4_state, (unsigned char*)InputData, len_data);

	//Frees the memory used to store input.
	free(InputData);
	printf("All data is successfully sent!\n");

	printf("********************************************** sender end *************************************************\n");
	
	return num;

}
