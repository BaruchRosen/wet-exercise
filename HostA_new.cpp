// endHostA.cpp 

#include "pch.h"
#include <iostream>

using namespace std;


#include<stdio.h>
#include<winsock2.h>
#include<string.h>
#include <stdlib.h>
#include <time.h>

#pragma comment(lib,"ws2_32.lib") //Winsock Library
#pragma warning(disable : 4996)

#define SERVER "127.0.0.1"	//ip address of udp server
#define BUFLEN 1000	//Max length of buffer
#define PORT 67	//The port on which to listen for incoming data

int main(void)
{
	struct sockaddr_in si_other;
	int s,i,num2 ,num, slen = sizeof(si_other);
	char buf[BUFLEN], serv[] = { "127.0.0.1" }, port[] = { "67" }, IPB[] = { "127.0.0.1" };
	char messageAM[BUFLEN],messageMA[BUFLEN],messageTest[3*BUFLEN], *ret;
	WSADATA wsa;

	//Initialise winsock
	printf("\nInitialising Winsock...\n");
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("Failed. Error Code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	printf("Initialised.\n");

	//create socket
	if ((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == SOCKET_ERROR)
	{
		printf("socket() failed with error code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}

	//setup address structure
	memset((char *)&si_other, 0, sizeof(si_other));
	si_other.sin_family = AF_INET;
	si_other.sin_port = htons(PORT);
	si_other.sin_addr.S_un.S_addr = inet_addr(SERVER);

	printf("Connection to %s established\n", SERVER);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	
	//user input
	printf("\n\n Enter your message (dataAB): ");
	scanf("%[^\n]%*c", messageAM);

	//add ip of B
	strcat(messageAM, " $$$ ");
	strcat(messageAM, IPB);
	
	
	/*
	//triple code
	num2 = strlen(messageAM);
	for (i = 0; i < num2; i++)
	{
		messageTest[i * 3] = messageAM[i];
		messageTest[i * 3 + 1] = messageAM[i];
		messageTest[i * 3 + 2] = messageAM[i];
	}
	for (int i = 0; i < strlen(messageAM) * 3; i++)
	{
		printf("%c", messageTest[i]);
	}

	//decode
	*/



	//send data AB and B IP to M	
		if (sendto(s, messageAM, strlen(messageAM), 0, (struct sockaddr *) &si_other, slen) == SOCKET_ERROR)
		{
			printf("sendto() failed with error code : %d", WSAGetLastError());
			exit(EXIT_FAILURE);
		}
		
		//confirm sending
		ret = strtok(messageAM, "$$$");
		printf("\nMessage sent: %s ,",ret );
		printf(" \n data: dataAB\n");
		//////////////////////////  close socket
		

		//clear the buffer by filling null, it might have previously received data
		memset(buf, '\0', BUFLEN);
		
		/*
		//try to receive some data, this is a blocking call
		if (recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen) == SOCKET_ERROR)
		{
			printf("recvfrom() failed with error code : %d", WSAGetLastError());
			exit(EXIT_FAILURE);
		}
		printf("\n recived back:\n");

		puts(buf);
		printf("\n end of message\n");

		if (recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen) == SOCKET_ERROR)
		{
			printf("recvfrom() failed with error code : %d", WSAGetLastError());
			exit(EXIT_FAILURE);
		}
		printf("\n recived back:\n");

		puts(buf);
		printf("\n end of message\n");
	*/

		if (recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen) == SOCKET_ERROR)
		{
			printf("recvfrom() failed with error code : %d", WSAGetLastError());
			//exit(EXIT_FAILURE);
		}
		ret = strtok(buf, "$$$");
		printf("Message  received: %s \n" , ret);
		//puts(buf);
		printf(" \ndata:dataBA \n");
		//////////////////////////////////////////////////////////////



		scanf("%s", buf);
		
	closesocket(s);
	WSACleanup();


	return 0;
}
